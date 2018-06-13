#include "daiglib.hpp"
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include<iostream>
#include <fstream>
#include <chrono>
#include <zmq.hpp>
#include <thread>
using namespace std;
daiglib::daiglib(){
};
string gstatus = "blank";

void daiglib::update(string msg) {
    /* setter function to set the status msg*/
    // cout <<"update:"<<msg <<endl;
        gstatus =msg;
} 
string daiglib::check_dependent(){
/*  This function will read from the json file and create object of sub , 
    checks weather all sub are responding. 
*/    
// read json file 
string status_msg;
 Json::Value root;
    Json::Reader reader;
    const Json::Value defValue; //used for default reference
     ifstream ifile("config.json");
    //  const char *connection;
      string connection;
      string name;
     bool isJsonOK = (ifile != NULL && reader.parse(ifile, root));
     if (isJsonOK) {
        const Json::Value& nodes = root["nodes"];
        for (int i = 0; i < nodes.size(); i++){
             cout << "    name: " << nodes[i]["name"].asString();
             cout << " connect: " << nodes[i]["connect"].asString();
             name=(nodes[i]["name"].asString());
             connection=nodes[i]["connect"].asString();
            //  connection=(nodes[i]["connect"].asString()).c_str();
                cout <<"connection : "<<connection<<endl;
             bool status = sub(name,connection);

             if (!status){ 
                 cout <<" Name : "<< nodes[i]["name"].asString()<<"------Not Working"<<endl;
                // cout <<" Name : "<< nodes[i]["connect"].asString()<<endl;
                status_msg = nodes[i]["name"].asString() + "offline";
             }
             cout << endl;
             // call subcribers
             status_msg = nodes[i]["name"].asString() + "online";

        }
    } else
        cout << "json is not correct format !!" << endl;

    return status_msg;
}

void daiglib::publish_status( string msg){
//read json file
Json::Value root;
    Json::Reader reader;
    const Json::Value defValue; //used for default reference
     ifstream ifile("config.json");
     const char* connection;
     const char* name;
     bool isJsonOK = (ifile != NULL && reader.parse(ifile, root));
     if (isJsonOK) {
        const Json::Value& nodes = root["pub"];
        for (int i = 0; i < nodes.size(); i++){
             cout << "    name: " << nodes[i]["name"].asString();
             cout << " bind: " << nodes[i]["connect"].asString();
             name=(nodes[i]["name"].asString()).c_str();
             connection=(nodes[i]["connect"].asString()).c_str();

             cout <<" conection obtained" << connection<<endl;
        }
            thread thread_pub(&daiglib::pub,this,msg,connection);
            //  thread thread_pub(&daiglib::check, this);
            //  thread t1 = move(thread_pub);
             cout << endl;
             // call subcribers
             thread_pub.detach();

        
    } else
        cout << "json is not correct format !!" << endl;
}
void daiglib::check(){
    while (true){
    cout <<"check "<<endl;
     cout <<"check 2"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
bool daiglib::sub(string filter, string connection){
    /*
     connects with publisher and check for the messages returns true flase if alive or dead.
    */
    cout <<"connection :"<< connection<<endl;
   cout << "i amin sub "<<endl;
    bool status=false;
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);
    // const char* filter = sfilter;
    cout << "before sub socket"<<endl;
    socket.setsockopt(ZMQ_SUBSCRIBE, filter.c_str(), strlen(filter.c_str()));
    cout << "after sub socket"<<endl;
    const char*  conn = connection.c_str();
    cout <<"connection :"<< connection<<endl;
    cout <<"conn :"<< conn<<endl;
    socket.connect(connection.c_str());  //"tcp://127.0.0.1:5555"
    cout << "after sub connection"<<endl;
    int i=0;
    //while(true) {

        if (socket.connected()){
            cout <<"online:"<<i<<endl;
            }
        else{cout <<"offline:"<<i<<endl;}
        zmq::message_t request;
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        socket.recv(&request);  // ZMQ_NOBLOCK flag for not to wait.
        cout<<"after request \n";
        std::string message = std::string(static_cast<char*>(request.data()), request.size());
        if(message!=""){std::cout<<"sub: is online \n";
            status=true;
            }
        std::cout << "Message received!"<<static_cast<int>(i)<< std::endl;
        std::cout << message << std::endl;
        i=i+1;
        socket.disconnect(connection.c_str());
        socket.close();
        context.close();
        // zmq_ctx_destroy(context);
    //}
    return status;
}

void daiglib::pub(string msg, const char* bindconn)
{
    // Todo
    cout << " Iam PUB "<<endl;
   // cout << "iamm pb 2"<<endl;
    zmq::context_t context(1);
    // cout << "after context"<<endl;
    zmq::socket_t socket(context, ZMQ_PUB);
    // cout << "after scoket"<<endl;
    socket.bind(bindconn);
    cout << " before while" <<endl;
    int i = 0;
    while (true)
    {
        cout << " in while"<< endl;
       // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        cout <<"gstatus : "<<gstatus <<endl;
        std::string text = gstatus + std::to_string(i);
        std::cout << text << ":" << i;
        zmq::message_t message(text.size());
        memcpy(message.data(), text.c_str(), text.size());
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        socket.send(message);   

        i += 1;
    }
}
