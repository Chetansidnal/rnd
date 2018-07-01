#include <iostream>
#include "/home/chetan/Dropbox/rnd/zmq_testcode/my_lib/daiglib.cpp"
using namespace std;
void sample(daiglib&);
int main()
{
    string path = "config.json";
    daiglib d;
    string status;
    status = "nodeD ON";
    d.start_publishing(status,path);
    int i=0;
    while (true)
    {
      status = d.check_dependent(path);
       string statusA = "nodeD ON" + to_string(i);
       string code = "44DD";
        cout << "I am NodeD:" << status << endl;
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
    string status = "nodeD ON SAMPLE";
    string code = "5DDF";
     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    d.update(code , status);
}