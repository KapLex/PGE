#include <pspkernel.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeControls.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE Controls", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD();

static int lua_pgeControlsUpdate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.controls.update() takes no arguments.");
		
	pgeControlsUpdate();
	
	return 0;
}

static int lua_pgeControlsEnable(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.controls.enable() takes no arguments.");
		
	pgeControlsEnable();
	
	return 0;
}

static int lua_pgeControlsDisable(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.controls.disable() takes no arguments.");
		
	pgeControlsDisable();
	
	return 0;
}

static int lua_pgeControlsPressedAny(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.controls.pressedany() takes no arguments.");
	
	lua_pushboolean(L, pgeControlsPressedAny());
	
	return 1;
}

static int lua_pgeControlsHeldAny(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.controls.heldany() takes no arguments.");
	
	lua_pushboolean(L, pgeControlsHeldAny());
	
	return 1;
}

static int lua_pgeControlsReleasedAny(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.controls.releasedany() takes no arguments.");
	
	lua_pushboolean(L, pgeControlsReleasedAny());
	
	return 1;
}

static int lua_pgeControlsPressed(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.controls.pressed(buttons) takes one argument.");
		
	unsigned int buttons = lua_tonumber(L, 1);
	
	lua_pushboolean(L, pgeControlsPressed(buttons));
	
	return 1;
}

static int lua_pgeControlsHeld(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.controls.held(buttons) takes one argument.");
		
	unsigned int buttons = luaL_checkint(L, 1);
	
	lua_pushboolean(L, pgeControlsHeld(buttons));
	
	return 1;
}

static int lua_pgeControlsReleased(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.controls.released(buttons) takes one argument.");
		
	unsigned int buttons = luaL_checkint(L, 1);
	
	lua_pushboolean(L, pgeControlsReleased(buttons));
	
	return 1;
}

static int lua_pgeControlsAnalogX(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.controls.analogx() takes no arguments.");
	
	lua_pushnumber(L, pgeControlsAnalogX());
	
	return 1;
}

static int lua_pgeControlsAnalogY(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.controls.analogy() takes no arguments.");
	
	lua_pushnumber(L, pgeControlsAnalogY());
	
	return 1;
}

static int lua_pgeControlsAnalogAngle(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.controls.analogangle() takes no arguments.");
	
	lua_pushnumber(L, pgeControlsAnalogAngle());
	
	return 1;
}

static int lua_pgeControlsAnalogMag(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.controls.analogmag() takes no arguments.");
	
	lua_pushnumber(L, pgeControlsAnalogMag());
	
	return 1;
}

static const luaL_reg lua_pgeControls_functions[] =
{
	{"update",		lua_pgeControlsUpdate},
	{"enable",		lua_pgeControlsEnable},
	{"disable",		lua_pgeControlsDisable},
	{"pressedany",	lua_pgeControlsPressedAny},
	{"heldany",		lua_pgeControlsHeldAny},
	{"releasedany",	lua_pgeControlsReleasedAny},
	{"pressed",		lua_pgeControlsPressed},
	{"held",		lua_pgeControlsHeld},
	{"released",	lua_pgeControlsReleased},
	{"analogx",		lua_pgeControlsAnalogX},
	{"analogy",		lua_pgeControlsAnalogY},
	{"analogangle",	lua_pgeControlsAnalogAngle},
	{"analogmag",	lua_pgeControlsAnalogMag},
	{0, 0}
};

void lua_pgeControls_init(lua_State *L)
{
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeControls_functions);
	lua_setfield(L, -2, "controls"); /* pge */
	lua_pop(L, 1);
	
	lua_pushnumber(L, PGE_CTRL_SELECT); lua_setglobal(L, "PGE_CTRL_SELECT");
	lua_pushnumber(L, PGE_CTRL_START); lua_setglobal(L, "PGE_CTRL_START");
	lua_pushnumber(L, PGE_CTRL_UP); lua_setglobal(L, "PGE_CTRL_UP");
	lua_pushnumber(L, PGE_CTRL_RIGHT); lua_setglobal(L, "PGE_CTRL_RIGHT");
	lua_pushnumber(L, PGE_CTRL_DOWN); lua_setglobal(L, "PGE_CTRL_DOWN");
	lua_pushnumber(L, PGE_CTRL_LEFT); lua_setglobal(L, "PGE_CTRL_LEFT");
	lua_pushnumber(L, PGE_CTRL_LTRIGGER); lua_setglobal(L, "PGE_CTRL_LTRIGGER");
	lua_pushnumber(L, PGE_CTRL_RTRIGGER); lua_setglobal(L, "PGE_CTRL_RTRIGGER");
	lua_pushnumber(L, PGE_CTRL_TRIANGLE); lua_setglobal(L, "PGE_CTRL_TRIANGLE");
	lua_pushnumber(L, PGE_CTRL_CIRCLE); lua_setglobal(L, "PGE_CTRL_CIRCLE");
	lua_pushnumber(L, PGE_CTRL_CROSS); lua_setglobal(L, "PGE_CTRL_CROSS");
	lua_pushnumber(L, PGE_CTRL_SQUARE); lua_setglobal(L, "PGE_CTRL_SQUARE");
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
	
	pgeLuaRegisterDependency("pge.math");
	
	lua_State *L = pgeLuaGetState();
	
	pgeControlsInit();
	
	lua_pgeControls_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
