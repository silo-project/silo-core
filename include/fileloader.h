//
// Created by penta on 2020-05-01.
//

#ifndef SILO_CORE_FILELOADER_H
#define SILO_CORE_FILELOADER_H

#include <string>
#include "tinyxml2.h"
#include "circuit.h"

namespace FileLoader {
    Circuit* logisim(tinyxml2::XMLNode* project, const char* name);                     // Get "name" in the XML
    AbstractCircuit* logisimAbstract(tinyxml2::XMLNode* project, const char* name);     // Get "name" in the XML
    AbstractCircuit* loadAbstract(const char* lib, const char* name);
    AbstractCircuit* localAbstract(const char* lib, const char* name);
    AbstractCircuit* luaAbstract(const char* lib, const char* name);
}

#endif //SILO_CORE_FILELOADER_H
