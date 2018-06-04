#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
#include <thread>
#include <chrono>
#include <zmq.hpp>
using namespace std;
// zmq::socket_t socket;
// void bindcon();

class SocketCreator
{
  zmq::socket_t *s;

public:
  SocketCreator()
  {
    zmq::context_t context(1);
    s = new zmq::socket_t(context, ZMQ_PUB);
    cout << "check constructor" << endl;
  }
  void bind()
  {
    cout << "inside bind" << endl;
    s->bind("tcp://127.0.0.1:5555");
    cout << "check bind" << endl;
  }
  void check()
  {
    cout << "check check" << endl;
  }
  void send(string msg)
  {
    zmq::message_t message(msg.size());
    memcpy(message.data(), msg.c_str(), msg.size());
    cout << "check msg" << endl;
    s->send(message);
  }
};

class testa {
  public:
  void display(){
    cout << "display "<<endl;
  }
};

int main() {
//   int i=0;
// const char* connection = "tcp://127.0.0.1:5555";
// // zmq::context_t context(1);
// // zmq::socket_t socket(context, ZMQ_PUB);
// // socket.bind("tcp://127.0.0.1:5555");
// cout << "check1 before bind"<<endl;
// // zmq::socket_t socket = bindcon(connection);
// //socket.setsockopt(ZMQ_PUB, 1);
// //socket.connect("tcp://127.0.0.1:5555");
// cout << "check2 after bind"<<endl;
// while(true) {
// std::string text = "Hello World:"+std::to_string(i);
// std::cout<<text<<":"<<i;
// zmq::message_t message(text.size());
// memcpy(message.data(), text.c_str(), text.size());
//   std::this_thread::sleep_for(std::chrono::milliseconds(2000));
// socket.send(message);
// std::string text2 = "welcome user:"+std::to_string(i);
// zmq::message_t message2(text2.size());
// memcpy(message2.data(), text2.c_str(), text2.size());
// socket.send(message2);
// // socket.unbind("tcp://127.0.0.1:5555");  
// i+=1;
// }
 
  testa ta;
  ta.display();
   SocketCreator sc;
  sc.check();
  sc.bind();
  while(true){
  sc.send("welcome user:");
  }
  return 0;
}

// 
// void bindcon(const char* connection)
// {
//   cout << "check-3 inside bind"<<endl;
//   zmq::context_t context(1);
//   socket(context, ZMQ_PUB);
   
//   socket.bind("tcp://127.0.0.1:5555");
//   cout << "check-4 inside bind"<<endl;
  
// }


// void pub_rcv();

// int main() {
// zmq::context_t context(1);
// zmq::socket_t socket(context, ZMQ_PUB);

// socket.connect("tcp://localhost:5555");
// int i=0;
// while(true) {

// std::string text = "PUB2 Iamalive :"+std::to_string(i);
// std::cout<<text<<":"<<i;
// zmq::message_t message(text.size());
// memcpy(message.data(), text.c_str(), text.size());
//   std::this_thread::sleep_for(std::chrono::milliseconds(2000));
// socket.send(message);
// i+=1;
// }
  
//   return 0;
// }

// void pub_rcv(){
//   zmq::context_t context(1);
//   zmq::socket_t socket(context, ZMQ_PUB);
//   zmq::message_t request;
//   socket.bind("tcp://localhost:5556");
//   const char* filter = "RES ";
// // int timeout = 0;
// socket.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));
//  int i=0;
//   while(true) {
// std::this_thread::sleep_for(std::chrono::milliseconds(1000));

// // cout<<"before request \n";
// // if (socket.connected()){
// //   cout <<"online:"<<i<<endl;
// // }
// // else{cout <<"offline:"<<i<<endl;}
// //socket.setsockopt(ZMQ_LINGER, &timeout, sizeof(timeout));
// socket.recv(&request);
// cout<<"after request \n";
// std::string message = std::string(static_cast<char*>(request.data()), request.size());
// if(message==""){std::cout<<"sub: is offline \n";}
// std::cout << "Message received!"<<static_cast<int>(i)<< std::endl;
// std::cout << message << std::endl;
// i=i+1;
// }
// }



