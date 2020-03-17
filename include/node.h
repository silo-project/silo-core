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

    std::vector<Value *> getOutputs() const;
    std::vector<uint8_t> getOutputWidths() const;
    std::vector<ConnectionInfo> getConnection() const;

    void addOutput(Value *value);
    void addConnection(const ConnectionInfo& newConnection);

    void setOutputs(const std::vector<Value *>& outputValues);
    void setOutputWidths(const std::vector<uint8_t>& outputWidthValues);

    virtual void calculate() = 0;
};

class Receiver {
private:
    std::vector<Value *> inputs;
    std::vector<Value *> previousInput;
    std::vector<uint8_t> inputWidths;

    bool firstInputFlag = true;
    SILO_STATUS errorFlag = SUCCESS;

    bool getBit(uint8_t digit, uint64_t value) const;

    SingleBit addSingleSignal(SingleBit nowValue, SingleBit newValue);
    Value *addSignal(Value *nowSignal, Value *newSignal, uint8_t width);

    uint64_t setBit(uint8_t digit, uint64_t value, bool setValue) const;

public:
    ~Receiver();

    std::vector<Value *> getInputs() const;
    std::vector<Value *> getPreviousInput() const;
    std::vector<uint8_t> getInputWidths() const;

    void addInput(Value *value);

    SILO_STATUS setInput(uint8_t inputNumber, Value *inputValue);
    void setInputs(const std::vector<Value *>& inputValues);
    void setPreviousInput(uint8_t inputNumber, Value inputValue);
    void setPreviousInputs(const std::vector<Value *>& inputValues);
    void setInputWidths(const std::vector<uint8_t>& inputWidthValues);
    void setFirstInputFlag();
};

class AbstractNode {
private:
    std::unordered_map<std::string, uint8_t> gateProperties;

public:
    std::unordered_map<std::string, uint8_t> getGateProperties() const;

    void setGateProperties(const std::unordered_map<std::string, uint8_t>& properties);

    virtual SILO_STATUS init() = 0;
};

class AbstractGate : public Sender, public Receiver, public AbstractNode {
    
};

#endif
