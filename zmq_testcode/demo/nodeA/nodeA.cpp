#include <iostream>
#include "/home/chetan/Dropbox/rnd/zmq_testcode/my_lib/daiglib.cpp"
using namespace std;

void sample();
int main()
{

    daiglib d;
    string status;
    while (true)
    {
        //sample();
        status = d.check_dependent();

        cout << "I am NodeA:" << status << endl;
         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    cout << " Node Finished"<<endl;
    return 0;
}

void sample(){
    int i = 0;
  
//   while (true)
//   {
    zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_SUB);
  const char *filter = "nodeC ";
  const char *connection = "tcp://127.0.0.1:5556";
  socket.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));
  socket.connect(connection);
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
    socket.disconnect("tcp://127.0.0.1:5556");
    socket.close();
//   }
};