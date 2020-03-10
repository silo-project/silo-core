#include "buffer_gate.h"

void BufferGate::calculate() {
  std::vector<Value *> inputs = this->getInputs();
  std::vector<Value *> outputs;
  uint64_t outputValue;
  uint64_t outputUnknown;
  uint64_t outputError;

  if (outputValue == 0) // 0/1
  {
    outputValue = inputs[0]->getValue();
    outputUnknown = inputs[0]->getUnknown();
    outputError = inputs[0]->getError();
  }

  //<TODO> 버퍼게이트의 floating/1과 0/floating 속성 구현하기

  outputs.push_back(
      new Value(properties.dataBits, outputValue, outputUnknown, outputError));
  this->setOutputs(outputs);
}

void BufferGate::nodeInitialization() {
  std::unordered_map<std::string, uint8_t> gateProperties;
  std::vector<uint8_t> inputWidth;
  std::vector<uint8_t> outputWidth;

  gateProperties = this->getGateProperties();

  this->properties.dataBits = gateProperties.find("Data Bits")->second;
  this->properties.outputValue = gateProperties.find("Output Value")->second;

  inputWidth.push_back(properties.dataBits);
  outputWidth.push_back(properties.dataBits);
  this->setInputWidths(inputWidth);
  this->setOutputWidths(outputWidth);

  this->addOutput(
      new Value(this->properties.dataBits, 0, 0, 0xffffffffffffffff));
  this->addInput(
      new Value(this->properties.dataBits, 0, 0, 0xffffffffffffffff));
}