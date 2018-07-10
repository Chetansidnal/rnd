#include <diagnose/diaglib.hpp>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <zmq.hpp>
#include <thread>
#define REQUEST_TIMEOUT 2500
using namespace std;

diaglib::diaglib(){};
bool self_status = true;
string self_message = "No Messages are updated by User";
string self_code = "0000";
Json::Value self_json;
string self_timestamp = "";
string self_name = "";

void diaglib::update(string code, string msg)
{
    /* setter function to set the status msg*/
    // current date/time based on current system
    time_t now = time(0);

    // convert now to string form
    char *dt = ctime(&now);

    //cout << "The local date and time is: " << dt << endl;
    self_message = msg;
    self_code = code;
    self_timestamp = dt;
}
string diaglib::check_dependent(string path)
{
    /*  This function will read from the json file and create object of sub , 
    checks weather all sub are responding. 
*/
    // read json file
    string status_msg;
    Json::Value root;
    Json::Reader reader;
    const Json::Value defValue; //used for default reference
    ifstream ifile(path);
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

            // Call for subscriber
            Json::Value rcv_root = sub(name, connection);

            if (rcv_root.empty())
            {
                if (self_json.empty())
                {
                
                    self_json["nodes"].append(buildErrorMsg(name));
                    
                }
                if (!self_json.empty())
                {
                   
                    bool writeFlag = true;
                    for (int k = 0; k < self_json["nodes"].size(); k++)
                    {

                        if (self_json["nodes"][k]["name"] == nodes[i]["name"])
                        {
                           
                            self_json["nodes"][k]["status"] = false;
                            writeFlag = false;
                        }
                    }
                    if (writeFlag)
                    {
                        self_json["nodes"].append(buildErrorMsg(name));
                    }
                }
            }
            if (!rcv_root.empty())
            {
               
                if (self_json.empty())
                {
                   
                    for (int j = 0; j < rcv_root["nodes"].size(); j++)
                        self_json["nodes"].append(rcv_root["nodes"][j]);
                }
                if (!self_json.empty())
                {
                    
                    for (int j = 0; j < rcv_root["nodes"].size(); j++)
                    {
                        bool writeFlag = true;
                        for (int k = 0; k < self_json["nodes"].size(); k++)
                        {
                            if (self_json["nodes"][k]["name"] == rcv_root["nodes"][j]["name"])
                            {
                               
                                self_json["nodes"][k]["status"] = rcv_root["nodes"][j]["status"];
                                self_json["nodes"][k]["code"] = rcv_root["nodes"][j]["code"];
                                self_json["nodes"][k]["message"] = rcv_root["nodes"][j]["message"];
                                self_json["nodes"][k]["timestamp"] = rcv_root["nodes"][j]["timestamp"];
                                writeFlag = false;
                            }
                        }
                        if (writeFlag)
                        {
                            
                            self_json["nodes"].append(rcv_root["nodes"][j]);
                        }
                    }
                }
            }
            if (rcv_root.empty())
            {
                cout << " Name : " << nodes[i]["name"].asString() << "------Not Working" << endl;
                status_msg = nodes[i]["name"].asString() + "offline";
            }
        }
    }
    else
        cout << "json is not correct format !!" << endl;

    return status_msg;
}

