//
// Created by penta on 2020-05-02.
//

#include "library.h"
#include <map>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <fstream>

#include "Crc32.h"

#include "libtcc.h"

#include "executor.h"

extern "C" {
#include <cstdio>

TccLibrary* workinglib = nullptr;

static int TCC_registerAbstractCircuitExecutor(const char* compname, void(*executorPointer)(void* abstractNode)) {
    //puts("registerAbstractCircuitExecutor()");
    AbstractCircuit *ac = new AbstractCircuit();

    ac->executor = new TccExecutor(workinglib, reinterpret_cast<void (*)(AbstractNode *)>(executorPointer));
    workinglib->registerAbstractCircuit(ac, compname);
    //lua_settop(L, 0);
    return 0;
}
}

std::map<uint32_t, Library*>* LibraryManager::libraryMap = nullptr;

LibraryManager::LibraryManager() {
    if(libraryMap == nullptr)
        libraryMap = new std::map<uint32_t, Library*>();
};

std::map<uint32_t, Library*>* LibraryManager::getLibraryMapPtr() {
    return libraryMap;
}

bool LibraryManager::hasLibrary(const char* libname) {
    return libraryMap->find(crc32_1byte_tableless(libname, strlen(libname))) != libraryMap->end();
}

Library* LibraryManager::getLibrary(const char* libname) {
    return libraryMap->at(crc32_1byte_tableless(libname, strlen(libname)));
}

void LibraryManager::registerLibrary(Library* library, const char* libname) {
    libraryMap->insert(std::pair<uint32_t, Library*>(crc32_1byte_tableless(libname, strlen(libname)), library));
};

void LibraryManager::deleteLibrary(const char* libname) {
    libraryMap->erase(crc32_1byte_tableless(libname, strlen(libname)));
};

/*auto Library::calculateCrc(const char* x) {
    return static_cast<uint64_t>(crc32_1byte_tableless(x, strlen(x))) << 32 | crc32_1byte_tableless(y, strlen(y));
}*/

Library::Library() {
    abstractCircuitMap = new std::map<uint32_t, AbstractCircuit*>();
}

std::map<uint32_t, AbstractCircuit*>* Library::getAbstractCircuitMapPtr() {
    return abstractCircuitMap;
}

bool Library::hasAbstractCircuit(const char* circname) {
    return abstractCircuitMap->find(crc32_1byte_tableless(circname, strlen(circname))) != abstractCircuitMap->end();
}

AbstractCircuit* Library::getAbstractCircuit(const char *circname) {
    if(!hasAbstractCircuit(circname)) {
        std::cout << "No Circuit " << circname << std::endl;
        return nullptr;
    }
    return abstractCircuitMap->at(crc32_1byte_tableless(circname, strlen(circname)));
}

void Library::registerAbstractCircuit(AbstractCircuit* abstractCircuit, const char *circname) {
    std::cout << "Register Circuit " << circname << std::endl;
    abstractCircuitMap->insert(std::pair<uint32_t, AbstractCircuit*>(crc32_1byte_tableless(circname, strlen(circname)), abstractCircuit));
}

//TCCState* TccLibrary::s;

TccLibrary::TccLibrary(const char *_tccfile) {
    while(workinglib) {};
    workinglib = this;

    tccfile = _tccfile;
    std::cout << "INIT TCC LIBRARY " << tccfile << std::endl;
    s = tcc_new();
    if(!s) std::cout << "Can’t create a TCC context" << std::endl;
    else std::cout << "TCC context Created" << std::endl;
    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);

    if (tcc_add_file(s, tccfile) > 0) {
        std::cout << "Compilation error !" << std::endl;
    }

    std::cout << "FILEREADY TCC LIBRARY " << tccfile << std::endl;

    tcc_add_symbol(s, "TCC_registerAbstractCircuitExecutor", reinterpret_cast<void*>(TCC_registerAbstractCircuitExecutor));

    tcc_relocate(s, TCC_RELOCATE_AUTO);

    void* onload = tcc_get_symbol(s, "onLoad");

    if(!onload) {
        std::cout << "NO onLoad()" << std::endl;
    }

    (reinterpret_cast<int(*)()>(onload))();
    std::cout << "LOADED TCC LIBRARY " << tccfile << std::endl;

    tcc_delete(s);
    workinglib = nullptr;
}

TccLibrary::~TccLibrary() {

}
