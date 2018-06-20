#include "daiglib.hpp"
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include<iostream>
#include <fstream>
#include <chrono>
#include <zmq.hpp>
#include <thread>
#define REQUEST_TIMEOUT 2500
using namespace std;


daiglib::daiglib(){
};
bool self_status = true;
string self_message= "No Messages are updated by User";
string self_code = "XXXX";
Json::Value self_json;
string self_timestamp = "";
string self_name="";

void daiglib::update(string code, string msg) {
    /* setter function to set the status msg*/
    // current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);

   //cout << "The local date and time is: " << dt << endl;
        self_message =msg;
        self_code = code;
        self_timestamp = dt;

}
string daiglib::check_dependent()
{
    /*  This function will read from the json file and create object of sub , 
    checks weather all sub are responding. 
*/
    // read json file
    string status_msg;
    Json::Value root;
    Json::Reader reader;
    const Json::Value defValue; //used for default reference
    ifstream ifile("config.json");
    string connection;
    string name;
    bool isJsonOK = (ifile != NULL && reader.parse(ifile, root));
    if (isJsonOK)
    {
        const Json::Value &nodes = root["nodes"];
        int numberOfnodes = nodes.size();
        int i;
        for (i = 0; i < nodes.size(); i++)
        {
            // Extracting information fromt the config file
            cout << "    name: " << nodes[i]["name"].asString();
            cout << " connect: " << nodes[i]["connect"].asString();
            name = (nodes[i]["name"].asString());
            connection = nodes[i]["connect"].asString();
            //cout << "connection : " << connection << endl;
             cout << " ia m in check depednt "<<endl;
            Json::Value rcv_root = sub(name, connection);


            // Json::StyledWriter writer;
            // string recive_string =  writer.write(rcv_root);
            // cout<<"name"<<name<<"----"<<recive_string<<endl;
            // string self_jsonstr =  writer.write(self_json);
            // cout<<"self_jsonstr"<<"----"<<self_jsonstr<<endl;

            if (rcv_root.empty()){
                if (self_json.empty()){
                    cout <<" if slefjson empty"<<endl;
                    self_json["nodes"].append(buildErrorMsg(name));
                    cout <<" if slefjson after appending"<<endl;
                }
                if (!self_json.empty())
                    {  
                         cout <<" if slefjson NOT empty"<<endl;
                         bool writeFlag = true;
                        for(int k =0; k<self_json["nodes"].size(); k++){
                              
                            if (self_json["nodes"][k]["name"]==nodes[i]["name"]) {
                                cout <<" if slefjson NOT empty Matched updating"<<endl;
                                self_json["nodes"][k]["status"]=false;
                                writeFlag = false;    
                                

                            }
                            
                        }
                        if (writeFlag){self_json["nodes"].append(buildErrorMsg(name));}
                        
                    }
                // if (!self_json.empty() && self_json["nodes"].size()==i+1)
                // {
                //     self_json["nodes"][i]["status"]=false;
                // }
            }
            if (!rcv_root.empty()){
                cout << "rcv_root NOT empty"<<endl;
                 if (self_json.empty()){
                      cout << "self_json  empty"<<endl;
                     for(int j=0; j<rcv_root["nodes"].size(); j++)
                    self_json["nodes"].append(rcv_root["nodes"][j]);
                }
                if (!self_json.empty()){
                    cout << "self_json NOT empty"<<endl;
                    for(int j=0; j<rcv_root["nodes"].size(); j++){
                        bool writeFlag = true;
                        for(int k =0; k<self_json["nodes"].size(); k++){
                            if(self_json["nodes"][k]["name"]==rcv_root["nodes"][j]["name"]){
                                 cout << "updating self_sons"<<endl;
                               // self_json["nodes"][i]["name"]=rcv_root["nodes"][i]["name"];
                                self_json["nodes"][k]["status"]=rcv_root["nodes"][j]["status"];
                                self_json["nodes"][k]["code"]=rcv_root["nodes"][j]["code"];
                                self_json["nodes"][k]["message"]=rcv_root["nodes"][j]["message"];
                                self_json["nodes"][k]["timestamp"]=rcv_root["nodes"][j]["timestamp"];
                                writeFlag =false;
                            }
                           
                        }
                         if (writeFlag) {
                              cout << "appedning "<<endl;
                             self_json["nodes"].append(rcv_root["nodes"][j]);}
                    }
                    //self_json["nodes"].append(rcv_root["nodes"]);
                }
                // if (!self_json.empty() && self_json["nodes"].size()==i+1){
                //     self_json["nodes"][i]["name"]=rcv_root["nodes"][i]["name"];
                //     self_json["nodes"][i]["status"]=rcv_root["nodes"][i]["status"];
                //     self_json["nodes"][i]["code"]=rcv_root["nodes"][i]["code"];
                //     self_json["nodes"][i]["message"]=rcv_root["nodes"][i]["message"];
                //     self_json["nodes"][i]["timestamp"]=rcv_root["nodes"][i]["timestamp"];
                //    // self_json["nodes"][i]["status"]=rcv_root["nodes"][i]["status"];
                // }
            }
            // if (self_json["nodes"].size() < i){
            //     self_json["nodes"].append(buildOwnMsg(name));
            // }
            // if (self_json["nodes"].size() == i+1){
            //      self_json["nodes"][i+1]["name"]=root["pubs"][0]["name"];
            //     self_json["nodes"][i+1]["status"]=self_status;
            //     self_json["nodes"][i+1]["code"]=self_code;
            //     self_json["nodes"][i+1]["message"]=self_message;
            //     self_json["nodes"][i+1]["timestamp"]=self_timestamp;
            // }
            if (rcv_root.empty())
            {
                cout << " Name : " << nodes[i]["name"].asString() << "------Not Working" << endl;
                status_msg = nodes[i]["name"].asString() + "offline";
            }
            // cout << endl;
            // status_msg = nodes[i]["name"].asString() + "online";
        }
    }
    else
        cout << "json is not correct format !!" << endl;

    return status_msg;
}

