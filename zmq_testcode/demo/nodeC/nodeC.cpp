#include <iostream>
#include "/home/chetan/Dropbox/rnd/zmq_testcode/my_lib/daiglib.cpp"
using namespace std;

int main()
{
    daiglib d;
    string status;
    status = "nodeC ON";
    cout << "Nodec " << endl;
    d.publish_status(status);
    int i = 0;
    cout << "main before while";
    while (true)
    {
        status = "nodeC ON" + to_string(i);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        cout << "main sleep :" <<to_string(i);
         d.update(status);
        i++;
    }
    return 0;
}