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
	pgeRect destrect;
	pgeRect sourcerect;
	
	float xoffset, yoffset;
	float step;
	
	// Init the controls
	pgeControlsInit(); 
	
	// Init graphics
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);
	
	pgeTexture *image = pgeTextureLoad("pge.png", PGE_RAM);
	xoffset = 0.0f;
	yoffset = 0.0f;
	
	sourcerect.x = 0.0f;
	sourcerect.y = 0.0f;
	sourcerect.w = image->width;
	sourcerect.h = image->height;
	destrect.x = xoffset + 240 - (image->width/2);
	destrect.y = yoffset + 136 - (image->height/2);
	destrect.w = image->width;
	destrect.h = image->height;

	if(!image)
		sceKernelExitGame();
	
	while(pgeRunning())
	{
		// Update the controller data
		pgeControlsUpdate();

		// Start drawing
		pgeGfxStartDrawing();

		// Clear screen (black)
		pgeGfxClearScreen(0);

		pgeTextureActivate(image);
		
		pgeGfxDrawTexture(&destrect, &sourcerect, 0, 255);

		pgeGfxEndDrawing();

		// Swap buffer (wait for vysnc)
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);

		// Update parameters depending on buttons being held
		if (pgeControlsHeld(PGE_CTRL_LTRIGGER))
		{
			step = 10.0f;
		}
		else
		{
			step = 1.0f;
		}
		
		if (pgeControlsHeld(PGE_CTRL_SQUARE))
		{
			if (pgeControlsHeld(PGE_CTRL_RTRIGGER))
			{
				sourcerect.w += step;
			}
			else
			{
				sourcerect.x += step;
			}
		}
		if (pgeControlsHeld(PGE_CTRL_TRIANGLE))
		{
			if (pgeControlsHeld(PGE_CTRL_RTRIGGER))
			{
				sourcerect.h += step;
			}
			else
			{
				sourcerect.y += step;
			}
		}
		if (pgeControlsHeld(PGE_CTRL_CROSS))
		{
			if (pgeControlsHeld(PGE_CTRL_RTRIGGER))
			{
				sourcerect.h -= step;
			}
			else
			{
				sourcerect.y -= step;
			}
		}
		if (pgeControlsHeld(PGE_CTRL_CIRCLE))
		{
			if (pgeControlsHeld(PGE_CTRL_RTRIGGER))
			{
				sourcerect.w -= step;
			}
			else
			{
				sourcerect.x -= step;
			}
		}
		if (pgeControlsAnalogX() > 64)
		{
			// right
			destrect.w += step;
			destrect.x = xoffset + 240 - (destrect.w/2);
		}
		if (pgeControlsAnalogX() < -64)
		{
			// left
			destrect.w -= step;
			destrect.x = xoffset + 240 - (destrect.w/2);
		}
		if (pgeControlsAnalogY() > 64)
		{
			// up
			destrect.h += step;
			destrect.y = yoffset + 136 - (destrect.h/2);
		}
		if (pgeControlsAnalogY() < -64)
		{
			// down
			destrect.h -= step;
			destrect.y = yoffset + 136 - (destrect.h/2);
		}
		if (pgeControlsHeld(PGE_CTRL_LEFT))
		{
			xoffset -= step;
			destrect.x = xoffset + 240 - (destrect.w/2);
		}
		if (pgeControlsHeld(PGE_CTRL_RIGHT))
		{
			xoffset += step;
			destrect.x = xoffset + 240 - (destrect.w/2);
		}
		if (pgeControlsHeld(PGE_CTRL_UP))
		{
			yoffset -= step;
			destrect.y = yoffset + 136 - (destrect.h/2);
		}
		if (pgeControlsHeld(PGE_CTRL_DOWN))
		{
			yoffset += step;
			destrect.y = yoffset + 136 - (destrect.h/2);
		}
	}
	
	// Shutdown graphics
	pgeGfxShutdown();
	
	pgeExit();
	
	return 0;
}
