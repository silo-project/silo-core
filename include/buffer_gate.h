#include "node.h"

#ifndef BUFFER_GATE_H
#define BUFFER_GATE_H

struct BufferGateProperties {
  uint8_t dataBits;
  uint8_t outputValue;
};

class BufferGate : public AbstractGate {
private:
  BufferGateProperties properties;

public:
  virtual void calculate();
  virtual void nodeInitialization();
};

#endif