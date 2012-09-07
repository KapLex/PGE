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
	// Colors
	enum colors
	{
		RED =	0xFF0000FF,
		GREEN =	0xFF00FF00,
		BLUE =	0xFFFF0000,
		WHITE =	0xFFFFFFFF
	};

 // Init font library
	pgeFontInit();

	// Init graphics
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);

	// Load first font, 12 point, 128x128 texture, in VRAM
	pgeFont *verdana12 = pgeFontLoad("./verdana.ttf", 12, PGE_FONT_SIZE_POINTS, PGE_VRAM);

        // Load second font, 20 pixels, 128x128 texture, in VRAM
	pgeFont *impact20 = pgeFontLoad("./impact.ttf", 20, PGE_FONT_SIZE_PIXELS, PGE_VRAM);

	// Make sure the fonts are loaded
	if(!verdana12 || !impact20)
		sceKernelExitGame();

	while(pgeRunning())
	{
		// Begin drawing
		pgeGfxStartDrawing();

		// Clear screen to black
		pgeGfxClearScreen(0);
		
		// Activate our first font
		pgeFontActivate(verdana12);

		// Draw our character set using the first font
		pgeFontPrintf(verdana12, 100, 50, RED, " .,!?:;0123456789");
		pgeFontPrintf(verdana12, 100, 70, GREEN, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		pgeFontPrintf(verdana12, 100, 90, BLUE, "abcdefghijklmnopqrstuvwxyz");
		pgeFontPrintf(verdana12, 100, 110, WHITE, "@#\"£$%%^&*()[]{}<>/\\|~`+-=_~'");

		// Activate our second font
		pgeFontActivate(impact20);

		// Draw our character set using the second font
		pgeFontPrintf(impact20, 100, 150, RED, " .,!?:;0123456789");
		pgeFontPrintf(impact20, 100, 170, GREEN, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		pgeFontPrintf(impact20, 100, 190, BLUE, "abcdefghijklmnopqrstuvwxyz");
		pgeFontPrintf(impact20, 100, 210, WHITE, "@#\"£$%%^&*()[]{}<>/\\|~`+-=_~'");

		// End drawing
		pgeGfxEndDrawing();
		
		// Swap buffers (waiting for vsync)
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);
	}

	// Destroy our first font
	pgeFontDestroy(verdana12);
	
	// Destroy our second font
	pgeFontDestroy(impact20);

	// Shutdown font library
	pgeFontShutdown();
	
	// Shutdown graphics
	pgeGfxShutdown();
	
	pgeExit();

	return 0;
}
