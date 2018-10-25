//Check if mosquitto is running with the correct config file if you are the broker
//Check if mosquitto-clients is installed if you are a client
//https://github.com/eclipse/paho.mqtt.cpp
//Inspired by paho cpp samples

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Asynchronous mqtt publisher using SSL based on async_publish.cpp *
*            in the paho mqtt cpp library                          *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <sstream>
#include <fstream>
#include "header/json.hpp"
#include <cstdlib>
#include <string>
#include <chrono>
#include <cstring>
#include "mqtt/async_client.h"
#include "yaml-cpp/yaml.h"


using json = nlohmann::json;

//ATTENTION, LES CLIENTS DOIVENT AVOIR UN NOM+ID DIFFERENTS !!

YAML::Node config = YAML::LoadFile("../config/config.yaml");

const std::string SERVER_ADDRESS(config["server_address"].as<std::string>());
const std::string CLIENT_NAME(config["clients"]["niryo"]["name"].as<std::string>());
const int CLIENT_ID(config["ID_entity"].as<int>());
const std::string TOPIC(config["clients"]["server"]["topic"].as<std::string>());

const std::string LWT_PAYLOAD = config["clients"]["niryo"]["name"].as<std::string>() + std::to_string(CLIENT_ID) + " is now offline...";

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


class message_processing {
public:
	char* get_usr_msg() {
		char* msg = new char[1024];
		std::cout << "\nWrite your message:\n" << std::endl;
		std::cin >> msg;
		return msg;
	}
};


//inter process comm = named pipes ?? (fifo)
//http://www.raspberry-projects.com/pi/programming-in-c/pipes/named-pipes-fifos
//ou ultra simple sub/pub python
//ou sockets


int main(int argc, char **argv) {

	//char* payload;
	//message_processing mp;

	std::cout << "Initializing for server '" << SERVER_ADDRESS << "'..." << std::endl;
	std::string CLIENT = CLIENT_NAME + std::to_string(CLIENT_ID);
	mqtt::async_client client(SERVER_ADDRESS,CLIENT);

	//Set up SSL
	mqtt::ssl_options sslopts;
	sslopts.set_trust_store("../certs/ca.crt");

	mqtt::message willmsg(TOPIC, LWT_PAYLOAD, 1, true);
	mqtt::will_options will(willmsg);

	mqtt::connect_options connOpts;
	connOpts.set_user_name("IDOSdevice2");
	connOpts.set_password("TrYaGA1N");
	connOpts.set_will(will);
	connOpts.set_ssl(sslopts);

	callback cb;
	client.set_callback(cb);

	std::cout << "  Setup : OK..." << std::endl;

	try {
		std::cout << "Connecting to the MQTT server..." << std::flush;
		mqtt::token_ptr conntok = client.connect(connOpts);
		std::cout << "Waiting for the connection..." << std::endl;
		conntok->wait();
		std::cout << "  ...OK" << std::endl;


		/* JSON TEST */

		std::ifstream ifs("../config/message.json");
		if(!ifs.is_open()) {
	    std::cout << "ERROR: Could not open file" << std::endl;
	    return false;
	  }
		json j = json::parse(ifs);
		ifs.close();
		j["sender_id"] = "500";
	  j["receiver_id"] = "202";
	  j["data"]["function"] = "roadMap";

	  for (int i =0; i< j["data"]["payload"].size();i++) {
	    j["data"]["payload"][i] = "1";
	  }

	  std::cout << "" << std::endl;
	  std::cout << j << std::endl;
		std::cout << "" << std::endl;

		//char* msg = new char[1024];
		//msg = &j.dump()[0u];


		//payload = mp.get_usr_msg();
		mqtt::delivery_token_ptr pubtok;
		pubtok = client.publish(TOPIC, j.dump().c_str(), strlen(j.dump().c_str()), QOS, false);
		std::cout << "SENDING MESSAGE..." << std::endl;
		std::cout << "  ...with token: " << pubtok->get_message_id() << std::endl;
		std::cout << "  ...for message with " << pubtok->get_message()->get_payload().size() << " bytes" << std::endl;
		pubtok->wait_for(TIMEOUT);
		std::cout << "  ...OK" << std::endl;


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
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}




  return 0;

}
