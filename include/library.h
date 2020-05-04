//
// Created by penta on 2020-05-02.
//

#ifndef CIRCUIT_MANAGER_H
#define CIRCUIT_MANAGER_H

#include "circuit.h"
#include <map>
#include <string>

extern "C" {
#include "libtcc.h"
}

class Library {
protected:
    std::map<uint32_t, AbstractCircuit*>* abstractCircuitMap;

public:
    std::map<uint32_t, AbstractCircuit*>* getAbstractCircuitMapPtr();
    AbstractCircuit* getAbstractCircuit(const char* circname);
    bool hasAbstractCircuit(const char* circname);
    void registerAbstractCircuit(AbstractCircuit* abstractCircuit, const char* circname);
    Library();
};

class TccLibrary : public Library {
protected:
    const char* tccfile;
    TCCState* s;

public:
    TccLibrary(const char* _tccfile);
    ~TccLibrary();

private:
    TccLibrary();
};

class LibraryManager {
protected:
    static std::map<uint32_t, Library*>* libraryMap;

public:
    std::map<uint32_t, Library*>* getLibraryMapPtr();
    Library* getLibrary(const char* libname);
    bool hasLibrary(const char* libname);
    void registerLibrary(Library* Library, const char* libname);
    void deleteLibrary(const char* libname);
    LibraryManager();
};

#endif // CIRCUIT_MANAGER_H
