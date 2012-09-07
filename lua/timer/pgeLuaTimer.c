#include <pspkernel.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeTimer.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE Timer", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD(); 

pgeLuaCreateUserdataHandlers(pgeTimer, pgeTimer*)

static int lua_pgeTimerCreate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.timer.create() takes no arguments.");
		
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	pgeTimer *timer = pgeTimerCreate();
	
	if(!timer)
		return luaL_error(L, "Error: pge.timer.create(). Error creating timer.");
		
	pgeTimer **luatimer = pushpgeTimer(L);
	
	*luatimer = timer;
	
	return 1;
}

static int lua_pgeTimerUpdate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.timer.update(timer) takes one argument.");
		
	pgeTimer *timer = *topgeTimer(L, 1);
	
	pgeTimerUpdate(timer);
	
	return 0;
}

static int lua_pgeTimerGetDelta(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.timer.getdelta(timer) takes one argument.");
		
	pgeTimer *timer = *topgeTimer(L, 1);
	
	float delta = pgeTimerGetDeltaTime(timer);
	
	lua_pushnumber(L, delta);
	
	return 1;
}

static int lua_pgeTimerPeekDelta(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.timer.peekdelta(timer) takes one argument.");
		
	pgeTimer *timer = *topgeTimer(L, 1);
	
	float delta = pgeTimerPeekDeltaTime(timer);
	
	lua_pushnumber(L, delta);
	
	return 1;
}

static int lua_pgeTimerGetTotalTime(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.timer.totaltime(timer) takes one argument.");
		
	pgeTimer *timer = *topgeTimer(L, 1);
	
	float time = pgeTimerGetTotalTime(timer);
	
	lua_pushnumber(L, time);
	
	return 1;
}

static int lua_pgeTimerPause(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.timer.pause(timer) takes one argument.");
		
	pgeTimer *timer = *topgeTimer(L, 1);
	
	pgeTimerPause(timer);
	
	return 0;
}

static int lua_pgeTimerUnpause(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.timer.unpause(timer) takes one argument.");
		
	pgeTimer *timer = *topgeTimer(L, 1);
	
	pgeTimerUnpause(timer);
	
	return 0;
}

static int lua_pgeTimer_gc(lua_State *L)
{	
	pgeTimer *timer = *topgeTimer(L, 1);
	
	pgeTimerDestroy(timer);
	
	return 0;
}

static int lua_pgeTimer_tostring(lua_State *L)
{
	char buffer[128];
	
	sprintf(buffer, "%p", *topgeTimer(L, 1));
	
	lua_pushfstring(L, "pgeTimer (%s)", buffer);
	
	return 1;
}

static const luaL_reg lua_pgeTimer_methods[] =
{
	{"create",		lua_pgeTimerCreate},
	{"update",		lua_pgeTimerUpdate},
	{"getdelta",	lua_pgeTimerGetDelta},
	{"peekdelta",	lua_pgeTimerPeekDelta},
	{"totaltime",	lua_pgeTimerGetTotalTime},
	{"pause",		lua_pgeTimerPause},
	{"unpause",		lua_pgeTimerUnpause},
	{0, 0}
};
static const luaL_reg lua_pgeTimer_meta[] =
{
	{"__gc",		lua_pgeTimer_gc},
	{"__tostring",	lua_pgeTimer_tostring},
	{0, 0}
};

void lua_pgeTimer_init(lua_State *L)
{	
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeTimer_methods);
	luaL_newmetatable(L, "pgeTimer");
	luaL_register(L, 0, lua_pgeTimer_meta);
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pop(L, 1);
	lua_setfield(L, -2, "timer"); /* pge */
	lua_pop(L, 1);
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
	
	lua_State *L = pgeLuaGetState();
	
	lua_pgeTimer_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
