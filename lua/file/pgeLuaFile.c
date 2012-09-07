#include <pspkernel.h>
#include <malloc.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeFile.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE File", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD(); 

pgeLuaCreateUserdataHandlers(pgeFile, pgeFile*)

static int lua_pgeFileOpen(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.file.open(filename, flags) takes two arguments.");
		
	const char *filepath = luaL_checkstring(L, 1);
	
	int flags = luaL_checkint(L, 2);
		
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	pgeFile *newStream = pgeFileOpen((char *)filepath, flags);
		
	if(!newStream)
	{
		lua_pushnil(L);
		return 1;
	}
		
	pgeFile **luaNewStream = pushpgeFile(L);
	
	*luaNewStream = newStream;
	
	return 1;
}

static int lua_pgeFileOpenAsync(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.file.openasync(filename, flags) takes two arguments.");
		
	const char *filepath = luaL_checkstring(L, 1);
	
	int flags = luaL_checkint(L, 2);
		
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	pgeFile *newStream = pgeFileOpenAsync((char *)filepath, flags);
	
	if(!newStream)
	{
		lua_pushnil(L);
		return 1;
	}
		
	pgeFile **luaNewStream = pushpgeFile(L);
	
	*luaNewStream = newStream;
	
	return 1;
}

static int lua_pgeFileMemoryOpen(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.file.openmemory(data) takes one argument.");
		
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	size_t size;
		
	unsigned char *data = (unsigned char *)luaL_checklstring(L, 1, &size);
	
	pgeFile *newStream = pgeFileOpenMemory((void *)data, size);
	
	if(!newStream)
	{
		lua_pushnil(L);
		return 1;
	}
		
	pgeFile **luaNewStream = pushpgeFile(L);
	
	*luaNewStream = newStream;
	
	return 1;
}

static int lua_pgeFileClose(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.file.close(file) takes one argument.");
		
	pgeFile **handle = topgeFile(L, 1);
	
	pgeFileClose(*handle);
	
	return 0;
}

static int lua_pgeFileSeek(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 3)
		return luaL_error(L, "pge.file.seek(file, offset, direction) takes three arguments.");
		
	pgeFile **handle = topgeFile(L, 1);
	
	long offset = luaL_checkint(L, 2);
	
	unsigned int dir = luaL_checkint(L, 3);
	
	lua_pushinteger(L, pgeFileSeek(*handle, offset, dir));
	
	return 1;
}

static int lua_pgeFileRead(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "pge.file.read(file, size) takes two arguments.");
		
	pgeFile **handle = topgeFile(L, 1);
	
	unsigned int size = luaL_checkint(L, 2);
	
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	char *data = pgeMalloc(size);
	
	if(!data)
		return luaL_error(L, "pge.file.read(file, size) error. Not enough memory to allocate buffer.");
	
	int read = pgeFileRead(*handle, data, size);
	
	if(read <= 0)
		lua_pushnil(L);
	else
		lua_pushlstring(L, data, size);
	
	pgeFree(data);
	
	return 1;
}

static int lua_pgeFileReadNum(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.file.readnum(file) takes one argument.");
		
	pgeFile **handle = topgeFile(L, 1);
	
	int number = 0;
	
	int read = pgeFileRead(*handle, &number, 4);
	
	if(read != 4)
		lua_pushnil(L);
	else
		lua_pushinteger(L, number);
	
	return 1;
}

static int lua_pgeFileWrite(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "pge.file.write(file, data) takes two arguments.");
		
	pgeFile **handle = topgeFile(L, 1);
	
	int type = lua_type(L, 2);
	
	int write = 0;
		
	switch(type)
	{
		case LUA_TSTRING:
		{
			size_t size;
			char *data = (char *)luaL_checklstring(L, 2, &size);
			write = pgeFileWrite(*handle, (void *)data, size);
			break;
		}
			
		case LUA_TNUMBER:
		{
			float number = luaL_checknumber(L, 2);
			write = pgeFileWrite(*handle, &number, 4);
			break;
		}
			
		default:
			return luaL_error(L, "pge.file.write(file, data) data must be either a string or a number.");
			break;
	}
	
	lua_pushinteger(L, write);
	
	return 1;
}

