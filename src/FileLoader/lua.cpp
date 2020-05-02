//
// Created by penta on 2020-05-02.
//

#include <lua.hpp>

#include "fileloader.h"
#include "circuit.h"

AbstractCircuit* FileLoader::luaAbstract(const char* file, const char* name) {
    lua_State *L;
}