This file is aiming to explain as much as possible the utility of each documents/files used for the IDOS communication project (Gateway).

All the documents are stored either in the "/etc/mosquitto/" folder or in the "gatewayMQTT/" folder previously cloned from https://github.com/ThomasDegallaix/gatewayMQTT.git


As a visual support to these explanations you can open the .PNG files in this folder which summarise the software architecture of the project.

*****************************************************************************************************************************************************************************

"/etc/mosquitto/" :

	- certs : 
		- server.crt : SSL/TLS server certificate.
		- server.key : SSL/TLS server key.
		- server.csr : SSL/TLS certificate request
	
	- conf.d :
		- mosquitto.conf : Configuration file of the broker. 
		  It contains all the variables in order to setup the use of the SSL/TLS
		  communication and of a username/password.
		  It also contains the port on which the broker is listening to.

	- ca_certificates : 
		- ca.crt : SSL/TLS authority certificate

	- userList.txt : It contains the encrypted usernames and passwords accepted by the broker.




******************************************************************************************************************************************************************************

"gatewayMQTT/" : 

	- certs :
		- ca.crt : SSL/TLS authority certificate.
		- ca.key : SSL/TLS client key. Useful in order to create new client/server certificates.
		- ca.srl : késako
	
	- config :
		- message.json : Template of the message used by all the robots.
		- config.yaml : Configuration file for the gateway.

	- examples :
		- async_pub_sample : Example of a simple publisher.
		- async_sub_sample : Example of a simple subscriber.

	- header :
		- json.hpp : Header of the json library. Has to be included in each cpp file requiring this library.
		- msg_manager.h : Header for the declaration of the custom class msg_manager. 
		  Allows manipulation of the json message such as serialization/deserialization.

	- libraries :
		- json : Library used for the json message.
		- paho.mqtt.cpp : Library used for the MQTT protocol.
		- paho.mqtt.c : Library which is used as dependency for the mqtt.paho.cpp library.
		- yaml-cpp : Library included in order to be able to use yaml files.

	- testfiles :
		- testplace.cpp : Unit test. Currently only testing the use of json messages.

	- deprecated :
		- gateway_mqtt.cpp : Test with inclusion of both subscriber and publisher in the same program.
		- idos_message.h : Header for the declaration of the custom class idos_message.
		  It was used to manage a class formatted message before switching to a json formatted message.
		- idos_message.cpp : Definition of the idos_message class.

	- async_sub.cpp : MQTT subscriber using sockets in order to communicate with the main program of the robot. 
	  [MQTT topic --> Subscriber --> Socket --> Main program]

	- async_pub.cpp : MQTT publisher using sockets in order to communicate with the main program of the robot. 
	  [Main program --> Socket --> Publisher --> MQTT topic]

	- async_sub_serial.cpp : MQTT subscriber using serial port in order to communicate with the main program of the robot. 
	  [MQTT topic --> Subscriber --> Serial port --> Main program]

	- async_pub_serial.cpp : MQTT publisher using serial port in order to communicate with the main program of the robot. 
	  [MQTT topic --> Subscriber --> Serial port --> Main program]
	
	- msg_manager.cpp : Definition of the msg_manager class.

	- install.sh : Installation file. 
	  It has to be launched the first time you clone the repository in order to install all the dependencies and the binary files.

	- CMakeList.txt : Makefile called to build the project.

******************************************************************************************************************************************************************************

