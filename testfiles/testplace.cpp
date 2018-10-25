#include <iostream>
#include <sstream>
#include <fstream>
#include "../header/json.hpp"

using json = nlohmann::json;

//DUMP JSON LIKE IN PYTHON
//https://nlohmann.github.io/json/classnlohmann_1_1basic__json_a5adea76fedba9898d404fef8598aa663.html

int main(int argc, char **argv) {

  std::ifstream ifs("../config/message.json");

  if(!ifs.is_open()) {
    std::cout << "ERROR: Could not open file" << std::endl;
    return false;
  }

  json j = json::parse(ifs);
  ifs.close();

  std::cout << j << std::endl;

  j["sender_id"] = "500";
  j["receiver_id"] = "202";
  j["data"]["function"] = "roadMap";

  for (int i =0; i< j["data"]["payload"].size();i++) {
    j["data"]["payload"][i] = "1";
  }

  std::cout << "" << std::endl;
  std::cout << j << std::endl;

  //todo :reproduire la classe idos message avec le json

  return 0;
}
