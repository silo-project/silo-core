#include "simulation.h"

SILO_ERRHANDEL
Simulation::addNode(uint8_t gateID,
                    std::unordered_map<std::string, uint8_t> gateProperties) {
  switch (gateID) {
  case BUFFER_GATE_ID:
    this->nodeVector.push_back(new BufferGate);
    break;

  default:
    return GATE_ID_ERROR;
    break;
  }

  nodeVector[gateID]->gatePropertiesSetting(gateProperties);

  return nodeVector[gateID]->nodeInit();
}