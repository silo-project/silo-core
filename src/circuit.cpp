//
// Created by penta on 2020-05-01.
//

#include "circuit.h"

#include <utility>

using std::string;

circuitid_t Circuit::placeCircuit(Circuit* c) {
    this->CircuitVector.push_back(c);
    return this->CircuitVector.size();
}

Circuit* Circuit::getEditableCircuit(circuitid_t cid) {
    return this->CircuitVector.at(cid);
}

void Circuit::setAttribute(const string& n, string v) {
    this->AttributeMap[n] = std::move(v);
}

string Circuit::getAttribute(const string& n) {
    auto v = this->AttributeMap.find(n);
    return v == this->AttributeMap.end() ? std::string() : v->second;
}