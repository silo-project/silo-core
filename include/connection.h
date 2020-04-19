#ifndef CONNECTION_H
#define CONNECTION_H

#include <cstdint>



class AbstractNode;

struct Connection {
    AbstractNode* nextNode;
    uint8_t nextInputPin;
};

#endif