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

	- build : Folder used by cmake to store all the executables and the Makefile.
		- async_sub : Executable file of the MQTT subscriber.
		- async_pub : Executable file of the MQTT publisher.

	- certs :
		- ca.crt : SSL/TLS authority certificate.
		- ca.key : SSL/TLS client key. Useful in order to create new client/server certificates.
		- ca.srl : késako
	
	- config :
		- message.json : Template of the message used by all the robots.
		- config.yaml : Configuration file for the gateway.

	- header :
		- json.hpp : Header of the json library. Has to be included in each cpp file requiring this library.
		- msg_manager.h : Header for the declaration of the custom class msg_manager. 
		  Allows manipulation of json messages such as serialization/deserialization.

	- libraries :
		- json : Library used for json messages.
		- paho.mqtt.cpp : Library used for MQTT protocol.
		- paho.mqtt.c : Library which is used as dependency for the mqtt.paho.cpp library.
		- yaml-cpp : Library included in order to be able to use yaml files.

	- deprecated :
		- Previous versions of the code, not usable anymore.

	- async_sub.cpp : MQTT subscriber using sockets or serial port in order to communicate with 
	  the main program of the robot. 
	  [MQTT topic --> Subscriber --> Socket/Serial port --> Main program]

	- async_pub.cpp : MQTT publisher using sockets or serial port in order to communicate with 
		the main program of the robot. 
	  [Main program --> Socket/Serial port --> Publisher --> MQTT topic]

	- msg_manager.cpp : Definition of the msg_manager class.

	- install.sh : Installation file. 
	  It has to be launched the first time you clone the repository in order to install all the dependencies 
	  and the binary files.

	- CMakeList.txt : Makefile called to build the project.

******************************************************************************************************************************************************************************

