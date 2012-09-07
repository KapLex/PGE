#include <pspkernel.h>
#include <malloc.h>
#include <string.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeNet.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE Net", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD(); 

pgeLuaCreateUserdataHandlers(pgeSocketSet, pgeSocketSet)
pgeLuaCreateUserdataHandlers(pgeSocket, pgeSocket)

static int lua_pgeNetInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.net.init() takes no arguments.");
	
	lua_pushboolean(L, pgeNetInit());
	
	return 1;
}

static int lua_pgeNetShutdown(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.net.shutdown() takes no arguments.");
	
	lua_pushboolean(L, pgeNetShutdown());
	
	return 1;
}

static int lua_pgeNetGetFile(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.net.getfile(url, filepath) takes two arguments.");
		
	const char *url = luaL_checkstring(L, 1);
	
	if(!url)
		return luaL_error(L, "Argument error: pge.net.getfile(url, filepath), incorrect argument for url.");
		
	const char *filepath = luaL_checkstring(L, 2);
	
	if(!filepath)
		return luaL_error(L, "Argument error: pge.net.getfile(url, filepath), incorrect argument for filepath.");
		
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	lua_pushboolean(L, pgeNetGetFile(url, filepath));
	
	return 1;
}

static int lua_pgeNetPostForm(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2 && argc != 3)
		return luaL_error(L, "Argument error: pge.net.postform(url, data, [responsesize]) takes two or three arguments.");
		
	const char *url = luaL_checkstring(L, 1);
	
	const char *data = luaL_checkstring(L, 2);
	
	int responsesize = 0;
	
	char *response = NULL;
	
	if(argc == 3)
	{
		responsesize = luaL_checkint(L, 3);
	
		response = (char *)pgeMalloc(responsesize);
		
		memset(response, 0, responsesize);
		
		if(!response)
			return luaL_error(L, "Error: pge.net.postform(url, data, [responsesize]) Failed to allocate buffer.");
	}
	
	int result = pgeNetPostForm(url, (char*)data, response, responsesize);
	
	lua_pushboolean(L, result);
	
	if(strlen(response) > 0 && response != NULL)
		lua_pushstring(L, response);
	else
		lua_pushnil(L);
		
	if(response)
		pgeFree(response);
	
	return 2;
}

static int lua_pgeNetSwitchStatus(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.net.switchstatus() takes no arguments.");
	
	lua_pushboolean(L, pgeNetSwitchStatus());
	
	return 1;
}

static int lua_pgeNetDisconnect(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.net.disconnect() takes no arguments.");
	
	pgeNetDisconnect();
	
	return 0;
}

static int lua_pgeNetIsConnected(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.net.isconnected() takes no arguments.");
	
	lua_pushboolean(L, pgeNetIsConnected());
	
	return 1;
}

static int lua_pgeNetGetLocalIp(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.net.localip() takes no arguments.");
		
	char buffer[32];
	
	if(pgeNetGetLocalIp(buffer))
		lua_pushstring(L, buffer);
	else
		lua_pushnil(L);
	
	return 1;
}

static int lua_pgeNetResolveHost(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.net.resolve(hostname) takes one argument.");
		
	const char *hostname = luaL_checkstring(L, 1);
	
	if(!hostname)
		return luaL_error(L, "Argument error: pge.net.resolve(hostname). Incorrect argument.");
		
	char buffer[32];
	
	if(pgeNetResolveHost((char *)hostname, buffer))
		lua_pushstring(L, buffer);
	else
		lua_pushnil(L);
	
	return 1;
}

static int lua_pgeNetSocketCreate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.net.socket.create() takes no arguments.");
		
	pgeSocket *luasocket = pushpgeSocket(L);
		
	pgeSocket socket = pgeNetSocketCreate();
	
	*luasocket = socket;
	
	return 1;
}

