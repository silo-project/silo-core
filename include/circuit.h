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
#include "bimap.h"

using circuitid_t = int;
using circuitid_on_plane_t = int;
using posvalue_t = int32_t;

struct Pos { posvalue_t x, y; };

class Circuit {
public:
    circuitid_on_plane_t cpid;
    Pos pos;
    circuitid_t placeCircuit(Circuit*);
    Circuit* getEditableCircuit(circuitid_t);
    void removeCircuit(circuitid_t);
    void setAttribute(const std::string&, std::string);
    std::string getAttribute(const std::string&);
    circuitid_on_plane_t generateCircuitIDOnPlane(circuitid_on_plane_t start); // return next start id
protected:
    std::vector<Circuit*> CircuitVector;
    std::map<std::string, std::string> AttributeMap;
    codeproject::bimap<Pos, Pos> WireBiMap;
};

#endif //SILO_CORE_CIRCUIT_H
