/* Inlude guards */
#ifndef IDOS_MSG_H
#define IDOS_MSG_H

#include "json.hpp"
#include <vector>
#include <string>

using json = nlohmann::json;

class message {

public:

  /* constructor */
  message();
  /* destructor */
  ~message() {}

  /* setters */
  void set_senderId(json *msg);
  void set_receiverdId(json *msg, int receiver_id);
  void set_function(json *msg, std::string function);
  void set_payload(json *msg, std::vector<std::string> payload);
  void set_message(json *msg, std::string receiver_id,, std::string function std::vector<std::string> payload) {


  /* Clear the payload */
  void clear_payload(json *msg);
  /* Clear every field of the message */
  void clear_message(json *msg);
  /* Print every element of the payload */
  void print_payload(json *msg);
  /* Print the message */
  void print_message(json *msg);

};


#endif
