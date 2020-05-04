//
// Created by penta on 2020-05-03.
//

#include <iostream>

#include "library.h"
#include "fileloader.h"
#include "circuit.h"

using namespace FileLoader;

AbstractCircuit* FileLoader::localAbstract(const char* lib, const char* name) {
    LibraryManager lm;

    if(lm.hasLibrary(lib)) {
        if(lm.getLibrary(lib)->getAbstractCircuit(name)->executor == nullptr) lm.deleteLibrary(lib);
    }

    std::cout << "LOADING LOCAL LIBRARY " << lib << " " << name << std::endl;

    switch (lib[1]) {
        case 'W':
            if (strcmp(lib, "#Wiring")) break;
            lm.registerLibrary(new TccLibrary("wiring.c"), lib);
        case 'G':
            if (strcmp(lib, "#Gates")) break;
            lm.registerLibrary(new TccLibrary("gates.c"), lib);
        case 'P':
            if (strcmp(lib, "#Plexers")) break;
            lm.registerLibrary(new TccLibrary("plexers.c"), lib);
        case 'A':
            if (strcmp(lib, "#Arithmetic")) break;
            lm.registerLibrary(new TccLibrary("arithmetic.c"), lib);
        case 'M':
            if (strcmp(lib, "#Memory")) break;
            lm.registerLibrary(new TccLibrary("memory.c"), lib);
        case 'I':
            if (strcmp(lib, "#I/O")) break;
            lm.registerLibrary(new TccLibrary("iando.c"), lib);
        case 'B':
            if (strcmp(lib, "#Base")) break;
            lm.registerLibrary(new TccLibrary("base.c"), lib);
    }

    return lm.getLibrary(lib)->getAbstractCircuit(name);
}