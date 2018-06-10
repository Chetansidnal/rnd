#include <iostream>
#include "/home/chetan/Dropbox/rnd/zmq_testcode/my_lib/daiglib.cpp"
using namespace std;

int main()
{

    daiglib d;
    string status;
    while (true)
    {
        status = d.check_dependent();

        cout << "I am NodeA:" << status << endl;
         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    cout << " Node Finished"<<endl;
    return 0;
}