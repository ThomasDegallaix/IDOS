Install STEP by STEP :

+ Get the repository :
+ 	git clone --recursive https://github.com/ThomasDegallaix/gatewayMQTT.git
+ 	cd gatewayMQTT
+ Install the gateway regarding the entity type (TYPE NUMBER : "1" = turtlebot, "2" = ISENBOT, "3" = Niryo, "4" = control server, "5" =  hexapod)
+ 	./install.sh 


If you want to build new files for the project, add exectuables in CMakeLists.txt.
Then jump into the build folder and type:
+ cmake ..
+ sudo make

For more informations about the software architecture of the project, go into the Doc folder.
