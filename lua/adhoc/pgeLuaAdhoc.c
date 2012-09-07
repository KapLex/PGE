#include <pspkernel.h>
#include <string.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeAdhoc.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE Adhoc", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD(); 

static int lua_pgeAdhocInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.adhoc.init() takes no arguments.");
		
	int result = pgeAdhocInit(PGE_ADHOC_TYPE_NORMAL);
	
	if(result == 1)
		lua_pushboolean(L, 1);
	else
		lua_pushboolean(L, 0);
	
	return 1;
}

static int lua_pgeAdhocShutdown(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.adhoc.shutdown() takes no arguments.");
		
	lua_pushboolean(L, pgeAdhocShutdown());
	
	return 1;
}

static int lua_pgeAdhocConnect(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argment error: pge.adhoc.connect(name) takes one argument.");
		
	const char *name = luaL_checkstring(L, 1);
		
	lua_pushboolean(L, pgeAdhocConnect(name));
	
	return 1;
}

static int lua_pgeAdhocGetState(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.adhoc.state() takes no arguments.");
		
	lua_pushnumber(L, pgeAdhocGetState());
	
	return 1;
}

static int lua_pgeAdhocGetError(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.adhoc.geterror() takes no arguments.");
		
	lua_pushnumber(L, pgeAdhocGetError());
	
	return 1;
}

static int lua_pgeAdhocPeerExists(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argment error: pge.adhoc.peerexists() takes one argument.");
		
	const char *mac = luaL_checkstring(L, 1);
	
	lua_pushboolean(L, pgeAdhocPeerExists(mac));
	
	return 1;
}

static int lua_pgeAdhocMatchingInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1 && argc != 2)
		return luaL_error(L, "Argment error: pge.adhoc.matching.init(type, [mode]) takes one or two arguments.");
		
	int type = luaL_checkint(L, 1);
	
	int mode = PGE_ADHOC_MATCHING_MODE_PTP;
	
	if(argc == 2)
		mode = luaL_checkint(L, 2);
		
	lua_pushboolean(L, pgeAdhocMatchingInit(mode, type));
	
	return 1;
}

static int lua_pgeAdhocMatchingStart(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0 && argc != 1)
		return luaL_error(L, "Argment error: pge.adhoc.matching.start([hello]) takes zero or one argument.");
	
	const char *hello = NULL;
	
	if(argc == 1)
		hello = luaL_checkstring(L, 1);
		
	lua_pushboolean(L, pgeAdhocMatchingStart(hello));
	
	return 1;
}

static int lua_pgeAdhocMatchingAccept(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argment error: pge.adhoc.matching.accept(mac) takes one argument.");
	
	const char *mac = luaL_checkstring(L, 1);
		
	lua_pushboolean(L, pgeAdhocMatchingAccept(mac));
	
	return 1;
}

static int lua_pgeAdhocMatchingDecline(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argment error: pge.adhoc.matching.decline(mac) takes one argument.");
	
	const char *mac = luaL_checkstring(L, 1);
		
	lua_pushboolean(L, pgeAdhocMatchingDecline(mac));
	
	return 1;
}

static int lua_pgeAdhocMatchingShutdown(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.adhoc.matching.shutdown() takes no arguments.");
		
	lua_pushboolean(L, pgeAdhocMatchingShutdown());
	
	return 1;
}

static int lua_pgeAdhocMatchingGetEvents(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.adhoc.matching.events() takes no arguments.");
		
	pgeAdhocPeerEvent *event = pgeAdhocMatchingGetEvents();
		
	lua_newtable(L);
	
	int i = 0;
	
	for(i = 0;i < 15;i++)
	{
		if(event[i].event > 0)
		{
			lua_pushnumber(L, i + 1);
		
			lua_newtable(L);
		
				lua_pushstring(L, "mac");
				lua_pushstring(L, event[i].mac);
				lua_settable(L, -3);
	
				lua_pushstring(L, "nickname");
				lua_pushstring(L, event[i].nickname);
				lua_settable(L, -3);
			
				lua_pushstring(L, "hello");
				lua_pushstring(L, event[i].hello);
				lua_settable(L, -3);
	
				lua_pushstring(L, "event");
				lua_pushnumber(L, event[i].event);
				lua_settable(L, -3);

			lua_settable(L, -3);
		}
	}
			
	return 1;
}

