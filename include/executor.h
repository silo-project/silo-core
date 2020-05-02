//
// Created by penta on 2020-05-02.
//

#ifndef SILO_CORE_EXECUTOR_H
#define SILO_CORE_EXECUTOR_H

#include "node.h"
#include "lua.hpp"

class Executor {
public:
    virtual void execute(AbstractNode*);
};

class LuaExecutor : public Executor {
public:
    LuaExecutor(const char* scriptfile);
    ~LuaExecutor();
    void execute(AbstractNode *abstractNode);

public:
    lua_State* L;
};

#endif //SILO_CORE_EXECUTOR_H
