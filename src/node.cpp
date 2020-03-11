#include "node.h"

/**********ISendable**********/

ISendable::~ISendable() {
  for (int i = 0; i < this->outputs.size(); i++) {
    delete this->outputs[i];
  }
}

std::vector<Value *> ISendable::getOutputs() { return this->outputs; }

std::vector<uint8_t> ISendable::getOutputWidths() { return this->outputWidths; }

void ISendable::addOutput(Value *value) { this->outputs.push_back(value); }

void ISendable::setOutputs(std::vector<Value *> outputValues) {
  for (int i = 0; i < this->outputs.size(); i++) {
    delete this->outputs[i];
  }
  this->outputs = outputValues;
}

void ISendable::setOutputWidths(std::vector<uint8_t> outputWidthValues) {
  this->outputWidths = outputWidthValues;
}

std::vector<ConnectionInfo> ISendable::getNodeConnection() {
  return this->nodeConnection;
}

/**********IReciveable**********/
IReceivable::~IReceivable() {
  for (int i = 0; i < this->inputs.size(); i++) {
    delete this->inputs[i];
  }
  for (int i = 0; i < this->previousInput.size(); i++) {
    delete this->previousInput[i];
  }
}

std::vector<uint8_t> IReceivable::getInputWidths() { return this->inputWidths; }

std::vector<Value *> IReceivable::getInputs() { return this->inputs; }

std::vector<Value *> IReceivable::getPreviousInput() {
  return this->previousInput;
}

void IReceivable::addInput(Value *value) {
  this->inputs.push_back(value);
  this->previousInput.push_back(value);
}

void IReceivable::setInput(uint8_t inputNumber, Value inputValue) {
  delete this->inputs[inputNumber];
  this->inputs[inputNumber] = &inputValue;
}

void IReceivable::setInputs(std::vector<Value *> inputValues) {
  for (int i = 0; i < this->inputs.size(); i++) {
    delete this->inputs[i];
  }
  this->inputs = inputValues;
}

void IReceivable::setPreviousInput(uint8_t inputNumber, Value inputValue) {
  delete this->previousInput[inputNumber];
  this->previousInput[inputNumber] = &inputValue;
}

void IReceivable::setPreviousInputs(std::vector<Value *> inputValues) {
  for (int i = 0; i < this->previousInput.size(); i++) {
    delete this->previousInput[i];
  }
  this->previousInput = inputValues;
}

void IReceivable::setInputWidths(std::vector<uint8_t> inputWidthValues) {
  this->inputWidths = inputWidthValues;
}

/**********AbstractNode**********/
void AbstractNode::gatePropertiesSetting(
    std::unordered_map<std::string, uint8_t> properties) {
  this->gateProperties = properties;
}

std::unordered_map<std::string, uint8_t> AbstractNode::getGateProperties() {
  return this->gateProperties;
}
