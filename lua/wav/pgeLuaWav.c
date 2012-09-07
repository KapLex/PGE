#include <pspkernel.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeWav.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE Wav", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD(); 

pgeLuaCreateUserdataHandlers(pgeWav, pgeWav*)

static int lua_pgeWavLoad(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.wav.load(filename) takes one argument.");
		
	const char *filepath = luaL_checkstring(L, 1);
	
	if(!filepath)
		return luaL_error(L, "Argument error: pge.wav.load(filename), argument must be a file path.");
		
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	pgeWav *newWav = pgeWavLoad(filepath);
	
	if(!newWav)
	{
		lua_pushnil(L);
		return 1;
	}
		
	pgeWav **luaNewWav = pushpgeWav(L);
	
	*luaNewWav = newWav;
	
	return 1;
}

static int lua_pgeWavLoadMemory(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.wav.loadmemory(data) takes one argument.");
		
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	size_t size;
		
	unsigned char *data = (unsigned char *)luaL_checklstring(L, 1, &size);
	
	pgeWav *newWav = pgeWavLoadMemory(data, size);
	
	if(!newWav)
	{
		lua_pushnil(L);
		return 1;
	}
		
	pgeWav **luaNewWav = pushpgeWav(L);
	
	*luaNewWav = newWav;
	
	return 1;
}

static int lua_pgeWavPlay(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.wav.play(wav) takes one argument.");
		
	pgeWav *handle = *topgeWav(L, 1);
	
	pgeWavPlay(handle);
	
	return 0;
}

static int lua_pgeWavStop(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.wav.stop(wav) takes one argument.");
		
	pgeWav *handle = *topgeWav(L, 1);
	
	pgeWavStop(handle);
	
	return 0;
}

static int lua_pgeWavStopAll(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "pge.wav.stopall() takes no arguments.");
		
	pgeWavStopAll();
	
	return 0;
}

static int lua_pgeWavIsPlaying(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.wav.isplaying(wav) takes one argument.");
		
	pgeWav *handle = *topgeWav(L, 1);
	
	lua_pushboolean(L, pgeWavIsPlaying(handle));
	
	return 1;
}

static int lua_pgeWavLoop(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1 && argc != 2)
		return luaL_error(L, "pge.wav.loop(wav, [true|false]) takes one or two arguments.");
		
	pgeWav *handle = *topgeWav(L, 1);
	
	int loop = 0;
	
	if(argc == 2)
		loop = lua_toboolean(L, 1);
	else
		loop = handle->loop ^= 1;
	
	pgeWavLoop(handle, loop);
	
	return 0;
}

static int lua_pgeWavVolume(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2 && argc != 3)
		return luaL_error(L, "pge.wav.volume(wav, leftvolume, [rightvolume]) takes two or three arguments.");
		
	pgeWav *handle = *topgeWav(L, 1);
	
	int leftvolume = luaL_checkint(L, 2);
	
	if(leftvolume < 0)
		leftvolume = 0;
	else if(leftvolume > 100)
		leftvolume = 100;
		
	int rightvolume = leftvolume;
	
	if(argc == 3)
	{
		rightvolume = luaL_checkint(L, 3);
	
		if(rightvolume < 0)
			rightvolume = 0;
		else if(rightvolume > 100)
			rightvolume = 100;
	}
	
	pgeWavVolume(handle, leftvolume, rightvolume);
	
	return 0;
}

static int lua_pgeWavData(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.wav.data(wav) takes one argument.");
		
	pgeWav *handle = *topgeWav(L, 1);
	
	lua_pushlstring(L, (char *)handle->data, handle->datalength);
	
	return 1;
}	

static int lua_pgeWavPitch(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "pge.wav.pitch(wav, pitch) takes two arguments.");
		
	pgeWav *handle = *topgeWav(L, 1);
	
	float pitch = lua_tonumber(L, 2);
	
	pgeWavPitch(handle, pitch);
	
	return 0;
}

static int lua_pgeWav_gc(lua_State *L)
{
	pgeWav **handle = topgeWav(L, 1);
	
	//printf("Unloading WAV\n");
	pgeWavDestroy(*handle);
	
	return 0;
}
	
static int lua_pgeWav_tostring(lua_State *L)
{
	char buffer[128];
	
	sprintf(buffer, "%p", *topgeWav(L, 1));
	
	lua_pushfstring(L, "pgeWav (%s)", buffer);
	
	return 1;
}

static const luaL_reg lua_pgeWav_methods[] =
{
	{"load",		lua_pgeWavLoad},
	{"loadmemory",	lua_pgeWavLoadMemory},
	{"play", 		lua_pgeWavPlay},
	{"stop",		lua_pgeWavStop},
	{"stopall",		lua_pgeWavStopAll},
	{"isplaying",	lua_pgeWavIsPlaying},
	{"loop",		lua_pgeWavLoop},
	{"volume",		lua_pgeWavVolume},
	{"pitch",		lua_pgeWavPitch},
	{"data",		lua_pgeWavData},
	{0, 0}
};
static const luaL_reg lua_pgeWav_meta[] =
{
	{"__gc",       lua_pgeWav_gc},
	{"__tostring", lua_pgeWav_tostring},
	{0, 0}
};

void lua_pgeWav_init(lua_State *L)
{	
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeWav_methods);
	luaL_newmetatable(L, "pgeWav");
	luaL_register(L, 0, lua_pgeWav_meta);
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pop(L, 1);
	lua_setfield(L, -2, "wav"); /* pge */
	lua_pop(L, 1);	
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
	
	pgeLuaRegisterDependency("pge.file");
	
	lua_State *L = pgeLuaGetState();
	
	pgeWavInit();
	
	lua_pgeWav_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
