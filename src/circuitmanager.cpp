//
// Created by penta on 2020-05-02.
//

#include "circuitmanager.h"
#include <map>
#include <cstdint>
#include <cstring>

#include "Crc32.h"

std::map<uint64_t, AbstractCircuit*>* AbstractCircuitManager::abstractCircuitMap = nullptr;

auto AbstractCircuitManager::calculateCrc(const char* x, const char* y) {
    return static_cast<uint64_t>(crc32_1byte_tableless(x, strlen(x))) << 32 | crc32_1byte_tableless(y, strlen(y));
}

AbstractCircuitManager::AbstractCircuitManager() {
    if(abstractCircuitMap == nullptr) 
        abstractCircuitMap = new std::map<uint64_t, AbstractCircuit*>();
};

std::map<uint64_t, AbstractCircuit*>* AbstractCircuitManager::getAbstractCircuitMapPtr() {
    return abstractCircuitMap;
}

bool AbstractCircuitManager::hasAbstractCircuit(const char* libname, const char* circname) {
    return abstractCircuitMap->find(AbstractCircuitManager::calculateCrc(libname, circname)) != abstractCircuitMap->end();
}

AbstractCircuit* AbstractCircuitManager::getAbstractCircuit(const char *libname, const char *circname) {
    return abstractCircuitMap->at(AbstractCircuitManager::calculateCrc(libname, circname));
}

void AbstractCircuitManager::registerAbstractCircuit(AbstractCircuit* abstractCircuit, const char *libname, const char *circname) {
    abstractCircuitMap->insert(std::pair<uint64_t, AbstractCircuit*>(AbstractCircuitManager::calculateCrc(libname, circname), abstractCircuit));
};