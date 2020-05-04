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
    Library* l = nullptr;

    if(lm.hasLibrary(lib)) {
        if(typeid(lm.getLibrary(lib)) != typeid(Library*)) lm.deleteLibrary(lib);
        else l = lm.getLibrary(lib);
    } else {
        switch (lib[1]) {
            case 'W':
                if (strcmp(lib, "#Wiring")) break;
                l = new TccLibrary("wiring.c");
                break;
            case 'G':
                if (strcmp(lib, "#Gates")) break;
                l = new TccLibrary("gates.c");
                break;
            case 'P':
                if (strcmp(lib, "#Plexers")) break;
                l = new TccLibrary("plexers.c");
                break;
            case 'A':
                if (strcmp(lib, "#Arithmetic")) break;
                l = new TccLibrary("arithmetic.c");
                break;
            case 'M':
                if (strcmp(lib, "#Memory")) break;
                l = new TccLibrary("memory.c");
                break;
            case 'I':
                if (strcmp(lib, "#I/O")) break;
                l = new TccLibrary("iando.c");
                break;
            case 'B':
                if (strcmp(lib, "#Base")) break;
                l = new TccLibrary("base.c");
                break;
            default:
                std::cout << "UNKNOWN LOCAL LIBRARY" << std::endl;
                return nullptr;
        }
        std::cout << "LOADING LOCAL LIBRARY " << lib << " " << name << std::endl;
        lm.registerLibrary(l, lib);
    }

    return l->getAbstractCircuit(name);
}