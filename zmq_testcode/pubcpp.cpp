#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
#include <thread>
#include <zmq.hpp>
using namespace std;
int main() {
// zmq::context_t context(1);
// zmq::socket_t socket(context, ZMQ_PUB);

// socket.connect("tcp://localhost:5555");

// // while(true) {
// std::string text = "Hello World";
// zmq::message_t message(text.size());
// memcpy(message.data(), text.c_str(), text.size());
// socket.send(message);
std::cout<<"message sent ";
  return 0;
}