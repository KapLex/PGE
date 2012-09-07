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
	
	unsigned int white = pgeGfxCreateColor(255, 255, 255, 255);
	
	unsigned int blue = pgeGfxCreateColor(0, 0, 255, 255);
	
	unsigned int red = pgeGfxCreateColor(255, 0, 0, 255);
	
	unsigned int green = pgeGfxCreateColor(0, 255, 0, 255);

	while(pgeRunning())
	{
		// Start drawing
		pgeGfxStartDrawing();

		// Clear screen (black)
		pgeGfxClearScreen(0);

		// Draw circle with center at x 50, y 50, radius of 50 using 30 points, colored white
		pgeGfxDrawCircle(50, 50, 50, 30, white);

		// Draw an outline for the circle with center at x 50, y 50, radius of 50 using 30 points, colored blue
		pgeGfxDrawCircleOutline(50, 50, 50, 30, blue);
		
		// Draw a star at x 300, y 100, 19 inner radius, 50 outer radius, 5 points, colored red, rotation 0
		pgeGfxDrawStar(300, 100, 19, 50, 5, red, 1);

		// Draw an outline for the star at x 300, y 100, 19 inner radius, 50 outer radius, 5 points, colored green
		pgeGfxDrawStarOutline(300, 100, 19, 50, 5, green, 1);

		// Draw rectangle at x 20, y 200, 30 width, 60 height, colored blue, rotation 0
		pgeGfxDrawRect(20, 200, 30, 60, blue, 0);
		
		// Draw an outline for the rectangle at x 20, y 200, 30 width, 60 height, colored white, rotation 0
		pgeGfxDrawRectOutline(20, 200, 30, 60, white, 0);

		// Draw rectangle at x 60, y 200, 30 width, 60 height, colored blue, rotation 0
		pgeGfxDrawRect(60, 200, 30, 60, blue, 0);
		
		// Draw rectangle at x 120, y 200, 30 width, 60 height, colored blue, rotation 1
		pgeGfxDrawRect(120, 200, 30, 60, blue, 1);

		// Draw rectangle at x 190, y 200, 30 width, 60 height, colored blue, rotation by half of pi
		pgeGfxDrawRect(190, 200, 30, 60, blue, 1.57079632679489f);

		// Draw rectangle at x 260, y 200, 30 width, 60 height, colored blue, rotation by 3 times half of pi + 1
		pgeGfxDrawRect(260, 200, 30, 60, blue, 3*1.57079632679489f + 1);

		// End drawing
		pgeGfxEndDrawing();

		// Swap buffer (wait for vysnc)
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);
	}
	
	// Shutdown graphics
	pgeGfxShutdown();
	
	pgeExit();
	
	return 0;
}
