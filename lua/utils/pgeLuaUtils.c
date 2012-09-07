#include <pspkernel.h>
#include <malloc.h>
#include <string.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../../pgeUtils.h"
#include "../pgemodule.h"

PSP_MODULE_INFO("PGE Utils", 0x0006, 1, 1);
PSP_HEAP_SIZE_KB(64);
PSP_NO_CREATE_MAIN_THREAD();

void pgeSystemGetPsid(unsigned char *psid);

static int lua_pgeUtilsNetDialogInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.utils.netinit() takes no arguments.");
	
	lua_pushboolean(L, pgeUtilsNetDialogInit());
	
	return 1;
}

static int lua_pgeUtilsNetDialogUpdate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.utils.netupdate() takes no arguments.");
	
	lua_pushinteger(L, pgeUtilsNetDialogUpdate());
	
	return 1;
}

static int lua_pgeUtilsBrowserInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.utils.browserinit(url) takes one argument.");
		
	const char *url = luaL_checkstring(L, 1);
	
	lua_pushboolean(L, pgeUtilsBrowserInit(4*1024*1024, url));
	
	return 1;
}

static int lua_pgeUtilsBrowserUpdate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.utils.browserupdate() takes no arguments.");
	
	lua_pushinteger(L, pgeUtilsBrowserUpdate());
	
	return 1;
}

static int lua_pgeUtilsAdhocDialogInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.utils.adhocinit(type, name) takes two arguments.");
		
	int type = luaL_checkint(L, 1);
		
	const char *name = luaL_checkstring(L, 2);
	
	lua_pushboolean(L, pgeUtilsAdhocDialogInit(type, (char *)name));
	
	return 1;
}

static int lua_pgeUtilsAdhocDialogUpdate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.utils.adhocupdate() takes no arguments.");
	
	lua_pushinteger(L, pgeUtilsAdhocDialogUpdate());
	
	return 1;
}

static int lua_pgeUtilsMsgDialogInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1 && argc != 2)
		return luaL_error(L, "Argument error: pge.utils.msginit(text, [options]) takes one or two arguments.");
		
	const char *text = luaL_checkstring(L, 1);
	
	int options = 0;
	
	if(argc == 2)
		options = luaL_checkint(L, 2);
	
	lua_pushboolean(L, pgeUtilsMsgDialogInit(options, text));
	
	return 1;
}

static int lua_pgeUtilsMsgDialogErrorInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1 && argc != 2)
		return luaL_error(L, "Argument error: pge.utils.errormsginit(error) takes one argument.");
		
	unsigned int error = luaL_checkint(L, 1);
	
	lua_pushboolean(L, pgeUtilsMsgDialogErrorInit(error));
	
	return 1;
}

static int lua_pgeUtilsMsgDialogUpdate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.utils.msgupdate() takes no arguments.");
	
	lua_pushinteger(L, pgeUtilsMsgDialogUpdate());
	
	return 1;
}

static int lua_pgeUtilsMsgDialogAbort(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.utils.msgabort() takes no arguments.");
	
	lua_pushboolean(L, pgeUtilsMsgDialogAbort());
	
	return 1;
}

static int lua_pgeUtilsOskInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0 && argc != 1 && argc != 2)
		return luaL_error(L, "Argument error: pge.utils.oskinit([description], [initialtext]) takes zero, one or two arguments.");
		
	const char *desc = NULL;
	
	const char *initialtext = NULL;
	
	if(argc > 0)
		desc = luaL_checkstring(L, 1);
		
	if(argc == 2)
		initialtext = luaL_checkstring(L, 2);
	
	lua_pushboolean(L, pgeUtilsOskInit((char *)desc, (char *)initialtext));
	
	return 1;
}

static char *luaOskOutText = NULL;

static int lua_pgeUtilsOskUpdate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.utils.oskupdate() takes no arguments.");
		
	if(luaOskOutText == NULL)
	{
		luaOskOutText = (char *)pgeMalloc(512);
		
		if(luaOskOutText == NULL)
			return luaL_error(L, "Error: pge.utils.oskupdate() couldn't allocate buffer.");
	}
	
	int result = pgeUtilsOskUpdate(luaOskOutText);
	
	if(result == 0 || result == 2)
	{
		lua_pushboolean(L, 1);
		lua_pushstring(L, luaOskOutText);
		pgeFree(luaOskOutText);
		luaOskOutText = NULL;
	}
	else if(result == -1)
	{
		lua_pushboolean(L, 0);
		lua_pushstring(L, "");
	}
	else
	{
		lua_pushboolean(L, 1);
		lua_pushstring(L, "");
	}
	
	return 2;
}

static int pgeUtilsSaveDataType = -1;

