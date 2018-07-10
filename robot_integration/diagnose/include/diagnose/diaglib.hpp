// #ifdef DIAGLIB_HPP
// #define DIAGLIB_HPP
// #endif
#include <iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>

using namespace std;

class diaglib
{
      public:
        diaglib();
        string check_dependent(string);
        /**
         * check_dependent for reading config file and subscribing the dependents,
         * incorporating dependent status in own status as json format.
         * Needs to call in side continuous loop.
         *
         * @param path
         *          string
         */

        void start_publishing(string msg, string path);
        /**
         * start_publishing for reading config file and starting publisher as server,
         * formatting status as json format.
         * Needs to call only once, then it will create its own thread starts the server.
         *
         * @param msg
         *              string 
         * @param path
         *              string
         */
        void update(string code, string msg);
        /**
         * update for updating the program status with code and message.  
         *
         * @param code
         *              string 
         * @param msg
         *              string
         */
        void check();
        /**
             * this is dummy method , not yet implmented
             */
      private:
        string getstatus(string gstatus);
        Json::Value sub(string filter, string connection);
        void pub(string msg, string bindconn);
        Json::Value buildErrorMsg(string name);
        Json::Value buildOwnMsg(string name);
};
