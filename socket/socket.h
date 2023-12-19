#pragma once

#include<cstring>
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;
namespace cc
{
    namespace socket_
    {
        class Socket
        {
            public:
                Socket();
                Socket(int socketfd);
                ~Socket();

                bool bind(const string &ip, int port);
                bool listen(int backlog);
                bool connect(const string & ip, int port);
                int accept();
                int send(const char * buf, int len);
                int recv(char * buf, int len);
                void close();

            
            //protected:
                std::string m_ip;
                int m_port;
                int m_sockfd;

        };
    }
} // namespace cc
