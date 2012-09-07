#include <pspkernel.h>
#include <pspctrl.h>
#include <string.h>
#include <unistd.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../pge.h"
#include "pgeLuaIni.h"

static lua_State *L;
static int debuginitialized = 0;
static char initpath[256];

int sce_newlib_heap_kb_size = -1024*3;

int pgeSupportExecEboot(const char *path);

static void pgeLuaDebugOutput(const char *text)
{	
	if(!text)
	{
		debuginitialized = 0;
		return;
	}
	
	if(!debuginitialized)
	{
		#ifdef __PSP__
		pspDebugScreenInit();
		#endif
		debuginitialized = 1;
	}
	
	#ifdef __PSP__
	pspDebugScreenPrintf(text);
	#else
	printf(text);
	#endif
}

static void pgeLuaRestart(void)
{
	char ebootpath[256];
	
	strcpy(ebootpath, initpath);
	strcat(ebootpath, "/EBOOT.PBP");
	
	printf("0x%08X\n", pgeSupportExecEboot(ebootpath));
}

typedef struct
{
	int active;
	char name[256];
	
} pgeLuaDepEntry;

pgeLuaDepEntry pgeLuaDeps[64];

int pgeLuaRegisterDependency(const char *dependency)
{
	int i;
	
	for(i = 0;i < 64;i++)
	{
		if(pgeLuaDeps[i].active == 0)
		{
			pgeLuaDeps[i].active = 1;
			sprintf(pgeLuaDeps[i].name, dependency);
			
			return 1;
		}
	}
	
	return 0;
}

static int pgeLuaRequireDep(const char *module)
{	
	char modpath[256];
	char cwdpath[256];
	
	strcpy(cwdpath, initpath);
	strcat(cwdpath, "/");
	
	strcpy(modpath, initpath);
	
	strcat(modpath, "/modules/");
	strcat(modpath, module);
	strcat(modpath, ".prx");
	
	int ret = sceKernelLoadModule(modpath, 0, NULL);
	
	if(ret < 0 && ret != (int)0x80020139)
	{
		printf("Error: 0x%08X\n", ret);
		return 0;
	}

	int fd;
	
	ret = sceKernelStartModule(ret, strlen(initpath) + 1, (void *)cwdpath, &fd, NULL);
	
	if(ret < 0 && ret != (int)0x8002012E)
	{
		printf("Error2: 0x%08X\n", ret);
		return 0;
	}
	
	return 1;
}

static int pgeLuaCheckDeps(void)
{
	int i;
	
	for(i = 0;i < 64;i++)
	{
		if(pgeLuaDeps[i].active == 1)
		{
			pgeLuaRequireDep(pgeLuaDeps[i].name);
			pgeLuaDeps[i].active = 0;
			i = 0;
		}
	}
	
	return 1;
}

int pgeLuaRequire(const char *module)
{	
	char modpath[256];
	char cwdpath[256];
	
	strcpy(cwdpath, initpath);
	strcat(cwdpath, "/");
	
	strcpy(modpath, initpath);
	
	strcat(modpath, "/modules/");
	strcat(modpath, module);
	strcat(modpath, ".prx");
		
	int ret = sceKernelLoadModule(modpath, 0, NULL);
	
	if(ret < 0 && ret != (int)0x80020139)
	{
		printf("Error: 0x%08X\n", ret);
		return 0;
	}

	int fd;
	
	ret = sceKernelStartModule(ret, strlen(initpath) + 1, (void *)cwdpath, &fd, NULL);
	
	if(ret < 0 && ret != (int)0x8002012E)
	{
		printf("Error2: 0x%08X\n", ret);
		return 0;
	}
		
	pgeLuaCheckDeps();
	
	return 1;
}

static int lua_pgeRunning(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.running() takes no arguments.");
		
	lua_pushboolean(L, pgeRunning());
	
	return 1;
}

static int lua_pgeVersion(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.version() takes no arguments.");
		
	lua_pushinteger(L, pgeVersion());
	
	return 1;
}

static int lua_pgeDelay(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argment error: pge.delay(microseconds) takes one argument.");
		
	int microseconds = luaL_checkint(L, 1);
	
	pgeDelay(microseconds);
	
	return 0;
}

static int lua_pgeExit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argment error: pge.exit() takes no arguments.");
	
	pgeExit();
	
	return 0;
}

static int lua_pgeRequire(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argment error: pge.require(module) takes one argument.");
		
	const char *path = luaL_checkstring(L, 1);

	int ret = pgeLuaRequire(path);
	
	lua_pushboolean(L, ret);

	return 1;
}

static const luaL_reg lua_pge_functions[] =
{
	{"running",		lua_pgeRunning},
	{"delay",		lua_pgeDelay},
	{"version",		lua_pgeVersion},
	{"exit",		lua_pgeExit},
	{"require",		lua_pgeRequire},
	{0, 0}
};

int lua_pge_init(lua_State *L)
{	
	lua_newtable(L);
	luaL_register(L, 0, lua_pge_functions);
	lua_setglobal(L, "pge");
	
	lua_newtable(L);
	lua_setglobal(L, "pgedeps");
	
	return 1;
}

lua_State *pgeLuaGetState(void)
{
	return L;
}

int pgeLuaRunScript(const char *scriptpath)
{		
	int error = 0;
	
	char errortext[1024];
	
	const char *errormsg = NULL;
		
	L = lua_open();
	
	luaL_openlibs(L);
		
	lua_pge_init(L);
	
	error = luaL_loadfile(L, scriptpath);
	
	if(error == 0)
		error = lua_pcall(L, 0, LUA_MULTRET, 0);
		
	if(error)
	{
		errormsg = lua_tostring(L, -1);
		sprintf(errortext, "Error: %s\n", lua_tostring(L, -1));
		pgeLuaDebugOutput(errortext);
		lua_pop(L, 1);
	}
	
	lua_close(L);
	
	return error;
}

int main(int argc, char*argv[])
{	
	(void)argc;
	(void)argv;
	
	int error = 0;

	char scriptpath[256];
	
	getcwd(initpath, 256);
		
	pgeLuaIniFile inifile;
	
	pgeLuaIniReadFile("pge.ini", &inifile);
	
	if(inifile.browserused)
		sce_newlib_heap_kb_size -= 7*1024;
	
	strcpy(scriptpath, initpath);
	strcat(scriptpath, "/script.lua");
	
	SceCtrlData pad;
	
	while(pgeRunning())
	{
		error = pgeLuaRunScript(scriptpath);
			
		if(error)
		{
			#ifdef __PSP__
			pgeLuaDebugOutput("\nPress START to restart.\n");
			#endif
		
			while(pgeRunning())
			{
				sceCtrlPeekBufferPositive(&pad, 1);
			
				if(pad.Buttons & PSP_CTRL_START)
				{
					pgeLuaRestart();
				}
				
				sceKernelDelayThread(1000);
			}
		
		}
		
		if(!error)
			break;
	}
	
	pgeExit();
	
	return 0;
}
