/* Inlude guards */
#ifndef MSG_MANAGER_H
#define MSG_MANAGER_H

#include "json.hpp"
#include <vector>
#include <string>

class msg_manager {

public:

  /* constructor */
  msg_manager();
  /* destructor */
  ~msg_manager(){}

  /* setters */
  void set_senderId(nlohmann::json &json_msg, int sender_id);
  void set_receiverdId(nlohmann::json &json_msg, int receiver_id);
  void set_function(nlohmann::json &json_msg, std::string function);
  void set_payload(nlohmann::json &json_msg, std::vector<std::string> payload);
  void set_message(nlohmann::json &json_msg, int sender_id, int receiver_id, std::string function, std::vector<std::string> payload);


  /* Clear the payload */
  void clear_payload(nlohmann::json &json_msg);
  /* Clear every field of the message */
  void clear_message(nlohmann::json &json_msg);
  /* Print every element of the payload */
  void print_payload(nlohmann::json json_msg);
  /* Print the message */
  void print_message(nlohmann::json json_msg);
  /* Serialization */
  std::string serialization(nlohmann::json json_msg);
  /* Deserialization */
  nlohmann::json deserialization(std::string string_msg);
};


#endif