static int lua_pgeAdhocPtpHostStart(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.adhoc.ptp.hoststart() takes no arguments.");
		
	lua_pushnumber(L, pgeAdhocPtpHostStart());
	
	return 1;
}

static int lua_pgeAdhocPtpClientStart(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argment error: pge.adhoc.ptp.clientstart(mac) takes one argument.");
		
	const char *mac = luaL_checkstring(L, 1);
		
	lua_pushnumber(L, pgeAdhocPtpClientStart(mac));
	
	return 1;
}

static int lua_pgeAdhocPtpSend(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argment error: pge.adhoc.ptp.send(data) takes one argument.");
		
	size_t size;
		
	char *data = (char *)luaL_checklstring(L, 1, &size);
		
	lua_pushboolean(L, pgeAdhocPtpSend(data, (int *)&size));
	
	return 1;
}

static int lua_pgeAdhocPtpReceive(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.adhoc.ptp.receive() takes no arguments.");
		
	int size = 128;
	
	char data[size];
	
	memset(data, 0, size);
	
	pgeAdhocPtpReceive(data, &size);
		
	lua_pushstring(L, data);
	
	return 1;
}

static int lua_pgeAdhocPtpCheckForData(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.adhoc.ptp.checkfordata() takes no arguments.");
		
	lua_pushboolean(L, pgeAdhocPtpCheckForData());
	
	return 1;
}

static int lua_pgeAdhocPtpFlush(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.adhoc.ptp.flush() takes no arguments.");
		
	lua_pushboolean(L, pgeAdhocPtpFlush());
	
	return 1;
}

static int lua_pgeAdhocPtpHostShutdown(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.adhoc.ptp.hostshutdown() takes no arguments.");
		
	lua_pushboolean(L, pgeAdhocPtpHostShutdown());
	
	return 1;
}

static int lua_pgeAdhocPtpClientShutdown(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.adhoc.ptp.clientshutdown() takes no arguments.");
		
	lua_pushboolean(L, pgeAdhocPtpClientShutdown());
	
	return 1;
}

static const luaL_reg lua_pgeAdhoc_functions[] =
{
	{"init",			lua_pgeAdhocInit},
	{"shutdown",		lua_pgeAdhocShutdown},
	{"connect",			lua_pgeAdhocConnect},
	{"state",			lua_pgeAdhocGetState},
	{"geterror",		lua_pgeAdhocGetError},
	{"peerexists",		lua_pgeAdhocPeerExists},
	{0, 0}
};

static const luaL_reg lua_pgeAdhocMatching_functions[] =
{
	{"init",		lua_pgeAdhocMatchingInit},
	{"start",		lua_pgeAdhocMatchingStart},
	{"accept",		lua_pgeAdhocMatchingAccept},
	{"decline",		lua_pgeAdhocMatchingDecline},
	{"shutdown",	lua_pgeAdhocMatchingShutdown},
	{"events",		lua_pgeAdhocMatchingGetEvents},
	{0, 0}
};

static const luaL_reg lua_pgeAdhocPtp_functions[] =
{
	{"hoststart",		lua_pgeAdhocPtpHostStart},
	{"clientstart",		lua_pgeAdhocPtpClientStart},
	{"receive",			lua_pgeAdhocPtpReceive},
	{"send",			lua_pgeAdhocPtpSend},
	{"checkfordata",	lua_pgeAdhocPtpCheckForData},
	{"flush",			lua_pgeAdhocPtpFlush},
	{"hostshutdown",	lua_pgeAdhocPtpHostShutdown},
	{"clientshutdown",	lua_pgeAdhocPtpClientShutdown},
	{0, 0}
};

