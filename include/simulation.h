#ifndef SIMULATION_H
#define SIMULATION_H

#include <cstdint>
#include <map>
#include <vector>

#include "node.h"
#include "value.h"
#include "connection.h"



class Simulation {
private:
    std::vector< AbstractGate* > nodeVector;
    std::vector< AbstractGate* > firstPropagation;

    void deduplication(std::vector< AbstractGate* >* array);

public:
    std::vector< Value* > getNodeOutputs(uint32_t nodeID) const;

    status_t addNode(uint8_t gateID, std::unordered_map< std::string, uint8_t > gateProperties);
    void addConnection(uint32_t outputNodeID, uint8_t outputNumber, uint32_t inputNodeID, uint8_t inputNumber);

    void setNodeInputs(uint32_t nodeID, std::vector< Value* > inputs);

    status_t autoPropagation();  // < TODO > autoPropagation 함수 마저 구현
    void reset();
    void clear();
};

#endif