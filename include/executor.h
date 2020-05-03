//
// Created by penta on 2020-05-02.
//

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <lua.hpp>

#include "node.h"

class Executor {
public:
    virtual void execute(AbstractNode*);
};

class LuaExecutor : public Executor {
public:
    LuaExecutor();
    ~LuaExecutor();
    void setLuaFile(const char* _luafile);
    void execute(AbstractNode* abstractNode);

public:
    lua_State* L;

protected:
    const char* luafile;
};

#endif // EXECUTOR_H
