/*
 * This file is part of "Phoenix Game Engine".
 *
 * Copyright (C) 2008 Phoenix Game Engine
 * Copyright (C) 2008 InsertWittyName <tias_dp@hotmail.com>
 * Copyright (C) 2008 MK2k <pge@mk2k.net>
 *
 * Phoenix Game Engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 
 * Phoenix Game Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 
 * You should have received a copy of the GNU General Public License
 * along with Phoenix Game Engine.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <pspkernel.h>
#include <pspctrl.h>
#include <pspaudio.h>
#include <pspdebug.h>
#include <pge/pge.h>
#include <pge/pgeControls.h>
#include <pge/pgeWav.h>

// Include our bin2c'd WAV file (see makefile for how it was created)
#include "eightbitmono.c"

// Our bin2o'd file (see makefile for how it was created)
extern unsigned char eightbitstereo_start[];
extern int eightbitstereo_size;

int main(int argc, char*argv[])
{
	pspDebugScreenInit();
	
	// Init controls
	pgeControlsInit();
	
	// Init WAV playback
	pgeWavInit();

	// Load our WAV files

	// Load from memory
	pgeWav* wav8M = pgeWavLoadMemory(eightbitmono, size_eightbitmono);
	pgeWav* wav8S = pgeWavLoadMemory(eightbitstereo_start, eightbitstereo_size);

	// Load from file
	pgeWav* wav16M = pgeWavLoad("16bitmono.wav");
	pgeWav* wav16S = pgeWavLoad("16bitstereo.wav");
	
	pspDebugScreenPrintf("Press CROSS to play 8 bit mono sample\n");
	pspDebugScreenPrintf("Press SQUARE to play 8 bit stereo sample\n");
	pspDebugScreenPrintf("Press TRIANGLE to play 16 bit mono sample\n");
	pspDebugScreenPrintf("Press CIRCLE to play 16 bit stereo sample\n\n");

	pspDebugScreenPrintf("Press START to stop all WAVs currently playing\n");
	pspDebugScreenPrintf("Press SELECT to set loop\n");

	while(pgeRunning())
	{
		// Update controller data
		pgeControlsUpdate();

		if(pgeControlsPressed(PGE_CTRL_CROSS))
			pgeWavPlay(wav8M);

		if(pgeControlsPressed(PGE_CTRL_CIRCLE))
			pgeWavPlay(wav16S);

		if(pgeControlsPressed(PGE_CTRL_SQUARE))
			pgeWavPlay(wav8S);
				
		if(pgeControlsPressed(PGE_CTRL_TRIANGLE))
			pgeWavPlay(wav16M);

		if(pgeControlsPressed(PGE_CTRL_START))
			pgeWavStopAll();
			
		if(pgeControlsPressed(PGE_CTRL_SELECT))
			pgeWavLoop(wav16M, 1);
	}
	
	// Destroy the WAVs
	pgeWavDestroy(wav8M);
	pgeWavDestroy(wav8S);
	pgeWavDestroy(wav16M);
	pgeWavDestroy(wav16S);
	
	// Shutdown WAV playback
	pgeWavShutdown();
	
	// Shutdown controls
	pgeControlsShutdown();
	
	pgeExit();
	
	return 0;
}
