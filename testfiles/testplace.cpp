#include <iostream>
#include <sstream>
#include <fstream>
#include "../header/json.hpp"

using json = nlohmann::json;

int main(int argc, char **argv) {

  std::ifstream ifs("../config/message.json", std::ifstream::binary);

  if(!ifs.is_open()) {
    std::cout << "ERROR: Could not open file" << std::endl;
    return false;
  }

  json j = json::parse(ifs);

  std::cout << j << std::endl;

  j["sender_id"] = "500";
  j["receiver_id"] = "202";
  j["datatype"] = "strg";
  j["data"]["function"] = "roadMap";

  int length = 0;
  for (int i =0; i< j["data"]["payload"].size();i++) {
    j["data"]["payload"][i] = "1";
    length += j["data"]["payload"][i].get<std::string>().length();
  }

  j["data"]["length"] = length + j["datatype"].get<std::string>().length();

  std::cout << "" << std::endl;
  std::cout << j << std::endl;

  //todo :reproduire la classe idos message avec le json

  return 0;
}
