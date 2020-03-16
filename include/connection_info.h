#ifndef CONNECTION_INFO_H
#define CONNECTION_INFO_H

#include <cstdint>
#include <vector>

class AbstractGate;

struct ConnectionInfo {
    AbstractGate *nextNode;
    uint8_t nextInputPin;
};

#endif