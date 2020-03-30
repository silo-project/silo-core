#include "Gates/not_gate.h"



SILO_STATUS NotGate::init() {
    std::unordered_map< std::string, uint8_t > gateProperties = this->getGateProperties();

    if (gateProperties.find("Data Bits") == gateProperties.cend() 
        || gateProperties.find("Output Value") == gateProperties.cend()) {
        return GATE_PROPERTIES_ERROR;
    }

    this->properties.dataBits = gateProperties.find("Data Bits")->second;
    this->properties.outputValue = gateProperties.find("Output Value")->second;

    std::vector< uint8_t > inputWidth;
    std::vector< uint8_t > outputWidth;

    inputWidth.push_back(properties.dataBits);
    outputWidth.push_back(properties.dataBits);
    this->setInputWidths(inputWidth);
    this->setOutputWidths(outputWidth);

    Value* newOutput = new Value(this->properties.dataBits, 0, 0, INT64_MAX);
    Value* newInput = new Value(this->properties.dataBits, 0, 0, INT64_MAX);

    if (newOutput == nullptr || newInput == nullptr) {
        return OUT_OF_MEMORY_ERROR;
    }

    this->addOutput(newOutput);
    this->addInput(newInput);

    return SUCCESS;
}


void NotGate::calculate() {
    std::vector<Value*> inputs = this->getInputs();
    uint64_t outputValue = 0;
    uint64_t outputState = 0;

    if (properties.outputValue == 0) /* 0/1 */ {
        outputValue = ~inputs[0]-> getValue() | inputs[0]->getState();
        outputState = inputs[0]->getState();
    }
    else if (properties.outputValue == 1) /* 0/floating */ {
        outputValue = inputs[0]->getState();
        outputState = ~inputs[0]->getValue() | inputs[0]->getState();
    }
    else /* floating/1 */ {
        outputValue = ~inputs[0]->getValue() | inputs[0]->getState();
        outputState = inputs[0]->getValue() | inputs[0]->getState();
    }

    std::vector<Value*> outputs;
    outputs.push_back(new Value(properties.dataBits, outputValue, outputState));
    this->setOutputs(outputs);
}
