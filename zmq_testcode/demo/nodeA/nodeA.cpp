#include <iostream>
#include "/home/chetan/Dropbox/rnd/zmq_testcode/my_lib/daiglib.hpp"
using namespace std;

int main()
{

    daiglib d;
    string status;
    while (true)
    {
        status = d.check_dependent();
        cout << "I am NodeA:" << status << endl;
    }

    return 0;
}