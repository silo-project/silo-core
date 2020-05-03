//
// Created by penta on 2020-05-01.
//

#include "circuit.h"
#include "value.h"

#include <utility>

using std::string;

circuit_id AbstractCircuit::placeAbstractCircuit(AbstractCircuit* abstractCircuit) {
    this->abstractCircuitVector.push_back(abstractCircuit);
    return this->abstractCircuitVector.size();
}

AbstractCircuit* AbstractCircuit::getEditableAbstractCircuit(circuit_id id) {
    return this->abstractCircuitVector.at(id);
}

void AbstractCircuit::removeAbstractCircuit(circuit_id id) {
    delete this->abstractCircuitVector.at(id);
    this->abstractCircuitVector.erase(abstractCircuitVector.begin() + id);
}

void AbstractCircuit::placeWire(int32_t ax, int32_t ay, int32_t bx, int32_t by, uint8_t width) {
    AbstractWire* abstractWire = new AbstractWire;

    abstractWire->a.x = ax; 
    abstractWire->a.y = ay;
    abstractWire->b.x = bx; 
    abstractWire->b.y = by;

    abstractWire->width = width;

    this->abstractWireVector.push_back(abstractWire);
}

Circuit::Circuit(AbstractCircuit* _abstractCircuit) {
    this->abstractCircuit = _abstractCircuit;
    this->position = abstractCircuit->position;

    for(auto a : _abstractCircuit->abstractCircuitVector) 
        this->circuitVector.push_back(new Circuit(a));

    for(auto w : _abstractCircuit->abstractWireVector) 
        this->wireValueVector.push_back(new Value(w->width, 0, 0));
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