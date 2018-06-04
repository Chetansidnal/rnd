#include <iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {


    Json::Value root;
    Json::Reader reader;
    const Json::Value defValue; //used for default reference
  //  cout <<"check-1"<<endl;
    ifstream ifile("config.json");
   // cout <<"check-2"<<endl;
    bool isJsonOK = (ifile != NULL && reader.parse(ifile, root));
  //  cout <<"check-3"<<endl;
    
    if (isJsonOK) {
        const Json::Value& nodes = root["nodes"];
        for (int i = 0; i < nodes.size(); i++){
            //string outstr = 
             cout << "    name: " << nodes[i]["name"].asString();
             cout << " connect: " << nodes[i]["connect"].asString();
             cout << endl;
        }
        // const Json::Value s = root.get("name", defValue);
        // cout <<"check-1";
        // cout << "In Nodes - : " << s.asString()<<endl;
        // if (s.isObject()) {

        //     Json::Value s2 = s.get("name", "");
        //     cout << "IN A2 - : " << s2.asString() << endl;
        //     cout << "IN A2 - : " << s.get("connect","").asString() << endl;
        // } else {
        //     cout << "no object type!!!" << endl;
        // }
    } else
        cout << "json is not correct format !!" << endl;

    return 1;
}