static int lua_pgeNetSocketAccept(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.net.socket.accept(socket) takes one argument.");
		
	pgeSocket socket;
		
	if(lua_type(L, 1) == LUA_TUSERDATA)
		socket = *topgeSocket(L, 1);
	else if(lua_type(L, 1) == LUA_TNUMBER)
		socket = luaL_checkint(L, 1);
	else
		return luaL_error(L, "Argument error: pge.net.socket.accept(socket). Argument must be a socket or a number.");
	
	pgeSocket newsocket = *pushpgeSocket(L);
	
	newsocket = pgeNetSocketAccept(socket);
	
	return 1;
}

static int lua_pgeNetSocketBind(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.net.socket.bind(socket, port) takes two arguments.");
		
	pgeSocket socket;
		
	if(lua_type(L, 1) == LUA_TUSERDATA)
		socket = *topgeSocket(L, 1);
	else if(lua_type(L, 1) == LUA_TNUMBER)
		socket = luaL_checkint(L, 1);
	else
		return luaL_error(L, "Argument error: pge.net.socket.bind(socket, port). First argument must be a socket or a number.");
	
	int port = luaL_checkinteger(L, 2);
		
	lua_pushboolean(L, pgeNetSocketBind(socket, port));
	
	return 1;
}

static int lua_pgeNetSocketListen(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.net.socket.listen(socket, maximum) takes two arguments.");
		
	pgeSocket socket;
		
	if(lua_type(L, 1) == LUA_TUSERDATA)
		socket = *topgeSocket(L, 1);
	else if(lua_type(L, 1) == LUA_TNUMBER)
		socket = luaL_checkint(L, 1);
	else
		return luaL_error(L, "Argument error: pge.net.socket.listen(socket). Argument must be a socket or a number.");
	
	int max = luaL_checkint(L, 2);
	
	lua_pushboolean(L, pgeNetSocketListen(socket, max));
	
	return 1;
}

static int lua_pgeNetSocketConnect(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 3)
		return luaL_error(L, "Argument error: pge.net.socket.connect(socket, ip, port) takes three arguments.");
		
	pgeSocket socket;
		
	if(lua_type(L, 1) == LUA_TUSERDATA)
		socket = *topgeSocket(L, 1);
	else if(lua_type(L, 1) == LUA_TNUMBER)
		socket = luaL_checkint(L, 1);
	else
		return luaL_error(L, "Argument error: pge.net.socket.connect(socket, ip, port). First argument must be a socket or a number.");
	
	const char *ip = luaL_checkstring(L, 2);
	
	int port = luaL_checkinteger(L, 3);
		
	lua_pushboolean(L, pgeNetSocketConnect(socket, (char *)ip, port));
	
	return 1;
}

static int lua_pgeNetSocketSend(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.net.socket.send(socket, data) takes two arguments.");
		
	pgeSocket socket;
		
	if(lua_type(L, 1) == LUA_TUSERDATA)
		socket = *topgeSocket(L, 1);
	else if(lua_type(L, 1) == LUA_TNUMBER)
		socket = luaL_checkint(L, 1);
	else
		return luaL_error(L, "Argument error: pge.net.socket.send(socket, data). First argument must be a socket or a number.");
	
	size_t size;
	
	const char *data = luaL_checklstring(L, 2, &size);
		
	lua_pushinteger(L, pgeNetSocketSend(socket, data, size));
	
	return 1;
}

