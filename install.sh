#!/bin/bash
#
# Need to be called only at the first build call of the project
# Don't forget to choose the entity type on which you are installing the gateway:
# "1" = turtlebot, "2" = ISENBOT, "3" = Niryo, "4" = control server, "5" =  hexapod
###############################################################

while read -e -n1 -r -p "Enter the entity type on which you are installing the gateway:
1 = turtlebot, 2 = ISENBOT, 3 = Niryo, 4 = control server, 5 =  hexapod 
Entity type : " && ! [[ "$REPLY" =~ ^[1-5]+$ ]]
do
	printf "\nEnter a number between 1 and 5 !"
done
	
mkdir build
cd build/
case $REPLY in
[1])
	cmake -DBUILD_DEPENDENCIES=TRUE -DTURTLEBOT_CONFIG=TRUE ..
	sudo make install
	cd ..
	sudo rm -r build/
	mkdir build
	cd build
	cmake ..
	make 
	;;
[2]) 
	cmake -DBUILD_DEPENDENCIES=TRUE -DISENBOT_CONFIG=TRUE ..
	sudo make install
	cd ..
	sudo rm -r build/
	mkdir build
	cd build
	cmake ..
	make 
	;;
[3]) 
	cmake -DBUILD_DEPENDENCIES=TRUE -DNIRYO_CONFIG=TRUE ..
	sudo make install
	cd ..
	sudo rm -r build/
	mkdir build
	cd build
	cmake ..
	make 
	;;
[4])
	cmake -DBUILD_DEPENDENCIES=TRUE -DSERVER_CONFIG=TRUE ..
	sudo make install
	cd ..
	sudo rm -r build/
	mkdir build
	cd build
	cmake ..
	make 
	;;
[5])
	cmake -DBUILD_DEPENDENCIES=TRUE -DHEXAPOD_CONFIG=TRUE ..
	sudo make install
	cd ..
	sudo rm -r build/
	mkdir build
	cd build
	cmake ..
	make 
	;;
esac
  
   


