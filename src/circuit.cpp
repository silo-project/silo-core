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

string Circuit::getAttribute(const string& n) {
    auto v = this->AttributeMap.find(n);
    return v == this->AttributeMap.end() ? std::string() : v->second;
}
