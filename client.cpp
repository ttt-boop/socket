#include<iostream>
#include "socket/socket.h"
using namespace cc::socket_;

int main(){
    //1.创建socket
    Socket client;
    // int sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // if (sockfd < 0){
    //     printf("create socket error: errno=%d errmsg=%s\n", errno, strerror(errno));
    //     return 1;
    // }
    // else {
    //     printf("create socket success!\n");
    // }

    // 2.链接服务端
    std::string ip = "127.0.0.1";
    int port = 8080;
    client.connect(ip,port);
    // struct sockaddr_in sockaddr;
    // std::memset(&sockaddr, 0, sizeof(sockaddr));
    // sockaddr.sin_family = AF_INET;
    // sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    // sockaddr.sin_port = htons(port);
    // if (::connect(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0){
    //     printf("socket connect error: errno=%d errmsg=%s\n", errno, strerror(errno));
    //     return 1;
    // }
    // else {
    //     printf("socket connect success: ip = %s, prot = %d\n", ip.c_str(), port);
    // }

    //3.向服务端发送数据
    std::string data = "hello chchch";
    client.send(data.c_str(), data.size());
    // ::send(sockfd, data.c_str(), data.size(), 0);
    printf("send: %s\n", data.c_str());

    //4.接收服务端的数据
    char buf[1024] = {0};
    client.recv(buf, sizeof(buf));
    // ::recv(sockfd, buf, sizeof(buf), 0);
    printf("recv: %s\n", buf);

    //7.关闭socket
    client.close();
    // ::close(sockfd);

    return 0;
}