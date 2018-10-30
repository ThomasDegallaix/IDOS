/* Definition of all the methods used to manage idos messages */

#include "header/message.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using json = nlohmann::json;


/**********************************************setters**********************************************/
void message::set_senderId(json &msg, int sender_id) {
  msg["sender_id"] = sender_id;
}

void message::set_receiverdId(json &msg, int receiver_id) {
  msg["receiver_id"] = receiver_id;
}

void message::set_function(json &msg, std::string function) {
  msg["data"]["function"] = function;
}

void message::set_payload(json &msg, std::vector<std::string> payload) {
  clear_payload(msg);
  //work to do
  for (int i = 0; i < msg["data"]["payload"].size(); i++) {
    msg["data"]["payload"][i] = payload.at(i);
  }
}

void message::set_message(json &msg, int sender_id, int receiver_id, std::string function, std::vector<std::string> payload) {
  set_senderId(msg, sender_id);
  set_receiverdId(msg, receiver_id);
  set_function(msg, function);
  set_payload(msg, payload);
}

/**********************************************methods**********************************************/
void message::clear_message(json &msg) {
  set_senderId(msg, 0);
  set_receiverdId(msg, 0);
  set_function(msg, " ");
  clear_payload(msg);
}

void message::clear_payload(json &msg) {
  for(int i = 0; i < msg["data"]["payload"].size(); i++) {
    msg["data"]["payload"][i] = " ";
  }
}

void message::print_message(json msg) {
  std::cout << "******* INFOS ********" << std::endl;
  std::cout << "[SENDER_ID]: " << msg["sender_id"] << std::endl;
  std::cout << "[RECEIVER_ID]: " << msg["receiver_id"] << std::endl;
  std::cout << "[FUNCTION]: " << msg["data"]["function"] << std::endl;
  std::cout << "[PAYLOAD]: ";
  print_payload(msg);
  std::cout << "\n**********************" << std::endl;
}

void message::print_payload(json msg) {
  std::cout << "[ " ;
  for (auto i = msg["data"]["payload"].begin(); i != msg["data"]["payload"].end(); i++) {
    std::cout << *i << ' ';
  }
  std::cout << ']' ;
}

message::message() {};


int main(int argc, char **argv) {

  message msg;

  std::ifstream ifs("../config/message.json");
  if(!ifs.is_open()) {
    std::cout << "ERROR: Could not open file" << std::endl;
    return false;
  }
  json j = json::parse(ifs);
  ifs.close();

  std::vector<std::string> payload {"0","1","2","3","4","5","6", "7"};
  std::vector<std::string> payload2 {"a","b","c","d","e","f","g","h"};

  std::cout << "SETTING UP MESSAGE..." << std::endl;
  msg.set_message(j, 500, 202, "roadMap", payload);
  std::cout << "OK" << std::endl;
  msg.print_message(j);

  std::cout << "SETTING UP NEW PAYLOAD..." << std::endl;
  msg.set_payload(j, payload2);
  std::cout << "OK" << std::endl;
  msg.print_message(j);

  std::cout << "CLEARING MESSAGE..." << std::endl;
  msg.clear_message(j);
  std::cout << "OK" << std::endl;
  msg.print_message(j);


  return 0;
}
