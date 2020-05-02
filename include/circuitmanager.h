//
// Created by penta on 2020-05-02.
//

#ifndef SILO_CORE_CIRCUITMANAGER_H
#define SILO_CORE_CIRCUITMANAGER_H

#include "circuit.h"
#include <map>
#include <string>

#define ABSTRACTCIRCUITMANAGER_CALCULATECRC(x, y) (static_cast<uint64_t>(static_cast<uint64_t>(crc32_1byte_tableless((x), strlen(x))) << 32 | crc32_1byte_tableless((y), strlen(y))))

class AbstractCircuitManager {
protected:
    static std::map<uint64_t, AbstractCircuit*>* abstractCircuitMap;

public:
    std::map<uint64_t, AbstractCircuit*>* getAbstractCircuitMapPtr();
    AbstractCircuit* getAbstractCircuit(const char* libname, const char* circname);
    bool hasAbstractCircuit(const char *libname, const char *circname);
    void registerAbstractCircuit(AbstractCircuit* abstractCircuit, const char* libname, const char* circname);
    AbstractCircuitManager();
};


#endif //SILO_CORE_CIRCUITMANAGER_H
