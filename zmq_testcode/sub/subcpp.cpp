#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
#include <thread>
#include <zmq.hpp>
using namespace std;
void sub1();

int main() {


zmq::context_t context(1);
zmq::socket_t socket(context, ZMQ_SUB);

std::cout << "before bind\n";

int i=0;
std::cout << "after bind";
const char* filter = "Hello ";
socket.bind("tcp://127.0.0.1:5555");
int timeout = 0;
socket.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));
socket.setsockopt(ZMQ_LINGER, &timeout, sizeof(timeout));

while(true) {



// thread thread1 (sub1);
zmq::message_t request;
std::this_thread::sleep_for(std::chrono::milliseconds(1000));

cout<<"before request \n";
if (socket.connected()){
  cout <<"online:"<<i<<endl;
}
else{cout <<"offline:"<<i<<endl;}
socket.setsockopt(ZMQ_LINGER, &timeout, sizeof(timeout));
socket.recv(&request);
cout<<"after request \n";
std::string message = std::string(static_cast<char*>(request.data()), request.size());
if(message==""){std::cout<<"sub: is offline \n";}
std::cout << "Message received!"<<static_cast<int>(i)<< std::endl;
std::cout << message << std::endl;
i=i+1;
//socket.unbind("tcp://127.0.0.1:5555");
}

  return 0;
}

void sub1(){
zmq::context_t context(1);
zmq::socket_t socket(context, ZMQ_SUB);



zmq::message_t request;
int i=0;



while(true) {
  std::cout << "before connet sub2\n";
socket.bind("tcp://*:5555");
//socket.connect("tcp://127.0.0.1:5556");
std::cout << "after connect \n";
const char* filter = "hello ";
//const char* filter = "PUB2 ";
//const void* timeout = (const void*)10000;
socket.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));
//socket.setsockopt(ZMQ_LINGER, timeout, size_t(timeout));
std::this_thread::sleep_for(std::chrono::milliseconds(1000));

cout<<"2before request \n";
if (socket.connected()){
  cout <<"online2:"<<i<<endl;
}
else{cout <<"offline2:"<<i<<endl;}
socket.recv(&request);
cout<<"after request \n";
std::string message = std::string(static_cast<char*>(request.data()), request.size());
if(message==""){std::cout<<"2sub: is offline \n";}
std::cout << "2Message received!"<<static_cast<int>(i)<< std::endl;
std::cout << message << std::endl;
i=i+1;
socket.unbind("tcp://*:5555");
}
}