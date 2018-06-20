// #ifdef DIAGLIB_HPP
// #define DIAGLIB_HPP
// #endif
#include <iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>

using namespace std;

class daiglib
{
   public: 
            daiglib();
            string check_dependent();

            void publish_status(string msg);
           // void registernode();
            void update(string code, string msg);
            void check();
    private:
            string getstatus(string gstatus);
            Json::Value sub(string filter, string connection);
            void pub(string msg, string bindconn);
            Json::Value buildErrorMsg(string name);
            Json::Value buildOwnMsg(string name);
};