void diaglib::start_publishing(string msg, string path)
{
    //read json file
    Json::Value root;
    Json::Reader reader;
    const Json::Value defValue; //used for default reference
    ifstream ifile(path);
    string connection;
    const char *name;
    bool isJsonOK = (ifile != NULL && reader.parse(ifile, root));
    if (isJsonOK)
    {
        const Json::Value &nodes = root["pub"];
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << "    name: " << nodes[i]["name"].asString();
            cout << " bind: " << nodes[i]["connect"].asString();
            self_name = nodes[i]["name"].asString();
            name = (nodes[i]["name"].asString()).c_str();
            connection = (nodes[i]["connect"].asString());

            cout << " conection obtained" << connection << endl;
        }
        if (self_json.empty())
        {
            self_json["nodes"].append(buildOwnMsg(self_name));
        }
        thread thread_pub(&diaglib::pub, this, msg, connection);
        //  thread thread_pub(&diaglib::check, this);
        //  thread t1 = move(thread_pub);
        cout << endl;

        thread_pub.detach();
    }
    else
        cout << "json is not correct format !!" << endl;
}
void diaglib::check()
{
    while (true)
    {
        cout << "check " << endl;
        cout << "check 2" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
Json::Value diaglib::sub(string filter, string connection)
{
    /*
     connects with publisher and check for the messages returns true flase if alive or dead.
    */
    // cout << " ia m in sub " << endl;
    bool status = false;
    zmq::context_t context(1);
    // cout << " ia m in sub after context " << endl;
    zmq::socket_t socket(context, ZMQ_SUB);
    // cout << " ia m in sub after scoket" << endl;
    int linger = 0;
    string filter2 = "{";
    socket.setsockopt(ZMQ_SUBSCRIBE, filter2.c_str(), strlen(filter2.c_str()));
    // cout << " ia m in sub after scoket option " << endl;
    const char *conn = connection.c_str();
    socket.connect(connection.c_str()); //"tcp://127.0.0.1:5555"
    int i = 0;

    zmq::pollitem_t items[] = {{socket, 0, ZMQ_POLLIN, 0}};
    zmq::poll(&items[0], 1, REQUEST_TIMEOUT);
    zmq::message_t reply;
    zmq::message_t request;
    if (items[0].revents & ZMQ_POLLIN)
        socket.recv(&request); // ZMQ_NOBLOCK flag for not to wait.
    std::string message = std::string(static_cast<char *>(request.data()), request.size());
    if (message != "")
    {
        // std::cout << filter << ": is online \n";
        status = true;
    }

    std::cout << "Message received!" << static_cast<int>(i) << std::endl;
    std::cout << message << std::endl;
    i = i + 1;
    socket.disconnect(connection.c_str());
    socket.close();
    context.close();
    Json::Value reciveroot;
    Json::Reader reader;
    if (status)
    {
        if (!reader.parse(message, reciveroot))
        {
            std::cout << reader.getFormattedErrorMessages();
            exit(1);
        }
    }
    return reciveroot;
}

void diaglib::pub(string msg, string bindconn)
{

    Json::StyledWriter writer;
    zmq::context_t context(1);

    zmq::socket_t socket(context, ZMQ_PUB);
    socket.bind(bindconn.c_str());
    int i = 0;
    while (true)
    {

        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        self_json["nodes"][0]["name"] = self_name;
        self_json["nodes"][0]["status"] = self_status;
        self_json["nodes"][0]["code"] = self_code;
        self_json["nodes"][0]["message"] = self_message;
        self_json["nodes"][0]["timestamp"] = self_timestamp;

        string sendstring = writer.write(self_json);

        cout << "self_status : " << sendstring << endl;

        zmq::message_t message(sendstring.size());
        memcpy(message.data(), sendstring.c_str(), sendstring.size());
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        socket.send(message);

        i += 1;
        if (i > 1000)
        {
            i = 0;
        }
    }
}

Json::Value diaglib::buildErrorMsg(string name)
{
    Json::Value defaut_root;
    Json::Reader reader;
    // current date/time based on current system
    time_t now = time(0);

    // convert now to string form
    char *dt = ctime(&now);

    string jsonstr = "{";

    jsonstr = jsonstr + "\"name\":\"" + name + "\",";
    jsonstr = jsonstr + "\"status\":\"" + to_string(false) + "\", ";
    jsonstr = jsonstr + "\"code\":\"XXXX\",";
    jsonstr = jsonstr + "\"message\":\"Node is not Yet Started\",";
    jsonstr = jsonstr + "\"timestamp\":\"" + dt + "\"}";

    if (!reader.parse(jsonstr, defaut_root))
    {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    }
    return defaut_root;
}

Json::Value diaglib::buildOwnMsg(string name)
{
    Json::Value cur_root;
    Json::Reader reader;
    // current date/time based on current system
    time_t now = time(0);

    // convert now to string form
    char *dt = ctime(&now);

    string jsonstr = "{";
    jsonstr = jsonstr + "\"name\":\"" + name + "\",";
    jsonstr = jsonstr + "\"status\":\"" + to_string(true) + "\", ";
    jsonstr = jsonstr + "\"code\":\"" + self_code + "\",";
    jsonstr = jsonstr + "\"message\":\"" + self_message + "\",";
    jsonstr = jsonstr + "\"timestamp\":\"" + dt + "\"}";

    if (!reader.parse(jsonstr, cur_root))
    {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    }
    return cur_root;
}