/* Inlude guards */
#ifndef IDOS_MSG_H
#define IDOS_MSG_H

#include "json.hpp"
#include <vector>
#include <string>

class message {

public:

  /* constructor */
  message();
  /* destructor */
  ~message() {}

  /* setters */
  void set_senderId(nlohmann::json &msg, int sender_id);
  void set_receiverdId(nlohmann::json &msg, int receiver_id);
  void set_function(nlohmann::json &msg, std::string function);
  void set_payload(nlohmann::json &msg, std::vector<std::string> payload);
  void set_message(nlohmann::json &msg, int sender_id, int receiver_id, std::string function, std::vector<std::string> payload);


  /* Clear the payload */
  void clear_payload(nlohmann::json &msg);
  /* Clear every field of the message */
  void clear_message(nlohmann::json &msg);
  /* Print every element of the payload */
  void print_payload(nlohmann::json msg);
  /* Print the message */
  void print_message(nlohmann::json msg);

};


#endif
