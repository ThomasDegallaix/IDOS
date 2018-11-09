#!/bin/bash
#
# Need to be called only at the first build call of the project
#
###############################################################

mkdir build
cd build/
cmake -DBUILD_DEPENDENCIES=TRUE ..
sudo make install
cd ..
sudo rm -r build/
mkdir build
cd build
cmake ..
sudo make 


