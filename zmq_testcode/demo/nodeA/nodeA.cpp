#include <iostream>
#include "/home/chetan/Dropbox/rnd/zmq_testcode/my_lib/daiglib.cpp"
using namespace std;
void sample(daiglib&);
int main()
{

    daiglib d;
    string status;
    status = "nodeA ON";
    d.publish_status(status);
    int i=0;
    while (true)
    {
      //  status = d.check_dependent();
        status = "nodeA ON" + to_string(i);
        cout << "I am NodeA:" << status << endl;
         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
         cout << "main sleep :" <<to_string(i);
          //d.update(status);
          i++;
          sample(d);
    }

    cout << " Node Finished"<<endl;
    return 0;
}

void sample(daiglib& d ){
    cout<<"i am smaple"<<endl;
    string status = "nodeA ON SAMPLE";
     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    d.update(status);
}