//
// Created by penta on 2020-05-01.
//

#ifndef SILO_CORE_CIRCUIT_H
#define SILO_CORE_CIRCUIT_H

#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include "status_codes.h"

using circuitid_t = int;
using posvalue_t = int32_t;

struct Pos { posvalue_t x, y; };

class Circuit {
public:
    Pos pos;
    circuitid_t placeCircuit(Circuit*);
    Circuit* getEditableCircuit(circuitid_t);
    void setAttribute(const std::string&, std::string);
    std::string getAttribute(const std::string&);
protected:
    std::vector<Circuit*> CircuitVector;
    std::map<std::string, std::string> AttributeMap;
    std::map
};

#endif //SILO_CORE_CIRCUIT_H