static int lua_pgeFileTell(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.file.tell(file) takes one argument.");
		
	pgeFile **handle = topgeFile(L, 1);
	
	lua_pushinteger(L, pgeFileTell(*handle));
	
	return 1;
}

static int lua_pgeFileRewind(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.file.rewind(file) takes one argument.");
		
	pgeFile **handle = topgeFile(L, 1);
	
	lua_pushinteger(L, pgeFileRewind(*handle));
	
	return 1;
}

static int lua_pgeFileSize(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.file.size(file) takes one argument.");
		
	pgeFile **handle = topgeFile(L, 1);
	
	lua_pushinteger(L, pgeFileSize(*handle));
	
	return 1;
}

static int lua_pgeFileRemove(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.file.remove(filename) takes one argument.");
	
	const char *filepath = luaL_checkstring(L, 1);
	
	lua_pushinteger(L, pgeFileRemove(filepath));
	
	return 1;
}

static int lua_pgeFileRename(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "pge.file.rename(oldname, newname) takes two arguments.");
	
	const char *oldname = luaL_checkstring(L, 1);
	
	const char *newname = luaL_checkstring(L, 2);
	
	lua_pushinteger(L, pgeFileRename(oldname, newname));
	
	return 1;
}

static int lua_pgeFileExists(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.file.exists(filename) takes one argument.");
	
	const char *filename = luaL_checkstring(L, 1);
	
	lua_pushboolean(L, pgeFileExists(filename));
	
	return 1;
}

static const luaL_reg lua_pgeFile_methods[] =
{
	{"open",		lua_pgeFileOpen},
	{"openasync",	lua_pgeFileOpenAsync},
	{"openmemory",	lua_pgeFileMemoryOpen},
	{"close", 		lua_pgeFileClose},
	{"seek",		lua_pgeFileSeek},
	{"tell",		lua_pgeFileTell},
	{"rewind",		lua_pgeFileRewind},
	{"size",		lua_pgeFileSize},
	{"read",		lua_pgeFileRead},
	{"readnum",		lua_pgeFileReadNum},
	{"write",		lua_pgeFileWrite},
	{"remove",		lua_pgeFileRemove},
	{"rename",		lua_pgeFileRename},
	{"exists",		lua_pgeFileExists},
	{0, 0}
};

static int lua_pgeFile_tostring(lua_State *L)
{
	char buffer[128];
	
	sprintf(buffer, "%p", *topgeFile(L, 1));
	
	lua_pushfstring(L, "pgeFile (%s)", buffer);
	
	return 1;
}

static const luaL_reg lua_pgeFile_meta[] =
{
	{"__tostring", lua_pgeFile_tostring},
	{0, 0}
};
void lua_pgeFile_init(lua_State *L)
{	
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeFile_methods);
	luaL_newmetatable(L, "pgeFile");
	luaL_register(L, 0, lua_pgeFile_meta);
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pop(L, 1);
	
	lua_setfield(L, -2, "file"); /* pge */
	lua_pop(L, 1);

	lua_pushnumber(L, PGE_FILE_SET); lua_setglobal(L, "PGE_FILE_SET");
	lua_pushnumber(L, PGE_FILE_CUR); lua_setglobal(L, "PGE_FILE_CUR");
	lua_pushnumber(L, PGE_FILE_END); lua_setglobal(L, "PGE_FILE_END");
	
	lua_pushnumber(L, PGE_FILE_RDONLY); lua_setglobal(L, "PGE_FILE_RDONLY");
	lua_pushnumber(L, PGE_FILE_WRONLY); lua_setglobal(L, "PGE_FILE_WRONLY");
	lua_pushnumber(L, PGE_FILE_RDWR); lua_setglobal(L, "PGE_FILE_RDWR");
	lua_pushnumber(L, PGE_FILE_APPEND); lua_setglobal(L, "PGE_FILE_APPEND");
	lua_pushnumber(L, PGE_FILE_CREATE); lua_setglobal(L, "PGE_FILE_CREATE");
	lua_pushnumber(L, PGE_FILE_TRUNC); lua_setglobal(L, "PGE_FILE_TRUNC");
	lua_pushnumber(L, PGE_FILE_ALL); lua_setglobal(L, "PGE_FILE_ALL");
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
	
	lua_State *L = pgeLuaGetState();
	
	lua_pgeFile_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
