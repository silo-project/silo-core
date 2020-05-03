//
// Created by penta on 2020-05-02.
//

#include <lua.hpp>

#include "executor.h"

/*LuaExecutor::LuaExecutor(const char* scriptfile) {
    L = luaL_newstate();
    luaL_openlibs(L);
    int status = luaL_loadfile(L, scriptfile);
    if (status) {
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
    }
}

LuaExecutor::~LuaExecutor() {
    lua_close(L);
}

void LuaExecutor::execute(AbstractNode* abstractNode) {
    lua_newtable(L);

    // TODO LUA API

    int result = lua_pcall(L, 0, LUA_MULTRET, 0);

    if (result) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    printf("Script returned: %.0f\n", lua_tonumber(L, -1));
}*/

void Executor::execute(AbstractNode *) { }

void LuaExecutor::setLuaFile(const char *_luafile) {
    luafile = _luafile;
}
