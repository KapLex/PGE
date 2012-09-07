#include <pspkernel.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeDir.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE Dir", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD(); 

void __psp_init_cwd(char *argv_0);

pgeLuaCreateUserdataHandlers(pgeDir, pgeDir*)

static int lua_pgeDirExists(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.dir.exists(dirname) takes one argument.");
	
	const char *dirname = luaL_checkstring(L, 1);
	
	lua_pushboolean(L, pgeDirExists(dirname));
	
	return 1;
}

static int lua_pgeDirMake(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.dir.mkdir(name) takes one argument.");
	
	const char *name = luaL_checkstring(L, 1);
	
	lua_pushboolean(L, pgeDirMake(name));
	
	return 1;
}

static int lua_pgeDirRemove(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.dir.rmdir(name) takes one argument.");
	
	const char *dirpath = luaL_checkstring(L, 1);
	
	lua_pushboolean(L, pgeDirRemove(dirpath));
	
	return 1;
}

static int lua_pgeDirRename(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.dir.rename(oldname, newname) takes one argument.");
	
	const char *oldname = luaL_checkstring(L, 1);
	
	const char *newname = luaL_checkstring(L, 2);
	
	lua_pushboolean(L, pgeDirRename(oldname, newname));
	
	return 1;
}

static int lua_pgeDirChdir(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.dir.chdir(path) takes one argument.");
	
	const char *path = luaL_checkstring(L, 1);
	
	lua_pushboolean(L, pgeDirChdir(path));
	
	return 1;
}

static int lua_pgeDirGetCwd(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "pge.dir.getcwd() takes no arguments.");
	
	char path[256];
	
	pgeDirGetCwd(path, 256);
	
	lua_pushstring(L, path);
	
	return 1;
}

static int lua_pgeDirOpen(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0 && argc != 1)
		return luaL_error(L, "Argument error: pge.dir.open([path]) takes zero or one argument.");
		
	const char *path = "";
	
	if(argc == 0)
		path = "";
	else
		path = luaL_checkstring(L, 1);

	lua_gc(L, LUA_GCCOLLECT, 0);
	
	pgeDir *newDir = pgeDirOpen(path);
		
	if(!newDir)
	{
		lua_pushnil(L);
		return 1;
	}
		
	pgeDir **luaNewDir = pushpgeDir(L);
	
	*luaNewDir = newDir;
	
	return 1;
}

static int lua_pgeDirClose(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.dir.close(dir) takes one argument.");
		
	pgeDir **handle = topgeDir(L, 1);
	
	pgeDirClose(*handle);
	
	return 0;
}

static int lua_pgeDirRead(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.dir.read(dir) takes one argument.");
		
	pgeDir *handle = *topgeDir(L, 1);
	
	if(pgeDirRead(handle) <= 0)
	{
		lua_pushnil(L);
		return 1;
	}
	
	lua_newtable(L);
	
	int i = 0;
	
	for(i = 0;i < handle->count;i++)
	{
		lua_pushnumber(L, i + 1);
		
		lua_newtable(L);
		
			lua_pushstring(L, "name");
			lua_pushstring(L, handle->entries[i].name);
			lua_settable(L, -3);
	
			lua_pushstring(L, "size");
			lua_pushnumber(L, handle->entries[i].size);
			lua_settable(L, -3);
	
			lua_pushstring(L, "dir");
			lua_pushboolean(L, handle->entries[i].type);
			lua_settable(L, -3);

		lua_settable(L, -3);
	}
	
	return 1;
}

static const luaL_reg lua_pgeDir_methods[] =
{
	{"close",		lua_pgeDirClose},
	{"read",		lua_pgeDirRead},
	{"mkdir",		lua_pgeDirMake},
	{"rmdir",		lua_pgeDirRemove},
	{"chdir",		lua_pgeDirChdir},
	{"getcwd",		lua_pgeDirGetCwd},
	{"open",		lua_pgeDirOpen},
	{"exists",		lua_pgeDirExists},
	{"rename",		lua_pgeDirRename},
	{0, 0}
};

void lua_pgeDir_init(lua_State *L)
{	
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeDir_methods);
	luaL_newmetatable(L, "pgeDir");
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pop(L, 1);
	
	lua_setfield(L, -2, "dir"); /* pge */
	lua_pop(L, 1);
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	
	__psp_init_cwd((char *)argp);
	
	lua_State *L = pgeLuaGetState();
	
	lua_pgeDir_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
