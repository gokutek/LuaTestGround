#include <assert.h>
#include <vector>
#include <string.h>
#include <stdint.h>
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
	char FinalPath[1024];
	sprintf_s(FinalPath, "%s;%s", lua_tostring(L, -1), Path);
	lua_pushstring(L, FinalPath);
	lua_setfield(L, -3, "path");
	lua_pop(L, 2);
}

static int TArray_New(lua_State* L)
{
	void* ud = lua_newuserdata(L, sizeof(std::vector<int64_t>));
	new(ud) std::vector<int64_t>();
	luaL_setmetatable(L, "TArray");
	return 1;
}

static int TArray_Add(lua_State* L)
{
	std::vector<int64_t>* vec = (std::vector<int64_t>*)lua_touserdata(L, -2);
	int64_t value = lua_tointeger(L, -1);
	vec->push_back(value);
	return 0;
}

static int TArray_Get(lua_State* L)
{
	std::vector<int64_t>* vec = (std::vector<int64_t>*)lua_touserdata(L, -2);
	int64_t index = lua_tointeger(L, -1);
	lua_pushinteger(L, vec->at(index));
	return 1;
}

static int TArray_Length(lua_State* L)
{
	std::vector<int64_t>* vec = (std::vector<int64_t>*)lua_touserdata(L, -1);
	lua_pushinteger(L, vec->size());
	return 1;
}

static int TArray_Delete(lua_State* L)
{
	return 0;
}

static void RegTarrayLib(lua_State* L)
{
	luaL_newmetatable(L, "TArray");

	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_rawset(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushvalue(L, -2);
	lua_rawset(L, -3);

	lua_pushvalue(L, -1);
	lua_setmetatable(L, -2);

	lua_pushstring(L, "__call");
	lua_pushcfunction(L, TArray_New);
	lua_rawset(L, -3);

	lua_pushstring(L, "Add");
	lua_pushcfunction(L, TArray_Add);
	lua_rawset(L, -3);

	lua_pushstring(L, "Get");
	lua_pushcfunction(L, TArray_Get);
	lua_rawset(L, -3);

	lua_pushstring(L, "Length");
	lua_pushcfunction(L, TArray_Length);
	lua_rawset(L, -3);

	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, TArray_Delete);
	lua_rawset(L, -3);

	lua_setglobal(L, "TArray");
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

	RegTarrayLib(L);

	int result = luaL_loadfile(L, "../Script/test_unlua.lua");	// [-0, +1, m]
	assert(result == 0);
	result = lua_pcall(L, 0, LUA_MULTRET, 0);	// [-(nargs + 1), +(nresults|1), ¨C]
	assert(result == LUA_OK);
}

void test_unlua_main()
{
	FLuaContext_CreateState();
}
