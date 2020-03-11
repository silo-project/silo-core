#include "gates.h"
#include "gate_id.h"
#include "node.h"
#include "value.h"
#include "error_handel.h"
#include "connection_info.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation
{
private:
    std::vector<AbstractGate*> nodeVector;

public:
    SILO_ERRHANDEL addNode(uint8_t gateID, std::unordered_map<std::string, uint8_t> gateProperties);
};

#endif