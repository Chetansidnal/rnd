#include <iostream>
#include "/home/chetan/Dropbox/rnd/zmq_testcode/my_lib/daiglib.cpp"
using namespace std;

int main()
{
    daiglib d;
    string path = "config.json";
    string status;
    status = "nodeB ON";
    d.start_publishing(status,path);
    int i = 0;
    while (true)
    {
        status = "nodeB ON" + to_string(i);
        string code = "2211";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        d.update(code, status);
        i++;
    }
    return 0;
}