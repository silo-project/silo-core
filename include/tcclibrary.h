//
// Created by penta on 2020-05-06.
//

#ifndef SILO_CORE_TCCLIBRARY_H
#define SILO_CORE_TCCLIBRARY_H

#include "library.h"
#include "libtcc.h"

class TccLibrary : public Library {
protected:
    const char* tccfile;
    TCCState* s;
    char* templibdir;

public:
    TccLibrary(const char* _tccfile);
    ~TccLibrary();

private:
    TccLibrary();
};

#endif //SILO_CORE_TCCLIBRARY_H
