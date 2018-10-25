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

void idos_message::set_length() {
  int payload_length = 0;
  for (int i = 0; i < _payload.size(); i++) {
    payload_length += _payload.at(i).length();
  }
  _length = _datatype.length() + payload_length;
}

void idos_message::set_datatype(std::string datatype) {
  _datatype = datatype;
}

void idos_message::set_payload(std::vector<std::string> payload) {
  clear_payload();
  _payload.resize(payload.size());
  _payload = std::move(payload);
  set_length();
}

/**********************************************constructor**********************************************/
//SENDER_ID has to be a constant related to the robot on which the gateway is installed
//RECEIVER_ID  needs to be able to look into the robots database in order to know which one is online
idos_message::idos_message(short int sender_id, short int receiver_id, std::string datatype, std::vector<std::string> payload) {
  set_senderId(sender_id);
  set_receiverdId(receiver_id);
  set_datatype(datatype);
  set_payload(payload);
}

/**********************************************methods**********************************************/
void idos_message::clear_message() {
  set_senderId(0);
  set_receiverdId(0);
  set_datatype("");
  clear_payload();
}

void idos_message::clear_payload() {
  _payload.clear();
  set_length();
}

void idos_message::print_message() {
  std::cout << "******* INFOS ********" << std::endl;
  std::cout << "[SENDER_ID]: " << get_senderId() << std::endl;
  std::cout << "[RECEIVER_ID]: " << get_receiverId() << std::endl;
  std::cout << "[LENGTH]: " << get_length() << std::endl;
  std::cout << "[DATATYPE]: " << get_datatype() << std::endl;
  std::cout << "[PAYLOAD]: ";
  print_payload();
  std::cout << "\n**********************" << std::endl;
}

void idos_message::print_payload() {
  std::cout << '[' ;
  for (auto i = _payload.begin(); i != _payload.end(); i++) {
    std::cout << *i << ' ';
  }
  std::cout << ']' ;
}

template <typename T>
T idos_message::unpack() {
  //if selon DATATYPE
  //ITÉRATION DU VECTEUR
  //Transfert dans un vecteur/array de type selon DATATYPE
  //Retour de la nouvelle liste
  if (_datatype.compare("strg") == 0) {

  }
  else if (_datatype.compare("intg") == 0) {

  }
  else if (_datatype.compare("dble") == 0) {

  }
  //return
}

//Ajout d'une gestion des ids receiver et sender en fonction des paramètres du robot

int main(int argc, char **argv) {


  std::vector<std::string> payload {"0","1","2","3","4","5","6", "7"};
  std::vector<std::string> payload2 {"un","deux","trois","quatre","cinq"};

  std::cout << "SETTING UP MESSAGE..." << std::endl;
  idos_message msg(500,201,"intg",payload);
  std::cout << "OK" << std::endl;
  msg.print_message();

  std::cout << "SETTING UP NEW PAYLOAD..." << std::endl;
  msg.set_payload(payload2);
  std::cout << "OK" << std::endl;
  msg.print_message();

  std::cout << "CLEARING MESSAGE..." << std::endl;
  msg.clear_message();
  std::cout << "OK" << std::endl;
  msg.print_message();


  return 0;
}
