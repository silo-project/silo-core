//
// Created by penta on 2020-05-02.
//

#ifndef CIRCUIT_MANAGER_H
#define CIRCUIT_MANAGER_H

#include "circuit.h"
#include <map>
#include <string>

class AbstractCircuitManager {
protected:
    static std::map<uint64_t, AbstractCircuit*>* abstractCircuitMap;

public:
    std::map<uint64_t, AbstractCircuit*>* getAbstractCircuitMapPtr();
    AbstractCircuit* getAbstractCircuit(const char* libname, const char* circname);
    bool hasAbstractCircuit(const char* libname, const char* circname);
    void registerAbstractCircuit(AbstractCircuit* abstractCircuit, const char* libname, const char* circname);
    AbstractCircuitManager();

public:
    static auto calculateCrc(const char* x, const char* y);
};


#endif // CIRCUIT_MANAGER_H
