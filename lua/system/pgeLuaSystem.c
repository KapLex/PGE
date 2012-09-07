#include <pspkernel.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeSystem.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE System", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD();

unsigned long pgeVramAvailable();

static int lua_pgeSystemGetNickname(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.system.nickname() takes no arguments.");
		
	char nickname[128];
	
	pgeSystemGetNickname(nickname);
	
	lua_pushstring(L, nickname);
	
	return 1;
}

static int lua_pgeSystemGetPsid(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.system.psid() takes no arguments.");
		
	unsigned char psid[16];
	
	pgeSystemGetPsid(psid);
	
	//char string[60];
	
	//sprintf(string, "%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X", psid[0], psid[1], psid[2], psid[3], psid[4], psid[5], psid[6], psid[7], psid[8], psid[9], psid[10], psid[11], psid[12], psid[13], psid[14], psid[15]);
	
	lua_pushstring(L, (char *)psid);
	
	return 1;
}

static int lua_pgeSystemGetLanguage(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.system.language() takes no arguments.");
	
	int language = pgeSystemGetLanguage();
	
	lua_pushinteger(L, language);
	
	return 1;
}

static int lua_pgeSystemGetMac(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.system.mac() takes no arguments.");
		
	unsigned char mac[8];
	
	pgeSystemGetMac(mac);
	
	char string[30];
	
	sprintf(string, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	
	lua_pushstring(L, string);
	
	return 1;
}

static int lua_pgeSystemMsSize(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.system.mssize() takes no arguments.");
	
	lua_pushnumber(L, pgeSystemMsSize());
	
	return 1;
}

static int lua_pgeSystemMsFreeSize(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.system.msfreesize() takes no arguments.");
	
	lua_pushnumber(L, pgeSystemMsFreeSize());
	
	return 1;
}

static int lua_pgeSystemGetFreeRam(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.system.freeram() takes no arguments.");
	
	lua_pushnumber(L, pgeSystemGetFreeRam());
	
	return 1;
}

static int lua_pgeSystemGetFreeVram(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.system.freevram() takes no arguments.");
	
	lua_pushnumber(L, pgeVramAvailable());
	
	return 1;
}

static int lua_pgeSystemSetCpu(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.system.cpu(frequency) takes one argument.");
		
	int freq = luaL_checknumber(L, 1);
	
	lua_pushboolean(L, pgeSystemSetCpu(freq));
	
	return 1;
}

static int lua_pgeSystemGetBatteryPercent(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.system.battery.percent() takes no arguments.");
	
	lua_pushnumber(L, pgeSystemGetBatteryPercent());
	
	return 1;
}

static int lua_pgeSystemGetBatteryTime(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.system.battery.time() takes no arguments.");
	
	lua_pushnumber(L, pgeSystemGetBatteryTime());
	
	return 1;
}

static int lua_pgeSystemGetBatteryCharging(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.system.battery.charging() takes no arguments.");
	
	lua_pushboolean(L, pgeSystemGetBatteryCharging());
	
	return 1;
}

static int lua_pgeSystemGetBatteryExists(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.system.battery.exists() takes no arguments.");
	
	lua_pushboolean(L, pgeSystemGetBatteryExists());
	
	return 1;
}

static int lua_pgeSystemGetBatteryIsLow(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.system.battery.islow() takes no arguments.");
	
	lua_pushboolean(L, pgeSystemGetBatteryIsLow());
	
	return 1;
}

static const luaL_reg lua_pgeSystem_functions[] =
{
	{"nickname",		lua_pgeSystemGetNickname},
	{"psid",			lua_pgeSystemGetPsid},
	{"language",		lua_pgeSystemGetLanguage},
	{"mac",				lua_pgeSystemGetMac},
	{"mssize",			lua_pgeSystemMsSize},
	{"msfreesize",		lua_pgeSystemMsFreeSize},
	{"freeram",			lua_pgeSystemGetFreeRam},
	{"freevram",		lua_pgeSystemGetFreeVram},
	{"cpu",				lua_pgeSystemSetCpu},
	{0, 0}
};

static const luaL_reg lua_pgeSystemBattery_functions[] =
{
	{"percent",			lua_pgeSystemGetBatteryPercent},
	{"time",			lua_pgeSystemGetBatteryTime},
	{"charging",		lua_pgeSystemGetBatteryCharging},
	{"exists",			lua_pgeSystemGetBatteryExists},
	{"islow",			lua_pgeSystemGetBatteryIsLow},
	{0, 0}
};

void lua_pgeSystem_init(lua_State *L)
{	
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeSystem_functions);
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeSystemBattery_functions);
	lua_setfield(L, -2, "battery");
	lua_setfield(L, -2, "system"); /* pge */
	lua_pop(L, 1);
	
	lua_pushnumber(L, PGE_LANGUAGE_JAPANESE); lua_setglobal(L, "PGE_LANGUAGE_JAPANESE");
	lua_pushnumber(L, PGE_LANGUAGE_ENGLISH); lua_setglobal(L, "PGE_LANGUAGE_ENGLISH");
	lua_pushnumber(L, PGE_LANGUAGE_FRENCH); lua_setglobal(L, "PGE_LANGUAGE_FRENCH");
	lua_pushnumber(L, PGE_LANGUAGE_SPANISH); lua_setglobal(L, "PGE_LANGUAGE_SPANISH");
	lua_pushnumber(L, PGE_LANGUAGE_GERMAN); lua_setglobal(L, "PGE_LANGUAGE_GERMAN");
	lua_pushnumber(L, PGE_LANGUAGE_ITALIAN); lua_setglobal(L, "PGE_LANGUAGE_ITALIAN");
	lua_pushnumber(L, PGE_LANGUAGE_DUTCH); lua_setglobal(L, "PGE_LANGUAGE_DUTCH");
	lua_pushnumber(L, PGE_LANGUAGE_PORTUGUESE); lua_setglobal(L, "PGE_LANGUAGE_PORTUGUESE");
	lua_pushnumber(L, PGE_LANGUAGE_RUSSIAN); lua_setglobal(L, "PGE_LANGUAGE_RUSSIAN");
	lua_pushnumber(L, PGE_LANGUAGE_KOREAN); lua_setglobal(L, "PGE_LANGUAGE_KOREAN");
	lua_pushnumber(L, PGE_LANGUAGE_CHINESE_TRADITIONAL); lua_setglobal(L, "PGE_LANGUAGE_CHINESE_TRADITIONAL");
	lua_pushnumber(L, PGE_LANGUAGE_CHINESE_SIMPLIFIED); lua_setglobal(L, "PGE_LANGUAGE_CHINESE_SIMPLIFIED");
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
	
	pgeLuaRegisterDependency("pge.math");
		
	lua_State *L = pgeLuaGetState();
	
	lua_pgeSystem_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