static int lua_pgeNetSocketReceive(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1 && argc != 2)
		return luaL_error(L, "Argument error: pge.net.socket.receive(socket, [size]) takes one or two arguments.");
		
	pgeSocket socket;
	
	if(lua_type(L, 1) == LUA_TUSERDATA)
		socket = *topgeSocket(L, 1);
	else if(lua_type(L, 1) == LUA_TNUMBER)
		socket = luaL_checkint(L, 1);
	else
		return luaL_error(L, "Argument error: pge.net.socket.receive(socket, [size]). First argument must be a socket or a number.");
	
	int size = 256;
	
	if(argc == 2)
		size = luaL_checkinteger(L, 2);
		
	char *data = pgeMalloc(size);
	
	if(!data)
		return luaL_error(L, "Error: pge.net.socket.receive(socket, [size]). Error allocating buffer.");
	
	int count = pgeNetSocketReceive(socket, data, size);
	
	if(count > 0)
		lua_pushlstring(L, data, count);
	else
		lua_pushstring(L, "");
		
	pgeFree(data);
	
	return 1;
}

static int lua_pgeNetSocketClose(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.net.socket.close(socket) takes one argument.");
		
	pgeSocket socket;
	
	if(lua_type(L, 1) == LUA_TUSERDATA)
		socket = *topgeSocket(L, 1);
	else if(lua_type(L, 1) == LUA_TNUMBER)
		socket = luaL_checkint(L, 1);
	else
		return luaL_error(L, "Argument error: pge.net.socket.close(socket). Argument must be a socket or a number.");
	
	pgeNetSocketClose(socket);
	
	return 0;
}

static int lua_pgeNetSocketSetCreate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.net.socketset.create() takes no arguments.");
		
	pgeSocketSet *set = pushpgeSocketSet(L);
	
	pgeNetSocketSetClear(set);
	
	return 1;
}

static int lua_pgeNetSocketSetAdd(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.net.socketset.add(socketset, socket) takes two arguments.");
		
	pgeSocketSet *set = topgeSocketSet(L, 1);
	
	pgeSocket socket;
	
	if(lua_type(L, 2) == LUA_TUSERDATA)
		socket = *topgeSocket(L, 2);
	else if(lua_type(L, 2) == LUA_TNUMBER)
		socket = luaL_checkint(L, 2);
	else
		return luaL_error(L, "Argument error: pge.net.socketset.add(socketset, socket). Second argument must be a socket or a number.");
	
	pgeNetSocketSetAdd(socket, set);
	
	return 0;
}

static int lua_pgeNetSocketSetClear(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.net.socketset.clear(socketset) takes one argument.");
		
	pgeSocketSet *set = topgeSocketSet(L, 1);
	
	pgeNetSocketSetClear(set);
	
	return 0;
}

static int lua_pgeNetSocketSetRemove(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.net.socketset.remove(socketset, socket) takes two arguments.");
		
	pgeSocketSet *set = topgeSocketSet(L, 1);
	
	pgeSocket socket;
	
	if(lua_type(L, 2) == LUA_TUSERDATA)
		socket = *topgeSocket(L, 2);
	else if(lua_type(L, 2) == LUA_TNUMBER)
		socket = luaL_checkint(L, 2);
	else
		return luaL_error(L, "Argument error: pge.net.socketset.remove(socketset, socket). Second argument must be a socket or a number.");
	
	pgeNetSocketSetRemove(socket, set);
	
	return 0;
}

static int lua_pgeNetSocketSetIsMember(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.net.socketset.ismember(socketset, socket) takes two arguments.");
		
	pgeSocketSet *set = topgeSocketSet(L, 1);
	
	pgeSocket socket;
	
	if(lua_type(L, 2) == LUA_TUSERDATA)
		socket = *topgeSocket(L, 2);
	else if(lua_type(L, 2) == LUA_TNUMBER)
		socket = luaL_checkint(L, 2);
	else
		return luaL_error(L, "Argument error: pge.net.socketset.ismember(socketset, socket). Second argument must be a socket or a number.");
	
	lua_pushboolean(L, pgeNetSocketSetIsMember(socket, set));
	
	return 1;
}

static int lua_pgeNetSocketSetSelect(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.net.socketset.select(socketset) takes one argument.");
		
	pgeSocketSet *set = topgeSocketSet(L, 1);
	
	lua_pushinteger(L, pgeNetSocketSetSelect(256, set));
	
	return 1;
}

