#include <pspkernel.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeGfx.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE Gfx", 0x0006, 1, 1);
//PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER|PSP_THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD(); 

#define CLAMP(val, min, max) ((val)>(max)?(max):((val)<(min)?(min):(val)))

#ifndef RGBA
#define RGBA(r,g,b,a)	((r) | ((g)<<8) | ((b)<<16) | ((a)<<24))
#endif

#define A(color) ((u8)(color >> 24 & 0xFF))
#define B(color) ((u8)(color >> 16 & 0xFF))
#define G(color) ((u8)(color >> 8 & 0xFF))
#define R(color) ((u8)(color & 0xFF))

typedef unsigned int pgeColor;

pgeLuaCreateUserdataHandlers(pgeColor, pgeColor)

static int lua_pgeGfxStartDrawing(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.gfx.startdrawing() takes no arguments.");
	
	pgeGfxStartDrawing();
	
	return 0;
}

static int lua_pgeGfxEndDrawing(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.gfx.enddrawing() takes no arguments.");
	
	pgeGfxEndDrawing();
	
	return 0;
}

static int lua_pgeGfxSwapBuffers(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0 && argc != 1)
		return luaL_error(L, "Argment error: pge.gfx.swapbuffers([vsync]) takes zero or one argument.");
		
	int vsync = 1;
	
	if(argc == 1)
		vsync = lua_toboolean(L, 1);
	
	pgeGfxSwapBuffers(vsync);
	
	return 0;
}

static int lua_pgeGfxCreateColor(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 3 && argc != 4)
		return luaL_error(L, "Argument error: pge.gfx.createcolor(r, g, b, [a]) takes either three color arguments or three color arguments and an alpha value."); 
	
	pgeColor *color = pushpgeColor(L);
	
	unsigned char r = CLAMP(luaL_checkint(L, 1), 0, 255); 
	unsigned char g = CLAMP(luaL_checkint(L, 2), 0, 255); 
	unsigned char b = CLAMP(luaL_checkint(L, 3), 0, 255);
	unsigned char a = 255;
	
	if(argc == 4)
	{
		a = CLAMP(luaL_checkint(L, 4), 0, 255);
	}

	*color = RGBA(r, g, b, a);
	
	return 1;
}

static int lua_pgeGfxColorRed(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 1 && argc != 2)
		return luaL_error(L, "Argument error: pge.gfx.red(color, [value]) takes one or two arguments.");
		
	pgeColor *color = topgeColor(L, 1);
	
	if(argc == 1)
	{
		lua_pushinteger(L, R(*color));
		
		return 1;
	}
	else
	{
		unsigned char r = CLAMP(luaL_checkint(L, 2), 0, 255);

		*color = RGBA(r, G(*color), B(*color), A(*color));
		
		return 0;
	}
}

static int lua_pgeGfxColorGreen(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 1 && argc != 2)
		return luaL_error(L, "Argument error: pge.gfx.green(color, [value]) takes one or two arguments.");
		
	pgeColor *color = topgeColor(L, 1);
	
	if(argc == 1)
	{
		lua_pushinteger(L, G(*color));
		
		return 1;
	}
	else
	{
		unsigned char g = CLAMP(luaL_checkint(L, 2), 0, 255);

		*color = RGBA(R(*color), g, B(*color), A(*color));
		
		return 0;
	}
}

static int lua_pgeGfxColorBlue(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 1 && argc != 2)
		return luaL_error(L, "Argument error: pge.gfx.blue(color, [value]) takes one or two arguments.");
		
	pgeColor *color = topgeColor(L, 1);
	
	if(argc == 1)
	{
		lua_pushinteger(L, B(*color));
		
		return 1;
	}
	else
	{
		unsigned char b = CLAMP(luaL_checkint(L, 2), 0, 255);

		*color = RGBA(R(*color), G(*color), b, A(*color));
		
		return 0;
	}
}

