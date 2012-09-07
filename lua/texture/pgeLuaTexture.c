#include <pspkernel.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../pgemodule.h"
#include "../../pgeTexture.h"
#include "../../pgeGfx.h"

PSP_MODULE_INFO("PGE Texture", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD();

#define CLAMP(val, min, max) ((val)>(max)?(max):((val)<(min)?(min):(val)))

typedef unsigned int pgeColor;

pgeLuaCreateUserdataHandlers(pgeTexture, pgeTexture*)
pgeLuaCreateUserdataHandlers(pgeColor, pgeColor)

static int lua_pgeTexture_gc(lua_State *L)
{	
	pgeTexture **texture = topgeTexture(L, 1);
	
	pgeTextureDestroy(*texture);
	
	return 0;
}
	
static int lua_pgeTexture_tostring(lua_State *L)
{
	char buffer[128];
	
	sprintf(buffer, "%p", *topgeTexture(L, 1));
	
	lua_pushfstring(L, "pgeTexture (%s)", buffer);
	
	return 1;
}

static int lua_pgeTextureLoad(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1 && argc != 2 && argc != 3)
		return luaL_error(L, "Argument error: pge.texture.load(filename, [memorylocation], [swizzle]) takes one, two or three arguments.");
		
	const char *filepath = luaL_checkstring(L, 1);
	
	if(!filepath)
		return luaL_error(L, "Argument error: pge.texture.load(filename, [memorylocation], [swizzle]), filename must be a file path.");
		
	int location;
	
	if(argc > 1)
		location = luaL_checkint(L, 2);
	else
		location = PGE_RAM;
		
	unsigned char swizzle = 1;
	
	if(argc > 2)
		swizzle = lua_toboolean(L, 3);
		
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	pgeTexture *texture = pgeTextureLoad(filepath, location, swizzle);
	
	if(!texture)
	{
		lua_pushnil(L);
		return 1;
	}
		
	pgeTexture **luatexture = pushpgeTexture(L);
	
	*luatexture = texture;
	
	return 1;
}

static int lua_pgeTextureLoadMemory(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1 && argc != 2 && argc != 3)
		return luaL_error(L, "Argument error: pge.texture.loadmemory(data, [memorylocation], [swizzle]) takes one, two or three arguments.");
		
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	size_t size;
		
	unsigned char *data = (unsigned char *)luaL_checklstring(L, 1, &size);
	
	int location;
	
	if(argc > 1)
		location = luaL_checkint(L, 2);
	else
		location = PGE_RAM;
		
	unsigned char swizzle = 1;
	
	if(argc > 2)
		swizzle = lua_toboolean(L, 3);
	
	pgeTexture *texture = pgeTextureLoadMemory(data, size, location, swizzle);
	
	if(!texture)
	{
		lua_pushnil(L);
		return 1;
	}
		
	pgeTexture **luaTexture = pushpgeTexture(L);
	
	*luaTexture = texture;
	
	return 1;
}

static int lua_pgeTextureCreate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2 && argc != 3 && argc != 4)
		return luaL_error(L, "Argument error: pge.texture.create(width, height, [format], [memorylocation]) takes two, three or four arguments.");
		
	int width = luaL_checkint(L, 1);
	int height = luaL_checkint(L, 2);
	
	int format;
	
	if(argc > 2)
		format = luaL_checkint(L, 3);
	else
		format = PGE_PIXEL_FORMAT_8888;
		
	int location;
		
	if(argc == 4)
		location = luaL_checkint(L, 4);
	else
		location = PGE_RAM;
		
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	pgeTexture *texture = pgeTextureCreate(width, height, format, location);
	
	if(!texture)
	{
		lua_pushnil(L);
		return 1;
	}
		
	pgeTexture **luatexture = pushpgeTexture(L);
	
	*luatexture = texture;
	
	return 1;
}

static int lua_pgeTextureActivate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.texture.activate(texture) takes one argument.");
		
	pgeTexture **texture = topgeTexture(L, 1);
	
	pgeTextureActivate(*texture);
	
	return 0;
}

