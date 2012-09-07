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
	
	pgeTexture *image1 = pgeTextureLoad("image1.png", PGE_RAM);
	
	pgeTexture *image2 = pgeTextureLoad("image2.png", PGE_RAM);
	
	if(!image1 || !image2)
		sceKernelExitGame();
	
	int alpha = 0;
	
	int modifier = 1;

	while(pgeRunning())
	{
		// Start drawing
		pgeGfxStartDrawing();

		// Clear screen (black)
		pgeGfxClearScreen(0);

		pgeTextureActivate(image1);
		
		pgeGfxDrawTextureEasy(240 - (image1->width/2), 136 - (image1->height/2), image1, 0, alpha);
		
		pgeTextureActivate(image2);
		
		pgeGfxDrawTextureEasy(240 - (image1->width/2), 136 - (image1->height/2), image2, 0, 255 - alpha);

		// End drawing
		pgeGfxEndDrawing();

		// Swap buffer (wait for vysnc)
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);
		
		alpha += modifier;
		
		if(alpha > 255)
		{
			modifier = -1;
			alpha = 255;
		}
		else if(alpha < 0)
		{
			modifier = 1;
			alpha = 0;
		}
	}
	
	// Shutdown graphics
	pgeGfxShutdown();
	
	pgeExit();
	
	return 0;
}
