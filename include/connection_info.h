#include <cstdint>
#include <vector>

#ifndef CONNECTION_INFO_H
#define CONNECTION_INFO_H

class AbstractGate;

struct ConnectionInfo {
    AbstractGate* nextNode;
    uint8_t nextInputPin;
};

#endif