static int lua_pgeGfxTextureDraw(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 3 && argc != 5 && argc != 9 && argc != 10 && argc != 11)
		return luaL_error(L, "pge.texture.draw(texture, x, y, [width], [height], [texstartx], [texstarty], [texendx], [texendy], [rotation], [alpha]) takes three, five, nine, ten or eleven arguments.");
		
	pgeTexture *texture = *topgeTexture(L, 1);
	
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float width = texture->width;
	float height = texture->height;
	float u0 = 0.0f;
	float u1 = texture->width;
	float v0 = 0.0f;
	float v1 = texture->height;
	float angle = 0.0f;
	unsigned char alpha = 255;
	
	if(argc > 3)
	{
		width = luaL_checknumber(L, 4);
		height = luaL_checknumber(L, 5);
	}
	
	if(argc > 5)
	{
		u0 = luaL_checknumber(L, 6);
		v0 = luaL_checknumber(L, 7);
		u1 = luaL_checknumber(L, 8);
		v1 = luaL_checknumber(L, 9);
	}
		
	if(argc > 9)
		angle = luaL_checknumber(L, 10);
			
	if(argc == 11)
		alpha = CLAMP(luaL_checkint(L, 11), 0, 255);
			
	pgeRect rect = {x, y, width, height};
		
	pgeRect texrect = {u0, v0, u1, v1};
			
	pgeGfxDrawTexture(&rect, &texrect, angle, alpha);

	return 0;
}

static int lua_pgeGfxTextureDrawEasy(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 3 && argc != 4 && argc != 5)
		return luaL_error(L, "pge.texture.draweasy(texture, x, y, [rotation], [alpha]) takes three, four or five arguments.");
		
	pgeTexture **texture = topgeTexture(L, 1);
	
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	
	float angle = 0.0f;
	unsigned char alpha = 255;
		
	if(argc > 3)
		angle = luaL_checknumber(L, 4);
			
	if(argc == 5)
		alpha = CLAMP(luaL_checkint(L, 5), 0, 255);
			
	pgeGfxDrawTextureEasy(*texture, x, y, angle, alpha);
	
	return 0;
}

static int lua_pgeTextureWidth(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.texture.width(texture) takes one argument.");
		
	pgeTexture *texture = *topgeTexture(L, 1);
	
	lua_pushinteger(L, texture->width);
	
	return 1;
}

static int lua_pgeTextureHeight(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.texture.height(texture) takes one argument.");
		
	pgeTexture *texture = *topgeTexture(L, 1);
	
	lua_pushinteger(L, texture->height);
	
	return 1;
}

static int lua_pgeTextureSetRenderTarget(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.texture.settarget(texture) takes one argument.");
		
	pgeTexture *texture = *topgeTexture(L, 1);
	
	if(texture->location == PGE_RAM)
	{
		lua_pushboolean(L, 0);
	}
	else
	{
		pgeGfxRenderToTexture(texture);
		lua_pushboolean(L, 1);
	}
	
	return 1;
}

static int lua_pgeTextureSave(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "pge.texture.save(texture, filename) takes two arguments.");
		
	pgeTexture *texture = *topgeTexture(L, 1);
	
	const char *filepath = luaL_checkstring(L, 2);
	
	pgeTextureSave(texture, filepath);
	
	return 1;
}

static int lua_pgeTextureScreenshot(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.texture.screenshot(filename) takes one argument."); 

	const char *filename = luaL_checkstring(L, 1);
	
	pgeTextureScreenshot(filename);
		
	return 0;
}

static int lua_pgeTextureModeSet(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.texture.setmode(mode) takes one argument.");
		
	int mode = luaL_checkint(L, 1);
	
	lua_pushinteger(L, pgeTextureModeSet(mode));
	
	return 1;
}

static int lua_pgeTextureToRam(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.texture.toram(texture) takes one argument.");
		
	pgeTexture **texture = topgeTexture(L, 1);
	
	lua_pushboolean(L, pgeTextureToRam(*texture));
	
	return 1;
}

static int lua_pgeTextureToVram(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.texture.tovram(texture) takes one argument.");
		
	pgeTexture **texture = topgeTexture(L, 1);
	
	lua_pushboolean(L, pgeTextureToVram(*texture));
	
	return 1;
}

static int lua_pgeTextureSwizzle(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.texture.swizzle(texture) takes one argument.");
		
	pgeTexture **texture = topgeTexture(L, 1);
	
	lua_pushboolean(L, pgeTextureSwizzle(*texture));
	
	return 1;
}

static int lua_pgeTextureUnswizzle(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "pge.texture.unswizzle(texture) takes one argument.");
		
	pgeTexture **texture = topgeTexture(L, 1);
	
	lua_pushboolean(L, pgeTextureUnswizzle(*texture));
	
	return 1;
}

