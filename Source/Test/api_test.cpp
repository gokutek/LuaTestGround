#include <assert.h>
#include <string.h>
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

	lua_pushstring(L, "1.23");
	type = lua_type(L, -1);
	assert(type == LUA_TSTRING);

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

static void test_table()
{
	lua_State* L = luaL_newstate();
	
	lua_newtable(L);				// 1
	lua_pushstring(L, "key");		// 2
	lua_pushstring(L, "value");		// 3
	lua_settable(L, -3);			// 1
	assert(lua_gettop(L) == 1);

	lua_pushstring(L, "key");		// 2
	lua_gettable(L, -2);			// 2
	const char* value = lua_tostring(L, -1);
	assert(!strcmp(value, "value"));

	lua_close(L);
}

static void add_package_path(lua_State* L, const char* path)
{
	assert(path);
	lua_getglobal(L, "package");	// [-0, +1, e]
	lua_getfield(L, -1, "path");	// [-0, +1, e]
	char final_path[1024];
	sprintf_s(final_path, "%s;%s", lua_tostring(L, -1), path);
	lua_pushstring(L, final_path);	// [-0, +1, m]
	lua_setfield(L, -3, "path");	// [-1, +0, e]
	lua_pop(L, 2);
}

static void test_print()
{
	int result;
	lua_State* L = luaL_newstate();
	luaL_openlibs(L); // 不打开标准库的话，print都调用不了
	add_package_path(L, "../Script/?.lua");
	result = luaL_loadfile(L, "../Script/api_test_loadfile.lua");
	assert(result == 0);
	lua_pcall(L, 0, LUA_MULTRET, 0);
 	lua_close(L);
}

void api_test_main()
{
	test_lua_type();
	test_lua_rotate();
	test_lua_is_number();
	test_lua_tonumber();
	test_table();
	test_print();
}

/*
===============================================================================
http://www.lua.org/manual/5.4/
API后面的[-o, +p, x]意思：
The first field, o, is how many elements the function pops from the stack.
The second field, p, is how many elements the function pushes onto the stack. 
(Any function always pushes its results after popping its arguments.) A field 
in the form x|y means the function can push (or pop) x or y elements, depending 
on the situation; an interrogation mark '?' means that we cannot know how many 
elements the function pops/pushes by looking only at its arguments. (For instance, 
they may depend on what is in the stack.) The third field, x, tells whether the 
function may raise errors: '-' means the function never raises any error; 'm' 
means the function may raise only out-of-memory errors; 'v' means the function 
may raise the errors explained in the text; 'e' means the function can run 
arbitrary Lua code, either directly or through metamethods, and therefore may 
raise any errors.
===============================================================================
*/
