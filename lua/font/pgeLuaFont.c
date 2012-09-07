#include <pspkernel.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeFont.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE Font", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(128);
PSP_NO_CREATE_MAIN_THREAD();

typedef unsigned int pgeColor;

pgeLuaCreateUserdataHandlers(pgeColor, pgeColor)
pgeLuaCreateUserdataHandlers(pgeFont, pgeFont*)

static int lua_pgeFont_gc(lua_State *L) // garbage collect
{
	//printf("Unload font\n");
	
	pgeFont **font = topgeFont(L, 1);
	
	pgeFontDestroy(*font);
	
	return 0;
}
	
static int lua_pgeFont_tostring(lua_State *L)
{
	char buffer[128];
	
	sprintf(buffer, "%p", *topgeFont(L, 1));
	
	lua_pushfstring(L, "pgeFont (%s)", buffer);
	
	return 1;
}

static int lua_pgeFontLoad(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2 && argc != 3)
		return luaL_error(L, "Argument error: pge.font.load(filename, pixelsize, [location]) takes two or three arguments.");
		
	const char *filepath = luaL_checkstring(L, 1);
	
	if(!filepath)
		return luaL_error(L, "Argument error: pge.font.load(filename, pixelsize, [location]), argument must be a file path.");
		
	int fontsize = luaL_checkint(L, 2);
	
	int location = PGE_RAM;
	
	if(argc == 3)
		location = luaL_checkint(L, 3);
		
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	pgeFont *font = pgeFontLoad(filepath, fontsize, PGE_FONT_SIZE_PIXELS, location);
	
	if(!font)
	{
		lua_pushnil(L);
		return 1;
	}
		
	pgeFont **luafont = pushpgeFont(L);
	
	*luafont = font;
	
	return 1;
}

static int lua_pgeFontLoadMemory(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 3)
		return luaL_error(L, "Argument error: pge.font.loadmemory(data, pixelsize, [location]) takes three arguments.");
	
	size_t size;
		
	unsigned char *data = (unsigned char *)luaL_checklstring(L, 1, &size);
	
	if(!data)
		return luaL_error(L, "Argument error: pge.font.loadmemory(data, pixelsize, [location]), data not valid.");
		
	int fontsize = luaL_checkint(L, 2);
	
	int location = PGE_RAM;
	
	if(argc == 3)
		location = luaL_checkint(L, 3);
		
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	pgeFont *font = pgeFontLoadMemory(data, size, fontsize, PGE_FONT_SIZE_PIXELS, location);
	
	if(!font)
	{
		lua_pushnil(L);
		return 1;
	}
		
	pgeFont **luafont = pushpgeFont(L);
	
	*luafont = font;
	
	return 1;
}

static int lua_pgeFontPrint(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 5)
		return luaL_error(L, "Argument error: pge.font.print(font, x, y, color, text) takes five arguments.");
	
	pgeFont **font = topgeFont(L, 1);
	
	short x = luaL_checkint(L, 2);
	
	short y = luaL_checkint(L, 3);
	
	pgeColor color = *topgeColor(L, 4);
	
	const char *text = luaL_checkstring(L, 5);
	
	lua_pushinteger(L, pgeFontPrintf(*font, x, y, color, text));
	
	return 1;
}

static int lua_pgeFontPrintCenter(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 4)
		return luaL_error(L, "Argument error: pge.font.printcenter(font, y, color, text) takes four arguments.");
	
	pgeFont **font = topgeFont(L, 1);
	
	short y = luaL_checkint(L, 2);
	
	pgeColor color = *topgeColor(L, 3);
	
	const char *text = luaL_checkstring(L, 4);
	
	lua_pushinteger(L, pgeFontPrintfCenter(*font, y, color, text));
	
	return 1;
}

static int lua_pgeFontMeasure(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.font.measure(font, text) takes two arguments.");
	
	pgeFont **font = topgeFont(L, 1);
	
	const char *text = luaL_checkstring(L, 2);
	
	lua_pushinteger(L, pgeFontMeasureText(*font, text));
	
	return 1;
}

static int lua_pgeFontHeight(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.font.height(font) takes one argument.");
	
	pgeFont **font = topgeFont(L, 1);
	
	lua_pushinteger(L, pgeFontGetHeight(*font));
	
	return 1;
}

static int lua_pgeFontActivate(lua_State *L)
{	
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.font.activate(font) takes one argument.");
		
	pgeFont **font = topgeFont(L, 1);
			
	pgeFontActivate(*font);
	
	return 0;
}

static int lua_pgeFontSetCharset(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.font.setcharset(charset) takes one argument.");
	
	const char *charset = luaL_checkstring(L, 1);
	
	lua_pushboolean(L, pgeFontSetCharset(charset));
	
	return 1;
}

static int lua_pgeFontResetCharset(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.font.resetcharset() takes no arguments.");
	
	pgeFontResetCharset();
	
	return 0;
}

static const luaL_reg lua_pgeFont_methods[] =
{
	{"load",			lua_pgeFontLoad},
	{"loadmemory",		lua_pgeFontLoadMemory},
	{"print",			lua_pgeFontPrint},
	{"printcenter",		lua_pgeFontPrintCenter},
	{"measure",			lua_pgeFontMeasure},
	{"height",			lua_pgeFontHeight},
	{"activate",		lua_pgeFontActivate},
	{"setcharset",		lua_pgeFontSetCharset},
	{"ressetcharset",	lua_pgeFontResetCharset},
	{0, 0}
};

static const luaL_reg lua_pgeFont_meta[] =
{
	{"__gc",       lua_pgeFont_gc},
	{"__tostring", lua_pgeFont_tostring},
	{0, 0}
};
	
void lua_pgeFont_init(lua_State *L)
{	
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeFont_methods);
	luaL_newmetatable(L, "pgeFont");
	luaL_register(L, 0, lua_pgeFont_meta);
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pop(L, 1);
	lua_setfield(L, -2, "font"); /* pge */
	lua_pop(L, 1);	
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
	
	pgeLuaRegisterDependency("pge.gfx");

	lua_State *L = pgeLuaGetState();
	
	pgeFontInit();
	
	lua_pgeFont_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
