#ifndef NODE_H
#define NODE_H

#include "connection_info.h"
#include "value.h"
#include "error_handling.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct SingleBit {
  bool value = 0;
  bool unknown = 0;
  bool error = 0;
};

class Sender {
private:
  std::vector<Value *> outputs;
  std::vector<uint8_t> outputWidths;
  std::vector<ConnectionInfo> nodeConnection;

public:
  ~Sender();
  std::vector<Value *> getOutputs();
  std::vector<uint8_t> getOutputWidths();
  void addOutput(Value *value);
  void setOutputs(std::vector<Value *> outputValues);
  void setOutputWidths(std::vector<uint8_t>);
  std::vector<ConnectionInfo> getNodeConnection();
  void addConnection(ConnectionInfo newConnection);
  virtual void calculate() = 0;
};

class Receiver {
private:
  std::vector<Value *> inputs;
  std::vector<Value *> previousInput;
  std::vector<uint8_t> inputWidths;

  bool firstInputFlag = true;
  SILO_STATUS errorFlag = SUCCESS;

  SingleBit addSingleSignal(SingleBit nowValue, SingleBit newValue);
  bool getBit(uint8_t digit, uint64_t value);
  uint64_t setBit(uint8_t digit, uint64_t value, bool setValue);
  Value *addSignal(Value *nowSignal, Value *newSignal, uint8_t width);

public:
  ~Receiver();
  std::vector<uint8_t> getInputWidths();
  std::vector<Value *> getInputs();
  std::vector<Value *> getPreviousInput();
  void addInput(Value *value);
  SILO_STATUS setInput(uint8_t inputNumber, Value *inputValue);
  void setInputs(std::vector<Value *> inputValues);
  void setPreviousInput(uint8_t inputNumber, Value inputValue);
  void setPreviousInputs(std::vector<Value *> inputValues);
  void setInputWidths(std::vector<uint8_t> inputWidthValues);
  void setFirstInputFlag();
};

class AbstractNode {
private:
  std::unordered_map<std::string, uint8_t> gateProperties;

public:
  void
  gatePropertiesSetting(std::unordered_map<std::string, uint8_t> properties);
  std::unordered_map<std::string, uint8_t> getGateProperties();
  virtual SILO_STATUS nodeInit() = 0;
};

class AbstractGate : public Sender, public Receiver, public AbstractNode {};

#endif