static int lua_pgeGfxColorAlpha(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 1 && argc != 2)
		return luaL_error(L, "Argument error: pge.gfx.alpha(color, [value]) takes one or two arguments.");
		
	pgeColor *color = topgeColor(L, 1);
	
	if(argc == 1)
	{
		lua_pushinteger(L, A(*color));
		
		return 1;
	}
	else
	{
		unsigned char a = CLAMP(luaL_checkint(L, 2), 0, 255);

		*color = RGBA(R(*color), G(*color), B(*color), a);
		
		return 0;
	}
}

static int lua_pgeGfxClearScreen(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1 && argc != 0)
		return luaL_error(L, "Argment error: pge.gfx.clearscreen([color]) takes zero or one argument.");
	
	pgeColor color = 0;
	
	if(argc == 1)
		color = *topgeColor(L, 1);
	
	pgeGfxClearScreen(color);
	
	return 0;
}

static int lua_pgeGfxRenderToScreen(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.gfx.rendertoscreen() takes no arguments.");
	
	pgeGfxRenderToScreen();
	
	return 0;
}

static int lua_pgeGfxDrawLine(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 5)
		return luaL_error(L, "Argument error: pge.gfx.drawline(startx, starty, endx, endy, color) takes five arguments."); 
	
	float startx = luaL_checknumber(L, 1); 
	float starty = luaL_checknumber(L, 2);
	float endx = luaL_checknumber(L, 3);
	float endy = luaL_checknumber(L, 4);
	pgeColor color = *topgeColor(L, 5);
	
	pgeGfxDrawLine(startx, starty, endx, endy, color);
		
	return 0;
}

static int lua_pgeGfxDrawStar(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 6 && argc != 7)
		return luaL_error(L, "Argument error: pge.gfx.drawstar(x, y, outerradius, innerradius, numpoints, color, [rotation]) takes six or seven arguments."); 
	
	float x = luaL_checknumber(L, 1); 
	float y = luaL_checknumber(L, 2);
	float outerradius = luaL_checknumber(L, 3);
	float innerradius = luaL_checknumber(L, 4);
	unsigned int numpoints = luaL_checkint(L, 5);
	pgeColor color = *topgeColor(L, 6);
	
	float rotation = 0.0f;
	
	if(argc == 7)
		rotation = luaL_checknumber(L, 7);
	
	pgeGfxDrawStar(x, y, outerradius, innerradius, numpoints, color, rotation);
		
	return 0;
}

static int lua_pgeGfxDrawStarOutline(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 6 && argc != 7)
		return luaL_error(L, "Argument error: pge.gfx.drawstaroutline(x, y, outerradius, innerradius, numpoints, color, [rotation]) takes six or seven arguments."); 
	
	float x = luaL_checknumber(L, 1); 
	float y = luaL_checknumber(L, 2);
	float outerradius = luaL_checknumber(L, 3);
	float innerradius = luaL_checknumber(L, 4);
	unsigned int numpoints = luaL_checkint(L, 5);
	pgeColor color = *topgeColor(L, 6);
	float rotation = 0.0f;
	
	if(argc == 7)
		rotation = luaL_checknumber(L, 7);
	
	pgeGfxDrawStarOutline(x, y, outerradius, innerradius, numpoints, color, rotation);
		
	return 0;
}

static int lua_pgeGfxDrawCircle(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 5)
		return luaL_error(L, "Argument error: pge.gfx.drawcircle(x, y, radius, numsteps, color) takes five arguments."); 
	
	float x = luaL_checknumber(L, 1); 
	float y = luaL_checknumber(L, 2);
	float radius = luaL_checknumber(L, 3);
	unsigned int numsteps = luaL_checkint(L, 4);
	pgeColor color = *topgeColor(L, 5);
	
	pgeGfxDrawCircle(x, y, radius, numsteps, color);
		
	return 0;
}

static int lua_pgeGfxDrawCircleOutline(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 5)
		return luaL_error(L, "Argument error: pge.gfx.drawcircleoutline(x, y, radius, numsteps, color) takes five arguments."); 
	
	float x = luaL_checknumber(L, 1); 
	float y = luaL_checknumber(L, 2);
	float radius = luaL_checknumber(L, 3);
	unsigned int numsteps = luaL_checkint(L, 4);
	pgeColor color = *topgeColor(L, 5);
	
	pgeGfxDrawCircleOutline(x, y, radius, numsteps, color);
		
	return 0;
}

