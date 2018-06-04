#include <iostream>
#include "daiglib.hpp"
using namespace std;
void main(){
daiglib d;
string status;
status = "nodeB ON";
d.publish_status(status);
}