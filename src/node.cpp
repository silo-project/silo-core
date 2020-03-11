#include "node.h"

/**********Sender**********/

Sender::~Sender() {
  for (int i = 0; i < this->outputs.size(); i++) {
    delete this->outputs[i];
  }
}

std::vector<Value *> Sender::getOutputs() { return this->outputs; }

std::vector<uint8_t> Sender::getOutputWidths() { return this->outputWidths; }

void Sender::addOutput(Value *value) { this->outputs.push_back(value); }

void Sender::setOutputs(std::vector<Value *> outputValues) {
  for (int i = 0; i < this->outputs.size(); i++) {
    delete this->outputs[i];
  }
  this->outputs = outputValues;
}

void Sender::setOutputWidths(std::vector<uint8_t> outputWidthValues) {
  this->outputWidths = outputWidthValues;
}

std::vector<ConnectionInfo> Sender::getNodeConnection() {
  return this->nodeConnection;
}

void Sender::addConnection(ConnectionInfo newConnection)
{
  this->nodeConnection.push_back(newConnection);
}

/**********Receiver**********/
Receiver::~Receiver() {
  for (int i = 0; i < this->inputs.size(); i++) {
    delete this->inputs[i];
  }
  for (int i = 0; i < this->previousInput.size(); i++) {
    delete this->previousInput[i];
  }
}

std::vector<uint8_t> Receiver::getInputWidths() { return this->inputWidths; }

std::vector<Value *> Receiver::getInputs() { return this->inputs; }

std::vector<Value *> Receiver::getPreviousInput() {
  return this->previousInput;
}

void Receiver::addInput(Value *value) {
  this->inputs.push_back(value);
  this->previousInput.push_back(value);
}

void Receiver::setInput(uint8_t inputNumber, Value inputValue) {
  delete this->inputs[inputNumber];
  this->inputs[inputNumber] = &inputValue;
}

void Receiver::setInputs(std::vector<Value *> inputValues) {
  for (int i = 0; i < this->inputs.size(); i++) {
    delete this->inputs[i];
  }
  this->inputs = inputValues;
}

void Receiver::setPreviousInput(uint8_t inputNumber, Value inputValue) {
  delete this->previousInput[inputNumber];
  this->previousInput[inputNumber] = &inputValue;
}

void Receiver::setPreviousInputs(std::vector<Value *> inputValues) {
  for (int i = 0; i < this->previousInput.size(); i++) {
    delete this->previousInput[i];
  }
  this->previousInput = inputValues;
}

void Receiver::setInputWidths(std::vector<uint8_t> inputWidthValues) {
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
