//
// Created by penta on 2020-05-19.
//

#ifndef SILO_CORE_TCPSERVER_H
#define SILO_CORE_TCPSERVER_H

#define MAX_TCP_BUFFER_SIZE 1024

#include <thread>
#include <vector>

#ifdef WIN32
#include <winsock2.h>
#else
#endif

enum SocketType { HTTP, WS };

class AcceptedSocket {
public:
    SOCKET s;
    SocketType sockettype = SocketType::HTTP;
    char* rbuf;
    //char* wbuf;
    size_t rlen;/*, wlen;*/

public:
    AcceptedSocket(SOCKET _s);
    ~AcceptedSocket();
};

class ServerSocket {
protected:
    WSADATA wsaData;
    sockaddr_in sockaddr;
    std::thread* t;
    timeval to;
    std::vector<AcceptedSocket*> clients;

public:
    SOCKET sockfd;
    bool stopflag;
    fd_set rset;

public:
    ServerSocket(unsigned short portnum) noexcept;
    ~ServerSocket();
    void run();
};

#endif //SILO_CORE_TCPSERVER_H
