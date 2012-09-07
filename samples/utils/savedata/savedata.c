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

#include <pge/pge.h>
#include <pge/pgeGfx.h>
#include <pge/pgeControls.h>
#include <pge/pgeUtils.h>

#include <stdlib.h>

int main(int argc, char*argv[])
{
	// Init graphics
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);
	
	pgeControlsInit();
	
	char savedata[256];
	
	char loaddata[256];
	
	sprintf(savedata, "score: 10");
	
	pgeUtilsSavedataInit(PGE_UTILS_SAVEDATA_TYPE_LISTSAVE, &savedata, 256, "TEST99999", "1js8th5jsnxk9htj" , "Test Title", "Sub Title", "This is the detail of my game save");

	int result = -1;
	
	// Save
	while(pgeRunning())
	{
		pgeControlsUpdate();
		
		// Start drawing
		pgeGfxStartDrawing();

		// Clear screen (black)
		pgeGfxClearScreen(0);
		
		// End drawing
		pgeGfxEndDrawing();
		
		// We always update the dialog after pgeGfxEndDrawing()
		
		result = pgeUtilsSavedataUpdate();

		// Swap buffer (wait for vysnc)
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);
		
		if(result > -1)
			break;
	}
	
	pgeUtilsSavedataInit(PGE_UTILS_SAVEDATA_TYPE_LISTLOAD, &loaddata, 256, "TEST99999", "1js8th5jsnxk9htj" , "Test Title", "Sub Title", "This is the detail of my game save");
	
	// Load
	while(pgeRunning())
	{
		pgeControlsUpdate();
		
		// Start drawing
		pgeGfxStartDrawing();

		// Clear screen (black)
		pgeGfxClearScreen(0);
		
		// End drawing
		pgeGfxEndDrawing();
		
		// We always update the dailog after pgeGfxEndDrawing()
		
		// Pass the buffer to load the data into
		result = pgeUtilsSavedataUpdate();

		// Swap buffer (wait for vysnc)
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);
		
		if(result > -1)
		{
			pspDebugScreenInit();
			pspDebugScreenPrintf("Loaded: %s", loaddata);
			sceKernelDelayThread(5*1000*1000);
			break;
		}
	}
	
	// Shutdown graphics
	pgeGfxShutdown();
	
	pgeControlsShutdown();
	
	pgeExit();
	
	return 0;
}
