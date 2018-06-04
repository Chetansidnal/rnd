#include <iostream>
#include "/home/chetan/Dropbox/rnd/zmq_testcode/my_lib/daiglib.hpp"
using namespace std;
void main(){
daiglib d;
string status;
status = "nodeC ON";
d.publish_status(status);
}