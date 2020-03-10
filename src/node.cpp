#include "node.h"

std::vector<uint8_t> ISendable::getOutputWidths() { return this->outputWidths; }
std::vector<Value *> ISendable::getOutputs() { return this->outputs; }
std::vector<uint8_t> IReciveable::getInputWidths() { return this->inputWidths; }
std::vector<Value *> IReciveable::getInputs() { return this->inputs; }
std::vector<Value *> IReciveable::getPreviousInput() {
  return this->previousInput;
}

void ISendable::setOutputs(std::vector<Value *> outputValues) {
  for (int i = 0; i < this->outputs.size(); i++) {
    delete this->outputs[i];
  }
  this->outputs = outputValues;
}

void ISendable::setOutputWidths(std::vector<uint8_t> outputWidthValues) {
  this->outputWidths = outputWidthValues;
}

void IReciveable::addInput(Value *value) {
  this->inputs.push_back(value);
  this->previousInput.push_back(value);
}

void ISendable::addOutput(Value *value) { this->outputs.push_back(value); }

void IReciveable::setInputs(uint8_t inputNumber, Value inputValue) {
  delete this->inputs[inputNumber];
  this->inputs[inputNumber] = &inputValue;
}

void IReciveable::setInputs(std::vector<Value *> inputValues) {
  for (int i = 0; i < this->inputs.size(); i++) {
    delete this->inputs[i];
  }
  this->inputs = inputValues;
}

void IReciveable::setPreviousInputs(uint8_t inputNumber, Value inputValue) {
  delete this->previousInput[inputNumber];
  this->previousInput[inputNumber] = &inputValue;
}

void IReciveable::setPreviousInputs(std::vector<Value *> inputValues) {
  for (int i = 0; i < this->previousInput.size(); i++) {
    delete this->previousInput[i];
  }
  this->previousInput = inputValues;
}

void IReciveable::setInputWidths(std::vector<uint8_t> inputWidthValues) {
  this->inputWidths = inputWidthValues;
}

std::vector<ConnectionInfo> ISendable::getNodeConnection() {
  return this->nodeConnection;
}

void AbstractNode::gatePropertiesSetting(
    std::unordered_map<std::string, uint8_t> properties) {
  this->gateProperties = properties;
}

std::unordered_map<std::string, uint8_t> AbstractNode::getGateProperties() {
  return this->gateProperties;
}

ISendable::~ISendable() {
  for (int i = 0; i < this->outputs.size(); i++) {
    delete this->outputs[i];
  }
}

IReciveable::~IReciveable() {
  for (int i = 0; i < this->inputs.size(); i++) {
    delete this->inputs[i];
  }
  for (int i = 0; i < this->previousInput.size(); i++) {
    delete this->previousInput[i];
  }
}