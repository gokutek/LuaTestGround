#include <assert.h>
#include <string.h>
#include "lua.hpp"

static void test_lua_type()
{
	lua_State* L = luaL_newstate();

	// ��Ȼ������ջ�з�integer��number�������ǵ����Ͷ���LUA_TNUMBER
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
	�ڶ���������ʾ������Ϊ3��ջ��֮���Ԫ��
	����������1��ʾ��ջ��������ת
	���Խ���ЩԪ�������һ��Բ����Ȼ��˳ʱ�����ʱ����ת������ת֮��Ϊ��10 20 50 30 40
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
	�������Ĳ�֮ͬ�����ڵ�����������-1����ʾ��ջ�׷�����ת��
	��ת֮��Ϊ��10 20 40 50 30
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

	// ����ַ������Ա�ת��Ϊnumber������lua_isnumber��Ȼ��������ֵ���lua_isinteger������
	lua_pushstring(L, "1234");
	assert(lua_isnumber(L, -1));
	assert(!lua_isinteger(L, -1));

	// �ַ�������ת��Ϊnumber
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
	luaL_openlibs(L); // ���򿪱�׼��Ļ���print�����ò���
	add_package_path(L, "../Script/?.lua");
	result = luaL_loadfile(L, "../Script/api_test_loadfile.lua");
	assert(result == 0);
	lua_pcall(L, 0, LUA_MULTRET, 0);
 	lua_close(L);
}

static void test_get_field()
{
	lua_State* L = luaL_newstate();
	lua_newtable(L);
	lua_pushstring(L, "world");
	lua_setfield(L, -2, "hello");	// [-1, +0, e]
	lua_getfield(L, -1, "hello");
	const char* value = lua_tostring(L, -1);
	assert(!strcmp(value, "world"));
	lua_close(L);
}

static void test_set_global()
{
	lua_State* L = luaL_newstate();
	lua_pushstring(L, "WORLD");
	lua_setglobal(L, "HELLO");	// [-1, +0, e]
	lua_getglobal(L, "HELLO"); // [-0, +1, e]
	const char* value = lua_tostring(L, -1);
	assert(!strcmp(value, "WORLD"));
	lua_close(L);
}

static void test_create_table()
{
	// lua_createtable�ڲ����Ż���ʵ����lua_newtable���Ǵ���Ĭ�ϲ�����lua_createtable
}

/** ����lua�ļ��ж����ȫ�ֺ��� */
static void test_call_lua()
{
	int result;
	lua_State* L = luaL_newstate();
	luaL_openlibs(L); // ���򿪱�׼��Ļ���print�����ò���
	add_package_path(L, "../Script/?.lua");

	result = luaL_loadfile(L, "../Script/api_test_call_lua.lua");	// [-0, +1, m]
	assert(result == 0);
	result = lua_pcall(L, 0, LUA_MULTRET, 0);	// [-(nargs + 1), +(nresults|1), �C]
	assert(result == LUA_OK);
	lua_getglobal(L, "mymath");
	lua_pushinteger(L, 30); // ����x
	lua_pushinteger(L, 12);	// ����y
	lua_pcall(L, 2, LUA_MULTRET, 0);
	lua_Integer sum = lua_tointeger(L, -2);
	lua_Integer diff = lua_tointeger(L, -1);
	assert(sum == 42);
	assert(diff == 18);
	lua_pop(L, 2); // ������ֵ��ջ
	lua_close(L);
}

/** ����require����lua�ļ� */
static void test_call_require()
{
	int result;
	lua_State* L = luaL_newstate();
	luaL_openlibs(L); // ���򿪱�׼��Ļ���print�����ò���
	add_package_path(L, "../Script/?.lua");

	lua_getglobal(L, "require");
	lua_pushstring(L, "api_test_call_lua");
	result = lua_pcall(L, 1, LUA_MULTRET, 0);	// [-(nargs + 1), +(nresults|1), �C]
	assert(result == LUA_OK);

	lua_getglobal(L, "mymath");
	lua_pushinteger(L, 30); // ����x
	lua_pushinteger(L, 12);	// ����y
	lua_pcall(L, 2, LUA_MULTRET, 0);
	lua_Integer sum = lua_tointeger(L, -2);
	lua_Integer diff = lua_tointeger(L, -1);
	assert(sum == 42);
	assert(diff == 18);
	lua_pop(L, 2); // ������ֵ��ջ
	lua_close(L);
}

static void test_newmetatable()
{
	lua_State* L = luaL_newstate();

	int ret = luaL_newmetatable(L, "ObjectMap");
	assert(1 == ret);
	lua_pop(L, 1);

	ret = luaL_newmetatable(L, "ObjectMap");
	assert(0 == ret);
	lua_pop(L, 1);

	lua_close(L);
}

static int TArray_New(lua_State* L)
{
	return 0;
}

static void test___call()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L); // ���򿪱�׼��Ļ���print�����ò���
	add_package_path(L, "../Script/?.lua");

	luaL_newmetatable(L, "TArray");
	lua_pushstring(L, "__call");
	lua_pushcfunction(L, TArray_New);
	lua_rawset(L, -3);

	int result = luaL_loadfile(L, "../Script/api_test___call.lua");	// [-0, +1, m]
	assert(result == 0);
	result = lua_pcall(L, 0, 0, 0);	// [-(nargs + 1), +(nresults|1), �C]
	assert(result == LUA_OK);

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
	test_get_field();
	test_set_global();
	test_create_table();
	test_call_lua();
	test_call_require();
	test_newmetatable();
	test___call();
}

/*
===============================================================================
http://www.lua.org/manual/5.4/
API�����[-o, +p, x]��˼��
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
