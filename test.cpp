#include <iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<cstring>
#include<arpa/inet.h>
#include<unistd.h>

#include "util/Logger.h"

using namespace std;

using namespace cc::util;

int main(){

    Logger::instance()->open("./test.log");
    Logger::instance()->level(Logger::DEBUG);
    Logger::instance()->max(1024);
    //Logger::instance()->log(Logger::DEBUG, __FILE__, __LINE__, "name is %s, age is %d", "chch", 18);
    // debug("asjdlkasd");
    // error("error msg");
    // warn("warn msg");
    // info("info msg");
    // fatal("fatal msg");
    std::cout<<"over!"<<std::endl;
}