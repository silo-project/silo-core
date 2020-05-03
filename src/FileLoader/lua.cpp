//
// Created by penta on 2020-05-03.
//

#include "fileloader.h"
#include "circuit.h"
#include "library.h"
#include "typeinfo"

AbstractCircuit* FileLoader::luaAbstract(const char* lib, const char* name) {
    LibraryManager lm;
    if(lm.hasLibrary(lib)) {
        if(typeid(*lm.getLibrary(lib)) != typeid(LuaLibrary)) lm.deleteLibrary(lib);
    } else lm.registerLibrary(new LuaLibrary(lib), lib);
    return lm.getLibrary(lib)->getAbstractCircuit(name);
}