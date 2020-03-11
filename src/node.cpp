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

/**********Reciever**********/
Reciever::~Reciever() {
  for (int i = 0; i < this->inputs.size(); i++) {
    delete this->inputs[i];
  }
  for (int i = 0; i < this->previousInput.size(); i++) {
    delete this->previousInput[i];
  }
}

std::vector<uint8_t> Reciever::getInputWidths() { return this->inputWidths; }

std::vector<Value *> Reciever::getInputs() { return this->inputs; }

std::vector<Value *> Reciever::getPreviousInput() {
  return this->previousInput;
}

void Reciever::addInput(Value *value) {
  this->inputs.push_back(value);
  this->previousInput.push_back(value);
}

void Reciever::setInput(uint8_t inputNumber, Value inputValue) {
  delete this->inputs[inputNumber];
  this->inputs[inputNumber] = &inputValue;
}

void Reciever::setInputs(std::vector<Value *> inputValues) {
  for (int i = 0; i < this->inputs.size(); i++) {
    delete this->inputs[i];
  }
  this->inputs = inputValues;
}

void Reciever::setPreviousInput(uint8_t inputNumber, Value inputValue) {
  delete this->previousInput[inputNumber];
  this->previousInput[inputNumber] = &inputValue;
}

void Reciever::setPreviousInputs(std::vector<Value *> inputValues) {
  for (int i = 0; i < this->previousInput.size(); i++) {
    delete this->previousInput[i];
  }
  this->previousInput = inputValues;
}

void Reciever::setInputWidths(std::vector<uint8_t> inputWidthValues) {
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
