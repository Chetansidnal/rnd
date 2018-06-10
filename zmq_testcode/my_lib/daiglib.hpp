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
            void update(string gstatus);
            void check();
    private:
            string getstatus(string gstatus);
            bool sub(const char *filter, string connection);
            void pub(string msg, const char *bindconn);
};

