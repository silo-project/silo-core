//
// Created by penta on 2020-05-01.
//

#ifndef SILO_CORE_FILELOADER_H
#define SILO_CORE_FILELOADER_H

#include <string>
#include "tinyxml2.h"
#include "circuit.h"

namespace FileLoader {
    Circuit* logisim(const char*);
    Circuit *logisim(tinyxml2::XMLNode*);
}

#endif //SILO_CORE_FILELOADER_H
