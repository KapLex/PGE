#include <pspkernel.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeMp3.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE Mp3", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD();

pgeLuaCreateUserdataHandlers(pgeMp3Info, pgeMp3Info)

static int lua_pgeMp3Play(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.play(filename) takes one argument.");
	
	const char *filename = luaL_checkstring(L, 1);
	
	lua_pushboolean(L, pgeMp3Play(filename));
	
	return 1;
}

static int lua_pgeMp3PlayMemory(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.playmemory(data) takes one argument.");
		
	size_t size;
		
	unsigned char *data = (unsigned char *)luaL_checklstring(L, 1, &size);
	
	lua_pushboolean(L, pgeMp3PlayMemory(data, size));
	
	return 1;
}

static int lua_pgeMp3Stop(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.mp3.stop() takes no arguments.");
	
	pgeMp3Stop();
	
	return 0;
}

static int lua_pgeMp3Pause(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.mp3.pause() takes no arguments.");
	
	pgeMp3Pause();
	
	return 0;
}

static int lua_pgeMp3Loop(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.loop(true|false) takes one argument.");
	
	int loop = lua_toboolean(L, 1);
	
	pgeMp3Loop(loop);
	
	return 0;
}

static int lua_pgeMp3Volume(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.volume(volume) takes one argument.");
	
	int volume = lua_tointeger(L, 1);
	
	int newvolume = pgeMp3Volume(volume);
	
	lua_pushinteger(L, newvolume);
	
	return 1;
}

static int lua_pgeMp3IsPlaying(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.mp3.isplaying() takes no arguments.");
	
	lua_pushboolean(L, pgeMp3IsPlaying());
	
	return 1;
}

static int lua_pgeMp3GetAudioData(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.getaudiodata(position) takes one argument.");
		
	int position = luaL_checkint(L, 1);
		
	short *data = pgeMp3GetAudioData();
	
	lua_pushinteger(L, data[position]);
	
	return 1;
}

static int lua_pgeMp3GetInfo(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.mp3.getinfo() takes no arguments.");
	
	pgeMp3Info mp3info = pgeMp3GetInfo();
	
	pgeMp3Info *luaMp3Info = pushpgeMp3Info(L);
	
	*luaMp3Info = mp3info;
	
	return 1;
}

static int lua_pgeMp3GetInfoTitle(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.title(mp3info) takes one argument.");
	
	pgeMp3Info mp3info = *topgeMp3Info(L, 1);
	
	if(mp3info.title != NULL)
		lua_pushstring(L, mp3info.title);
	else
		lua_pushstring(L, "");
	
	return 1;
}

static int lua_pgeMp3GetInfoArtist(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.artist(mp3info) takes one argument.");
	
	pgeMp3Info mp3info = *topgeMp3Info(L, 1);
	
	if(mp3info.artist != NULL)
		lua_pushstring(L, mp3info.artist);
	else
		lua_pushstring(L, "");
	
	return 1;
}

static int lua_pgeMp3GetInfoAlbum(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.album(mp3info) takes one argument.");
	
	pgeMp3Info mp3info = *topgeMp3Info(L, 1);
	
	if(mp3info.album != NULL)
		lua_pushstring(L, mp3info.album);
	else
		lua_pushstring(L, "");
	
	return 1;
}

static int lua_pgeMp3GetInfoYear(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.year(mp3info) takes one argument.");
	
	pgeMp3Info mp3info = *topgeMp3Info(L, 1);
	
	if(mp3info.year != NULL)
		lua_pushstring(L, mp3info.year);
	else
		lua_pushstring(L, "");
	
	return 1;
}

static int lua_pgeMp3GetInfoComment(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.comment(mp3info) takes one argument.");
	
	pgeMp3Info mp3info = *topgeMp3Info(L, 1);
	
	if(mp3info.comment != NULL)
		lua_pushstring(L, mp3info.comment);
	else
		lua_pushstring(L, "");
	
	return 1;
}

static int lua_pgeMp3GetInfoGenreCode(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.genrecode(mp3info) takes one argument.");
	
	pgeMp3Info mp3info = *topgeMp3Info(L, 1);
	
	if(mp3info.genrecode != NULL)
		lua_pushstring(L, mp3info.genrecode);
	else
		lua_pushstring(L, "");
	
	return 1;
}