static int lua_pgeUtilsListSaveInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 5)
		return luaL_error(L, "Argument error: pge.utils.saveinit(data, name, title, subtitle, detail) takes five arguments.");
		
	pgeUtilsSaveDataType = PGE_UTILS_SAVEDATA_TYPE_LISTSAVE;
		
	const char *data = luaL_checkstring(L, 1);
	
	const char *name = luaL_checkstring(L, 2);
	
	const char *title = luaL_checkstring(L, 3);
	
	const char *subtitle = luaL_checkstring(L, 4);
	
	const char *detail = luaL_checkstring(L, 5);
	
	unsigned int datasize = strlen(data) + 1;
	
	unsigned char psid[16];
	
	pgeSystemGetPsid(psid);
	
	char *key = (char *)psid;
		
	lua_pushboolean(L, pgeUtilsSavedataInit(PGE_UTILS_SAVEDATA_TYPE_LISTSAVE, (void *)data, datasize, name, key, title, subtitle, detail));
	
	return 1;
}

static char *pgeUtilsSavedataData = NULL;

static int lua_pgeUtilsListLoadInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.utils.loadinit(datasize, name) takes two arguments.");
		
	unsigned int datasize = luaL_checkinteger(L, 1);
	
	datasize++;
	
	if(pgeUtilsSavedataData)
		pgeFree(pgeUtilsSavedataData);
	
	pgeUtilsSavedataData = (char *)pgeMalloc(datasize);
	
	if(!pgeUtilsSavedataData)
	{
		lua_pushboolean(L, 0);
		
		return 1;
	}
	
	const char *name = luaL_checkstring(L, 2);
	
	unsigned char psid[16];
	
	pgeSystemGetPsid(psid);
	
	char *key = (char *)psid;
	
	pgeUtilsSaveDataType = PGE_UTILS_SAVEDATA_TYPE_LISTLOAD;
	
	lua_pushboolean(L, pgeUtilsSavedataInit(PGE_UTILS_SAVEDATA_TYPE_LISTLOAD, pgeUtilsSavedataData, datasize, name, key, NULL, NULL, NULL));
	
	return 1;
}

static int lua_pgeUtilsAutoLoadInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
		return luaL_error(L, "Argument error: pge.utils.autoloadinit(datasize, name) takes two arguments.");
		
	unsigned int datasize = luaL_checkinteger(L, 1);
	
	datasize++;
	
	if(pgeUtilsSavedataData)
		pgeFree(pgeUtilsSavedataData);
	
	pgeUtilsSavedataData = (char *)pgeMalloc(datasize);
	
	if(!pgeUtilsSavedataData)
	{
		lua_pushboolean(L, 0);
		
		return 1;
	}
	
	const char *name = luaL_checkstring(L, 2);
	
	unsigned char psid[16];
	
	pgeSystemGetPsid(psid);
	
	char *key = (char *)psid;
	
	pgeUtilsSaveDataType = PGE_UTILS_SAVEDATA_TYPE_AUTOLOAD;
	
	lua_pushboolean(L, pgeUtilsSavedataInit(PGE_UTILS_SAVEDATA_TYPE_AUTOLOAD, pgeUtilsSavedataData, datasize, name, key, NULL, NULL, NULL));
		
	return 1;
}

static int lua_pgeUtilsAutoSaveInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 5)
		return luaL_error(L, "Argument error: pge.utils.autosaveinit(data, name, title, subtitle, detail) takes five arguments.");
		
	pgeUtilsSaveDataType = PGE_UTILS_SAVEDATA_TYPE_AUTOSAVE;
		
	const char *data = luaL_checkstring(L, 1);
	
	const char *name = luaL_checkstring(L, 2);
	
	const char *title = luaL_checkstring(L, 3);
	
	const char *subtitle = luaL_checkstring(L, 4);
	
	const char *detail = luaL_checkstring(L, 5);
	
	unsigned int datasize = strlen(data) + 1;
	
	unsigned char psid[16];
	
	pgeSystemGetPsid(psid);
	
	char *key = (char *)psid;
		
	lua_pushboolean(L, pgeUtilsSavedataInit(PGE_UTILS_SAVEDATA_TYPE_AUTOSAVE, (void *)data, datasize, name, key, title, subtitle, detail));
	
	return 1;
}

static int lua_pgeUtilsListDeleteInit(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
		return luaL_error(L, "Argument error: pge.utils.deleteinit(name) takes one argument.");
		
	pgeUtilsSaveDataType = PGE_UTILS_SAVEDATA_TYPE_LISTDELETE;
	
	const char *name = luaL_checkstring(L, 1);
	
	unsigned char psid[16];
	
	pgeSystemGetPsid(psid);
	
	char *key = (char *)psid;
		
	lua_pushboolean(L, pgeUtilsSavedataInit(PGE_UTILS_SAVEDATA_TYPE_LISTDELETE, NULL, 0, name, key, NULL, NULL, NULL));
	
	return 1;
}

static int lua_pgeUtilsSaveDataUpdate(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 0)
		return luaL_error(L, "Argument error: pge.utils.savedataupdate() takes no arguments.");
		
	int result = pgeUtilsSavedataUpdate();
	
	lua_pushinteger(L, result);
	
	if(pgeUtilsSaveDataType == PGE_UTILS_SAVEDATA_TYPE_LISTSAVE || pgeUtilsSaveDataType == PGE_UTILS_SAVEDATA_TYPE_AUTOSAVE || pgeUtilsSaveDataType == PGE_UTILS_SAVEDATA_TYPE_LISTDELETE)
		return 1;
		
	if(result == 0)
	{
		lua_pushstring(L, pgeUtilsSavedataData);
		pgeFree(pgeUtilsSavedataData);
	}
	else
		lua_pushnil(L);
		
	return 2;
}

