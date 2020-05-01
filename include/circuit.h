#ifndef SILO_CORE_CIRCUIT_H
#define SILO_CORE_CIRCUIT_H

#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include "status_codes.h"

using circuit_id = int32_t;

struct Position {
    int32_t x;
    int32_t y;
};

class Circuit {
public:
    Position position;

public:
    circuit_id placeCircuit(Circuit* circuit);
    Circuit* getEditableCircuit(circuit_id id);
    void Circuit::removeCircuit(circuit_id id);
    void setAttribute(const std::string& name, std::string attr);
    std::string getAttribute(const std::string& name);

protected:
    std::vector<Circuit*> circuitVector;
    std::map<std::string, std::string> attributeMap;
};

#endif
