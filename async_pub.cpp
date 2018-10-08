//Check if mosquitto is running if you are the broker
//Check if mosquitto-clients is installed if you are a client
//https://github.com/eclipse/paho.mqtt.cpp
//Inspired by paho cpp samples

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* Asynchronous mqtt publisher using SSL based on async_publish.cpp *
*            in the paho mqtt cpp library                          *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <cstring>
#include "mqtt/async_client.h"
#include "yaml-cpp/yaml.h"


YAML::Node config = YAML::LoadFile("../config/config.yaml");

const std::string SERVER_ADDRESS(config["server_address"].as<std::string>());
const std::string CLIENT_ID(config["client_id"].as<std::string>());
const std::string TOPIC(config["topic_server"].as<std::string>());

//Print by the other clients
const char* LWT_PAYLOAD = "The control server is now offline...";

const int QOS = config["QOS"].as<int>();

//DO WE NEED IT ?
const auto TIMEOUT = std::chrono::seconds(config["TIMEOUT"].as<int>());

/* A callback class for use with the main MQTT client */
class callback : public virtual mqtt::callback
{
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


//inter process comm = named pipes ?? (fifo)
//http://www.raspberry-projects.com/pi/programming-in-c/pipes/named-pipes-fifos
//ou ultra simple sub/pub python


//Créer nouveau certificat ssl
//Créer un topic pour les willmsg ? => commencer à utiliser l'arborescence mqtt

int main(int argc, char **argv) {



  return 0;
	
}
