//
// Created by penta on 2020-05-03.
//

#include <iostream>
#include <cstring>
#include <iostream>

#include "tinyxml2.h"

#include "fileloader.h"
#include "circuit.h"
#include "library.h"

using namespace tinyxml2;

AbstractCircuit* FileLoader::loadAbstract(const char* lib, const char* name) {
    if(!strlen(lib)) return nullptr;
    LibraryManager lm;

    if(lm.hasLibrary(lib)) {
        Library* l = lm.getLibrary(lib);
        if(l->hasAbstractCircuit(name)) return l->getAbstractCircuit(name);
    }

    if(memcmp(lib, "file#", 5) == 0) {
        XMLDocument doc;
        if (doc.LoadFile(static_cast<const char *>(lib + 5)) != XML_SUCCESS) {
            std::cout << "fileloader.cpp:29 Unable to load XML " << lib + 5 << std::endl;
            return nullptr;
        } else std::cout << "fileloader.cpp:31 XML Loaded " << lib + 5 << std::endl;
        Library *l = new Library();
        lm.registerLibrary(l, lib);
        l->registerAbstractCircuit(logisimAbstract(doc.FirstChild()->NextSibling(), lib, name), name);
        return l->getAbstractCircuit(name);
    }

    if(lib[0] == '#')
        return localAbstract(lib, name);

    if(memcmp(lib, "tcc#", 4) == 0)
        return tccAbstract(lib, name);

    std::cout << "fileloader.cpp:44 Unknown Tag " << lib << std::endl;
    return nullptr;
}