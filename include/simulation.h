#ifndef SIMULATION_H
#define SIMULATION_H

#include "gates.h"
#include "gate_id.h"
#include "node.h"
#include "value.h"
#include "error_handling.h"
#include "connection_info.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

class Simulation
{
private:
    std::vector<AbstractGate*> nodeVector;

public:
    SILO_STATUS addNode(uint8_t gateID, std::unordered_map<std::string, uint8_t> gateProperties);
};

#endif