static int lua_pgeNetSocketEq(lua_State *L)
{
	pgeSocket a = -1;
	pgeSocket b = -2;
	
	if(lua_type(L, 1) == LUA_TUSERDATA)
		a = *topgeSocket(L, 1);
	else if(lua_type(L, 1) == LUA_TNUMBER)
		a = luaL_checkint(L, 1);
		
	if(lua_type(L, 2) == LUA_TUSERDATA)
		b = *topgeSocket(L, 2);
	else if(lua_type(L, 2) == LUA_TNUMBER)
		b = luaL_checkint(L, 2);
		
	lua_pushboolean(L, a == b);
	
	//printf("EQ called!!!\n");
	
	return 1;
}

static const luaL_reg lua_pgeNet_functions[] =
{
	{"init",			lua_pgeNetInit},
	{"shutdown",		lua_pgeNetShutdown},
	{"getfile",			lua_pgeNetGetFile},
	{"postform",		lua_pgeNetPostForm},
	{"switchstatus",	lua_pgeNetSwitchStatus},
	{"disconnect",		lua_pgeNetDisconnect},
	{"isconnected",		lua_pgeNetIsConnected},
	{"localip",			lua_pgeNetGetLocalIp},
	{"resolve",			lua_pgeNetResolveHost},
	{0, 0}
};

static const luaL_reg lua_pgeNetSocket_functions[] =
{
	{"create",			lua_pgeNetSocketCreate},
	{"accept",			lua_pgeNetSocketAccept},
	{"bind",			lua_pgeNetSocketBind},
	{"listen",			lua_pgeNetSocketListen},
	{"connect",			lua_pgeNetSocketConnect},
	{"send",			lua_pgeNetSocketSend},
	{"receive",			lua_pgeNetSocketReceive},
	{"close",			lua_pgeNetSocketClose},
	{"createset",		lua_pgeNetSocketSetCreate},
	{"add",				lua_pgeNetSocketSetAdd},
	{"clear",			lua_pgeNetSocketSetClear},
	{"remove",			lua_pgeNetSocketSetRemove},
	{"ismember",		lua_pgeNetSocketSetIsMember},
	{"select",			lua_pgeNetSocketSetSelect},
	{0, 0}
};

static int lua_pgeNetSocketToString(lua_State *L)
{
	char buffer[128];
	
	sprintf(buffer, "%d", *topgeSocket(L, 1));
	
	lua_pushfstring(L, buffer);
	
	return 1;
}

static const luaL_reg lua_pgeNetSocket_meta[] =
{
	{"__eq",	lua_pgeNetSocketEq},
	{"__tostring",	lua_pgeNetSocketToString},
	{0, 0},
};

static const luaL_reg lua_pgeNetSocketSet_functions[] =
{
	{"create",		lua_pgeNetSocketSetCreate},
	{"add",			lua_pgeNetSocketSetAdd},
	{"clear",		lua_pgeNetSocketSetClear},
	{"remove",		lua_pgeNetSocketSetRemove},
	{"ismember",	lua_pgeNetSocketSetIsMember},
	{"select",		lua_pgeNetSocketSetSelect},
	{0, 0}
};

void lua_pgeNet_init(lua_State *L)
{	
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeNet_functions);
	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeNetSocket_functions);
	luaL_newmetatable(L, "pgeSocket");
	luaL_register(L, 0, lua_pgeNetSocket_meta);
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pop(L, 1);
	lua_setfield(L, -2, "socket"); /* net */
	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeNetSocketSet_functions);
	luaL_newmetatable(L, "pgeSocketSet");
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pop(L, 1);
	lua_setfield(L, -2, "socketset"); /* net */
	
	lua_setfield(L, -2, "net"); /* pge */
	lua_pop(L, 1);
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
	
	lua_State *L = pgeLuaGetState();
	
	lua_pgeNet_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
