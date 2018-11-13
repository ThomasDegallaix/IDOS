THIS FILE IS AIMING TO EXPLAIN AS MUCH AS POSSIBLE THE UTILITY OF EACH DOCUMENTS/FILES USED FOR THE IDOS COMMUNICATION PROJECT (GATEWAY)

ALL THE DOCUMENT ARE STORED EITHER IN THE "/ETC/MOSQUITTO/" FOLDER OR IN THE "GATEWAYMQTT/" FOLDER PREVIOUSLY CLONED FROM https://github.com/ThomasDegallaix/gatewayMQTT.git

AS A VISUAL SUPPORT TO THESE EXPLANATIONS YOU CAN OPEN THE .PNG FILES IN THIS FOLDER WHICH SUMMARISE THE SOFTWARE ARCHITECTURE OF THE PROJECT

*****************************************************************************************************************************************************************************

"/etc/mosquitto/" :

	- certs : 
		- server.crt : SSL/TLS server certificate.
		- server.key : SSL/TLS server key.
	
	- conf.d :
		- mosquitto.conf : Configuration file of the broker. 
		  It contains all the variables in order to setup the use of the SSL/TLS communication and of a username/password.
		  It also contains the port on which the broker is listening to.

	- ca_certificates : 
		- ca.crt : SSL/TLS authority certificate

	- userList.txt : It contains the encrypted usernames and passwords accepted by the broker.




******************************************************************************************************************************************************************************

"gatewayMQTT/" : 


