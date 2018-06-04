// #ifdef DIAGLIB_HPP
// #define DIAGLIB_HPP
// #endif
#include <iostream>
using namespace std;

class daiglib
{
   public: 
            daiglib();
            string check_dependent();

            void publish_status(string msg);
           // void registernode();
            string update(string gstatus);
    private:
            string getstatus(string gstatus);
            bool sub(const char *filter, const char *connection);
            void pub(string msg, const char *bindconn);
};