void daiglib::publish_status( string msg){
//read json file
Json::Value root;
    Json::Reader reader;
    const Json::Value defValue; //used for default reference
     ifstream ifile("config.json");
     string connection;
     const char* name;
     bool isJsonOK = (ifile != NULL && reader.parse(ifile, root));
     if (isJsonOK) {
        const Json::Value& nodes = root["pub"];
        for (int i = 0; i < nodes.size(); i++){
             cout << "    name: " << nodes[i]["name"].asString();
             cout << " bind: " << nodes[i]["connect"].asString();
             self_name=nodes[i]["name"].asString();
             name=(nodes[i]["name"].asString()).c_str();
             connection=(nodes[i]["connect"].asString());
            
             cout <<" conection obtained" << connection<<endl;
        }
         if(self_json.empty()){
             cout << " ia m in pub json empty "<<endl;
            self_json["nodes"].append(buildOwnMsg(self_name));
        }
        cout << " ia m in pub jaon wmoty outy "<<endl;
            thread thread_pub(&daiglib::pub,this,msg,connection);
            //  thread thread_pub(&daiglib::check, this);
            //  thread t1 = move(thread_pub);
             cout << endl;

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
Json::Value daiglib::sub(string filter, string connection){
    /*
     connects with publisher and check for the messages returns true flase if alive or dead.
    */
    cout << " ia m in sub "<<endl;
    bool status=false;
    zmq::context_t context(1);
    cout << " ia m in sub after context "<<endl;
    zmq::socket_t socket(context, ZMQ_SUB);
    cout << " ia m in sub after scoket"<<endl;
    int linger = 0;
    string filter2 = "{";
    //socket.setsockopt(ZMQ_LINGER, &linger, sizeof (linger));
    socket.setsockopt(ZMQ_SUBSCRIBE, filter2.c_str(), strlen(filter2.c_str()));
    cout << " ia m in sub after scoket option "<<endl;
    const char*  conn = connection.c_str();
    socket.connect(connection.c_str());  //"tcp://127.0.0.1:5555"
    int i=0;
    //while(true) {
     zmq::pollitem_t items [] = { { socket, 0, ZMQ_POLLIN, 0 } };
     zmq::poll (&items[0], 1, REQUEST_TIMEOUT);
     zmq::message_t reply;
        // if (socket.connected()){
        //     cout <<"online:"<<i<<endl;
        //     }
        // else{cout <<"offline:"<<i<<endl;}
        zmq::message_t request;
         if (items [0].revents & ZMQ_POLLIN)        
        socket.recv(&request);  // ZMQ_NOBLOCK flag for not to wait.
        cout<<"after request \n";
        std::string message = std::string(static_cast<char*>(request.data()), request.size());
        if(message!=""){std::cout<<filter<<": is online \n";
            status=true;
            
            }

        std::cout << "Message received!"<<static_cast<int>(i)<< std::endl;
        std::cout << message << std::endl;
        i=i+1;
        socket.disconnect(connection.c_str());
        socket.close();
        context.close();
        Json::Value reciveroot;
        Json:: Reader reader;
        if(status){
            if (!reader.parse(message, reciveroot))
                {
                    std::cout << reader.getFormattedErrorMessages();
                    exit(1);
                }
        }
        
        // zmq_ctx_destroy(context);
    //}
    return reciveroot;
}

void daiglib::pub(string msg, string bindconn)
{
    // Todo
    //cout << " ia m in pub "<<endl;
    Json::StyledWriter writer;
    zmq::context_t context(1);
   // cout << " ia m in pub after context "<<endl;
    zmq::socket_t socket(context, ZMQ_PUB);
    //cout << " ia m in pub after scoket"<<endl;
    socket.bind(bindconn.c_str());
    //cout << " ia m in pub after bind "<<endl;
    int i = 0;
    while (true)
    {
       
       // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
       //cout << " ia m in pub "<<endl;
        self_json["nodes"][0]["name"]= self_name;
        self_json["nodes"][0]["status"]=self_status;
        self_json["nodes"][0]["code"]=self_code;
        self_json["nodes"][0]["message"]=self_message;
        self_json["nodes"][0]["timestamp"]=self_timestamp;

        string sendstring = writer.write(self_json);
        
        cout <<"self_status : "<<sendstring <<endl;
        //std::string text = self_status + std::to_string(i);
        //std::cout << text << ":" << i;
        zmq::message_t message(sendstring.size());
        memcpy(message.data(), sendstring.c_str(), sendstring.size());
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        socket.send(message);   

        i += 1;
    }
}

Json::Value daiglib::buildErrorMsg(string name)
{
    Json::Value defaut_root;
    Json::Reader reader;
    // current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);

   cout << "The local date and time is: " << dt << endl;

    //string nodeName = NAME;
    string jsonstr = "{";
    
    jsonstr = jsonstr + "\"name\":\""+name+"\",";
    jsonstr = jsonstr + "\"status\":\""+to_string(false)+"\", ";
    jsonstr = jsonstr + "\"code\":\"XXXX\",";
    jsonstr = jsonstr + "\"message\":\"Node is not Yet Started\",";
    jsonstr = jsonstr +"\"timestamp\":\""+dt+"\"}";

    if (!reader.parse(jsonstr, defaut_root))
    {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    }
  return defaut_root;
}

Json::Value daiglib::buildOwnMsg(string name)
{
    Json::Value cur_root;
    Json::Reader reader;
    // current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);

  // cout << "The local date and time is: " << dt << endl;

    //string nodeName = NAME;
   string jsonstr = "{";
    jsonstr = jsonstr + "\"name\":\""+name+"\",";
    jsonstr = jsonstr + "\"status\":\""+to_string(true)+"\", ";
    jsonstr = jsonstr + "\"code\":\""+ self_code+"\",";
    jsonstr = jsonstr + "\"message\":\""+self_message+"\",";
    jsonstr = jsonstr +"\"timestamp\":\""+dt+"\"}";

    if (!reader.parse(jsonstr, cur_root))
    {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    }
  return cur_root;
}