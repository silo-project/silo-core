//
// Created by penta on 2020-05-03.
//

#include "fileloader.h"
#include "circuit.h"

using namespace FileLoader;

AbstractCircuit* FileLoader::localAbstract(const char* lib, const char* name) {
    switch (lib[1]) {
        case 'W':
            if (strcmp(lib, "#Wiring")) break;
            return luaAbstract("wiring.lua", name);
        case 'G':
            if (strcmp(lib, "#Gates")) break;
            return luaAbstract("gates.lua", name);
        case 'P':
            if (strcmp(lib, "#Plexers")) break;
            return luaAbstract("plexers.lua", name);
        case 'A':
            if (strcmp(lib, "#Arithmetic")) break;
            return luaAbstract("arithmetic.lua", name);
        case 'M':
            if (strcmp(lib, "#Memory")) break;
            return luaAbstract("memory.lua", name);
        case 'I':
            if (strcmp(lib, "#I/O")) break;
            return luaAbstract("iando.lua", name);
        case 'B':
            if (strcmp(lib, "#Base")) break;
            return luaAbstract("base.lua", name);
    }
}