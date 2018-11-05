/* Definition of all the methods used to manage idos messages */

#include "header/msg_manager.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using json = nlohmann::json;


/**********************************************setters**********************************************/
void msg_manager::set_senderId(json &json_msg, int sender_id) {
  json_msg["sender_id"] = sender_id;
}

void msg_manager::set_receiverdId(json &json_msg, int receiver_id) {
  json_msg["receiver_id"] = receiver_id;
}

void msg_manager::set_function(json &json_msg, std::string function) {
  json_msg["data"]["function"] = function;
}

void msg_manager::set_payload(json &json_msg, std::vector<std::string> payload) {
  clear_payload(json_msg);
  for (int i = 0; i < json_msg["data"]["payload"].size(); i++) {
    json_msg["data"]["payload"][i] = payload.at(i);
  }
}

void msg_manager::set_message(json &json_msg, int sender_id, int receiver_id, std::string function, std::vector<std::string> payload) {
  clear_message(json_msg);
  set_senderId(json_msg, sender_id);
  set_receiverdId(json_msg, receiver_id);
  set_function(json_msg, function);
  set_payload(json_msg, payload);
}


/**********************************************message management**********************************************/
void msg_manager::clear_message(json &json_msg) {
  set_senderId(json_msg, 0);
  set_receiverdId(json_msg, 0);
  set_function(json_msg, " ");
  clear_payload(json_msg);
}

void msg_manager::clear_payload(json &json_msg) {
  for(int i = 0; i < json_msg["data"]["payload"].size(); i++) {
    json_msg["data"]["payload"][i] = " ";
  }
}

void msg_manager::print_message(json json_msg) {
  std::cout << "******* INFOS ********" << std::endl;
  std::cout << "[SENDER_ID]: " << json_msg["sender_id"] << std::endl;
  std::cout << "[RECEIVER_ID]: " << json_msg["receiver_id"] << std::endl;
  std::cout << "[FUNCTION]: " << json_msg["data"]["function"] << std::endl;
  std::cout << "[PAYLOAD]: ";
  print_payload(json_msg);
  std::cout << "\n**********************" << std::endl;
}

void msg_manager::print_payload(json json_msg) {
  std::cout << "[ " ;
  for (auto i = json_msg["data"]["payload"].begin(); i != json_msg["data"]["payload"].end(); i++) {
    std::cout << *i << ' ';
  }
  std::cout << ']' ;
}

std::string msg_manager::serialization(json json_msg) {
  std::string string_msg = json_msg.dump();
  return string_msg;
}

nlohmann::json msg_manager::deserialization(std::string string_msg) {
  auto json_msg = json::parse(string_msg);
  return json_msg;
}

msg_manager::msg_manager() {}



/**********************************************Tests**********************************************/
/*
int main(int argc, char **argv) {

  msg_manager msg;

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
*/
