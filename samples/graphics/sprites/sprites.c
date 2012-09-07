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

#define UP								0
#define DOWN							1
#define LEFT							2
#define RIGHT							3

#define SPRITEDIM					32	// dimension of each sprite on the sprite sheet

#define ANIMFRAMES				3		// number of frames for each walking animation
#define ANIMWAIT					5		// number of cycles to wait until next animation frame

#define SPRITESIT					0		// Defining here the occurency of the different
#define SPRITEWALKDOWN		1		// sprites in the file
#define SPRITESTANDDOWN		2
#define SPRITEWALKRIGHT		4
#define SPRITESTANDRIGHT	5
#define SPRITEWALKLEFT		4		// Yep that's right, *RIGHT and *LEFT is the
#define SPRITESTANDLEFT		5		// same sprite, it will get mirrored in the code
#define SPRITEWALKUP			7
#define SPRITESTANDUP			8

int main(int argc, char*argv[])
{
	// sprite parameters
	int direction = RIGHT;
	int animframe = 0;
	int animwait = 10;
	int spriteoffset = SPRITESTANDRIGHT;
	float xpos = 50.0f;
	float ypos = 50.0f;
	float zoom = 1.0f;
	float walkspeed = 1.0f;
	
	pgeRect destrect;
	pgeRect sourcerect;

	// Init the controls
	pgeControlsInit(); 
	
	// Init graphics
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);
	
	pgeTexture *spritesheet = pgeTextureLoad("russelchao.png", PGE_RAM);

	if(!spritesheet)
		sceKernelExitGame();
	
	while(pgeRunning())
	{
		// Update the controller data
		pgeControlsUpdate();

		// Start drawing
		pgeGfxStartDrawing();

		// Clear screen (black)
		pgeGfxClearScreen(0);

		pgeTextureActivate(spritesheet);
		
		destrect.x = xpos;
		destrect.w = SPRITEDIM*zoom;
		destrect.y = ypos;
		destrect.h = SPRITEDIM*zoom;
		
		sourcerect.x = (spriteoffset+animframe)*SPRITEDIM;
		sourcerect.w = SPRITEDIM;
		sourcerect.y = 0;
		sourcerect.h = SPRITEDIM;
		
		if(direction == LEFT)
		{
			// in this case, the sprite character looking to the left, we have to
			// mirror the sprite
			sourcerect.x = (spriteoffset+animframe+1)*SPRITEDIM;
			sourcerect.w = -SPRITEDIM;
		}
		
		pgeGfxDrawTexture(&destrect, &sourcerect, 0, 255);

		pgeGfxEndDrawing();

		// Swap buffer (wait for vysnc)
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);

		// Handle Controls
		if (pgeControlsHeld(PGE_CTRL_LEFT) || pgeControlsAnalogX() < -64)
		{
			direction = LEFT;
			spriteoffset = SPRITEWALKLEFT;
			xpos -= walkspeed;
		}
		if (pgeControlsHeld(PGE_CTRL_RIGHT) || pgeControlsAnalogX() > 64)
		{
			direction = RIGHT;
			spriteoffset = SPRITEWALKRIGHT;
			xpos += walkspeed;
		}
		if (pgeControlsHeld(PGE_CTRL_UP) || pgeControlsAnalogY() < -64)
		{
			direction = UP;
			spriteoffset = SPRITEWALKUP;
			ypos -= walkspeed;
		}
		if (pgeControlsHeld(PGE_CTRL_DOWN) || pgeControlsAnalogY() > 64)
		{
			direction = DOWN;
			spriteoffset = SPRITEWALKDOWN;
			ypos += walkspeed;
		}
		if(!pgeControlsHeld(PGE_CTRL_UP) && !pgeControlsHeld(PGE_CTRL_DOWN) && !pgeControlsHeld(PGE_CTRL_LEFT) && !pgeControlsHeld(PGE_CTRL_RIGHT) && (pgeControlsAnalogX() >= -64) && (pgeControlsAnalogX() <= 64) && (pgeControlsAnalogY() >= -64) && (pgeControlsAnalogY() <= 64))
		{
			animframe = 0;
			switch(direction)
			{
				case UP:
					spriteoffset = SPRITESTANDUP;
					break;
				case DOWN:
					spriteoffset = SPRITESTANDDOWN;
					break;
				case LEFT:
					spriteoffset = SPRITESTANDLEFT;
					break;
				case RIGHT:
					spriteoffset = SPRITESTANDRIGHT;
					break;
				default:
					spriteoffset = SPRITESTANDUP;
			}
		}
		else
		{
			animwait--;
			if(animwait <= 0)
			{
				animwait = ANIMWAIT;
				animframe++;
				if(animframe >= ANIMFRAMES)
				{
					animframe = 0;
				}
			}
		}
		
		// Boundary check for the sprite and screen borders
		if(xpos < 0.0f)
		{
			xpos = 0.0f;
		}
		if(xpos > 480 - SPRITEDIM*2)
		{
			xpos = 480 - SPRITEDIM*2;
		}
		if(ypos < 0.0f)
		{
			ypos = 0.0f;
		}
		if(ypos > 272 - SPRITEDIM*2)
		{
			ypos = 272 - SPRITEDIM*2;
		}

		if(xpos < 240.0f)
		{
			zoom = 1.0f;
		}
		else
		{
			if(xpos >= 240.0f && xpos <= 280.0f)
			{
				zoom = 1.0f + (xpos - 240.0f) / 40.0f;
			}
			else
			{
				zoom = 2.0f;
			}
		}
	}
	
	// Shutdown graphics
	pgeGfxShutdown();
	
	pgeExit();
	
	return 0;
}
