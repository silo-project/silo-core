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

void ISendable::addConnection(ConnectionInfo newConnection)
{
  this->nodeConnection.push_back(newConnection);
}

/**********IReciveable**********/
IReciveable::~IReciveable() {
  for (int i = 0; i < this->inputs.size(); i++) {
    delete this->inputs[i];
  }
  for (int i = 0; i < this->previousInput.size(); i++) {
    delete this->previousInput[i];
  }
}

std::vector<uint8_t> IReciveable::getInputWidths() { return this->inputWidths; }

std::vector<Value *> IReciveable::getInputs() { return this->inputs; }

std::vector<Value *> IReciveable::getPreviousInput() {
  return this->previousInput;
}

void IReciveable::addInput(Value *value) {
  this->inputs.push_back(value);
  this->previousInput.push_back(value);
}

void IReciveable::setInput(uint8_t inputNumber, Value inputValue) {
  delete this->inputs[inputNumber];
  this->inputs[inputNumber] = &inputValue;
}

void IReciveable::setInputs(std::vector<Value *> inputValues) {
  for (int i = 0; i < this->inputs.size(); i++) {
    delete this->inputs[i];
  }
  this->inputs = inputValues;
}

void IReciveable::setPreviousInput(uint8_t inputNumber, Value inputValue) {
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

/**********AbstractNode**********/
void AbstractNode::gatePropertiesSetting(
    std::unordered_map<std::string, uint8_t> properties) {
  this->gateProperties = properties;
}

std::unordered_map<std::string, uint8_t> AbstractNode::getGateProperties() {
  return this->gateProperties;
}
