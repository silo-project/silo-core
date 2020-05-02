//
// Created by penta on 2020-05-02.
//

#include "circuitmanager.h"
#include <map>
#include <cstdint>
#include <cstring>

#include "Crc32.h"

std::map<uint64_t, AbstractCircuit*>* AbstractCircuitManager::abstractCircuitMap = nullptr;

AbstractCircuitManager::AbstractCircuitManager() {
    if(abstractCircuitMap == nullptr) abstractCircuitMap = new std::map<uint64_t, AbstractCircuit*>();
};

std::map<uint64_t, AbstractCircuit *>* AbstractCircuitManager::getAbstractCircuitMapPtr() {
    return abstractCircuitMap;
}

bool AbstractCircuitManager::hasAbstractCircuit(const char *libname, const char *circname) {
    return abstractCircuitMap->find(ABSTRACTCIRCUITMANAGER_CALCULATECRC(libname, circname)) != abstractCircuitMap->end();
}

AbstractCircuit* AbstractCircuitManager::getAbstractCircuit(const char *libname, const char *circname) {
    return abstractCircuitMap->at(ABSTRACTCIRCUITMANAGER_CALCULATECRC(libname, circname));
}

void AbstractCircuitManager::registerAbstractCircuit(AbstractCircuit* abstractCircuit, const char *libname, const char *circname) {
    abstractCircuitMap->insert(std::pair<uint64_t, AbstractCircuit*>(ABSTRACTCIRCUITMANAGER_CALCULATECRC(libname, circname), abstractCircuit));
};