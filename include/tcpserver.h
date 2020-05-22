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
    explicit AcceptedSocket(SOCKET _s);
    ~AcceptedSocket();
};

class ServerSocket {
protected:
    WSADATA wsaData;
    sockaddr_in sockaddr;
    std::thread* t;
    timeval to;
    std::vector<AcceptedSocket*> clients;
    std::string* rootpath;

public:
    SOCKET sockfd;
    bool stopflag;

public:
    explicit ServerSocket(unsigned short portnum) noexcept;
    ~ServerSocket();
    void run();

protected:
    static void threadRunner(std::string* rootpath, SOCKET *serversocket, std::vector<AcceptedSocket *> *clients, bool *stopflag, timeval *timeout);
};

#endif //SILO_CORE_TCPSERVER_H
