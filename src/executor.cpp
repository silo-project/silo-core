//
// Created by penta on 2020-05-02.
//

#include <lua.hpp>

#include "executor.h"

LuaExecutor::LuaExecutor(LuaLibrary* _library, const char* _executorname) {
    library = _library;
    executorname = _executorname;
}

void LuaExecutor::execute(AbstractNode* abstractNode) {
    library->L;
}

void Executor::execute(AbstractNode *) { }
