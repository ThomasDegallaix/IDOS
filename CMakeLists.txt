cmake_minimum_required(VERSION 2.8)
include(CheckCXXCompilerFlag)

project(gateway_mqtt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_INSTALL_PATH "/usr/local/lib/")
set(CMAKE_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries/")

##TRUE IF YOU ONLY WANT TO BUILD THE LIBRARIES, OTHERWISE IT WILL BUILD THE GATEWAY
set(BUILD_DEPENDENCIES FALSE CACHE BOOL "Build every needed libraries")
##PARAMETERS TO CONFIGURE THE GATEWAY REGARDING THE ROBOT TYPE
set(TURTLEBOT_CONFIG FALSE CACHE BOOL "Configure the gateway with Turtlebot's parameter")
set(ISENBOT_CONFIG FALSE CACHE BOOL "Configure the gateway with ISENBOT's parameter")
set(NIRYO_CONFIG FALSE CACHE BOOL "Configure the gateway with Niryo's parameter")
set(SERVER_CONFIG FALSE CACHE BOOL "Configure the gateway with Server's parameter")
set(HEXAPOD_CONFIG FALSE CACHE BOOL "Configure the gateway with Hexapod's parameter")

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

include_directories(header)

if(BUILD_DEPENDENCIES)

      ExternalProject_Add(paho.mqtt.c
                            SOURCE_DIR "${CMAKE_LIB_PATH}/paho.mqtt.c"
                            BUILD_COMMAND make
                            INSTALL_COMMAND make install
                            CMAKE_ARGS -DPAHO_WITH_SSL=TRUE -DPAHO_ENABLE_TESTING=FALSE)

      ExternalProject_Add(paho.mqtt.cpp
                            SOURCE_DIR "${CMAKE_LIB_PATH}/paho.mqtt.cpp"
                            BINARY_DIR "${CMAKE_LIB_PATH}/paho.mqtt.cpp/build"
                            DEPENDS paho.mqtt.c
                            BUILD_COMMAND make
                            INSTALL_COMMAND make install
                            CMAKE_ARGS -DPAHO_MQTT_C_PATH=home/thomas-ubuntu/Desktop/gatewayMQTT/libraries/paho.mqtt.c -DPAHO_WITH_SSL=TRUE ..)

      ExternalProject_Add(yaml-cpp
                            SOURCE_DIR "${CMAKE_LIB_PATH}/yaml-cpp"
                            BUILD_COMMAND make
                            INSTALL_COMMAND make install
                            CMAKE_ARGS -DBUILD_SHARED_LIBS=ON -DYAML_CPP_BUILD_TESTS=OFF)

      add_library(YAML_CPP_LIB SHARED "${CMAKE_LIB_PATH}/yaml-cpp")
      set_target_properties(YAML_CPP_LIB PROPERTIES LINKER_LANGUAGE CXX)
      install(TARGETS YAML_CPP_LIB DESTINATION ${CMAKE_INSTALL_PATH})

	if(TURTLEBOT_CONFIG)
		file(APPEND ${CMAKE_CURRENT_SOURCE_DIR}/config/config.yaml "entity_type: turtlebot")
	elseif(ISENBOT_CONFIG)
		file(APPEND ${CMAKE_CURRENT_SOURCE_DIR}/config/config.yaml "entity_type: isenbot")
	elseif(NIRYO_CONFIG)
		file(APPEND ${CMAKE_CURRENT_SOURCE_DIR}/config/config.yaml "entity_type: niryo")
	elseif(SERVER_CONFIG)
		file(APPEND ${CMAKE_CURRENT_SOURCE_DIR}/config/config.yaml "entity_type: server")
	elseif(HEXAPOD_CONFIG)
		file(APPEND ${CMAKE_CURRENT_SOURCE_DIR}/config/config.yaml "entity_type: hexapod")
	endif()

else()

      add_library(messageFunctions msg_manager.cpp)

      ## binary files
      add_executable(async_sub async_sub.cpp)
      add_executable(async_pub async_pub.cpp)



      ## Bring libraries
      find_library(PAHO_C_LIB NAMES libpaho-mqtt3a.so HINTS "${CMAKE_INSTALL_PATH}" REQUIRED)
      find_library(PAHO_CPP_LIB NAMES libpaho-mqttpp3.so HINTS "${CMAKE_INSTALL_PATH}" REQUIRED)
      find_library(YAML_CPP NAMES libyaml-cpp.so HINTS "${CMAKE_INSTALL_PATH}" REQUIRED)


      ## link binaries
      target_link_libraries(async_sub
          ${PAHO_C_LIB}
          ${PAHO_CPP_LIB}
          ${YAML_CPP}
          messageFunctions)
      target_link_libraries(async_pub
          ${PAHO_C_LIB}
          ${PAHO_CPP_LIB}
          ${YAML_CPP}
          messageFunctions)

endif()
