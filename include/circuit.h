#ifndef SILO_CORE_CIRCUIT_H
#define SILO_CORE_CIRCUIT_H

#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include "status_codes.h"

using circuit_id = int32_t;
using circuitid_on_plane_t = int32_t;

struct Position {
    int32_t x;
    int32_t y;
};

class Circuit {
public:
    Position position;
    circuitid_on_plane_t cpid;

public:
    circuit_id placeCircuit(Circuit* circuit);
    Circuit* getEditableCircuit(circuit_id id);
    void removeCircuit(circuit_id id);
    void setAttribute(const std::string& name, std::string attr);
    std::string getAttribute(const std::string& name);
    circuitid_on_plane_t generateCircuitIDOnPlane(circuitid_on_plane_t nextcpid);

protected:
    std::vector<Circuit*> circuitVector;
    std::map<std::string, std::string> attributeMap;
};

#endif