#include <string.h>
#include <windows.h>
#include "lua.hpp"

/**
 * Create weak value table
 */
static void CreateWeakValueTable(lua_State* L)
{
    lua_newtable(L);
    lua_newtable(L);
    lua_pushstring(L, "__mode");
    lua_pushstring(L, "v");
    lua_rawset(L, -3);
    lua_setmetatable(L, -2);
}

static void AddPackagePath(lua_State* L, const char* Path)
{
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "path");
	char FinalPath[MAX_PATH];
	sprintf_s(FinalPath, "%s;%s", lua_tostring(L, -1), Path);
	lua_pushstring(L, FinalPath);
	lua_setfield(L, -3, "path");
	lua_pop(L, 2);
}

static void FLuaContext_CreateState()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushstring(L, "ObjectMap");                             // create weak table 'ObjectMap'
	CreateWeakValueTable(L);
	lua_rawset(L, LUA_REGISTRYINDEX);

	lua_pushstring(L, "StructMap");                             // create weak table 'StructMap'
	CreateWeakValueTable(L);
	lua_rawset(L, LUA_REGISTRYINDEX);

	lua_pushstring(L, "ScriptContainerMap");                    // create weak table 'ScriptContainerMap'
	CreateWeakValueTable(L);
	lua_rawset(L, LUA_REGISTRYINDEX);

	lua_pushstring(L, "ArrayMap");                              // create weak table 'ArrayMap'
	CreateWeakValueTable(L);
	lua_rawset(L, LUA_REGISTRYINDEX);

	// add new package path
	AddPackagePath(L, "../Script/?.lua");
}

void test_unlua_main()
{
	FLuaContext_CreateState();
}
