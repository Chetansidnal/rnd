#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
#include <thread>
#include <chrono>
#include <zmq.hpp>
using namespace std;
void sub3();

int main()
{
  thread thread1(sub3);
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_SUB);
  const char *filter = "welcome ";
  socket.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));
 socket.connect("tcp://127.0.0.1:5555");
  int i = 0;
  while (true)
  {
     
    if (socket.connected())
    {
      cout << "online:" << i << endl;
    }
    else
    {
      cout << "offline:" << i << endl;
    }
    zmq::message_t request;
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    socket.recv(&request);
    cout << "after request \n";
    std::string message = std::string(static_cast<char *>(request.data()), request.size());
    if (message == "")
    {
      std::cout << "sub: is offline \n";
    }
    std::cout << "Message received!" << static_cast<int>(i) << std::endl;
    std::cout << message << std::endl;
    i = i + 1;
   // socket.disconnect("tcp://127.0.0.1:5555");
   // socket.close();
  }

  return 0;
}

void sub3()
{
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_SUB);
  const char *filter = "Hello ";
  socket.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));
  socket.connect("tcp://127.0.0.1:5555");
  int i = 0;
  while (true)
  {
    
    if (socket.connected())
    {
      cout << "online:" << i << endl;
    }
    else
    {
      cout << "offline:" << i << endl;
    }
    zmq::message_t request;
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    socket.recv(&request);
    cout << "after sub3 request \n";
    std::string message = std::string(static_cast<char *>(request.data()), request.size());
    if (message == "")
    {
      std::cout << "sub: is offline \n";
    }
    std::cout << "Message received by sub3!" << static_cast<int>(i) << std::endl;
    std::cout << message << std::endl;
    i = i + 1;
    // socket.disconnect("tcp://127.0.0.1:5555");
   // socket.close();
  }

  //   return 0;
}