static int lua_pgeGfxDrawRect(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 5 && argc != 6)
		return luaL_error(L, "Argument error: pge.gfx.drawrect(x, y, width, height, color, [rotation]) takes five or six arguments."); 
	
	float x = luaL_checknumber(L, 1); 
	float y = luaL_checknumber(L, 2);
	float width = luaL_checknumber(L, 3);
	float height = luaL_checknumber(L, 4);
	pgeColor color = *topgeColor(L, 5);
	
	float rotation = 0.0f;
	
	if(argc == 6)
		rotation = luaL_checknumber(L, 6);
	
	pgeRect rect = {x, y, width, height};

	pgeGfxDrawRect(&rect, color, rotation);
		
	return 0;
}

static int lua_pgeGfxDrawRectOutline(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 5 && argc != 6)
		return luaL_error(L, "Argument error: pge.gfx.drawrectoutline(x, y, width, height, color, [rotation]) takes five or six arguments."); 
	
	float x = luaL_checknumber(L, 1); 
	float y = luaL_checknumber(L, 2);
	float width = luaL_checknumber(L, 3);
	float height = luaL_checknumber(L, 4);
	pgeColor color = *topgeColor(L, 5);
	
	float rotation = 0.0f;
	
	if(argc == 6)
		rotation = luaL_checknumber(L, 6);
		
	pgeRect rect = {x, y, width, height};
	
	pgeGfxDrawRectOutline(&rect, color, rotation);
		
	return 0;
}

static int lua_pgeGfxDrawRectGrad(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 8 && argc != 9)
		return luaL_error(L, "Argument error: pge.gfx.drawrectgrad(x, y, width, height, color1, color2, color3, color4, [rotation]) takes eight or nine arguments."); 
	
	float x = luaL_checknumber(L, 1); 
	float y = luaL_checknumber(L, 2);
	float width = luaL_checknumber(L, 3);
	float height = luaL_checknumber(L, 4);
	pgeColor color1 = *topgeColor(L, 5);
	pgeColor color2 = *topgeColor(L, 6);
	pgeColor color3 = *topgeColor(L, 7);
	pgeColor color4 = *topgeColor(L, 8);
	
	float rotation = 0.0f;
	
	if(argc == 9)
		rotation = luaL_checknumber(L, 9);
		
	pgeRect rect = {x, y, width, height};
	
	pgeGfxDrawRectGrad(&rect, color1, color2, color3, color4, rotation);
		
	return 0;
}

static int lua_pgeGfxDrawCustom2D(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 3)
		return luaL_error(L, "Argument error: pge.gfx.drawcustom(primitive, type, vertices) takes three arguments.");

	int prim = luaL_checkint(L, 1);
	int vtype = luaL_checkint(L, 2);
	
	if(lua_type(L, 3) != LUA_TTABLE)
		return luaL_error(L, "Argument error: pge.gfx.drawcustom(primitive, type, vertices) vertices table missing.");
		
	int n = luaL_getn(L, 3);

	int quads = 0;
	
	int colorLuaIndex = -1;
	
	if(vtype & GU_TEXTURE_32BITF)
		quads += 2;
		
	if(vtype & GU_COLOR_8888)
	{
		quads++;
		colorLuaIndex = quads;
	}
	
	if(vtype & GU_NORMAL_32BITF)
		quads += 3;
		
	if(vtype & GU_VERTEX_32BITF)
		quads += 3;

	void* vertices = pgeGfxGetVertexMemory(n * quads * 4);
	
	float* vertex = (float*) vertices;
	
	int i;
	
	for(i = 1; i <= n; ++i)
	{
		lua_rawgeti(L, 3, i);
		int n2 = luaL_getn(L, -1);
		
		if(n2 != quads)
		{
			return luaL_error(L, "Argument error: pge.gfx.drawcustom(primitive, type, vertices) incorrect number of vertex components.");
		}
		
		int j;
		
		for(j = 1; j <= n2; ++j)
		{
			lua_rawgeti(L, -1, j);
			
			if(j != colorLuaIndex)
			{
				*vertex = luaL_checknumber(L, -1);
			}
			else
			{
				*((pgeColor*) vertex) = *topgeColor(L, -1);
			}
			
			lua_pop(L, 1);
			
			vertex++;
		}

		lua_pop(L, 1);
	}
	
	pgeGfxDrawCustom2D(prim, vtype, n, vertices);
		
	return 0;
}

