#include "socket.h"
#include "../util/Logger.h"
using namespace cc::util;
using namespace cc::socket_;

Socket::Socket() : m_ip(""), m_port(0), m_sockfd(0)
{
    
    // 1.创建socker
    m_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sockfd < 0){
        printf("create socket error: errno=%d errmsg=%s\n", errno, strerror(errno));
    }
    printf("create socket success!\n");
}

Socket::Socket(int socketfd) : m_ip(""), m_port(0), m_sockfd(socketfd)
{

}

Socket::~Socket()
{
    close();
}

bool Socket::bind(const string &ip, int port)
{
    struct sockaddr_in sockaddr;
    std::memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    if (ip.empty()){
        sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else{
        sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    }
    sockaddr.sin_port = htons(port);
    if (::bind(m_sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0){
        printf("socket bind error: errno=%d errmsg=%s\n", errno, strerror(errno));
        return false;
    }
    m_ip = ip;
    m_port = port;
    printf("socket bind success: ip = %s, prot = %d\n", ip.c_str(), port);
    return true;
}

bool Socket::listen(int backlog)
{
    if (::listen(m_sockfd, backlog) < 0){
        printf("socket listen error: errno=%d errmsg=%s\n", errno, strerror(errno));
        return false;
    }
    printf("socket listening ...\n");
    return true;
}

bool Socket::connect(const string & ip, int port)
{
    struct sockaddr_in sockaddr;
    std::memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_port = htons(port);
    if (::connect(m_sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0){
        printf("socket connect error: errno=%d errmsg=%s\n", errno, strerror(errno));
        return false;
    }
    m_ip = ip;
    m_port = port;
    printf("socket connect success: ip = %s, prot = %d\n", ip.c_str(), port);
    return true;
}

int Socket::accept()
{
    int connfd = ::accept(m_sockfd, nullptr, nullptr);
    if (connfd < 0){
        printf("socket accept error: errno=%d errmsg=%s\n", errno, strerror(errno));
        return -1;
    }
    printf("socket accept: conn=%d\n", connfd);
    return connfd;
}

int Socket::send(const char * buf, int len)
{
    return ::send(m_sockfd, buf, len, 0);
}

int Socket::recv(char * buf, int len)
{
    return ::recv(m_sockfd, buf, len, 0);
}

void Socket::close()
{
    if (m_sockfd > 0)
    {
        ::close(m_sockfd);
        m_sockfd = 0;
    }
}