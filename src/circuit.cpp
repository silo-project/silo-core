//
// Created by penta on 2020-05-01.
//

#include "circuit.h"

#include <utility>

using std::string;

circuit_id Circuit::placeCircuit(Circuit* circuit) {
    this->circuitVector.push_back(circuit);
    return this->circuitVector.size();
}

Circuit* Circuit::getEditableCircuit(circuit_id id) {
    return this->circuitVector.at(id);
}

void Circuit::removeCircuit(circuit_id id) {
    delete this->circuitVector.at(id);
    this->circuitVector.erase(circuitVector.begin() + id);
}

void Circuit::setAttribute(const string& name, string attr) {
    this->attributeMap[name] = std::move(attr);
}

string Circuit::getAttribute(const string& name) {
    auto v = this->attributeMap.find(name);
    return v == this->attributeMap.end() ? std::string() : v->second;
}

circuitid_on_plane_t Circuit::generateCircuitIDOnPlane(circuitid_on_plane_t nextcpid) {
    this->cpid = nextcpid;
    nextcpid++;
    for(auto p : this->circuitVector) {
        nextcpid = p->generateCircuitIDOnPlane(nextcpid);
    }
    return nextcpid;
}

void Circuit::placeWire(int32_t ax, int32_t ay, int32_t bx, int32_t by) {
    Wire* wire = static_cast<Wire *>(calloc(1, sizeof(Wire)));
    wire->a.x = ax; wire->a.y = ay;
    wire->b.x = bx; wire->b.y = by;
}
