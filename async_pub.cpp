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
		char msg[50];
		std::cout << "\nWrite your message:\n" << std::endl;
		std::cin >> msg;
		std::cout << "flag0" << std::endl;
		return &(?????)msg;
	}

};


//inter process comm = named pipes ?? (fifo)
//http://www.raspberry-projects.com/pi/programming-in-c/pipes/named-pipes-fifos
//ou ultra simple sub/pub python


//Créer nouveau certificat ssl
//Créer un topic pour les willmsg ? => commencer à utiliser l'arborescence mqtt

int main(int argc, char **argv) {

	char* payload;
	message_processing mp;

	std::cout << "Initializing for server '" << SERVER_ADDRESS << "'..." << std::endl;
	mqtt::async_client client(SERVER_ADDRESS,CLIENT_ID);

	//Set up SSL
	mqtt::ssl_options sslopts;
	//Certificate has to be changed      ===>    http://www.steves-internet-guide.com/mosquitto-tls/    http://www.steves-internet-guide.com/ssl-certificates-explained/
	sslopts.set_trust_store("../certs/ca.crt");

	mqtt::message willmsg(TOPIC, LWT_PAYLOAD, 1, true);
	mqtt::will_options will(willmsg);

	mqtt::connect_options connOpts;
	connOpts.set_user_name("IDOSdevice1");
	connOpts.set_password("TrYaGA1N");
	connOpts.set_will(will);
	connOpts.set_ssl(sslopts);

	callback cb;
	client.set_callback(cb);

	std::cout << "  Setup : OK..." << std::endl;

	try {
		std::cout << "Connecting to the MQTT server..." << std::flush;
		mqtt::token_ptr conntok = client.connect(connOpts);
		//std::cout << "Waiting for the connection..." << std::endl;
		//conntok->wait();
		std::cout << "  ...OK" << std::endl;

/*
		std::cout << "\nConnecting..." << std::endl;
		mqtt::token_ptr conntok = client.connect(connopts);
		std::cout << "Waiting for the connection..." << std::endl;
		conntok->wait();
		std::cout << "  ...OK" << std::endl;
*/

		payload = mp.get_usr_msg();
		mqtt::delivery_token_ptr pubtok;
//BUG HERE
		std::cout << "flag1" << std::endl;
		std::cout << strlen(payload) << std::endl;
		std::cout << "flag2" << std::endl;
		pubtok = client.publish(TOPIC, payload, strlen(payload), QOS, false);
		std::cout << "\nSending message..." << std::endl;
		pubtok->wait_for(TIMEOUT);
		std::cout << "  ...OK" << std::endl;

/*		std::cout << "\nSending message..." << std::endl;
		mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC, PAYLOAD1);
		pubmsg->set_qos(QOS);
		client.publish(pubmsg)->wait_for(TIMEOUT);
		std::cout << "  ...OK" << std::endl;*/

/*		// Now try with itemized publish.

		std::cout << "\nSending next message..." << std::endl;
		mqtt::delivery_token_ptr pubtok;
		pubtok = client.publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2), QOS, false);
		pubtok->wait_for(TIMEOUT);
		std::cout << "  ...OK" << std::endl;

		// Disconnect

		std::cout << "\nDisconnecting..." << std::endl;
		conntok = client.disconnect();
		conntok->wait();
		std::cout << "  ...OK" << std::endl;*/

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