static int lua_pgeGfxDrawCustom3D(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 3)
		return luaL_error(L, "Argument error: pge.gfx.drawcustom3d(primitive, type, vertices) takes three arguments.");

	int prim = luaL_checkint(L, 1);
	int vtype = luaL_checkint(L, 2);
	
	if(lua_type(L, 3) != LUA_TTABLE)
		return luaL_error(L, "Argument error: pge.gfx.drawcustom3d(primitive, type, vertices) vertices table missing.");
		
	int n = luaL_getn(L, 3);

	int quads = 0;
	
	int colorLuaIndex = -1;
	
	if(vtype & GU_TEXTURE_32BITF)
		quads += 2;
		
	if(vtype & GU_COLOR_8888)
	{
		quads++;
		colorLuaIndex = quads;
	}
	
	if(vtype & GU_NORMAL_32BITF)
		quads += 3;
		
	if(vtype & GU_VERTEX_32BITF)
		quads += 3;

	void* vertices = pgeGfxGetVertexMemory(n * quads * 4);
	
	float* vertex = (float*) vertices;
	
	int i;
	
	for(i = 1; i <= n; ++i)
	{
		lua_rawgeti(L, 3, i);
		int n2 = luaL_getn(L, -1);
		
		if(n2 != quads)
		{
			return luaL_error(L, "Argument error: pge.gfx.drawcustom(primitive, type, vertices) incorrect number of vertex components.");
		}
		
		int j;
		
		for(j = 1; j <= n2; ++j)
		{
			lua_rawgeti(L, -1, j);
			
			if(j != colorLuaIndex)
			{
				*vertex = luaL_checknumber(L, -1);
			}
			else
			{
				*((pgeColor*) vertex) = *topgeColor(L, -1);
			}
			
			lua_pop(L, 1);
			
			vertex++;
		}

		lua_pop(L, 1);
	}
	
	ScePspFVector3 pos = {0, 0, 0};
	
	pgeGfxDrawCustom3D(&pos, &pos, prim, vtype, n, vertices);
		
	return 0;
}

static int lua_pgeGfxTransparent(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 0 && argc != 1)
		return luaL_error(L, "Argument error: pge.gfx.transparent([color]) takes zero or one argument."); 

	if(argc == 1)
	{
		pgeColor color = *topgeColor(L, 1);
		
		pgeGfxSetTransparent(color);
	}
	else
		pgeGfxUnsetTransparent();
		
	return 0;
}

static int lua_pgeGfxSetBlendMode(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.gfx.setblendmode(mode) takes one argument."); 

	int mode = luaL_checkint(L, 1);
	
	lua_pushinteger(L, pgeGfxSetBlendMode(mode));
		
	return 1;
}

static int lua_pgeGfxDrawCube(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 10)
		return luaL_error(L, "Argument error: pge.gfx.drawcube(x, y, z, xrot, yrot, zrot, width, height, depth, color) takes ten arguments."); 

	ScePspFVector3 pos;
	
	ScePspFVector3 rot;
	
	pos.x = luaL_checknumber(L, 1);
	pos.y = luaL_checknumber(L, 2);
	pos.z = luaL_checknumber(L, 3);
	
	rot.x = luaL_checknumber(L, 4);
	rot.y = luaL_checknumber(L, 5);
	rot.z = luaL_checknumber(L, 6);
	
	float width = luaL_checknumber(L, 7);
	
	float height = luaL_checknumber(L, 8);
	
	float depth = luaL_checknumber(L, 9);
	
	pgeColor color = *topgeColor(L, 10);
	
	pgeGfxDrawCube(&pos, &rot, width, height, depth, color);
		
	return 0;
}

