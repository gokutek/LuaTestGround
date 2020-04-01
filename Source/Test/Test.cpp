#include <iostream>

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
}

int main()
{
	lua_State* L = luaL_newstate();
	lua_close(L);
	return 0;
}