static int lua_pgeTexturePixel(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 3 && argc != 4)
		return luaL_error(L, "pge.texture.pixel(texture, x, y, [color]) takes three or four arguments.");
		
	pgeTexture **texture = topgeTexture(L, 1);
	
	unsigned int x = luaL_checkint(L, 2);
	
	unsigned int y = luaL_checkint(L, 3);
	
	if(argc == 4)
	{
		pgeColor *color = topgeColor(L, 4);
		
		pgeTextureSetPixel(*texture, *color, x, y);
		
		return 0;
	}
	
	pgeColor *color = pushpgeColor(L);
	
	*color = pgeTextureGetPixel(*texture, x, y);
		
	return 1;
}

static const luaL_reg lua_pgeTexture_methods[] =
{
	{"load",		lua_pgeTextureLoad},
	{"loadmemory",	lua_pgeTextureLoadMemory},
	{"create", 		lua_pgeTextureCreate},
	{"activate",	lua_pgeTextureActivate},
	{"draweasy",	lua_pgeGfxTextureDrawEasy},
	{"draw",		lua_pgeGfxTextureDraw},
	{"width",		lua_pgeTextureWidth},
	{"height",		lua_pgeTextureHeight},
	{"setmode",		lua_pgeTextureModeSet},
	{"settarget",	lua_pgeTextureSetRenderTarget},
	{"save",		lua_pgeTextureSave},
	{"toram",		lua_pgeTextureToRam},
	{"tovram",		lua_pgeTextureToVram},
	{"swizzle",		lua_pgeTextureSwizzle},
	{"unswizzle",	lua_pgeTextureUnswizzle},
	{"pixel",		lua_pgeTexturePixel},
	{"screenshot",	lua_pgeTextureScreenshot},
	{0, 0}
};

static const luaL_reg lua_pgeTexture_meta[] =
{
	{"__gc",       lua_pgeTexture_gc},
	{"__tostring", lua_pgeTexture_tostring},
	{0, 0}
};

void lua_pgeTexture_init(lua_State *L)
{
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeTexture_methods);
	luaL_newmetatable(L, "pgeTexture");
	luaL_register(L, 0, lua_pgeTexture_meta);
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pop(L, 1);
	lua_setfield(L, -2, "texture"); /* pge */
	lua_pop(L, 1);
	
	lua_pushnumber(L, PGE_PIXEL_FORMAT_5650); lua_setglobal(L, "PGE_PIXEL_FORMAT_5650");
	lua_pushnumber(L, PGE_PIXEL_FORMAT_5551); lua_setglobal(L, "PGE_PIXEL_FORMAT_5551");
	lua_pushnumber(L, PGE_PIXEL_FORMAT_4444); lua_setglobal(L, "PGE_PIXEL_FORMAT_4444");
	lua_pushnumber(L, PGE_PIXEL_FORMAT_8888); lua_setglobal(L, "PGE_PIXEL_FORMAT_8888");
	lua_pushnumber(L, PGE_PIXEL_FORMAT_T4); lua_setglobal(L, "PGE_PIXEL_FORMAT_T4");
	lua_pushnumber(L, PGE_PIXEL_FORMAT_T8); lua_setglobal(L, "PGE_PIXEL_FORMAT_T8");
	lua_pushnumber(L, PGE_PIXEL_FORMAT_T16); lua_setglobal(L, "PGE_PIXEL_FORMAT_T16");
	lua_pushnumber(L, PGE_PIXEL_FORMAT_T32); lua_setglobal(L, "PGE_PIXEL_FORMAT_T32");
	
	lua_pushnumber(L, PGE_TEX_MODE_MODULATE); lua_setglobal(L, "PGE_TEX_MODE_MODULATE");
	lua_pushnumber(L, PGE_TEX_MODE_DECAL); lua_setglobal(L, "PGE_TEX_MODE_DECAL");
	lua_pushnumber(L, PGE_TEX_MODE_BLEND); lua_setglobal(L, "PGE_TEX_MODE_BLEND");
	lua_pushnumber(L, PGE_TEX_MODE_REPLACE); lua_setglobal(L, "PGE_TEX_MODE_REPLACE");
	lua_pushnumber(L, PGE_TEX_MODE_ADD); lua_setglobal(L, "PGE_TEX_MODE_ADD");
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
	
	pgeLuaRegisterDependency("pge.gfx");
		
	lua_State *L = pgeLuaGetState();
	
	lua_pgeTexture_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
