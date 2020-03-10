#include <cstdint>
#include <vector>

#ifndef CONNECTION_INFO
#define CONNECTION_INFO

class AbstractNode;

struct ConnectionInfo {
  AbstractNode *nextNode;
  uint8_t nextInputPin;
};

#endif