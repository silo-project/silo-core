#ifndef CONNECTION_INFO
#define CONNECTION_INFO

#include <cstdint>
#include <vector>

class AbstractNode;

struct ConnectionInfo {
  AbstractNode *nextNode;
  uint8_t nextInputPin;
};

#endif