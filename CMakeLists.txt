cmake_minimum_required(VERSION 2.8)
include(CheckCXXCompilerFlag)

#Faire en sorte d'installer et de build les librairies recquises ?

project(mqtt_gateway)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_PREFIX_PATH "/usr/local/lib/")

## find libraries
find_library(PAHO_C_LIB NAMES libpaho-mqtt3a.so HINTS "${CMAKE_PREFIX_PATH}" REQUIRED)
find_library(PAHO_CPP_LIB NAMES libpaho-mqttpp3.so HINTS "${CMAKE_PREFIX_PATH}" REQUIRED)
find_library(YAML_CPP_LIB NAMES libyaml-cpp.so HINTS "${CMAKE_PREFIX_PATH}" REQUIRED)

## binary files
add_executable(async_sub async_sub.cpp)

## link binaries
target_link_libraries(async_sub
    ${PAHO_C_LIB}
    ${PAHO_CPP_LIB}
    ${YAML_CPP_LIB})

