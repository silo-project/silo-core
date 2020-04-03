#include <algorithm>

#include "simulation.h"
#include "Gates/gates.h"
#include "error_handling.h"



SILO_STATUS Simulation::addNode(uint8_t gateID, std::unordered_map< std::string, uint8_t > gateProperties) {
    switch (static_cast< GATE_ID >(gateID)) {
        case GATE_ID::BUFFER_GATE:
            this->nodeVector.push_back(new BufferGate());
            break;
        case GATE_ID::NOT_GATE:
            this->nodeVector.push_back(new NotGate());
            break;
        case GATE_ID::AND_GATE:
            this->nodeVector.push_back(new AndGate());
            break;

        default:
            return GATE_ID_ERROR;
    }

    nodeVector[gateID]->setGateProperties(gateProperties);

    return nodeVector[gateID]->init();
}

void Simulation::addConnection(uint32_t outputNodeID, uint8_t outputNumber, uint32_t inputNodeID, uint8_t inputNumber) {
    ConnectionInfo newConnection;
    newConnection.nextNode = this->nodeVector[inputNodeID];
    newConnection.nextInputPin = inputNumber;

    this->nodeVector[outputNodeID]->addConnection(newConnection);
}

void Simulation::setNodeInputs(uint32_t nodeID, std::vector< Value* > inputs) {
    this->nodeVector[nodeID]->setInputs(inputs);
    this->firstPropagation.push_back(this->nodeVector[nodeID]);
}

std::vector<Value *> Simulation::getNodeOutputs(uint32_t nodeID) const {
    return this->nodeVector[nodeID]->getOutputs();
}

void Simulation::deduplication(std::vector< AbstractGate* > *array) {
    std::sort(array->begin(), array->end());
    array->erase(unique(array->begin(), array->end()), array->end());
}

SILO_STATUS Simulation::autoPropagation() {
    this->deduplication(&firstPropagation);

    return SUCCESS;
}

void Simulation::reset() {
}

void Simulation::clear() {
}

