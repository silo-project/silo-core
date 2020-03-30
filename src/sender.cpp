#include "sender.h"



Sender::~Sender() {
    for (auto output : this->outputs) {
        delete output;
    }
}

std::vector< Value* > Sender::getOutputs() const {
    return this->outputs;
}

std::vector< uint8_t > Sender::getOutputWidths() const {
    return this->outputWidths;
}

std::vector< ConnectionInfo > Sender::getConnection() const {
    return this->nodeConnection;
}



void Sender::addOutput(Value* value) {
    this->outputs.push_back(value);
}

void Sender::addConnection(const ConnectionInfo& newConnection) {
    this->nodeConnection.push_back(newConnection);
}



void Sender::setOutputs(const std::vector< Value* >& outputValues) {
    for (auto output : this->outputs) {
        delete output;
    }

    this->outputs = outputValues;
}

void Sender::setOutputWidths(const std::vector< uint8_t >& outputWidthValues) {
    this->outputWidths = outputWidthValues;
}