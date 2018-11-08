//Check if mosquitto is running with the correct config file if you are the broker
//Check if mosquitto-clients is installed if you are a client
//https://github.com/eclipse/paho.mqtt.cpp
//Inspired by paho cpp samples

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Asynchronous mqtt subscriber based on async_subscribe.cpp  *
*            in the paho mqtt cpp library                    *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

/*
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
*/

#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include "header/msg_manager.h"
#include "header/json.hpp"
#include "mqtt/async_client.h"
#include "yaml-cpp/yaml.h"

using json = nlohmann::json;
msg_manager m;

//ATTENTION, LES CLIENTS DOIVENT AVOIR UN NOM+ID DIFFERENTS !!

YAML::Node config = YAML::LoadFile("../config/config.yaml");

/* This variables set up the parameters of the mqtt communication */
const std::string SERVER_ADDRESS(config["server_address"].as<std::string>());
const std::string CLIENT_NAME(config["clients"]["server"]["name"].as<std::string>());
const int CLIENT_ID(config["ID_entity"].as<int>());
const std::string TOPIC(config["clients"]["server"]["topic"].as<std::string>());
/* Quality Of Service level - 1 = message devlivered at least once - use of ACK */
const int QOS = config["QOS"].as<int>();
/* In case of problems, number of time the client is trying to reconnect */
const int N_RETRY_ATTEMPTS = config["N_RETRY_ATTEMPTS"].as<int>();



/*************************************************************************** Action listener ***************************************************************************/

/* Callbacks for success of failures of requested actions.
 Override some functions of the iaction_listener class */
class action_listener : public virtual mqtt::iaction_listener {

  std::string name_; //name the action (pub or sub for example)

  /* A token is an object which tracks the delivery of a message + informations about the message */

  void on_failure(const mqtt::token& tok) override {
    std::cout << name_ << " failure";
		if (tok.get_message_id() != 0) {
      std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
    }
		std::cout << std::endl;
  }

  void on_success(const mqtt::token& tok) override {
		std::cout << name_ << " success";
		if (tok.get_message_id() != 0) {
			std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
    }
		auto top = tok.get_topics();
		if (top && !top->empty()) {
			std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
    }
		std::cout << std::endl;
	}
public:
  /* Constructor */
  action_listener(const std::string& name) : name_(name) {}

};

/*************************************************************************** CallBacks ***************************************************************************/

/* Callback which receives messages and monitor the connection to the broker
 If the connection is lost, it will attempt to restore it */
 // how callbacks works = Callbacks are declared in the async_client.cpp with the function set_callback(s)
class callback : public virtual mqtt::callback, public virtual mqtt::iaction_listener {

  /* Number of connection retries before timeout */
  int nretry_;
  /* Declaration of the MQTT client */
  mqtt::async_client& cli_;
  /* Object which contains the connection options */
  mqtt::connect_options& connOpts_;
  /* A listener which monitors the actions and displays the result */
  action_listener subListener_;

  /**************************** Actions (Callbacks) ****************************/

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

  /* Call reconnect() in case of failure until we reach the max number of retry */
  void on_failure(const mqtt::token& tok) override {
		std::cout << "Connection failed" << std::endl;
		if (++nretry_ > N_RETRY_ATTEMPTS)
			exit(1);
		reconnect();
	}

