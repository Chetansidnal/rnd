#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
#include <thread>
#include <chrono>
#include <zmq.hpp>

int main() {
zmq::context_t context(1);
zmq::socket_t socket(context, ZMQ_PUB);

socket.connect("tcp://127.0.0.1:5555");
int i=0;
while(true) {

std::string text = "Hello World:"+std::to_string(i);
std::cout<<text<<":"<<i;
zmq::message_t message(text.size());
memcpy(message.data(), text.c_str(), text.size());
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
socket.send(message);
i+=1;
}
  
  return 0;
}