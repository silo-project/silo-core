#include "value.h"
#include <cstdint>
#include <vector>

#ifndef NODE_H
#define NODE_H

using namespace std;

class ISendable {
public:
  virtual void propagate() = 0;
};

class IReciveable {
public:
  virtual void setNodeInput(uint8_t inputNumber, value inputValue) = 0;
  virtual void setNodeFunction() = 0;
};

class node : public ISendable, IReciveable {
private:
  vector<value> nodeInput;
  vector<value> nodeOutput;

  vector<node *> nextNode;
  vector<uint8_t> nextNodeInputNumber;

public:
  virtual void setNodeInput(uint8_t inputNumber, value inputValue);
  virtual void setNodeFunction();
  value getNodeOutput(uint8_t outputNumber);
  virtual void propagate();
  vector<node *> getNextPropagation();
};

#endif;