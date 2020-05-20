//
// Created by penta on 2020-05-19.
//

#include "tcpserver.h"
#include <iostream>
#include <algorithm>
#include <cstring>

const char* HTTPRequestEnd = "\r\n\r\n";

AcceptedSocket::AcceptedSocket(SOCKET _s) {
    s = _s;
    rbuf = static_cast<char*>(malloc(MAX_TCP_BUFFER_SIZE));
    rlen = 0;
    //wbuf = static_cast<char*>(malloc(MAX_TCP_BUFFER_SIZE));
}

AcceptedSocket::~AcceptedSocket() {
    closesocket(s);
    free(rbuf);
    //free(wbuf);
}

ServerSocket::ServerSocket(unsigned short portnum) noexcept {
    t = nullptr;
    stopflag = false;

    if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0) {
        std::cout << "" << std::endl;
        return;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == INVALID_SOCKET) return;

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(portnum);
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, reinterpret_cast<const struct sockaddr*>(&sockaddr), sizeof(sockaddr)) == SOCKET_ERROR) std::cout << "BIND FAILED" << std::endl;

    listen(sockfd, 8);

    unsigned long ltrue = 0x1;

    ioctlsocket(sockfd, FIONBIO, &ltrue);

    to.tv_sec = 0;
    to.tv_usec = 100000;
}

void ServerSocket::run() {
    if(t) return;
    t = new std::thread([](SOCKET* serversocket, std::vector<AcceptedSocket*>* clients, bool* stopflag, timeval* timeout) {
        std::cout << "SERVER THREAD RUNNING" << std::endl;
        fd_set rset;
        while (!(*stopflag)) {
            FD_ZERO(&rset);
            FD_SET(*serversocket, &rset);
            for(auto sock : *clients) FD_SET(sock->s, &rset);

            int ret = select(0, &rset, nullptr, nullptr, timeout);
            if (ret) {
                //std::cout << "INCOMING" << std::endl;

                if(FD_ISSET(*serversocket, &rset)) { // ACCEPT
                    std::cout << "CONNECTION INCOMING" << std::endl;
                    sockaddr_in caddr;
                    size_t caddersz = sizeof(caddr);
                    SOCKET clientsocket = accept(*serversocket, reinterpret_cast<struct sockaddr *>(&caddr),
                                                 reinterpret_cast<int *>(&caddersz));
                    if (clientsocket != INVALID_SOCKET) {
                        clients->push_back(new AcceptedSocket(clientsocket));
                    }
                    std::cout << "CONNECTION REGISTERED" << std::endl;
                }

                for(AcceptedSocket* sock : *clients) {
                    if(FD_ISSET(sock->s, &rset)) {    // DATA IN
                        char* nrbuf = static_cast<char *>(malloc(MAX_TCP_BUFFER_SIZE));
                        int rl = recv(sock->s, nrbuf, MAX_TCP_BUFFER_SIZE, 0);

                        if(rl == 0) {
                            clients->erase(std::find(clients->begin(), clients->end(), sock));
                            delete sock;
                            continue;
                        }

                        if(rl == SOCKET_ERROR) {
                            std::cout << WSAGetLastError() << std::endl;
                            continue;
                        }

                        std::cout << rl << std::endl;
                        if(sock->rlen + rl > MAX_TCP_BUFFER_SIZE) {
                            //rl = MAX_TCP_BUFFER_SIZE - sock->rlen;  // OVERFLOW
                            continue;
                        }

                        memcpy(sock->rbuf + (sock->rlen), nrbuf, rl);
                        free(nrbuf);
                        sock->rlen += rl;

                        switch(sock->sockettype) {
                            case SocketType::WS:
                                break;
                            case SocketType::HTTP:
                                if(sock->rlen >= 4 && memcmp(sock->rbuf + sock->rlen - 4, HTTPRequestEnd, 4) == 0) {
                                    std::cout << "HTTP REQUEST COMPLETE" << std::endl;
                                    sock->rbuf[sock->rlen] = '\0';
                                    std::cout << sock->rbuf << std::endl;
                                }
                                break;
                        }
                    }
                }
            }
        }
    }, &sockfd, &clients, &stopflag, &to);
}

ServerSocket::~ServerSocket() {
    stopflag = true;
    t->join();
    closesocket(sockfd);
    for(auto s : clients) delete s;
    WSACleanup();
    delete t;
}