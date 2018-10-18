/* Definition of all the methods used to manage idos messages */

#include "header/idos_message.h"
#include <iostream>
#include <string>

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

std::vector<std::string> &idos_message::get_payload() {
  return _payload;
}

/**********************************************setters**********************************************/
void idos_message::set_senderId(short int sender_id) {
  _sender_id = sender_id;
}

void idos_message::set_receiverdId(short int receiver_id) {
  _receiver_id = receiver_id;
}

void idos_message::set_length(int datatype_length) {
  int payload_length = 0;
  for (int i =0; i < _payload.size(); i++) {
    //sizeof ou .length() ?
    payload_length += _payload.at(i).length();
  }
  _length = datatype_length + payload_length;
}

void idos_message::set_datatype(std::string datatype) {
  _datatype = datatype;
}

void idos_message::set_payload(std::vector<std::string> payload) {
  _payload.resize(payload.size());
  _payload = std::move(payload);
}

/**********************************************constructor**********************************************/
idos_message::idos_message(short int sender_id, short int receiver_id, std::string datatype, std::vector<std::string> payload) {
  set_senderId(sender_id);
  set_receiverdId(receiver_id);
  set_datatype(datatype);
  set_payload(payload);
  set_length(datatype.length());
}

//Ajout d'une gestion des ids receiver et sender en fonction des âramètres du robot

int main(int argc, char **argv) {

  std::vector<std::string> payload {"0","1","2","3","4","5","6"};

  idos_message msg(500,201,"intg",payload);

  for (auto i = msg.get_payload().begin(); i != msg.get_payload().end(); i++) {
    std::cout << *i << ' ';
  }
  std::cout << "\n" << std::endl;

  std::vector<std::string> payload2 {"0","1","2","3","4","5","6","7"};

  msg.set_payload(payload2);

  for (auto i = msg.get_payload().begin(); i != msg.get_payload().end(); i++) {
    std::cout << *i << ' ';
  }
  std::cout << "\n" << std::endl;

  std::vector<std::string> payload3 {"0","1","2","3","4","5"};

  msg.set_payload(payload3);

  for (auto i = msg.get_payload().begin(); i != msg.get_payload().end(); i++) {
    std::cout << *i << ' ';
  }
  std::cout << "\n" << std::endl;

  //CREER UNE FONCTION CLEAR MESSAGE ??


  return 0;
}
