#ifndef CONNECTION_INFO
#define CONNECTION_INFO

#include <cstdint>
#include <vector>

class AbstractGate;

struct ConnectionInfo {
    AbstractGate *nextNode;
    uint8_t nextInputPin;
};

#endif