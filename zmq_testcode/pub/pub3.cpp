#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
#include <thread>
#include <chrono>
#include <zmq.hpp>
using namespace std;

int main()
{
    int i = 0;
    const char *connection = "tcp://127.0.0.1:5555";
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUB);
    
    //socket.connect("tcp://127.0.0.1:5555");
    socket.bind("tcp://127.0.0.1:5555");
    cout << "check1 before bind" << endl;
    // zmq::socket_t socket = bindcon(connection);
    //socket.setsockopt(ZMQ_PUB, 1);
    //socket.connect("tcp://127.0.0.1:5555");
    cout << "check2 after bind" << endl;
    while (true)
    {

        // cout << "check3 inside while" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        // zmq::message_t request; 
        // socket.recv(&request);
        std::string message = "hello ";//std::string(static_cast<char *>(request.data()), request.size());
    if (message == "")
    {
      std::cout << "sub: is offline \n";
    }
    else {
         cout << "check4 after request" << endl;
         std::string jsonstr = "{\"nodes\":[{\"code\":\"0000\",\"message\":\"Any error/state message\",\"name\":\"Ground\",\"status\":true,\"timestamp\":\"12:45:12 12:12:12\"},{\"code\":\"0000\",\"message\":\"Any error/state message\",\"name\":\"Grass\",\"status\":true,\"timestamp\":\"12:45:12 12:12:12\"}]}";
        std::string text = jsonstr + std::to_string(i);
        std::cout << text << ":" << i;
        zmq::message_t message(text.size());
        
        memcpy(message.data(), text.c_str(), text.size());
            //
        socket.send(message);
        // std::string text2 = "welcome user:" + std::to_string(i);
        // zmq::message_t message2(text2.size());
        // memcpy(message2.data(), text2.c_str(), text2.size());
        // socket.send(message2);
        // socket.unbind("tcp://127.0.0.1:5555");
        i += 1;
    }
    }
}
