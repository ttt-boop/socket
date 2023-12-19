#include <iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<cstring>
#include<arpa/inet.h>
#include<unistd.h>
#include<vector>
//#include "util/Logger.h"
#include "socket/socket.h"

using namespace cc::socket_;
using namespace std;


int main(){

    // Logger::instance()->open("./test.log");
    // Logger::instance()->level(Logger::DEBUG);
    // Logger::instance()->max(1024);
    //Logger::instance()->log(Logger::DEBUG, __FILE__, __LINE__, "name is %s, age is %d", "chch", 18);
    // debug("asjdlkasd");
    // error("error msg");
    // warn("warn msg");
    // info("info msg");
    // fatal("fatal msg");
    //std::cout<<"over!"<<std::endl;
    Socket s1;
    s1.bind("127.0.0.1",8081);
    s1.listen(5);
    int opt = 1;
        vector<int> opts = {SO_REUSEPORT, SO_REUSEADDR};
        for (unsigned int i = 0; i < opts.size(); i++)
        {
            if ((setsockopt(s1.m_sockfd, SOL_SOCKET, opts[i], (char *)&opt, sizeof(opt))) < 0)
            {
                cout << ": set listen sockopt Error" << endl;
                return false;
            }
        }

    //s1.close();

    Socket s2;
    for (unsigned int i = 0; i < opts.size(); i++)
        {
            if ((setsockopt(s2.m_sockfd, SOL_SOCKET, opts[i], (char *)&opt, sizeof(opt))) < 0)
            {
                cout << ": set listen sockopt Error" << endl;
                return false;
            }
        }
    s2.bind("127.0.0.1",8081);
    s2.listen(5);

    return 0;

}