//
// Created by penta on 2020-05-02.
//

#include "library.h"
#include <map>
#include <cstdint>
#include <cstring>

#include "Crc32.h"

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

    int res = luaL_dofile(this->L, luafile );

    lua_register(this->L, "registerAbstractCircuitExecutor", this->registerAbstractCircuitExecutor);

    lua_getglobal(this->L, "regAbstractCircuit" );
    lua_pushnumber(this->L, 30 );

    lua_pushnumber(this->L, 100 );

    lua_call(this->L, 2, 1 );

    int num = lua_tointeger(this->L, lua_gettop(L) );
}

LuaLibrary::~LuaLibrary() {
    lua_close(this->L);
}