static int lua_pgeMp3GetInfoGenreText(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.genretext(mp3info) takes one argument.");
	
	pgeMp3Info mp3info = *topgeMp3Info(L, 1);
	
	if(mp3info.genretext != NULL)
		lua_pushstring(L, mp3info.genretext);
	else
		lua_pushstring(L, "");
	
	return 1;
}

static int lua_pgeMp3GetInfoID3Version(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.id3version(mp3info) takes one argument.");
	
	pgeMp3Info mp3info = *topgeMp3Info(L, 1);
	
	lua_pushstring(L, mp3info.id3version);
	
	return 1;
}

static int lua_pgeMp3GetInfoTrack(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.track(mp3info) takes one argument.");
	
	pgeMp3Info mp3info = *topgeMp3Info(L, 1);
	
	lua_pushinteger(L, mp3info.track);
	
	return 1;
}

static int lua_pgeMp3GetInfoTrackText(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.tracktext(mp3info) takes one argument.");
	
	pgeMp3Info mp3info = *topgeMp3Info(L, 1);
	
	if(mp3info.tracktext != NULL)
		lua_pushstring(L, mp3info.tracktext);
	else
		lua_pushstring(L, "");
	
	return 1;
}

static int lua_pgeMp3GetInfoPictureOffset(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.picoffset(mp3info) takes one argument.");
	
	pgeMp3Info mp3info = *topgeMp3Info(L, 1);
	
	lua_pushinteger(L, mp3info.pictureoffset);
	
	return 1;
}

static int lua_pgeMp3GetInfoPictureLength(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.piclength(mp3info) takes one argument.");
	
	pgeMp3Info mp3info = *topgeMp3Info(L, 1);
	
	lua_pushinteger(L, mp3info.picturelength);
	
	return 1;
}

static int lua_pgeMp3GetInfoLength(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.mp3.length(mp3info) takes one argument.");
	
	pgeMp3Info mp3info = *topgeMp3Info(L, 1);
	
	lua_pushinteger(L, mp3info.length);
	
	return 1;
}

static const luaL_reg lua_pgeMp3Info_methods[] =
{
	{"title",			lua_pgeMp3GetInfoTitle},
	{"artist",			lua_pgeMp3GetInfoArtist},
	{"album",			lua_pgeMp3GetInfoAlbum},
	{"year",			lua_pgeMp3GetInfoYear},
	{"comment",			lua_pgeMp3GetInfoComment},
	{"genrecode",		lua_pgeMp3GetInfoGenreCode},
	{"genre",			lua_pgeMp3GetInfoGenreText},
	{"id3version",		lua_pgeMp3GetInfoID3Version},
	{"track",			lua_pgeMp3GetInfoTrack},
	{"tracktext",		lua_pgeMp3GetInfoTrackText},
	{"picoffset",		lua_pgeMp3GetInfoPictureOffset},
	{"piclength",		lua_pgeMp3GetInfoPictureLength},
	{"length",			lua_pgeMp3GetInfoLength},
	{0, 0}
};

static const luaL_reg lua_pgeMp3_functions[] =
{
	{"play",			lua_pgeMp3Play},
	{"playmemory",		lua_pgeMp3PlayMemory},
	{"stop",			lua_pgeMp3Stop},
	{"pause",			lua_pgeMp3Pause},
	{"loop",			lua_pgeMp3Loop},
	{"volume",			lua_pgeMp3Volume},
	{"isplaying",		lua_pgeMp3IsPlaying},
	{"getinfo",			lua_pgeMp3GetInfo},
	{"getaudiodata",	lua_pgeMp3GetAudioData},
	{0, 0}
};

void lua_pgeMp3_init(lua_State *L)
{	
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeMp3_functions);
	luaL_register(L, 0, lua_pgeMp3Info_methods);
	luaL_newmetatable(L, "pgeMp3Info");
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pop(L, 1);
	lua_setfield(L, -2, "mp3"); /* pge */
	lua_pop(L, 1);	
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
	
	pgeLuaRegisterDependency("pge.file");
		
	lua_State *L = pgeLuaGetState();
	
	lua_pgeMp3_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
