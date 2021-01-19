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

static void test_lua_rotate()
{
	lua_State* L = luaL_newstate();

	/*
	==============================================================================
	Index: 1	2	3	4	5
	Stack: 10	20	30	40	50
	第二个参数表示从索引为3到栈顶之间的元素
	第三个参数1表示向栈顶方向旋转
	可以将这些元素想象成一个圆环，然后顺时针或逆时针旋转它。旋转之后为：10 20 50 30 40
	==============================================================================
	*/
	lua_pushinteger(L, 10);
	lua_pushinteger(L, 20);
	lua_pushinteger(L, 30);
	lua_pushinteger(L, 40);
	lua_pushinteger(L, 50);
	lua_rotate(L, 3, 1);
	assert(lua_tointeger(L, 1) == 10);
	assert(lua_tointeger(L, 2) == 20);
	assert(lua_tointeger(L, 3) == 50);
	assert(lua_tointeger(L, 4) == 30);
	assert(lua_tointeger(L, 5) == 40);

	/*
	==============================================================================
	Index: 1	2	3	4	5
	Stack: 10	20	30	40	50
	与上例的不同之处在于第三个参数是-1，表示向栈底方向旋转。
	旋转之后为：10 20 40 50 30
	==============================================================================
	*/
	lua_settop(L, 0);
	lua_pushinteger(L, 10);
	lua_pushinteger(L, 20);
	lua_pushinteger(L, 40);
	lua_pushinteger(L, 50);
	lua_pushinteger(L, 30);
	lua_rotate(L, 3, -1);

	lua_close(L);
}

static void test_lua_is_number()
{
	lua_State* L = luaL_newstate();

	lua_pushinteger(L, 10);
	assert(lua_isnumber(L, -1));
	assert(lua_isinteger(L, -1));

	// 这个字符串可以被转换为number，所以lua_isnumber仍然成立，奇怪的是lua_isinteger不成立
	lua_pushstring(L, "1234");
	assert(lua_isnumber(L, -1));
	assert(!lua_isinteger(L, -1));

	// 字符串不能转换为number
	lua_pushstring(L, "hello");
	assert(!lua_isnumber(L, -1));

	lua_close(L);
}

static void test_lua_tonumber()
{
	lua_State* L = luaL_newstate();

	lua_pushinteger(L, 10);
	lua_Number num = lua_tonumber(L, -1);
	assert(num == 10);

	lua_pushnumber(L, 12.34);
	num = lua_tonumber(L, -1);
	assert(num == 12.34);

	lua_pushstring(L, "4567");
	num = lua_tonumber(L, -1);
	assert(num == 4567);

	lua_pushstring(L, "67.89");
	num = lua_tonumber(L, -1);
	assert(num == 67.89);

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
	test_lua_rotate();
	test_lua_is_number();
	test_lua_tonumber();

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
