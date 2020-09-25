extern "C"
{
#include "lua.h"
#include "lauxlib.h"
}

static int lencode(lua_State *L) 
{
	lua_pushnumber(L, 666);
	lua_pushstring(L, "hello");
	return 2; // 返回值表示栈里有几个返回值
}

extern "C" LUAMOD_API int luaopen_MyExtension(lua_State *L) 
{
	luaL_checkversion(L);

	luaL_Reg l[] = {
		{ "encode", lencode },
		{ NULL,  NULL },
	};

	luaL_newlib(L, l);

	return 1;
}
