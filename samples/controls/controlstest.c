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
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pge/pge.h>

int main(int argc, char*argv[])
{
	pspDebugScreenInit();
	
	// Init the controls
	pgeControlsInit();

	while(pgeRunning())
	{
		sceDisplayWaitVblankStart();

		pspDebugScreenSetXY(0, 2);

		// Update the controller data
		pgeControlsUpdate();

		// Print the analog values
		pspDebugScreenPrintf("Analog X = %i ", pgeControlsAnalogX());
		pspDebugScreenPrintf("Analog Y = %i       \n", pgeControlsAnalogY());
		
		// Disable controls if start pressed
		if (pgeControlsPressed(PGE_CTRL_START)) {
			pgeControlsDisable();
		}

		// Print the other buttons if 'held'
		if (pgeControlsHeld(PGE_CTRL_SQUARE)){
			pspDebugScreenPrintf("Square held \n");
		} else {
			pspDebugScreenPrintf("\n");
		}
		if (pgeControlsHeld(PGE_CTRL_TRIANGLE)){
			pspDebugScreenPrintf("Triangle held \n");
		} else {
			pspDebugScreenPrintf("\n");
		}
		if (pgeControlsHeld(PGE_CTRL_CIRCLE)){
			pspDebugScreenPrintf("Cicle held \n");
		} else {
			pspDebugScreenPrintf("\n");
		}
		if (pgeControlsHeld(PGE_CTRL_CROSS)){
			pspDebugScreenPrintf("Cross held \n");
		} else {
			pspDebugScreenPrintf("\n");
		}
		if (pgeControlsHeld(PGE_CTRL_UP)){
			pspDebugScreenPrintf("Up held \n");
		} else {
			pspDebugScreenPrintf("\n");
		}
		if (pgeControlsHeld(PGE_CTRL_DOWN)){
			pspDebugScreenPrintf("Down held \n");
		} else {
			pspDebugScreenPrintf("\n");
		}
		if (pgeControlsHeld(PGE_CTRL_LEFT)){
			pspDebugScreenPrintf("Left held \n");
		} else {
			pspDebugScreenPrintf("\n");
		}
		if (pgeControlsHeld(PGE_CTRL_RIGHT)){
			pspDebugScreenPrintf("Right held \n");
		} else {
			pspDebugScreenPrintf("\n");
		}
		if (pgeControlsHeld(PGE_CTRL_START)){
			pspDebugScreenPrintf("Start held \n");
		} else {
			pspDebugScreenPrintf("\n");
		}
		if (pgeControlsHeld(PGE_CTRL_SELECT)){
			pspDebugScreenPrintf("Select held \n");
		} else {
			pspDebugScreenPrintf("\n");
		}
		if (pgeControlsHeld(PGE_CTRL_LTRIGGER)){
			pspDebugScreenPrintf("L-trigger held \n");
		} else {
			pspDebugScreenPrintf("\n");
		}
		if (pgeControlsHeld(PGE_CTRL_RTRIGGER)){
			pspDebugScreenPrintf("R-trigger held \n");
		} else {
			pspDebugScreenPrintf("\n");
		}
		if(pgeControlsHeld(PGE_CTRL_RTRIGGER|PGE_CTRL_LTRIGGER))
			pspDebugScreenPrintf("Caught!!!");
	}
	
	// Shutdown the controls
	pgeControlsShutdown();

	pgeExit();
	return 0;
}
