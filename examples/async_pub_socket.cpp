//Check if mosquitto is running with the correct config file if you are the broker
//Check if mosquitto-clients is installed if you are a client
//https://github.com/eclipse/paho.mqtt.cpp
//Inspired by paho cpp samples

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Asynchronous mqtt publisher using SSL based on async_publish.cpp *
*            in the paho mqtt cpp library                          *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//for sockets

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <thread>
#include <chrono>
#include "../header/msg_manager.h"
#include "../header/json.hpp"
#include "mqtt/async_client.h"
#include "yaml-cpp/yaml.h"

#define MAXLINE 1024

using json = nlohmann::json;
msg_manager m;

//ATTENTION, LES CLIENTS DOIVENT AVOIR UN NOM+ID DIFFERENTS !!
YAML::Node config = YAML::LoadFile("../config/config.yaml");

/* This variables set up the parameters of the mqtt communication */
const std::string ENTITY_TYPE (config["entity_type"].as<std::string>());
const std::string SERVER_ADDRESS(config["server_address"].as<std::string>());
const std::string CLIENT_NAME(config["clients"][ENTITY_TYPE]["name"].as<std::string>());
const int CLIENT_ID = config["ID_entity"].as<int>(); //A REQUETER A LA BDD
const int TYPE_ID = config["clients"][ENTITY_TYPE]["ID_type"].as<int>();
/* Quality Of Service level - 1 = message devlivered at least once - use of ACK */
const int QOS = config["QOS"].as<int>();
/* In case of problems, number of time the client is trying to reconnect */
const int N_RETRY_ATTEMPTS = config["N_RETRY_ATTEMPTS"].as<int>();
const auto TIMEOUT = std::chrono::seconds(config["TIMEOUT"].as<int>());


/* A callback class for use with the main MQTT client */
class callback : public virtual mqtt::callback, public virtual mqtt::iaction_listener {

	/* Number of connection retries before timeout */
  int nretry_;
  /* Declaration of the MQTT client */
  mqtt::async_client& cli_;
  /* Object which contains the connection options */
  mqtt::connect_options& connOpts_;

	/* Try to reconnect in case of failure with the same connection options */
	// Call the async_client::connect() method
	void reconnect() {
		std::this_thread::sleep_for(std::chrono::milliseconds(2500));
		try {
			cli_.connect(connOpts_, nullptr, *this);
		}
		catch (const mqtt::exception& exc) {
			std::cerr << "Error: " << exc.what() << std::endl;
			exit(1);
		}
	}

  void on_success(const mqtt::token& tok) override {
    std::cout << "Connected" << std::endl;
  }

	/* Call reconnect() in case of failure until we reach the max number of retry */
	void on_failure(const mqtt::token& tok) override {
		std::cout << "Connection failed" << std::endl;
		if (++nretry_ > N_RETRY_ATTEMPTS)
			exit(1);
		reconnect();
	}


	/* If connection is lost (cf on_connection_lost() in async_client.cpp) call reconnect() */
  void connection_lost(const std::string& cause) override {
		std::cout << "\nConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;

		std::cout << "Reconnecting..." << std::endl;
		nretry_ = 0;
		reconnect();
	}

	void delivery_complete(mqtt::delivery_token_ptr tok) override {
		std::cout << "\tDelivery complete for token: "
			<< (tok ? tok->get_message_id() : -1) << std::endl;
	}

public:
	callback(mqtt::async_client& cli, mqtt::connect_options& connOpts): nretry_(0), cli_(cli), connOpts_(connOpts) {}
};




int main(int argc, char **argv) {


	std::cout << "Initializing for server '" << SERVER_ADDRESS << "'..." << std::endl;
	std::string CLIENT = CLIENT_NAME + std::to_string(CLIENT_ID) + "_pub";
	mqtt::async_client client(SERVER_ADDRESS,CLIENT);
	int sockfd;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;

	std::cout << "Setting up UDP socket communication" << std::endl;
	// Creating socket file descriptor
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
      std::cout << "ERROR: Socket creation failed" << std::endl;
      exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));

  // Filling server information
  servaddr.sin_family    = AF_INET; // IPv4
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(config["socket_port_SG"].as<int>());

  // Bind the socket with the server address
  if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) {
      std::cout << "ERROR: Bind failed" << std::endl;
      exit(EXIT_FAILURE);
  }

	std::cout << "Setting up MQTT connection options" << std::endl;
	//Set up SSL
	mqtt::ssl_options sslopts;
	sslopts.set_trust_store("../certs/ca.crt");
	//Set up connection options
	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);
	connOpts.set_user_name("IDOSdevice2");
	connOpts.set_password("TrYaGA1N");
	connOpts.set_ssl(sslopts);

	std::cout << "Setting up MQTT callbacks" << std::endl;
	callback cb(client, connOpts);
	client.set_callback(cb);

	std::cout << "Setup: OK..." << std::endl;

	try {
		std::cout << "Connecting to the MQTT server..." << std::flush;
		mqtt::token_ptr conntok = client.connect(connOpts);
		std::cout << "Waiting for the connection..." << std::endl;
		conntok->wait();
		std::cout << "Connection: OK..." << std::endl;

		while(1) {

			int retval;
			socklen_t len;
      json json_msg;

			retval = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
			buffer[retval] = '\0';


      try {
        std::string topic;
        mqtt::delivery_token_ptr pubtok;

        json_msg = m.deserialization(buffer);

        //Set the sender's id correclty according to the entityt on which the gateway is installed
        json_msg["sender_id"] = CLIENT_ID + TYPE_ID;

  			// Filter in order to publish in the correct topic depending on the receiver ID
  			if (json_msg["receiver_id"] == 0) {
  				topic = config["clients"]["operator"]["topic"].as<std::string>();
  			}
  			else if (100 <= json_msg["receiver_id"] && json_msg["receiver_id"] < 200) {
  				topic = config["clients"]["niryo"]["topic"].as<std::string>();
  			}
  			else if (200 <= json_msg["receiver_id"] && json_msg["receiver_id"] < 300) {
  				topic = config["clients"]["turtlebot"]["topic"].as<std::string>();
  			}
  			else if (300 <= json_msg["receiver_id"] && json_msg["receiver_id"] < 400) {
  				topic = config["clients"]["isenbot"]["topic"].as<std::string>();
  			}
  			else if (400 <= json_msg["receiver_id"] && json_msg["receiver_id"] < 500) {
  				topic = config["clients"]["hexapod"]["topic"].as<std::string>();
  			}
  			else if (json_msg["receiver_id"] == 500) {
  				topic = config["clients"]["server"]["topic"].as<std::string>();
  			}
        else {
          std::cerr << "ERROR: Could not choose a right topic" << std::endl;
          return 1;
        }
        pubtok = client.publish(topic, m.serialization(json_msg).c_str(), strlen(m.serialization(json_msg).c_str()), QOS, false);
  			std::cout << "SENDING MESSAGE..." << std::endl;
  			std::cout << "  ...with token: " << pubtok->get_message_id() << std::endl;
  			std::cout << "  ...for message with " << pubtok->get_message()->get_payload().size() << " bytes" << std::endl;
  			//pubtok->wait_for(TIMEOUT);
  			std::cout << "  ...OK\n" << std::endl;
      }
      catch (json::parse_error &e) {
        std::cerr << e.what() << std::endl;
      }
		}
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}
	close(sockfd);

  return 0;

}
