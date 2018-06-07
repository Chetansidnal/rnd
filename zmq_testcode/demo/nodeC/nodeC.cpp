#include <iostream>
#include "/home/chetan/Dropbox/rnd/zmq_testcode/my_lib/daiglib.cpp"
using namespace std;

int main(){
daiglib d;
string status;
status = "nodeC ON";
d.publish_status(status);
int i=0;

while(true) {
status= status + to_string(i);
 std::this_thread::sleep_for(std::chrono::milliseconds(1000));
d.update(status);
i++;
}
return 0;
}