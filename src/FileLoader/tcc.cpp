//
// Created by penta on 2020-05-03.
//

#include <iostream>

#include "fileloader.h"
#include "circuit.h"
#include "library.h"
#include "typeinfo"

AbstractCircuit* FileLoader::tccAbstract(const char* lib, const char* name) {
    LibraryManager lm;
    if(lm.hasLibrary(lib)) {
        if(lm.getLibrary(lib)->getAbstractCircuit(name)->executor == nullptr) lm.deleteLibrary(lib);
    }
    lm.registerLibrary(new TccLibrary(lib), lib);
    Library* l = lm.getLibrary(lib);
    return l->getAbstractCircuit(name);
}