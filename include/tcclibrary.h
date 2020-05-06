//
// Created by penta on 2020-05-06.
//

#ifndef SILO_CORE_TCCLIBRARY_H
#define SILO_CORE_TCCLIBRARY_H

#include "library.h"
#include "libtcc.h"

#include "tinyxml2.h"

class TccLibrary : public Library {
protected:
    const char* tccfile;
    TCCState* s;
    std::string templibdir;
    tinyxml2::XMLDocument* libinfo;

public:
    TccLibrary(const char* _tccfile);
    ~TccLibrary();

private:
    TccLibrary();
};

#endif //SILO_CORE_TCCLIBRARY_H
