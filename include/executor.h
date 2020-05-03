//
// Created by penta on 2020-05-02.
//

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <lua.hpp>

#include "node.h"
#include "library.h"

class Executor {
public:
    virtual void execute(AbstractNode*);
};

class LuaExecutor : public Executor {
public:
    LuaExecutor(LuaLibrary* _library, const char* _executorname);
    ~LuaExecutor();
    void execute(AbstractNode* abstractNode);

protected:
    const char* executorname;
    LuaLibrary* library;
};

#endif // EXECUTOR_H
