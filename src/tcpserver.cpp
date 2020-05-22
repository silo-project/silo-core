//
// Created by penta on 2020-05-19.
//

#include "tcpserver.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <httpparser/httprequestparser.h>

const char* HTTPRequestEnd = "\r\n\r\n";
const size_t HTTPRequestEndLength = 4;

inline void eraseAllSubStr(std::string &mainStr, const std::string &toErase) {
    size_t pos = std::string::npos;

    // Search for the substring in string in a loop untill nothing is found
    while ((pos = mainStr.find(toErase)) != std::string::npos) mainStr.erase(pos, toErase.length());
}

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

    rootpath = new std::string("../html/");

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

void ServerSocket::threadRunner(std::string* rootpath, SOCKET* serversocket, std::vector<AcceptedSocket*>* clients, bool* stopflag, timeval* timeout) {
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
                            sock->rbuf[sock->rlen] = '\0';
                            char* fc = sock->rbuf;
                            char* ec = nullptr;
                            for(;;) {
                                ec = strstr(fc, HTTPRequestEnd);
                                if(ec) { // Request From fc to ec
                                    size_t clen = ec - fc + HTTPRequestEndLength;

                                    httpparser::HttpRequestParser parser;
                                    httpparser::Request request;
                                    httpparser::HttpRequestParser::ParseResult res = parser.parse(request, fc, ec + HTTPRequestEndLength);

                                    std::cout << "REQUEST COMPLETE LEN: " << clen << std::endl;

                                    if(res == httpparser::HttpRequestParser::ParsingCompleted) {
                                        if (request.method == "GET" || request.method == "POST") {
                                            std::cout << request.uri << std::endl;
                                            std::string formuri(request.uri);
                                            eraseAllSubStr(formuri, "..");
                                            std::string s = (*rootpath) + "/" + formuri;
                                            std::cout << "OPENING IFSTREAM " << s << std::endl;
                                            std::ifstream in(s, std::ios::binary);
                                            if(in.good()) {
                                                std::cout << "200 OK " << s << std::endl;
                                                const char* ok_first = "HTTP/1.1 200 OK\r\nContent-Length: ";
                                                send(sock->s, ok_first, strlen(ok_first), 0);

                                                in.seekg(std::ios::end);
                                                in.ignore(std::numeric_limits<std::streamsize>::max());
                                                int flen = in.tellg();
                                                flen = std::filesystem::file_size(std::filesystem::path(s));
                                                std::cout << flen << std::endl;
                                                in.clear();
                                                in.seekg(std::ios::beg);
                                                char fclen[11];
                                                memset(fclen, 0x0, 11);
                                                itoa(flen, fclen, 10);
                                                send(sock->s, fclen, strlen(fclen), 0);

                                                send(sock->s, HTTPRequestEnd, HTTPRequestEndLength, 0);

                                                char* databuf = static_cast<char *>(malloc(MAX_TCP_BUFFER_SIZE));
                                                char* databuftowrite = databuf;
                                                int len;
                                                while(!in.eof()) {
                                                    memset(databuf, 0x0, MAX_TCP_BUFFER_SIZE);
                                                    in.read(databuf, MAX_TCP_BUFFER_SIZE);
                                                    len = in.gcount();
                                                    std::cout << len << " " << databuf << std::endl;
                                                    while (len > 0) {
                                                        int amount = send(sock->s, databuftowrite, len, 0);
                                                        len -= amount;
                                                        databuftowrite += amount;
                                                    }
                                                }
                                                free(databuf);
                                            } else {
                                                const char* not_found = "HTTP/1.1 404 Not Found\r\nContent-Length: 0";
                                                send(sock->s, not_found, strlen(not_found), 0);
                                                send(sock->s, HTTPRequestEnd, HTTPRequestEndLength, 0);
                                            }
                                        } else {
                                            std::cerr << "REQUIRE GET/PUT" << std::endl;
                                            const char* bad_request = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0";
                                            send(sock->s, bad_request, strlen(bad_request), 0);
                                            send(sock->s, HTTPRequestEnd, HTTPRequestEndLength, 0);
                                        }
                                    } else {
                                        std::cerr << "Parsing failed" << std::endl;
                                        const char* bad_request = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0";
                                        send(sock->s, bad_request, strlen(bad_request), 0);
                                        send(sock->s, HTTPRequestEnd, HTTPRequestEndLength, 0);


                                    }

                                } else {
                                    memmove(sock->rbuf, fc, sock->rlen - (fc - sock->rbuf));
                                    sock->rlen -= fc - sock->rbuf;
                                    break;
                                }

                                fc = ec + 4;
                            }
                            /*if(sock->rlen >= 4 && memcmp(sock->rbuf + sock->rlen - 4, HTTPRequestEnd, 4) == 0) {
                                std::cout << "HTTP REQUEST COMPLETE" << std::endl;
                                sock->rbuf[sock->rlen] = '\0';
                                std::cout << sock->rbuf << std::endl;
                            }*/
                            break;
                    }
                }
            }
        }
    }
}

void ServerSocket::run() {
    if(t) return;
    t = new std::thread(threadRunner, rootpath, &sockfd, &clients, &stopflag, &to);
}

ServerSocket::~ServerSocket() {
    stopflag = true;
    t->join();
    closesocket(sockfd);
    for(auto s : clients) delete s;
    WSACleanup();
    delete t;
    delete rootpath;
}