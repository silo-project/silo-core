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

void Sender::addConnection(ConnectionInfo newConnection) {
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

SingleBit Receiver::addSingleSignal(SingleBit nowValue, SingleBit newValue) {
  SingleBit result;

  result.error = nowValue.error | newValue.error;

  if (result.error) {
    return result;
  }

  if (nowValue.unknown == 1 ||
      ((nowValue.unknown == 0) && (nowValue.value == newValue.value))) {
    result.value = newValue.value;
    result.unknown = nowValue.unknown || newValue.unknown;
    return result;
  }

  errorFlag = INPUT_VALUE_CONFLICT_WARNING;
  result.error = 1;
  return result;
}

bool Receiver::getBit(uint8_t digit, uint64_t value) {
  return (value >> digit) & 1;
}

uint64_t Receiver::setBit(uint8_t digit, uint64_t value, bool setValue) {
  if (setValue) {
    return value | (1 << digit);
  } else {
    return value & ~(1 << digit);
  }
}

Value *Receiver::addSignal(Value *nowSignal, Value *newSignal, uint8_t width) {
  SingleBit nowSignalBit;
  SingleBit newSignalBit;

  uint64_t nowValue = nowSignal->getValue();
  uint64_t newValue = newSignal->getValue();
  uint64_t nowUnknown = nowSignal->getUnknown();
  uint64_t newUnknown = newSignal->getUnknown();
  uint64_t nowError = nowSignal->getError();
  uint64_t newError = newSignal->getError();

  delete nowSignal;
  delete newSignal;

  uint64_t value = 0;
  uint64_t unknown = 0;
  uint64_t error = 0;

  for (int i = 0; i < width; i++) {
    nowSignalBit.value = this->getBit(i, nowValue);
    nowSignalBit.unknown = this->getBit(i, nowUnknown);
    nowSignalBit.error = this->getBit(i, nowError);
    newSignalBit.value = this->getBit(i, newValue);
    newSignalBit.unknown = this->getBit(i, newUnknown);
    newSignalBit.error = this->getBit(i, newError);

    SingleBit signalBit = this->addSingleSignal(nowSignalBit, newSignalBit);

    value = this->setBit(i, value, signalBit.value);
    unknown = this->setBit(i, unknown, signalBit.unknown);
    error = this->setBit(i, error, signalBit.error);
  }

  return new Value(width, value, unknown, error);
}

SILO_ERRHANDEL Receiver::setInput(uint8_t inputNumber, Value *inputValue) {

  if (firstInputFlag) {
    firstInputFlag = false;
    delete this->inputs[inputNumber];
    this->inputs[inputNumber] = inputValue;
  } else {

    this->inputs[inputNumber] = this->addSignal(inputs[inputNumber], inputValue,
                                                inputValue->getWidth());
  }

  SILO_ERRHANDEL warning = errorFlag;
  errorFlag = 0;

  return warning;
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

void Receiver::setFirstInputFlag() { firstInputFlag = true; }

/**********AbstractNode**********/
void AbstractNode::gatePropertiesSetting(
    std::unordered_map<std::string, uint8_t> properties) {
  this->gateProperties = properties;
}

std::unordered_map<std::string, uint8_t> AbstractNode::getGateProperties() {
  return this->gateProperties;
}