static int lua_pgeGfxLookAt(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 9)
		return luaL_error(L, "Argument error: pge.gfx.lookat(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.z, up.y, up.z) takes nine arguments."); 
	
	ScePspFVector3 eye;
	ScePspFVector3 center;
	ScePspFVector3 up;
	
	eye.x = luaL_checknumber(L, 1);
	eye.y = luaL_checknumber(L, 2);
	eye.z = luaL_checknumber(L, 3);
	
	center.x = luaL_checknumber(L, 4);
	center.y = luaL_checknumber(L, 5);
	center.z = luaL_checknumber(L, 6);
	
	up.x = luaL_checknumber(L, 7);
	up.y = luaL_checknumber(L, 8);
	up.z = luaL_checknumber(L, 9);
	
	pgeGfxLookAt(&eye, &center, &up);
		
	return 0;
}

static int lua_pgeGfxProject(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 3)
		return luaL_error(L, "Argument error: pge.gfx.project(x, y, z) takes three arguments.");
		
	ScePspFVector3 object;
		
	object.x = luaL_checknumber(L, 1);
	object.y = luaL_checknumber(L, 2);
	object.z = luaL_checknumber(L, 3);
	
	ScePspFVector3 screen;
	
	pgeGfxProject(&object, &screen);
	
	lua_newtable(L);
	
	lua_pushstring(L, "x");
	lua_pushnumber(L, screen.x);
	lua_settable(L, -3);
		
	lua_pushstring(L, "y");
	lua_pushnumber(L, screen.y);
	lua_settable(L, -3);
		
	lua_pushstring(L, "z");
	lua_pushnumber(L, screen.z);
	lua_settable(L, -3);
	
	return 1;
}

static int lua_pgeGfxUnProject(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 3)
		return luaL_error(L, "Argument error: pge.gfx.unproject(x, y, z) takes three arguments.");
		
	ScePspFVector3 screen;
		
	screen.x = luaL_checknumber(L, 1);
	screen.y = luaL_checknumber(L, 2);
	screen.z = luaL_checknumber(L, 3);
	
	ScePspFVector3 object;
	
	pgeGfxUnproject(&screen, &object);
	
	lua_newtable(L);
	
	lua_pushstring(L, "x");
	lua_pushnumber(L, object.x);
	lua_settable(L, -3);
		
	lua_pushstring(L, "y");
	lua_pushnumber(L, object.y);
	lua_settable(L, -3);
		
	lua_pushstring(L, "z");
	lua_pushnumber(L, object.z);
	lua_settable(L, -3);
	
	return 1;
}

static int lua_pgeGfxGetMatrix(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.gfx.getmatrix(matrix) takes one argument.");
		
	int mode = luaL_checkint(L, 1);
		
	ScePspFMatrix4 view;
	
	pgeGfxGetMatrix(&view, mode);
		
	lua_newtable(L);
	
	lua_pushstring(L, "x");
	
	lua_newtable(L);
	
		lua_pushstring(L, "x");
		lua_pushnumber(L, view.x.x);
		lua_settable(L, -3);
		
		lua_pushstring(L, "y");
		lua_pushnumber(L, view.x.y);
		lua_settable(L, -3);
		
		lua_pushstring(L, "z");
		lua_pushnumber(L, view.x.z);
		lua_settable(L, -3);
		
		lua_pushstring(L, "w");
		lua_pushnumber(L, view.x.w);
		lua_settable(L, -3);
		
	lua_settable(L, -3);
	
	lua_pushstring(L, "y");
	
	lua_newtable(L);
	
		lua_pushstring(L, "x");
		lua_pushnumber(L, view.y.x);
		lua_settable(L, -3);
		
		lua_pushstring(L, "y");
		lua_pushnumber(L, view.y.y);
		lua_settable(L, -3);
		
		lua_pushstring(L, "z");
		lua_pushnumber(L, view.y.z);
		lua_settable(L, -3);
		
		lua_pushstring(L, "w");
		lua_pushnumber(L, view.y.w);
		lua_settable(L, -3);
		
	lua_settable(L, -3);
	
	lua_pushstring(L, "z");
	
	lua_newtable(L);
	
		lua_pushstring(L, "x");
		lua_pushnumber(L, view.z.x);
		lua_settable(L, -3);
		
		lua_pushstring(L, "y");
		lua_pushnumber(L, view.z.y);
		lua_settable(L, -3);
		
		lua_pushstring(L, "z");
		lua_pushnumber(L, view.z.z);
		lua_settable(L, -3);
		
		lua_pushstring(L, "w");
		lua_pushnumber(L, view.z.w);
		lua_settable(L, -3);
		
	lua_settable(L, -3);
	
	lua_pushstring(L, "w");
	
	lua_newtable(L);
	
		lua_pushstring(L, "x");
		lua_pushnumber(L, view.w.x);
		lua_settable(L, -3);
		
		lua_pushstring(L, "y");
		lua_pushnumber(L, view.w.y);
		lua_settable(L, -3);
		
		lua_pushstring(L, "z");
		lua_pushnumber(L, view.w.z);
		lua_settable(L, -3);
		
		lua_pushstring(L, "w");
		lua_pushnumber(L, view.w.w);
		lua_settable(L, -3);
		
	lua_settable(L, -3);
	
	return 1;
}

