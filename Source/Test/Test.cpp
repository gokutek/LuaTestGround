#include <assert.h>
#include <numeric>
#include <limits>
#include <stdint.h>
#include <iostream>

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
}

class UImage
{
public:
	int SetImage(const char* str)
	{
		std::cout << str << std::endl;
		return 0;
	}
};


static int pmain(lua_State *L)
{
	int argc = (int)lua_tointeger(L, 1);
	char **argv = (char **)lua_touserdata(L, 2);
	lua_pushinteger(L, std::numeric_limits<int64_t>::max());
	return 1;
}


int main(int argc, char** argv)
{
	lua_State *L = luaL_newstate();
	if (nullptr == L) 
	{
		return EXIT_FAILURE;
	}

	lua_pushcfunction(L, &pmain);  /* to call 'pmain' in protected mode */
	lua_pushinteger(L, argc);  /* 1st argument */
	lua_pushlightuserdata(L, argv); /* 2nd argument */
	int status = lua_pcall(L, 2, 1, 0);  /* do the call */
	int result = lua_toboolean(L, -1);  /* get result */

	int64_t exp = std::numeric_limits<int64_t>::max();
	int64_t x = lua_tointeger(L, 1);
	assert(x == exp);

	UImage* Image = new UImage();


	lua_close(L);
	return (result && status == LUA_OK) ? EXIT_SUCCESS : EXIT_FAILURE;
}
