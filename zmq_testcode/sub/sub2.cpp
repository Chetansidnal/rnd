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
  //thread thread1(sub3);
 
  int i = 0;
  
  while (true)
  {
     zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_SUB);
  const char *filter = "{";
  const char *connection = "tcp://127.0.0.1:5555";
  // int linger = 10;
  //    socket.setsockopt(ZMQ_LINGER, &linger, sizeof (linger));
     socket.setsockopt(ZMQ_SUBSCRIBE,  filter, strlen(filter));
  socket.connect(connection);
    if (socket.connected())
    {
      cout << "online:" << i << endl;
    }
    else
    {
      cout << "offline:" << i << endl;
    }
     //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    // std::string text2 = "welcome user:" + std::to_string(i);
    //     zmq::message_t message2(text2.size());
    //     memcpy(message2.data(), text2.c_str(), text2.size());
    //     socket.send(message2);
/* code for polling start */
 cout << "poll check:---1" << i << endl;
   // zmq::pollitem_t items[] = { { *client, 0, ZMQ_POLLIN, 0 }
    zmq::pollitem_t items [] = { { socket, 0, ZMQ_POLLIN, 0 } };
    cout << "poll check:---2" << i << endl;
   zmq::poll (&items[0], 1, 1000);
   
    cout << "poll check:---3" << i << endl;
    zmq::message_t reply;
    cout << "poll check:---4" << i << endl;
    if (items [0].revents & ZMQ_POLLIN)
        socket.recv (&reply);
    cout << "poll check:---5" << i << endl;
  std::string replymessage = std::string(static_cast<char *>(reply.data()), reply.size());
if (replymessage!=""){
  cout <<"Yes recieved" <<replymessage <<endl;
}
else{  cout <<" Server Is DEAD" <<endl;}
    //  Close socket in any case, we're done with it now
   
  

/*code polling ends*/

    // zmq::message_t request;
    
    // socket.recv(&request  );
    // cout << "after request \n";
    // std::string message = std::string(static_cast<char *>(request.data()), request.size());
    // if (message == "")
    // {
    //   std::cout << "sub: is offline \n";
    // }
    // std::cout << "Message received!" << static_cast<int>(i) << std::endl;
    // std::cout << message << std::endl;
    i = i + 1;
    socket.disconnect("tcp://127.0.0.1:5555");
    socket.close();
  }

  return 0;
}

void sub3()
{
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_SUB);
  const char *filter = "nodeB ";
  socket.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));
  const char *connection = "tcp://127.0.0.1:5555";
  socket.connect(connection);
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