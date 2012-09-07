#include <pspkernel.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeMath.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE Math", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD(); 

static int lua_pgeMathAtan(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.atan(value) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathAtan(x));
	
	return 1;
}

static int lua_pgeMathAtan2(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.math.atan2(y, x) takes two arguments.");
	
	float y = luaL_checknumber(L, 1);
	
	float x = luaL_checknumber(L, 2);
	
	lua_pushnumber(L, pgeMathAtan2(y, x));
	
	return 1;
}

static int lua_pgeMathCos(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.cos(radians) takes one argument.");
	
	float radians = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathCos(radians));
	
	return 1;
}

static int lua_pgeMathSin(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.sin(radians) takes one argument.");
	
	float radians = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathSin(radians));
	
	return 1;
}

static int lua_pgeMathAcos(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.acos(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathAcos(x));
	
	return 1;
}

static int lua_pgeMathAsin(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.asin(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathAsin(x));
	
	return 1;
}

static int lua_pgeMathCosh(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.cosh(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathCosh(x));
	
	return 1;
}

static int lua_pgeMathExp(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.exp(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathExp(x));
	
	return 1;
}

static int lua_pgeMathFmax(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.math.fmax(x, y) takes two arguments.");
	
	float x = luaL_checknumber(L, 1);
	
	float y = luaL_checknumber(L, 2);
	
	lua_pushnumber(L, pgeMathFmax(x, y));
	
	return 1;
}

static int lua_pgeMathFmin(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.math.fmin(x, y) takes two arguments.");
	
	float x = luaL_checknumber(L, 1);
	
	float y = luaL_checknumber(L, 2);
	
	lua_pushnumber(L, pgeMathFmin(x, y));
	
	return 1;
}

static int lua_pgeMathFmod(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.math.fmod(x, y) takes two arguments.");
	
	float x = luaL_checknumber(L, 1);
	
	float y = luaL_checknumber(L, 2);
	
	lua_pushnumber(L, pgeMathFmod(x, y));
	
	return 1;
}

static int lua_pgeMathLog(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.log(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathLog(x));
	
	return 1;
}

static int lua_pgeMathPow(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.math.pow(x, y) takes two arguments.");
	
	float x = luaL_checknumber(L, 1);
	
	float y = luaL_checknumber(L, 2);
	
	lua_pushnumber(L, pgeMathPow(x, y));
	
	return 1;
}

static int lua_pgeMathSrand(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.srand(seed) takes one argument.");
	
	unsigned int seed = luaL_checkint(L, 1);
	
	pgeMathSrand(seed);
	
	return 0;
}

static int lua_pgeMathRandFloat(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.math.randfloat(min, max) takes two arguments.");
	
	float min = luaL_checknumber(L, 1);
	
	float max = luaL_checknumber(L, 2);
	
	lua_pushnumber(L, pgeMathRandFloat(min, max));
	
	return 1;
}

static int lua_pgeMathSinCos(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.sincos(radians) takes one argument.");
	
	float radians = luaL_checknumber(L, 1);
	
	float sin = 0.0f;
	
	float cos = 0.0f;
	
	pgeMathSincos(radians, &sin, &cos);
	
	lua_pushnumber(L, sin);
	
	lua_pushnumber(L, cos);
	
	return 2;
}

static int lua_pgeMathSinh(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.sinh(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathSinh(x));
	
	return 1;
}

static int lua_pgeMathTan(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.tan(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathTan(x));
	
	return 1;
}

static int lua_pgeMathTanh(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.tanh(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathTanh(x));
	
	return 1;
}

static int lua_pgeMathSqrt(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.sqrt(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathSqrt(x));
	
	return 1;
}

static int lua_pgeMathRandInt(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.math.randint(min, max) takes two arguments.");
	
	float min = luaL_checknumber(L, 1);
	
	float max = luaL_checknumber(L, 2);
	
	lua_pushinteger(L, pgeMathRandInt(min, max));
	
	return 1;
}

static int lua_pgeMathAbs(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.abs(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathAbs(x));
	
	return 1;
}

static int lua_pgeMathCeil(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.ceil(value) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathCeil(x));
	
	return 1;
}

static int lua_pgeMathFloor(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.floor(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathFloor(x));
	
	return 1;
}

static int lua_pgeMathLog2(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.log2(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathLog2(x));
	
	return 1;
}

static int lua_pgeMathLog10(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.log10(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathLog10(x));
	
	return 1;
}

static int lua_pgeMathPow2(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.pow2(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathPow2(x));
	
	return 1;
}

static int lua_pgeMathRound(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.round(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathRound(x));
	
	return 1;
}

static int lua_pgeMathTrunc(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.trunc(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathTrunc(x));
	
	return 1;
}

static int lua_pgeMathInvSqrt(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.invsqrt(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathInvSqrt(x));
	
	return 1;
}

static int lua_pgeMathDegToRad(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.rad(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathDegToRad(x));
	
	return 1;
}

static int lua_pgeMathRadToDeg(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.math.deg(x) takes one argument.");
	
	float x = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, pgeMathRadToDeg(x));
	
	return 1;
}

static const luaL_reg lua_pgeMath_functions[] =
{
	{"atan",		lua_pgeMathAtan},
	{"atan2",		lua_pgeMathAtan2},
	{"cos",			lua_pgeMathCos},
	{"sin",			lua_pgeMathSin},
	{"acos",		lua_pgeMathAcos},
	{"asin",		lua_pgeMathAsin},
	{"cosh",		lua_pgeMathCosh},
	{"exp",			lua_pgeMathExp},
	{"fmax",		lua_pgeMathFmax},
	{"fmin",		lua_pgeMathFmin},
	{"fmod",		lua_pgeMathFmod},
	{"log",			lua_pgeMathLog},
	{"pow",			lua_pgeMathPow},
	{"srand",		lua_pgeMathSrand},
	{"randfloat",	lua_pgeMathRandFloat},
	{"sinh",		lua_pgeMathSinh},
	{"tan",			lua_pgeMathTan},
	{"tanh",		lua_pgeMathTanh},
	{"sqrt",		lua_pgeMathSqrt},
	{"sincos",		lua_pgeMathSinCos},
	{"randint",		lua_pgeMathRandInt},
	{"abs",			lua_pgeMathAbs},
	{"ceil",		lua_pgeMathCeil},
	{"floor",		lua_pgeMathFloor},
	{"log2",		lua_pgeMathLog2},
	{"log10",		lua_pgeMathLog10},
	{"pow2",		lua_pgeMathPow2},
	{"invsqrt",		lua_pgeMathInvSqrt},
	{"round",		lua_pgeMathRound},
	{"trunc",		lua_pgeMathTrunc},
	{"deg",			lua_pgeMathRadToDeg},
	{"rad",			lua_pgeMathDegToRad},
	{0, 0}
};

void lua_pgeMath_init(lua_State *L)
{	
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeMath_functions);
	lua_setfield(L, -2, "math"); /* pge */
	lua_pop(L, 1);	
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
	
	lua_State *L = pgeLuaGetState();
	
	lua_pgeMath_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
