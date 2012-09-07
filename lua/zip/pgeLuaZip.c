#include <pspkernel.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeZip.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE Zip", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD(); 

pgeLuaCreateUserdataHandlers(pgeZip, pgeZip*)
pgeLuaCreateUserdataHandlers(pgeZipFile, pgeZipFile*)

static int lua_pgeZipOpen(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.zip.open(filename) takes one argument.");
		
	const char *filepath = luaL_checkstring(L, 1);
	
	if(!filepath)
		return luaL_error(L, "Argument error: pge.zip.open(filename), argument must be a file path.");
		
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	pgeZip *newZip = pgeZipOpen(filepath);
	
	if(!newZip)
	{
		lua_pushnil(L);
		return 1;
	}
		
	pgeZip **luaNewZip = pushpgeZip(L);
	
	*luaNewZip = newZip;
	
	return 1;
}

static int lua_pgeZipClose(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.zip.close(zip) takes one argument.");
	
	pgeZip **handle = topgeZip(L, 1);
	
	lua_pushboolean(L, pgeZipClose(*handle));
	
	return 1;
}

static int lua_pgeZipFileRead(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2 && argc != 3)
		return luaL_error(L, "Argument error: pge.zip.read(zip, filename, [password]) takes two or three arguments.");
		
	pgeZip **handle = topgeZip(L, 1);
	
	const char *filename = luaL_checkstring(L, 2);
	
	const char *password;
	
	if(argc == 2)
		password = NULL;
	else
		password = luaL_checkstring(L, 3);
		
	lua_gc(L, LUA_GCCOLLECT, 0);
		
	pgeZipFile *newZipFile = pgeZipFileRead(*handle, filename, password);
	
	if(!newZipFile)
	{
		lua_pushnil(L);
		return 1;
	}
	
	pgeZipFile **luaNewZipFile = pushpgeZipFile(L);
	
	*luaNewZipFile = newZipFile;
	
	return 1;
}

static int lua_pgeZipExtract(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1 && argc != 2)
		return luaL_error(L, "Argument error: pge.zip.extract(zip, [password]) takes one or two arguments.");
	
	const char *password;
	
	pgeZip *handle = *topgeZip(L, 1);
	
	if(argc == 2)
		password = luaL_checkstring(L, 2);
	else
		password = NULL;
	
	lua_pushboolean(L, pgeZipExtract(handle, password));
	
	return 1;
}

static int lua_pgeZipFileData(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.zip.data(zipfile) takes one argument.");
	
	pgeZipFile *handle = *topgeZipFile(L, 1);
	
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	lua_pushlstring(L, (char *)handle->data, handle->size);
	
	return 1;
}

static int lua_pgeZipFileSize(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.zip.size(zipfile) takes one argument.");
	
	pgeZipFile *handle = *topgeZipFile(L, 1);
	
	lua_pushinteger(L, handle->size);
	
	return 1;
}

static int lua_pgeZip_gc(lua_State *L) // garbage collect
{	
	(void)L;
	return 0;
}
	
static int lua_pgeZip_tostring(lua_State *L)
{
	char buffer[128];
	
	sprintf(buffer, "%p", *topgeZip(L, 1));
	
	lua_pushfstring(L, "pgeZip (%s)", buffer);
	
	return 1;
}

static int lua_pgeZipFile_gc(lua_State *L) // garbage collect
{	
	//printf("Unload zipfile\n");
	
	pgeZipFile **handle = topgeZipFile(L, 1);
	
	pgeZipFileFree(*handle);
	
	return 0;
}
	
static int lua_pgeZipFile_tostring(lua_State *L)
{
	char buffer[128];
	
	sprintf(buffer, "%p", *topgeZipFile(L, 1));
	
	lua_pushfstring(L, "pgeZipFile (%s)", buffer);
	
	return 1;
}

static const luaL_reg lua_pgeZip_methods[] =
{
	{"open",		lua_pgeZipOpen},
	{"close",		lua_pgeZipClose},
	{"read",		lua_pgeZipFileRead},
	{"extract",		lua_pgeZipExtract},
  {0, 0}
};

static const luaL_reg lua_pgeZip_meta[] =
{
	{"__gc",       lua_pgeZip_gc},
	{"__tostring", lua_pgeZip_tostring},
	{0, 0}
};

static const luaL_reg lua_pgeZipFile_methods[] =
{
	{"data",		lua_pgeZipFileData},
	{"size",		lua_pgeZipFileSize},
	{0, 0}
};

static const luaL_reg lua_pgeZipFile_meta[] =
{
	{"__gc",       lua_pgeZipFile_gc},
	{"__tostring", lua_pgeZipFile_tostring},
	{0, 0}
};

void lua_pgeZip_init(lua_State *L)
{	
	lua_getglobal(L, "pge");	
	lua_newtable(L);
		
	luaL_register(L, 0, lua_pgeZip_methods);
	luaL_newmetatable(L, "pgeZip");
	luaL_register(L, 0, lua_pgeZip_meta);
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pop(L, 1);
	
	luaL_register(L, 0, lua_pgeZipFile_methods);
	luaL_newmetatable(L, "pgeZipFile");
	luaL_register(L, 0, lua_pgeZipFile_meta);
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pop(L, 1);

	lua_setfield(L, -2, "zip"); /* pge */
	lua_pop(L, 1);
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
	
	lua_State *L = pgeLuaGetState();
	
	lua_pgeZip_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
