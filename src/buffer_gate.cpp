#include "buffer_gate.h"

void BufferGate::calculate() {
  std::vector<Value *> inputs = this->getInputs();
  std::vector<Value *> outputs;
  uint64_t outputValue;
  uint64_t outputUnknown;
  uint64_t outputError;

  if (properties.outputValue == 0) // 0/1
  {
    outputValue = inputs[0]->getValue();
    outputUnknown = inputs[0]->getUnknown();
    outputError = inputs[0]->getError();
  }

  else if (properties.outputValue == 1) // 0/floating
  {
    outputValue = 0;
    outputUnknown = (inputs[0]->getValue()) | (inputs[0]->getUnknown());
    outputError = inputs[0]->getError();
  }

  else // floating/1
  {
    outputValue = inputs[0]->getValue();
    outputUnknown = (!(inputs[0]->getValue())) & (inputs[0]->getUnknown());
    outputError = inputs[0]->getError();
  }

  outputs.push_back(
      new Value(properties.dataBits, outputValue, outputUnknown, outputError));
  this->setOutputs(outputs);
}

void BufferGate::nodeInit() {
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

  this->addOutput(new Value(this->properties.dataBits, 0, 0, INT64_MAX));
  this->addInput(new Value(this->properties.dataBits, 0, 0, INT64_MAX));
}