  /* In case of successful connection, begin subscribing + give some informations about the connection*/
  void on_success(const mqtt::token& tok) override {
		std::cout << "\nConnection success" << std::endl;
		std::cout << "\nSubscribing to topic '" << TOPIC << "'\n"
			<< "\tfor client " << CLIENT_ID
			<< " using QoS" << QOS << "\n"
			<< "\nPress Q<Enter> to quit\n" << std::endl;

		cli_.subscribe(TOPIC, QOS, nullptr, subListener_);
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


  /* Deserialization + Sending to server/robot + Display informations when a message arrives */
  void message_arrived(mqtt::const_message_ptr msg) override {
		std::cout << "Message arrived" << std::endl;
		std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
		std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;



    //auto json_msg = m.deserialization(msg->to_string().c_str());

    //if (json_msg["receiver_id"] == config["clients"]["server"]["ID_type"].as<std::string>()) {
/*
      int sockfd;
      struct sockaddr_in servaddr;

      // Creating socket file descriptor
      if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
          std::cout << "ERROR: Socket creation failed" << std::endl;
          exit(EXIT_FAILURE);
      }

      memset(&servaddr, 0, sizeof(servaddr));

      // Filling server information
      const char* targetIp = "192.168.43.187";
      servaddr.sin_family = AF_INET;
      servaddr.sin_addr.s_addr = inet_addr(targetIp);
      servaddr.sin_port = htons(config["socket_port_GS"].as<int>());
      //inet_pton(AF_INET,"192.168.43.187", &servaddr.sin_addr.s_addr );

      std::cout << "Sending message to " << targetIp << " via UDP socket ..." << std::endl;
      // Sending message to control program
      int s;
      s = sendto(sockfd, msg->to_string().c_str(), strlen(msg->to_string().c_str()), 0, (const struct sockaddr *) &servaddr,  sizeof(servaddr));
      if (s < 0) {
        std::cout << "ERROR: Can't send UDP socket message" << std::endl;
        exit(EXIT_FAILURE);
      }
      else {
        std::cout << "DONE\n" << std::endl;
      }
      close(sockfd);
      */
      int fd; /* File descriptor for the port */

      const char* port = "/dev/ttyACM0";
      fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
      if (fd == -1) {
        perror("open_port: Unable to open /dev/ttyf1 - ");
      }
      else {
        fcntl(fd, F_SETFL, 0);
      }

      struct termios options;
      // Get the current options for the port
      tcgetattr(fd, &options);
      // Set the baud rates to 9600
      cfsetispeed(&options, B9600);
      cfsetospeed(&options, B9600);
      // Enable the receiver and et local mode
      options.c_cflag |= (CLOCAL | CREAD);
      options.c_cflag &= ~CSIZE; /* Mask the character size bits */
      options.c_cflag |= CS8;    /* Select 8 data bits */
      // Set the new options for the port
      tcsetattr(fd, TCSANOW, &options);

      int n = write(fd, msg->to_string().c_str(), strlen(msg->to_string().c_str()));
      if (n < 0) {
        std::cout << "ERROR: Could not write the " << n << " bytes on port " << port << std::endl;
      }
      close(fd);

    //}

    //m.clear_message(json_msg);

	}

  // Not useful here
  void delivery_complete(mqtt::delivery_token_ptr token) override {}

public:
  callback(mqtt::async_client& cli, mqtt::connect_options& connOpts): nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription") {}

};


int main(int argc, char **argv) {

  std::cout << "Initializing for server '" << SERVER_ADDRESS << "'..." << std::endl;
  std::string CLIENT = CLIENT_NAME + std::to_string(CLIENT_ID);
  mqtt::async_client client(SERVER_ADDRESS, CLIENT);

  std::cout << "Setting up MQTT connection options" << std::endl;
  //Set up SSL
  mqtt::ssl_options sslopts;
  sslopts.set_trust_store("../certs/ca.crt");
  //set_keep_alive_interval = max time should pass between client and serv without communication
  //set_clean_session = Sets whether the server should remember state for the client across reconnects
  //Set up connection options
  mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);
	connOpts.set_user_name("IDOSdevice1");
	connOpts.set_password("TrYaGA1N");
  connOpts.set_ssl(sslopts);

  std::cout << "Setting up MQTT callbacks" << std::endl;
	//Set an object as callbacks for the client
	callback cb(client, connOpts);
	client.set_callback(cb);

  std::cout << "Setup: OK..." << std::endl;

  // Start the connection.
	// When completed, the callback will subscribe to topic.

	try {
		std::cout << "Connecting to the MQTT server..." << std::flush;
		client.connect(connOpts, nullptr, cb);
	}
	catch (const mqtt::exception&) {
		std::cerr << "\nERROR: Unable to connect to MQTT server: '"
			<< SERVER_ADDRESS << "'" << std::endl;
		return 1;
	}



	// Just block till user tells us to quit.

	while (std::tolower(std::cin.get()) != 'q');

	// Disconnect

	try {
		std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
		client.disconnect()->wait();
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}

  return 0;
}