int lua_pgeAdhoc_init(lua_State *L)
{
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeAdhoc_functions);
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeAdhocMatching_functions);
	lua_setfield(L, -2, "matching");
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeAdhocPtp_functions);
	lua_setfield(L, -2, "ptp");
	lua_setfield(L, -2, "adhoc");
	lua_pop(L, 1);
	
	lua_pushnumber(L, PGE_ADHOC_EVENT_ERROR); lua_setglobal(L, "PGE_ADHOC_EVENT_ERROR");
	lua_pushnumber(L, PGE_ADHOC_EVENT_CONNECT); lua_setglobal(L, "PGE_ADHOC_EVENT_CONNECT");
	lua_pushnumber(L, PGE_ADHOC_EVENT_DISCONNECT); lua_setglobal(L, "PGE_ADHOC_EVENT_DISCONNECT");
	lua_pushnumber(L, PGE_ADHOC_EVENT_SCAN); lua_setglobal(L, "PGE_ADHOC_EVENT_SCAN");
	lua_pushnumber(L, PGE_ADHOC_EVENT_GAMEMODE); lua_setglobal(L, "PGE_ADHOC_EVENT_GAMEMODE");
	lua_pushnumber(L, PGE_ADHOC_EVENT_CANCEL); lua_setglobal(L, "PGE_ADHOC_EVENT_CANCEL");
	
	lua_pushnumber(L, PGE_ADHOC_MATCHING_EVENT_HELLO); lua_setglobal(L, "PGE_ADHOC_MATCHING_EVENT_HELLO");	
	lua_pushnumber(L, PGE_ADHOC_MATCHING_EVENT_REQUEST); lua_setglobal(L, "PGE_ADHOC_MATCHING_EVENT_REQUEST");
	lua_pushnumber(L, PGE_ADHOC_MATCHING_EVENT_LEAVE); lua_setglobal(L, "PGE_ADHOC_MATCHING_EVENT_LEAVE");
	lua_pushnumber(L, PGE_ADHOC_MATCHING_EVENT_DENY); lua_setglobal(L, "PGE_ADHOC_MATCHING_EVENT_DENY");
	lua_pushnumber(L, PGE_ADHOC_MATCHING_EVENT_CANCEL); lua_setglobal(L, "PGE_ADHOC_MATCHING_EVENT_CANCEL");
	lua_pushnumber(L, PGE_ADHOC_MATCHING_EVENT_ACCEPT); lua_setglobal(L, "PGE_ADHOC_MATCHING_EVENT_ACCEPT");
	lua_pushnumber(L, PGE_ADHOC_MATCHING_EVENT_ESTABLISHED); lua_setglobal(L, "PGE_ADHOC_MATCHING_EVENT_ESTABLISHED");
	lua_pushnumber(L, PGE_ADHOC_MATCHING_EVENT_TIMEOUT); lua_setglobal(L, "PGE_ADHOC_MATCHING_EVENT_TIMEOUT");
	lua_pushnumber(L, PGE_ADHOC_MATCHING_EVENT_ERROR); lua_setglobal(L, "PGE_ADHOC_MATCHING_EVENT_ERROR");
	lua_pushnumber(L, PGE_ADHOC_MATCHING_EVENT_BYE); lua_setglobal(L, "PGE_ADHOC_MATCHING_EVENT_BYE");
	
	lua_pushnumber(L, PGE_ADHOC_MATCHING_MODE_PTP); lua_setglobal(L, "PGE_ADHOC_MATCHING_MODE_PTP");
	
	lua_pushnumber(L, PGE_ADHOC_MATCHING_TYPE_HOST); lua_setglobal(L, "PGE_ADHOC_MATCHING_TYPE_HOST");
	lua_pushnumber(L, PGE_ADHOC_MATCHING_TYPE_CLIENT); lua_setglobal(L, "PGE_ADHOC_MATCHING_TYPE_CLIENT");
	
	return 1;
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
	
	lua_State *L = pgeLuaGetState();
	
	lua_pgeAdhoc_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
