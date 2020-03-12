#include "connection_info.h"
#include "error_handel.h"
#include "gate_id.h"
#include "gates.h"
#include "node.h"
#include "value.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#ifndef SIMULATION_H
#define SIMULATION_H

//<TODO> autoPropagation 함수 마저 구현

class Simulation {
private:
  std::vector<AbstractGate *> nodeVector;
  std::vector<AbstractGate *> firstPropagation;

  void deduplication(std::vector<AbstractGate *> *array);

public:
  SILO_ERRHANDEL
  addNode(uint8_t gateID,
          std::unordered_map<std::string, uint8_t> gateProperties);
  void addConnection(uint32_t outputNodeID, uint8_t outputNumber,
                     uint32_t inputNodeID, uint8_t inputNumber);
  void setNodeInputs(uint32_t nodeID, std::vector<Value *> inputs);
  std::vector<Value *> getNodeOutputs(uint32_t nodeID);
  SILO_ERRHANDEL autoPropagation();
  void resetSimulation();
  void clearSimulation();
};

#endif