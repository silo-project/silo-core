//
// Created by penta on 2020-05-03.
//

#include <cstring>

#include "tinyxml2.h"

#include "fileloader.h"
#include "circuit.h"
#include "library.h"

using namespace tinyxml2;

AbstractCircuit* FileLoader::loadAbstract(const char* lib, const char* name) {
    if(!strlen(lib)) return nullptr;
    LibraryManager lm;
    if(!lm.hasLibrary(lib)) lm.registerLibrary(new Library(), lib);
    Library* l = lm.getLibrary(lib);
    if(l->hasAbstractCircuit(name)) return l->getAbstractCircuit(name);
    else if(memcmp(lib, "file#", 5) == 0) {
        XMLDocument doc;
        if(doc.LoadFile(static_cast<const char*>(lib + 5)) != XML_SUCCESS) return nullptr;
        return logisimAbstract(doc.FirstChild()->NextSibling(), name);
    } else if(lib[0] == '#') {
        return localAbstract(lib, name);
    } else if(memcmp(lib, "lua#", 4) == 0) {
        return luaAbstract(lib, name);
    }
}