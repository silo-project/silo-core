#ifndef SILO_CORE_CIRCUIT_H
#define SILO_CORE_CIRCUIT_H

#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include "status_codes.h"
#include "value.h"

using circuit_id = int32_t;
using circuitid_on_plane_t = int32_t;

struct Position {
    int32_t x;
    int32_t y;
};

struct Wire {
    Position a, b;
    Value v;
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
    void placeWire(int32_t ax, int32_t ay, int32_t bx, int32_t by);

protected:
    std::vector<Circuit*> circuitVector;
    std::map<std::string, std::string> attributeMap;
    std::vector<Wire*> wireVector;
};

#endif