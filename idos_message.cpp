/* Definition of all the methods used to manage idos messages */

#include "header/idos_message.h"

/**********************************************getters**********************************************/
short int idos_message::get_senderId() {
  return _sender_id;
}

short int idos_message::get_receiverId() {
  return _receiver_id;
}

short int idos_message::get_length() {
  return _length;
}

std::string idos_message::get_datatype() {
  return _datatype;
}

std::vector<std::string> idos_message::get_payload() {
  return _payload;
}

/**********************************************setters**********************************************/
void idos_message::set_senderId(short int sender_id) {
  _sender_id = sender_id;
}

void idos_message::set_receiverdId(short int receiver_id) {
  _receiver_id = receiver_id;
}

void idos_message::set_length(int datatype_length, int payload_length) {
  _length = datatype_length + payload_length;
}
void idos_message::set_dataType(std::string datatype) {
  _datatype = datatype;
}

void idos_message::set_payload(std::vector<std::string> *payload) {
  _payload = payload;
}

/**********************************************constructor**********************************************/
idos_message::idos_message(short int sender_id, short int receiver_id, std::string datatype, std::vector<std::string> *payload) {
  set_senderId(sender_id);
  set_receiverdId(receiver_id);
  set_length(datatype.length(), //get length of payload); => iterate through every element of the vector and get length, then add
  set_datatype(datatype);
  //set payload ???
}