static int lua_pgeGfxLoadIdentity(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.gfx.loadidentity() takes no arguments."); 
	
	pgeGfxLoadIdentity();
		
	return 0;
}

static int lua_pgeGfxMatrixMode(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.gfx.matrixmode(matrix) takes one argument."); 
	
	int mode = luaL_checkint(L, 1);
	
	pgeGfxMatrixMode(mode);
		
	return 0;
}

static int lua_pgeGfxRotateX(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.gfx.rotatex(rotation) takes one argument."); 
	
	float rot = luaL_checknumber(L, 1);
	
	pgeGfxRotateX(rot);
		
	return 0;
}

static int lua_pgeGfxRotateY(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.gfx.rotatey(rotation) takes one argument."); 
	
	float rot = luaL_checknumber(L, 1);
	
	pgeGfxRotateY(rot);
		
	return 0;
}

static int lua_pgeGfxPerspective(lua_State *L)
{
	int argc = lua_gettop(L); 
	
	if(argc != 4)
		return luaL_error(L, "Argument error: pge.gfx.perspective(fov, aspect, near, far) takes four arguments."); 
	
	float fov = luaL_checknumber(L, 1);
	float aspect = luaL_checknumber(L, 2);
	float near = luaL_checknumber(L, 3);
	float far = luaL_checknumber(L, 4);
	
	pgeGfxPerspective(fov, aspect, near, far);
			
	return 0;
}

static const luaL_reg lua_pgeGfx_functions[] =
{
	{"startdrawing",		lua_pgeGfxStartDrawing},
	{"enddrawing",			lua_pgeGfxEndDrawing},
	{"swapbuffers",			lua_pgeGfxSwapBuffers},
	{"createcolor",			lua_pgeGfxCreateColor},
	{"clearscreen",			lua_pgeGfxClearScreen},
	{"drawline",			lua_pgeGfxDrawLine},
	{"drawstar",			lua_pgeGfxDrawStar},
	{"drawstaroutline",		lua_pgeGfxDrawStarOutline},
	{"drawcircle",			lua_pgeGfxDrawCircle},
	{"drawcircleoutline",	lua_pgeGfxDrawCircleOutline},
	{"drawrect",			lua_pgeGfxDrawRect},
	{"drawrectoutline",		lua_pgeGfxDrawRectOutline},
	{"drawrectgrad",		lua_pgeGfxDrawRectGrad},
	{"rendertoscreen",		lua_pgeGfxRenderToScreen},
	{"drawcustom",			lua_pgeGfxDrawCustom2D},
	{"drawcustom3d",		lua_pgeGfxDrawCustom3D},
	{"setblendmode",		lua_pgeGfxSetBlendMode},
	{"red",					lua_pgeGfxColorRed},
	{"green",				lua_pgeGfxColorGreen},
	{"blue",				lua_pgeGfxColorBlue},
	{"alpha",				lua_pgeGfxColorAlpha},
	{"drawcube",			lua_pgeGfxDrawCube},
	{"lookat",				lua_pgeGfxLookAt},
	{"getmatrix",			lua_pgeGfxGetMatrix},
	{"loadidentity",		lua_pgeGfxLoadIdentity},
	{"matrixmode",			lua_pgeGfxMatrixMode},
	{"rotatex",				lua_pgeGfxRotateX},
	{"rotatey",				lua_pgeGfxRotateY},
	{"perspective",			lua_pgeGfxPerspective},
	{"project",				lua_pgeGfxProject},
	{"unproject",			lua_pgeGfxUnProject},
	{"transparent",			lua_pgeGfxTransparent},
	{0, 0}
};

