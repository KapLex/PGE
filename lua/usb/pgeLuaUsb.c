#include <pspkernel.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeUsb.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE Usb", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD(); 

static int lua_pgeUsbInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.usb.init() takes no arguments.");
	
	lua_pushboolean(L, pgeUsbInit());
	
	return 1;
}

static int lua_pgeUsbShutdown(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.usb.shutdown() takes no arguments.");
	
	lua_pushboolean(L, pgeUsbShutdown());
	
	return 1;
}

static int lua_pgeUsbActivate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.usb.activate() takes no arguments.");
	
	lua_pushboolean(L, pgeUsbActivate());
	
	return 1;
}

static int lua_pgeUsbDeactivate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.usb.deactivate() takes no arguments.");
	
	lua_pushboolean(L, pgeUsbDeactivate());
	
	return 1;
}

static int lua_pgeUsbActivated(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.usb.activated() takes no arguments.");
		
	int state = pgeUsbGetState();
	
	lua_pushboolean(L, state & PGE_USB_ACTIVATED);
	
	return 1;
}

static int lua_pgeUsbCableConnected(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.usb.cable() takes no arguments.");
		
	int state = pgeUsbGetState();
	
	lua_pushboolean(L, state & PGE_USB_CABLE_CONNECTED);
	
	return 1;
}

static int lua_pgeUsbEstablished(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.usb.established() takes no arguments.");
		
	int state = pgeUsbGetState();
	
	lua_pushboolean(L, state & PGE_USB_CONNECTION_ESTABLISHED);
	
	return 1;
}

static const luaL_reg lua_pgeUsb_functions[] =
{
	{"init",			lua_pgeUsbInit},
	{"shutdown",		lua_pgeUsbShutdown},
	{"activate",		lua_pgeUsbActivate},
	{"deactivate",		lua_pgeUsbDeactivate},
	{"activated",		lua_pgeUsbActivated},
	{"cable",			lua_pgeUsbCableConnected},
	{"established",		lua_pgeUsbEstablished},
	{0, 0}
};

int lua_pgeUsb_init(lua_State *L)
{
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeUsb_functions);
	lua_setfield(L, -2, "usb"); /* pge */
	lua_pop(L, 1);
	
	return 1;
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
	
	lua_State *L = pgeLuaGetState();
	
	lua_pgeUsb_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
