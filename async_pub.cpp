//Check if mosquitto is running with the correct config file if you are the broker
//Check if mosquitto-clients is installed if you are a client
//https://github.com/eclipse/paho.mqtt.cpp
//Inspired by paho cpp samples

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Asynchronous mqtt publisher using SSL based on async_publish.cpp *
*            in the paho mqtt cpp library                          *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <chrono>
#include <vector>
#include "header/msg_manager.h"
#include "header/json.hpp"
#include "mqtt/async_client.h"
#include "yaml-cpp/yaml.h"

#define MAXLINE 1024

using json = nlohmann::json;
msg_manager m;

//ATTENTION, LES CLIENTS DOIVENT AVOIR UN NOM+ID DIFFERENTS !!
YAML::Node config = YAML::LoadFile("../config/config.yaml");

const std::string SERVER_ADDRESS(config["server_address"].as<std::string>());
const std::string CLIENT_NAME(config["clients"]["niryo"]["name"].as<std::string>());
const int CLIENT_ID(config["ID_entity"].as<int>());
const std::string TOPIC(config["clients"]["server"]["topic"].as<std::string>());
const int QOS = config["QOS"].as<int>();
const auto TIMEOUT = std::chrono::seconds(config["TIMEOUT"].as<int>());




/* A callback class for use with the main MQTT client */
class callback : public virtual mqtt::callback {
public:
	void connection_lost(const std::string& cause) override {
		std::cout << "\nConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;
	}

	void delivery_complete(mqtt::delivery_token_ptr tok) override {
		std::cout << "\tDelivery complete for token: "
			<< (tok ? tok->get_message_id() : -1) << std::endl;
	}
};




int main(int argc, char **argv) {


	std::cout << "Initializing for server '" << SERVER_ADDRESS << "'..." << std::endl;
	std::string CLIENT = CLIENT_NAME + std::to_string(CLIENT_ID);
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
	connOpts.set_user_name("IDOSdevice2");
	connOpts.set_password("TrYaGA1N");
	connOpts.set_ssl(sslopts);

	std::cout << "Setting up MQTT callbacks" << std::endl;
	callback cb;
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

			retval = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
			buffer[retval] = '\0';

			std::cout << buffer << std::endl;

			json json_msg = m.deserialization(buffer);

			mqtt::delivery_token_ptr pubtok;
			pubtok = client.publish(TOPIC, m.serialization(json_msg).c_str(), strlen(m.serialization(json_msg).c_str()), QOS, false);
			std::cout << "SENDING MESSAGE..." << std::endl;
			std::cout << "  ...with token: " << pubtok->get_message_id() << std::endl;
			std::cout << "  ...for message with " << pubtok->get_message()->get_payload().size() << " bytes" << std::endl;
			pubtok->wait_for(TIMEOUT);
			std::cout << "  ...OK\n" << std::endl;
		}
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}
	close(sockfd);

  return 0;

}
