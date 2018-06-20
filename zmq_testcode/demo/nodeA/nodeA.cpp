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
      status = d.check_dependent();
       string statusA = "nodeA ON" + to_string(i);
       string code = "4444";
        cout << "I am NodeA:" << status << endl;
         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
         cout << "main sleep :" <<to_string(i);
          d.update(code ,statusA);
          i++;
          sample(d);
    }

    cout << " Node Finished"<<endl;
    return 0;
}

void sample(daiglib& d ){
    cout<<"i am smaple"<<endl;
    string status = "nodeA ON SAMPLE";
    string code = "5555";
     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    d.update(code , status);
}