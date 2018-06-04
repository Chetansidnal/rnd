#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
#include <thread>
#include <chrono>
#include <zmq.hpp>

int main() {
zmq::context_t context(1);
zmq::socket_t socket(context, ZMQ_SUB);

socket.bind("tcp://localhost:5555");
const char* filter = "Hello";
socket.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));

zmq::message_t request;
while(true) {
socket.recv(&request);

std::string message = std::string(static_cast<char*>(request.data()), request.size());

std::cout << "Message received!" << std::endl;
std::cout << message << std::endl;
}
  return 0;
}