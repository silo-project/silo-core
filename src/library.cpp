//
// Created by penta on 2020-05-02.
//

#include "library.h"
#include <map>
#include <cstdint>
#include <cstring>
#include <iostream>

#include "Crc32.h"

#include "libtcc.h"

#include "executor.h"

/*extern "C" {
#include <cstdio>

TccLibrary* workinglib = NULL;

static int registerAbstractCircuitExecutor(lua_State *L) {
    //puts("registerAbstractCircuitExecutor()");
    AbstractCircuit *ac = new AbstractCircuit();

    const char *luaexecutorfuncname = lua_tostring(L, 2);

    ac->executor = new LuaExecutor(workinglib, luaexecutorfuncname);
    workinglib->registerAbstractCircuit(ac, lua_tostring(L, 1));
    //lua_settop(L, 0);
    return 0;
}
int registerAbstractCircuitExecutor(const char* partname, const char* funcname) {
    AbstractCircuit *ac = new AbstractCircuit();

    ac->executor = new LuaExecutor(workinglib, funcname);
    workinglib->registerAbstractCircuit(ac, partname);
}
}*/

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
};

TccLibrary::TccLibrary(const char *_tccfile) {
    tccfile = _tccfile;
}

TccLibrary::~TccLibrary() {

}
