#include <iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <fstream>
#include <ctime>

std::string text = "{\"nodes\":[{\"code\":\"0000\",\"message\":\"Any error/state message\",\"name\":\"Ground\",\"status\":true,\"timestamp\":\"12:45:12 12:12:12\"},{\"code\":\"0000\",\"message\":\"Any error/state message\",\"name\":\"Grass\",\"status\":true,\"timestamp\":\"12:45:12 12:12:12\"}]}";
std::string text2 = "{\"nodes\":[{\"code\":\"0001\",\"message\":\"Any error/state message\",\"name\":\"und\",\"status\":true,\"timestamp\":\"12:45:12 12:12:12\"},{\"code\":\"0000\",\"message\":\"Any error/state message\",\"name\":\"Grass\",\"status\":true,\"timestamp\":\"12:45:12 12:12:12\"}]}";

std::string addstr = "{\"code\":\"0000\",\"message\":\"Any error/state message\",\"name\":\"testnode\",\"status\":false,\"timestamp\":\"12:45:12 12:12:12\"}";
using namespace std;

string NAME = "testNode";
Json::Value update(bool status, string code, string message);
Json::Value check_message_format(string) ;

std::string getStringformat(string name ,bool status, string code, string message);

int main(int argc, char **argv)
{

    Json::Value root;
    Json::Value desearialize;
    Json::Value appe;
    Json::Value appe2;
    Json::Reader reader;
    Json::StyledWriter writer;
   
    const char *data;
    const Json::Value defValue; //used for default reference
                                //  cout <<"check-1"<<endl;
                                // ifstream ifile("config.json");
    ifstream ifile("status.json");
    // cout <<"check-2"<<endl;
    bool isJsonOK = true; //(ifile != NULL && reader.parse(ifile, root));
    if (!reader.parse(text, root))
    {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    }
    if (!reader.parse(addstr, appe))
    {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    }
    if (!reader.parse(text2, appe2))
    {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    }
    
   root["nodes"][0]["status"]=false;
   root["nodes"][1]["status"]=false;
    //  cout <<"check-3"<<endl;
    root["nodes"].append(appe);
    for (int i =0 ; i<appe2["nodes"].size(); i++ )
    root["nodes"].append(appe2["nodes"][i]);
    const std::string output1 = writer.write(root); // root.toStyledString();
    data = output1.c_str();
    //std::string message = std::string(static_cast<char *>(data , sizeof(data)));

    if (!reader.parse(output1, desearialize))
    {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    }
  
    const std::string output2 = root.toStyledString();
    cout << "ROOT-STring Single line ---" << output1 << endl;
    cout << "ROOT-STring multi line ---" << output1 << endl;
    if (isJsonOK)
    {
        cout << "deserializing------" << endl;

        const Json::Value &nodes = desearialize["nodes"];
    
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << "    name: " << nodes[i]["name"].asString() <<endl;
            cout << " status: " << nodes[i]["status"].asString() <<endl;
            cout << "    code: " << nodes[i]["code"].asString() <<endl;
            cout << " message: " << nodes[i]["message"].asString() <<endl;
            cout << " timestamp: " << nodes[i]["timestamp"].asString() <<endl;
        }

        /* to read config file enable this block of code

        const Json::Value& nodes = root["nodes"];
        for (int i = 0; i < nodes.size(); i++){
            //string outstr = 
             cout << "    name: " << nodes[i]["name"].asString();
             cout << " connect: " << nodes[i]["connect"].asString();
             cout << endl; 
             
        }
        */
    }
    else
        cout << "json is not correct format !!" << endl;

    return 1;
}

Json::Value update(bool status, string code, string message)
{
    Json::Value root;
    Json::Reader reader;
    // current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);

   cout << "The local date and time is: " << dt << endl;

    string nodeName = NAME;
    string jsonstr = "{\"code\":\""+code+"\",";
    jsonstr = jsonstr + "\"message\":\""+message+"\",";
    jsonstr = jsonstr + "\"name\":\""+nodeName+"\",";
    jsonstr = jsonstr + "\"status\":\""+to_string(status)+"\", ";

    jsonstr = jsonstr +"\"timestamp\":\""+dt+"\"}";

    if (!reader.parse(jsonstr, root))
    {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    }
  
}

Json::Value check_message_format(string stringTotest) {
    /* This Funtion checks if the required message format  */
    Json::Value root;
    Json::Reader reader;
    if (stringTotest.find("code"))
        if (stringTotest.find("message"))
            if (stringTotest.find("name"))
                if (stringTotest.find("status"))
                    if (stringTotest.find("timestamp"))
                        if (!reader.parse(stringTotest, root))
                        {
                            std::cout << reader.getFormattedErrorMessages();
                            exit(1);
                        }
    
    return root;
}

std::string getStringformat(string name ,bool status, string code, string message){
    
}