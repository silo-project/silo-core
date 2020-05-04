//
// Created by penta on 2020-05-03.
//

#include <iostream>

#include "fileloader.h"
#include "circuit.h"
#include "library.h"
#include "typeinfo"

AbstractCircuit* FileLoader::tccAbstract(const char* lib, const char* name) {
    std::cout << "LOADING TCC LIBRARY " << lib << " " << name << std::endl;

    LibraryManager lm;

    if(lm.hasLibrary(lib)) {
        if(typeid(lm.getLibrary(lib)) != typeid(Library*)) {
            lm.deleteLibrary(lib);
            std::cout << "DELETING NOT TCC LIBRARY " << lib << std::endl;
        } else return lm.getLibrary(lib)->getAbstractCircuit(name);
    }

    lm.registerLibrary(new TccLibrary(lib), lib);
    Library* l = lm.getLibrary(lib);
    return l->getAbstractCircuit(name);
}