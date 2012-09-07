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

int main(int argc, char*argv[])
{
	// Init graphics
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);
	
	pgeTexture *cubetex = pgeTextureLoad("cube.png", PGE_RAM);
	
	if(cubetex == NULL)
		sceKernelExitGame();
	
	int val = 0;
	
	ScePspFVector3 pos = {0, 0, -5.0f};

	while(pgeRunning())
	{
		pgeGfxSetMode3D(60.0f);
		
		// Start drawing
		pgeGfxStartDrawing();

		// Clear screen (black)
		pgeGfxClearScreen(0);
		
		ScePspFVector3 rot = {val * 0.79f * (GU_PI/180.0f), val * 0.98f * (GU_PI/180.0f), val * 1.32f * (GU_PI/180.0f)};
		
		pgeTextureActivate(cubetex);

		pgeGfxDrawCubeTexture(&pos, &rot, 2.0f, 1.0f, 3.0f);

		// End drawing
		pgeGfxEndDrawing();

		// Swap buffer (wait for vysnc)
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);
		
		val++;
	}
	
	pgeTextureDestroy(cubetex);
	
	// Shutdown graphics
	pgeGfxShutdown();
	
	pgeExit();
	
	return 0;
}
