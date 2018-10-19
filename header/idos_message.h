/* Define the message's hape used by entities involving in the idos system */

//https://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c4027/C-Tutorial-A-Beginners-Guide-to-stdvector-Part-1.htm
#include <vector>
#include <string>

/* Inlude guards */
#ifndef IDOS_MSG_H
#define IDOS_MSG_H


class idos_message {

public:

  /* constructor */
  idos_message(short int sender_id, short int receiver_id, std::string datatype, std::vector<std::string> payload);

  /* destructor */
  ~idos_message() {}

  /* getters */
  short int get_senderId();
  short int get_receiverId();
  short int get_length();
  std::string get_datatype();
  std::vector<std::string> &get_payload();

  /* setters */
  void set_senderId(short int sender_id);
  void set_receiverdId(short int receiver_id);
  void set_length();
  void set_datatype(std::string datatype);
  void set_payload(std::vector<std::string> payload);

  /* Clear the payload */
  void clear_payload();

private:
  //short int = 2bytes
  short int _sender_id;
  short int _receiver_id;
  //length = _datatype length + _payload length
  short int _length;
  std::string _datatype;
  std::vector<std::string> _payload;
};


#endif
