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
#include <pge/pge.h>

int main(int argc, char*argv[])
{
	// Init graphics
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);
	
	pgeAdhocInit(PGE_ADHOC_TYPE_GAMESHARING);
	
	int state = 0;
	
	pgeUtilsAdhocDialogInit(PGE_UTILS_NET_DIALOG_ADHOC_CONNECT, PGE_UTILS_ADHOC_GAMESHARE_NAME);

	while(pgeRunning())
	{
		// Start drawing
		pgeGfxStartDrawing();

		// Clear screen (black)
		pgeGfxClearScreen(0);

		// Draw circle at x 120, y 120, radius of 50 using 30 points, colored white
		pgeGfxDrawCircle(120, 120, 50, 30, 0xFFFFFFFF);
		
		// Draw rectangle at x 200, y 200, 30 width, 60 height, colored blue
		pgeGfxDrawRect(200, 200, 30, 60, 0xFFFF0000);
		
		// Draw a star at x 300, y 100, 25 inner radius, 50 outer radius, 5 points, colored red
		pgeGfxDrawStar(300, 100, 25, 50, 5, 0xFF0000FF);

		// End drawing
		pgeGfxEndDrawing();
		
		if(state < 600)
			pgeUtilsAdhocDialogUpdate();
		if(state == 600)
			pgeUtilsGameShareDialogInit("EBOOT.PBP", "Test");
		if(state > 600)
			pgeUtilsGameShareDialogUpdate();
		
		// Swap buffer (wait for vysnc)
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);
		
		state++;
	}
	
	// Shutdown graphics
	pgeGfxShutdown();
	
	pgeAdhocShutdown();
	
	pgeExit();

	return 0;
}
