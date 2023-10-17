// #include<iostream>
// #include<sys/socket.h>
// #include<netinet/in.h>
// #include<cstring>
// #include<arpa/inet.h>
// #include<unistd.h>
#include "socket/socket.h"
using namespace cc::socket_;
int main(){

    // 1.创建socker
    // int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // if (sockfd < 0){
    //     printf("create socket error: errno=%d errmsg=%s\n", errno, strerror(errno));
    //     return 1;
    // }
    // else {
    //     printf("create socket success!\n");
    // }

    Socket server;



    // 2.绑定socket
    std::string ip = "127.0.0.1";
    int port = 8080;

    server.bind(ip, port);


    // struct sockaddr_in sockaddr;
    // std::memset(&sockaddr, 0, sizeof(sockaddr));
    // sockaddr.sin_family = AF_INET;
    // sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    // sockaddr.sin_port = htons(port);
    // if (::bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0){
    //     printf("socket bind error: errno=%d errmsg=%s\n", errno, strerror(errno));
    //     return 1;
    // }
    // else {
    //     printf("socket bind success: ip = %s, prot = %d\n", ip.c_str(), port);
    // }

    //3.监听socket
    server.listen(1024);
    // if (::listen(sockfd, 1024) < 0){
    //     printf("socket listen error: errno=%d errmsg=%s\n", errno, strerror(errno));
    //     return 1;
    // }
    // else {
    //     printf("socket listening ...\n");
    // }


    while (true){
        // 4.接受客户端连接
        int connfd = server.accept();
        if (connfd < 0)
        {
            return 1;
        }
        Socket client(connfd);
        // int connfd = ::accept(sockfd, nullptr, nullptr);
        // //break;
        // if (connfd < 0){
        //     printf ("socket accept error: errno=%d errmsg=%s\n", errno, strerror(errno));
        //     return 1;
        // }
        
        char buf[1024] = {0};

        //5.接收客户端的数据
        size_t len = client.recv(buf, sizeof(buf));
        // size_t len = ::recv(connfd, buf, sizeof(buf), 0);
        printf("recv: connfd=%d msg=%s\n", connfd, buf);

        //6.向客户端发送数据
        client.send(buf, len);
        //::send(connfd, buf, len, 0);

        break;

    }
    //7.关闭socket
    server.close();

    return 0;
}