//
// Created by penta on 2020-05-02.
//

#include "library.h"
#include <map>
#include <cstdint>
#include <cstring>
#include <iostream>

#include "Crc32.h"

#include "executor.h"

extern "C" {
#include <cstdio>

LuaLibrary* workinglib = NULL;

static int registerAbstractCircuitExecutor(lua_State *L) {
    puts("registerAbstractCircuitExecutor()");
    AbstractCircuit *ac = new AbstractCircuit();

    const char *luaexecutorfuncname = lua_tostring(L, 2);

    ac->executor = new LuaExecutor(workinglib, luaexecutorfuncname);
    workinglib->registerAbstractCircuit(ac, lua_tostring(L, 1));
    lua_settop(L, 2);
    return 0;
}/*
int registerAbstractCircuitExecutor(const char* partname, const char* funcname) {
    AbstractCircuit *ac = new AbstractCircuit();

    ac->executor = new LuaExecutor(workinglib, funcname);
    workinglib->registerAbstractCircuit(ac, partname);
}*/
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


std::map<uint32_t, AbstractCircuit*>* Library::abstractCircuitMap = nullptr;

/*auto Library::calculateCrc(const char* x) {
    return static_cast<uint64_t>(crc32_1byte_tableless(x, strlen(x))) << 32 | crc32_1byte_tableless(y, strlen(y));
}*/

Library::Library() {
    if(abstractCircuitMap == nullptr)
        abstractCircuitMap = new std::map<uint32_t, AbstractCircuit*>();
}

std::map<uint32_t, AbstractCircuit*>* Library::getAbstractCircuitMapPtr() {
    return abstractCircuitMap;
}

bool Library::hasAbstractCircuit(const char* circname) {
    return abstractCircuitMap->find(crc32_1byte_tableless(circname, strlen(circname))) != abstractCircuitMap->end();
}

AbstractCircuit* Library::getAbstractCircuit(const char *circname) {
    return abstractCircuitMap->at(crc32_1byte_tableless(circname, strlen(circname)));
}

void Library::registerAbstractCircuit(AbstractCircuit* abstractCircuit, const char *circname) {
    abstractCircuitMap->insert(std::pair<uint64_t, AbstractCircuit*>(crc32_1byte_tableless(circname, strlen(circname)), abstractCircuit));
};

LuaLibrary::LuaLibrary(const char *_luafile) {
    luafile = _luafile;
    this->L = lua_open();
    luaL_openlibs(this->L);

    lua_pushcclosure(this->L, registerAbstractCircuitExecutor, 0);
    lua_setglobal(this->L, "registerAbstractCircuit");

    luaL_dofile(this->L, luafile);

    workinglib = this;

    lua_getglobal(this->L, "regAbstractCircuit");

    lua_call(this->L, 0, 1);
    std::cout << lua_tointeger(this->L, -1) << std::endl;
}

LuaLibrary::~LuaLibrary() {
    lua_close(this->L);
}
