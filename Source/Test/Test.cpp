﻿#include <assert.h>
#include <numeric>
#include <limits>
#include <stdint.h>
#include <iostream>
#include <windows.h>
#include "lua.hpp"

static void test_lua_type()
{
	lua_State* L = luaL_newstate();

	// 虽然可以向栈中放integer和number，但它们的类型都是LUA_TNUMBER
	lua_pushinteger(L, 1);
	int type = lua_type(L, -1);
	assert(type == LUA_TNUMBER);

	lua_pushnumber(L, 1.23);
	type = lua_type(L, -1);
	assert(type == LUA_TNUMBER);

	lua_close(L);
}

static int pmain(lua_State *L)
{
	int argc = (int)lua_tointeger(L, 1);
	char **argv = (char **)lua_touserdata(L, 2);
	lua_pushinteger(L, 0);
	return 1;
}

int main(int argc, char** argv)
{
	test_lua_type();

	wchar_t szWorkDir[MAX_PATH] = { 0 };
	GetModuleFileNameW(NULL, szWorkDir, sizeof(szWorkDir));
	*wcsrchr(szWorkDir, '\\') = 0;
	SetCurrentDirectoryW(szWorkDir);

	lua_State *L = luaL_newstate();
	lua_pushcfunction(L, &pmain);  /* to call 'pmain' in protected mode */
	lua_pushinteger(L, argc);  /* 1st argument */
	lua_pushlightuserdata(L, argv); /* 2nd argument */
	int status = lua_pcall(L, 2, 1, 0);  /* do the call */
	int result = lua_toboolean(L, -1);  /* get result */

	lua_Integer x = lua_tointeger(L, 1);
	assert(x == 0);

	lua_close(L);
	return EXIT_SUCCESS;
} 


/*
===============================================================================
测试用例1：
Lua作为宿主，在lua中可以使用C++对象Image
```
local img = Image.new()
img:method()
img = nil
```

测试用例2：
C++作为宿主，在C++中调用Lua函数：
```
call("x.lua", "method", x, y);
```

x.Lua:
```
function method(self, x, y)
end
```
===============================================================================
*/
