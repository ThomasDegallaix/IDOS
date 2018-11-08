cmake_minimum_required(VERSION 2.8)
include(CheckCXXCompilerFlag)

#Faire en sorte d'installer et de build les librairies requises ?

project(gateway_mqtt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_PREFIX_PATH "/libraries/")

## find libraries
find_library(PAHO_C_LIB NAMES libpaho-mqtt3a.so HINTS "/usr/local/lib/" REQUIRED)
find_library(PAHO_CPP_LIB NAMES libpaho-mqttpp3.so HINTS "/usr/local/lib/" REQUIRED)
find_library(YAML_CPP_LIB NAMES libyaml-cpp.a HINTS "${CMAKE_PREFIX_PATH}" REQUIRED)

add_library(messageFunctions msg_manager.cpp)

## binary files
#add_executable(msg_manager msg_manager.cpp)
add_executable(async_sub async_sub.cpp)
add_executable(async_pub async_pub.cpp)
add_executable(async_sub_sample examples/async_sub_sample.cpp)
add_executable(async_pub_sample examples/async_pub_sample.cpp)
#add_executable(testfile testfiles/testplace.cpp)
add_executable(async_sub_serial async_sub_serial.cpp)
add_executable(async_pub_serial async_pub_serial.cpp)

## link binaries
target_link_libraries(async_sub
    ${PAHO_C_LIB}
    ${PAHO_CPP_LIB}
    ${YAML_CPP_LIB}
    messageFunctions)
target_link_libraries(async_pub
    ${PAHO_C_LIB}
    ${PAHO_CPP_LIB}
    ${YAML_CPP_LIB}
    messageFunctions)
target_link_libraries(async_sub_sample
    ${PAHO_C_LIB}
    ${PAHO_CPP_LIB}
    ${YAML_CPP_LIB}
    messageFunctions)
target_link_libraries(async_pub_sample
    ${PAHO_C_LIB}
    ${PAHO_CPP_LIB}
    ${YAML_CPP_LIB}
    messageFunctions)



target_link_libraries(async_sub_serial
    ${PAHO_C_LIB}
    ${PAHO_CPP_LIB}
    ${YAML_CPP_LIB}
    messageFunctions)
target_link_libraries(async_pub_serial
    ${PAHO_C_LIB}
    ${PAHO_CPP_LIB}
    ${YAML_CPP_LIB}
    messageFunctions)