static const luaL_reg lua_pgeUtils_functions[] =
{
	{"netinit",			lua_pgeUtilsNetDialogInit},
	{"netupdate",		lua_pgeUtilsNetDialogUpdate},
	{"browserinit",		lua_pgeUtilsBrowserInit},
	{"browserupdate",	lua_pgeUtilsBrowserUpdate},
	{"adhocinit",		lua_pgeUtilsAdhocDialogInit},
	{"adhocupdate",		lua_pgeUtilsAdhocDialogUpdate},
	{"msginit",			lua_pgeUtilsMsgDialogInit},
	{"errormsginit",	lua_pgeUtilsMsgDialogErrorInit},
	{"msgupdate",		lua_pgeUtilsMsgDialogUpdate},
	{"msgabort",		lua_pgeUtilsMsgDialogAbort},
	{"oskinit",			lua_pgeUtilsOskInit},
	{"oskupdate",		lua_pgeUtilsOskUpdate},
	{"saveinit",		lua_pgeUtilsListSaveInit},
	{"loadinit",		lua_pgeUtilsListLoadInit},
	{"autosaveinit",	lua_pgeUtilsAutoSaveInit},
	{"autoloadinit",	lua_pgeUtilsAutoLoadInit},
	{"deleteinit",		lua_pgeUtilsListDeleteInit},
	{"savedataupdate",	lua_pgeUtilsSaveDataUpdate},
	{0, 0}
};

void lua_pgeUtils_init(lua_State *L)
{	
	lua_getglobal(L, "pge");	
	lua_newtable(L);
	luaL_register(L, 0, lua_pgeUtils_functions);
	lua_setfield(L, -2, "utils"); /* pge */
	lua_pop(L, 1);
	
	lua_pushnumber(L, PGE_UTILS_DIALOG_RUNNING); lua_setglobal(L, "PGE_UTILS_DIALOG_RUNNING");
	
	lua_pushnumber(L, PGE_UTILS_MSG_DIALOG_YESNO_BUTTONS); lua_setglobal(L, "PGE_UTILS_MSG_DIALOG_YESNO_BUTTONS");
	lua_pushnumber(L, PGE_UTILS_MSG_DIALOG_DEFAULT_BUTTON_NO); lua_setglobal(L, "PGE_UTILS_MSG_DIALOG_DEFAULT_BUTTON_NO");
	
	lua_pushnumber(L, PGE_UTILS_NET_DIALOG_ADHOC_CONNECT); lua_setglobal(L, "PGE_UTILS_ADHOC_CONNECT");
	lua_pushnumber(L, PGE_UTILS_NET_DIALOG_ADHOC_CREATE); lua_setglobal(L, "PGE_UTILS_ADHOC_CREATE");
	lua_pushnumber(L, PGE_UTILS_NET_DIALOG_ADHOC_JOIN); lua_setglobal(L, "PGE_UTILS_ADHOC_JOIN");

	lua_pushnumber(L, PGE_UTILS_MSG_DIALOG_RESULT_YES); lua_setglobal(L, "PGE_UTILS_MSG_DIALOG_RESULT_YES");
	lua_pushnumber(L, PGE_UTILS_MSG_DIALOG_RESULT_NO); lua_setglobal(L, "PGE_UTILS_MSG_DIALOG_RESULT_NO");
	lua_pushnumber(L, PGE_UTILS_MSG_DIALOG_RESULT_BACK); lua_setglobal(L, "PGE_UTILS_MSG_DIALOG_RESULT_BACK");
	
	lua_pushnumber(L, PGE_UTILS_SAVEDATA_TYPE_AUTOLOAD); lua_setglobal(L, "PGE_UTILS_SAVEDATA_TYPE_AUTOLOAD");
	lua_pushnumber(L, PGE_UTILS_SAVEDATA_TYPE_AUTOSAVE); lua_setglobal(L, "PGE_UTILS_SAVEDATA_TYPE_AUTOSAVE");
	lua_pushnumber(L, PGE_UTILS_SAVEDATA_TYPE_LISTLOAD); lua_setglobal(L, "PGE_UTILS_SAVEDATA_TYPE_LISTLOAD");
	lua_pushnumber(L, PGE_UTILS_SAVEDATA_TYPE_LISTSAVE); lua_setglobal(L, "PGE_UTILS_SAVEDATA_TYPE_LISTSAVE");
	lua_pushnumber(L, PGE_UTILS_SAVEDATA_TYPE_LISTDELETE); lua_setglobal(L, "PGE_UTILS_SAVEDATA_TYPE_LISTDELETE");
}

int module_start(SceSize args, void *argp) 
{
	(void)args;
	(void)argp;
	
	pgeLuaRegisterDependency("pge.system");
		
	lua_State *L = pgeLuaGetState();
	
	lua_pgeUtils_init(L);
	
	return 0; 
} 

int module_stop() 
{
	return 0; 
}
