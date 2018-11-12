//Check if mosquitto is running with the correct config file if you are the broker
//Check if mosquitto-clients is installed if you are a client
//https://github.com/eclipse/paho.mqtt.cpp
//Inspired by paho cpp samples

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Asynchronous mqtt publisher using SSL based on async_publish.cpp *
*            in the paho mqtt cpp library                          *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
	std::string CLIENT = CLIENT_NAME + std::to_string(CLIENT_ID) + "_pub";
	mqtt::async_client client(SERVER_ADDRESS,CLIENT);
	/*
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
*/

	int fd; /* File descriptor for the port */

	const char* port = "/dev/ttyACM0";
	char buffer[MAXLINE];
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
	// 8 bits, no parity, no stop bits
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;
	// No hardware flow control
	options.c_cflag &= ~CRTSCTS;
	// enable receiver, ignore status lines
	options.c_cflag |= CREAD | CLOCAL;
	// disable input/output flow control, disable restart chars
	options.c_iflag &= ~(IXON | IXOFF | IXANY);
	//disable canonical input, disable echo,
	//disable visually erase chars,
	//disable terminal-generated signals
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	//disable output processing
	options.c_oflag &= ~OPOST;
	// Set the new options for the port
	tcsetattr(fd, TCSANOW, &options);
	// Flush anything already in the serial buffer
	tcflush(fd, TCIFLUSH);


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


/*
			int retval;
			socklen_t len;

			retval = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
			buffer[retval] = '\0';

			std::cout << buffer << std::endl;
*/
			//json json_msg = m.deserialization(buffer);



			while(1) {

				// Flush anything already in the serial buffer
				memset(buffer,0,sizeof(buffer));
				int n = read(fd, buffer, sizeof(buffer));
				buffer[n] = 0;
				std::this_thread::sleep_for(std::chrono::milliseconds(50));

				std::cout << n << " bytes got read !" << std::endl;
				std::cout << buffer << std::endl;

				if (n < 0) {
					std::cout << "ERROR: Could not read serial port !" << std::endl;
				}
				else if (n > 0) {
					int z = 0;
					while(buffer[z] != '\0') {
						z++;
					}

					json json_msg = m.deserialization(buffer);

					std::string topic;
					mqtt::delivery_token_ptr pubtok;
					// Filter in order to publish on the correct topic depending on the receiver ID
					if (json_msg["receiver_id"] == 0) {
						topic = config["clients"]["operator"]["topic"].as<std::string>();
					}
					else if (100 <= json_msg["receiver_id"] && json_msg["receiver_id"] < 200) {
						topic = config["clients"]["niryo"]["topic"].as<std::string>();
					}
					else if (200 <= json_msg["receiver_id"] && json_msg["receiver_id"] < 300) {
						topic = config["clients"]["turtlebot"]["topic"].as<std::string>();
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
					pubtok = client.publish(topic, m.serialization(json_msg).c_str(), strlen(m.serialization(json_msg).c_str()), QOS, false);
					std::cout << "SENDING MESSAGE..." << std::endl;
					std::cout << "  ...with token: " << pubtok->get_message_id() << std::endl;
					std::cout << "  ...for message with " << pubtok->get_message()->get_payload().size() << " bytes" << std::endl;
					pubtok->wait_for(TIMEOUT);
					std::cout << "  ...OK\n" << std::endl;
				}


			}
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}
	close(fd);
	//close(sockfd);
  return 0;

}
