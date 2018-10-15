/* * * * * * * * * * * * * * * * * * * * * * * * * *
* Asynchronous mqtt subscriber/publisher using SSL *
*         using the paho mqtt cpp library          *
* * * * * * * * * * * * * * * * *    * * * * * * * */

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include "mqtt/async_client.h" //include almost the whole mqtt library
#include "yaml-cpp/yaml.h"
