#ifndef CONNECTION_INFO_H
#define CONNECTION_INFO_H

#include <cstdint>



class AbstractNode;

struct ConnectionInfo {
    AbstractNode* nextNode;
    uint8_t nextInputPin;
};

#endif