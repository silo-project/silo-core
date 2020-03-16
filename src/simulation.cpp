#include "simulation.h"

SILO_STATUS Simulation::addNode(uint8_t gateID, std::unordered_map<std::string, uint8_t> gateProperties) {
    switch (gateID) {
        case GATE_ID::BUFFER_GATE:
            this->nodeVector.push_back(new BufferGate());
            break;

        default:
            return GATE_ID_ERROR;
            break;
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

void Simulation::setNodeInputs(uint32_t nodeID, std::vector<Value *> inputs) {
    this->nodeVector[nodeID]->setInputs(inputs);
    this->firstPropagation.push_back(this->nodeVector[nodeID]);
}

std::vector<Value *> Simulation::getNodeOutputs(uint32_t nodeID) {
    return this->nodeVector[nodeID]->getOutputs();
}

void Simulation::deduplication(std::vector<AbstractGate *> *array) {
    std::sort(array->begin(), array->end());
    array->erase(unique(array->begin(), array->end()), array->end());
}

SILO_STATUS Simulation::autoPropagation() {
    this->deduplication(&firstPropagation);

    return SUCCESS;
}

