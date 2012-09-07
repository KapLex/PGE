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
	
	pgeTexture *texture = pgeTextureCreate(128, 128, PGE_PIXEL_FORMAT_8888, PGE_VRAM);

	if(!texture)
		sceKernelExitGame();
	
	pgeRect rect = {10, 10, 20, 20};
	
	float angle = 0.0f;
	float anglestep = 0.01f;
	
	while(pgeRunning())
	{
		// Start drawing
		pgeGfxStartDrawing();
		
		pgeGfxRenderToTexture(texture);
		
		pgeGfxClearScreen(0xFFFFFFFF);
		
		pgeGfxDrawRect(&rect, 0xFF000000, 0);
		
		pgeGfxRenderToScreen();

		// Clear screen (black)
		pgeGfxClearScreen(0);

		pgeTextureActivate(texture);
		
		//Draw the texture in the screen middle, rotated by angle, alpha 255
		pgeGfxDrawTextureEasy(texture, 240 - (texture->width/2), 136 - (texture->height/2), angle, 255);
		
		// End drawing
		pgeGfxEndDrawing();

		// Swap buffer (wait for vysnc)
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);
		
		angle += anglestep;
	}
	
	pgeTextureDestroy(texture);
	
	// Shutdown graphics
	pgeGfxShutdown();
	
	pgeExit();
	
	return 0;
}
