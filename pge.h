/*
 * pge.h: Header for the engine
 *
 * This file is part of "Phoenix Game Engine".
 *
 * Copyright (C) 2008 Phoenix Game Engine
 * Copyright (C) 2008 InsertWittyName <tias_dp@hotmail.com>
 * Copyright (C) 2008 MK2k <pge@mk2k.net>
 *
 */

#ifndef __PGE_H__
#define __PGE_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup pge Engine
 *  @{
 */
#include <pspkernel.h>
//#include <pspkerneltypes.h>

/*#include "pgeAdhoc.h"
#include "pgeWav.h"
#include "pgeTimer.h"
#include "pgeMath.h"
#include "pgeVram.h"
#include "pgeFont.h"
#include "pgeNet.h"
#include "pgeControls.h"
#include "pgeGfx.h"
#include "pgeTexture.h"
#include "pgeZip.h"
#include "pgeMp3.h"
#include "pgeUtils.h"
#include "pgeFile.h"
#include "pgeDir.h"
#include "pgeObj.h"
#include "pgeParticle.h"
#include "pgeUsb.h"
#include "pgeSystem.h"*/

#ifndef __PSP__
	#include "SDL.h"
	#include "SDL_opengl.h"
	#include "pgeEmulator.h"
#endif

/**
 * Check for program running status.
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

void *pgeMalloc(int size);

void *pgeRealloc(void *ptr, int size);

void pgeFree(void *ptr);

#ifdef __cplusplus
}
#endif // __cplusplus

/** @} */

#endif // __PGE_H__