void lua_pgeGfx_init(lua_State *L)
{	
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeGfx_functions);
	luaL_newmetatable(L, "pgeColor");
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pop(L, 1);
	lua_setfield(L, -2, "gfx"); /* pge */
	lua_pop(L, 1);
	
	lua_pushnumber(L, PGE_VERT_V); lua_setglobal(L, "PGE_VERT_V");
	lua_pushnumber(L, PGE_VERT_NV); lua_setglobal(L, "PGE_VERT_NV");
	lua_pushnumber(L, PGE_VERT_CV); lua_setglobal(L, "PGE_VERT_CV");
	lua_pushnumber(L, PGE_VERT_CNV); lua_setglobal(L, "PGE_VERT_CNV");
	lua_pushnumber(L, PGE_VERT_TV); lua_setglobal(L, "PGE_VERT_TV");
	lua_pushnumber(L, PGE_VERT_TNV); lua_setglobal(L, "PGE_VERT_TNV");
	lua_pushnumber(L, PGE_VERT_TCV); lua_setglobal(L, "PGE_VERT_TCV");
	lua_pushnumber(L, PGE_VERT_TCNV); lua_setglobal(L, "PGE_VERT_TCNV");
	
	lua_pushnumber(L, PGE_PRIM_POINTS); lua_setglobal(L, "PGE_PRIM_POINTS");
	lua_pushnumber(L, PGE_PRIM_LINES); lua_setglobal(L, "PGE_PRIM_LINES");
	lua_pushnumber(L, PGE_PRIM_LINE_STRIP); lua_setglobal(L, "PGE_PRIM_LINE_STRIP");
	lua_pushnumber(L, PGE_PRIM_TRIANGLES); lua_setglobal(L, "PGE_PRIM_TRIANGLES");
	lua_pushnumber(L, PGE_PRIM_TRIANGLE_STRIP); lua_setglobal(L, "PGE_PRIM_TRIANGLE_STRIP");
	lua_pushnumber(L, PGE_PRIM_TRIANGLE_FAN); lua_setglobal(L, "PGE_PRIM_TRIANGLE_FAN");
	lua_pushnumber(L, PGE_PRIM_SPRITES); lua_setglobal(L, "PGE_PRIM_SPRITES");
	
	lua_pushnumber(L, PGE_BLEND_MODE_TRANSPARENT); lua_setglobal(L, "PGE_BLEND_MODE_TRANSPARENT");
	lua_pushnumber(L, PGE_BLEND_MODE_REGULAR); lua_setglobal(L, "PGE_BLEND_MODE_REGULAR");
	
	lua_pushnumber(L, PGE_GFX_PROJECTION); lua_setglobal(L, "PGE_GFX_PROJECTION");
	lua_pushnumber(L, PGE_GFX_VIEW); lua_setglobal(L, "PGE_GFX_VIEW");
	lua_pushnumber(L, PGE_GFX_MODEL); lua_setglobal(L, "PGE_GFX_MODEL");
	
	lua_pushnumber(L, PGE_RAM); lua_setglobal(L, "PGE_RAM");
	lua_pushnumber(L, PGE_VRAM); lua_setglobal(L, "PGE_VRAM");
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
		
	lua_State *L = pgeLuaGetState();
	
	pgeLuaRegisterDependency("pge.math");
	
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);
	
	lua_pgeGfx_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
