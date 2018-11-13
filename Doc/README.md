This file is aiming to explain as much as possible the utility of each documents/files used for the IDOS communication project (Gateway).

All the documents are stored either in the "/etc/mosquitto/" folder or in the "gatewayMQTT/" folder previously cloned from https://github.com/ThomasDegallaix/gatewayMQTT.git


As a visual support to these explanations you can open the .PNG files in this folder which summarise the software architecture of the project.

*****************************************************************************************************************************************************************************

"/etc/mosquitto/" :

	- certs : 
		- server.crt : SSL/TLS server certificate.
		- server.key : SSL/TLS server key.
	
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


