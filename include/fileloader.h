//
// Created by penta on 2020-05-01.
//

#ifndef SILO_CORE_FILELOADER_H
#define SILO_CORE_FILELOADER_H

#include <string>
#include "tinyxml2.h"
#include "circuit.h"

namespace FileLoader {
    Circuit* logisim(const char* file, const char* name);   // Get "name" in "file"
    Circuit* logisim(const char* file);                     // Get MainCircuit in "file"
    Circuit* logisim(tinyxml2::XMLNode* project, const char* name);   // Get "name" in the XML
    AbstractCircuit* logisimAbstract(const char* file, const char* name);   // Get "name" in "file"
    AbstractCircuit* logisimAbstract(tinyxml2::XMLNode* project, const char* name);   // Get "name" in the XML
    AbstractCircuit* luaAbstract(const char* file, const char* name);
}

#endif //SILO_CORE_FILELOADER_H
