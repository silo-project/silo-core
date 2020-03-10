#include "connection_info.h"
#include "value.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef NODE_H
#define NODE_H

//<TODO> 커넥션 정보 설정 함수 만들기

class ISendable {
private:
  std::vector<Value *> outputs;
  std::vector<uint8_t> outputWidths;
  std::vector<ConnectionInfo> nodeConnection;

public:
  ~ISendable();
  std::vector<Value *> getOutputs();
  std::vector<uint8_t> getOutputWidths();
  void addOutput(Value *value);
  void setOutputs(std::vector<Value *> outputValues);
  void setOutputWidths(std::vector<uint8_t>);
  std::vector<ConnectionInfo> getNodeConnection();
  virtual void calculate() = 0;
};

class IReciveable {
private:
  std::vector<Value *> inputs;
  std::vector<Value *> previousInput;
  std::vector<uint8_t> inputWidths;

public:
  ~IReciveable();
  std::vector<uint8_t> getInputWidths();
  std::vector<Value *> getInputs();
  std::vector<Value *> getPreviousInput();
  void addInput(Value *value);
  void setInputs(uint8_t inputNumber, Value inputValue);
  void setInputs(std::vector<Value *> inputValues);
  void setPreviousInputs(uint8_t inputNumber, Value inputValue);
  void setPreviousInputs(std::vector<Value *> inputValues);
  void setInputWidths(std::vector<uint8_t> inputWidthValues);
};

class AbstractNode {
private:
  std::unordered_map<std::string, uint8_t> gateProperties;

public:
  void
  gatePropertiesSetting(std::unordered_map<std::string, uint8_t> properties);
  std::unordered_map<std::string, uint8_t> getGateProperties();
  virtual void nodeInitialization() = 0;
};

class AbstractGate : public ISendable,
                     public IReciveable,
                     public AbstractNode {};

#endif
