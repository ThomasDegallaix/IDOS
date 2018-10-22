/* * * * * * * * * * * * * * * * * * * * * * * * * *
* Asynchronous mqtt subscriber/publisher using SSL *
*         using the paho mqtt cpp library          *
* * * * * * * * * * * * * * * * *    * * * * * * * */

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include "mqtt/async_client.h" //include almost the whole mqtt library
#include "yaml-cpp/yaml.h"

/* TODO */
// test pub avec idos message
// configuration de la gateway selon le robot
// chargement des paramètres du robot
// communication inter process => MPI (python <=> C++)
// Callback lorsque l'appli principale veut envoyer un message via mqtt
// Callback lorsque l'appli principale doit recevoir un message via mqtt3
// Création des différents topics à utiliser
// soigner le code
// Repenser l'architecture du dossier (création d'un dossier pour les execs, dossier avec libraires, etc)
// documentation: Sources, fonctionnement, tuto d'utilisation, tuto d'installation


//LOAD DIFFERENT CONFIGURATIONS DIRECLTY AT THE BEGINNING OF MAIN
YAML::Node config = YAML::LoadFile("../config/config.yaml");

const std::string SERVER_ADDRESS(config["server_address"].as<std::string>());

//https://stackoverflow.com/questions/21031755/linux-c-how-to-programatically-get-mac-address-for-all-adapters-on-a-lan

//WORK TO DO HERE
const std::string CLIENT_NAME(config["clients"]["server"]["name"].as<std::string>());
const int CLIENT_ID(config["ID_entity"].as<int>());

//Need something more flexible
const std::string TOPIC(config["clients"]["server"]["topic"].as<std::string>());




//SOMETHING IS WRONG FOR THE MOMENT: SENT AT INITIALIZATION
//replace "server" by something generic
const std::string LWT_PAYLOAD = config["clients"]["server"]["name"].as<std::string>() + std::to_string(CLIENT_ID) + " is now offline...";





const auto TIMEOUT = std::chrono::seconds(config["TIMEOUT"].as<int>());
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
			<< "\tfor client " << CLIENT_NAME << CLIENT_ID
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

  /* Display informations when a message arrives */
  void message_arrived(mqtt::const_message_ptr msg) override {
		std::cout << "Message arrived" << std::endl;
		std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
		std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;

	}

  /* ACK */
  void delivery_complete(mqtt::delivery_token_ptr tok) override {
		std::cout << "\tDelivery complete for token: "
			<< (tok ? tok->get_message_id() : -1) << std::endl;
	}

public:
  callback(mqtt::async_client& cli, mqtt::connect_options& connOpts): nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription") {}

};


int main(int argc, char **argv) {

  std::cout << "Initializing for server '" << SERVER_ADDRESS << "'..." << std::endl;
  std::string CLIENT = CLIENT_NAME + std::to_string(CLIENT_ID);
  mqtt::async_client client(SERVER_ADDRESS, CLIENT);

  mqtt::ssl_options sslopts;
  sslopts.set_trust_store("../certs/ca.crt");

  mqtt::message willmsg(TOPIC, LWT_PAYLOAD, 1, true);
	mqtt::will_options will(willmsg);

  //set_keep_alive_interval = max time should pass between client and serv without communication
  //set_clean_session = Sets whether the server should remember state for the client across reconnects
  mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);
	connOpts.set_user_name("IDOSdevice1");
	connOpts.set_password("TrYaGA1N");
  connOpts.set_ssl(sslopts);
  connOpts.set_will(will);

	//Set an object as callbacks for the client
	callback cb(client, connOpts);
	client.set_callback(cb);

  std::cout << "Initialization: OK" << std::endl;

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
