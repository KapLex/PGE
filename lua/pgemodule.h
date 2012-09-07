/*
 * pgemodule.h: Header for PGE Lua Modules
 *
 * This file is part of "Phoenix Game Engine".
 *
 * Copyright (C) 2008 Phoenix Game Engine
 * Copyright (C) 2008 InsertWittyName <tias_dp@hotmail.com>
 * Copyright (C) 2008 MK2k <pge@mk2k.net>
 *
 */

#ifndef __PGEMODULE_H__
#define __PGEMODULE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define pgeLuaCreateUserdataHandlers(HANDLE, DATATYPE) \
DATATYPE *to##HANDLE (lua_State *L, int index) \
{ \
  DATATYPE* handle  = (DATATYPE*)lua_touserdata(L, index); \
  if (handle == NULL) luaL_typerror(L, index, #HANDLE); \
  return handle; \
} \
DATATYPE* push##HANDLE(lua_State *L) { \
	DATATYPE* newvalue = (DATATYPE*)lua_newuserdata(L, sizeof(DATATYPE)); \
	luaL_getmetatable(L, #HANDLE); \
	lua_setmetatable(L, -2); \
	return newvalue; \
}

/**
 * Check for program status.
 *
 * @returns 1 if program running, 0 if exit has been requested.
 */
int pgeRunning(void);

/**
 * Explicitely exit a program.
 */
void pgeExit(void);

/**
 * Get PGE version
 *
 * @returns The version of PGE running.
 */
int pgeVersion(void);

/**
 * Delay execution
 *
 * @param delay - Time to delay in microseconds
 */
void pgeDelay(unsigned int delay);

/**
 * Get the Lua instance from the main program
 *
 * @returns A pointer to the lua_State.
 */
lua_State *pgeLuaGetState(void);

/**
 * Load a PGE Lua module
 *
 * @param module - The name of the module, eg. pge.texture
 *
 * @returns 1 on success, otherwise 0.
 */
int pgeLuaRequire(const char *module);

/**
 * Register a PGE module dependency
 *
 * @param dependency - The dependency of the module. eg. "pge.math"
 *
 * @returns 1 on success, otherwise 0.
 */
int pgeLuaRegisterDependency(const char *dependency);

/**
 * Malloc for PGE
 *
 * @param size - Size to allocate.
 *
 * @returns A pointer on success, otherwise NULL.
 */
void *pgeMalloc(int size);

/**
 * Free for PGE
 *
 * @param ptr - The pointer to free.
 */
void pgeFree(void *ptr);

/**
 * Realloc for PGE
 *
 * @param ptr - The pointer to reallocate.
 *
 * @param size - Size to allocate.
 *
 * @returns A pointer on success.
 */
void *pgeRealloc(void *ptr, int size);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __PGEMODULE_H__
