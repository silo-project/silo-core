#include "buffer_gate.h"

SILO_STATUS BufferGate::init() {
    std::unordered_map<std::string, uint8_t> gateProperties;
    std::vector<uint8_t> inputWidth;
    std::vector<uint8_t> outputWidth;

    gateProperties = this->getGateProperties();

    if (gateProperties.find("Data Bits") == gateProperties.end() || gateProperties.find("Output Value") == gateProperties.end()) {
        return GATE_PROPERTIES_ERROR;
    }

    this->properties.dataBits = gateProperties.find("Data Bits")->second;
    this->properties.outputValue = gateProperties.find("Output Value")->second;

    inputWidth.push_back(properties.dataBits);
    outputWidth.push_back(properties.dataBits);
    this->setInputWidths(inputWidth);
    this->setOutputWidths(outputWidth);

    Value *newOutput = new Value(this->properties.dataBits, 0, 0, INT64_MAX);
    Value *newInput = new Value(this->properties.dataBits, 0, 0, INT64_MAX);

    if (newOutput == 0 || newInput == 0) {
        return OUT_OF_MEMORY_ERROR;
    }

    this->addOutput(newOutput);
    this->addInput(newInput);

    return SUCCESS;
}

void BufferGate::calculate() {
    std::vector<Value *> inputs = this->getInputs();
    std::vector<Value *> outputs;
    uint64_t outputValue = 0;
    uint64_t outputUnknown = 0;
    uint64_t outputError = 0;

    if (properties.outputValue == 0) /* 0/1 */ {
        outputValue = inputs[0]->getValue();
        outputUnknown = inputs[0]->getUnknown();
        outputError = inputs[0]->getError();
    } else if (properties.outputValue == 1) /* 0/floating */ {
        outputValue = 0;
        outputUnknown = (inputs[0]->getValue()) | (inputs[0]->getUnknown());
        outputError = inputs[0]->getError();
    } else /* floating/1 */ {
        outputValue = inputs[0]->getValue();
        outputUnknown = (!(inputs[0]->getValue())) & (inputs[0]->getUnknown());
        outputError = inputs[0]->getError();
    }

    outputs.push_back(new Value(properties.dataBits, outputValue, outputUnknown, outputError));
    this->setOutputs(outputs);
}