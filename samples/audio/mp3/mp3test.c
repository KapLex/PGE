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

#include <pspctrl.h>
#include <pspgu.h>
#include <pge/pge.h>

int loop = 1; // Looping flag

int main(int argc, char*argv[])
{	
	// Init controls
	pgeControlsInit();
	
	pgeFontInit();
	
	pgeFont *verdana12 = pgeFontLoad("./verdana.ttf", 12, PGE_FONT_SIZE_POINTS, PGE_RAM);
	
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);

	pgeMp3Play("test.mp3");
	
	pgeMp3Volume(32678);
		
	pgeMp3Loop(loop);
	
	pgeMp3Info mp3info = pgeMp3GetInfo();
	
	short *audiodata;
	
	int i;
	
	while(pgeRunning())
	{
		// Start drawing
		pgeGfxStartDrawing();

		// Clear screen (black)
		pgeGfxClearScreen(0);
		
		// Update controller data
		pgeControlsUpdate();
		
		audiodata = pgeMp3GetAudioData();
		
		pgeVertCV *lines = (pgeVertCV*) pgeGfxGetVertexMemory(400 * sizeof(pgeVertCV));
		
		for(i = 0; i < 400; i++)
		{
			lines[i].x = 40 + i;
			lines[i].y = ((audiodata[(i * 2)] + 32767) * 0.002f) + 130.0f;
			lines[i].color = 0xFFFFFF44;
		}
		
		pgeGfxDrawCustom2D(PGE_PRIM_LINE_STRIP, PGE_VERT_CV, 400, lines);
		
		pgeFontActivate(verdana12);

		pgeFontPrintf(verdana12, 30, 30, 0xFFFFFFFF, "Title: %s", mp3info.title);
		pgeFontPrintf(verdana12, 30, 45, 0xFFFFFFFF, "Artist: %s", mp3info.artist);
		pgeFontPrintf(verdana12, 30, 60, 0xFFFFFFFF, "Album: %s", mp3info.album);
		pgeFontPrintf(verdana12, 30, 75, 0xFFFFFFFF, "Year: %s", mp3info.year);
		pgeFontPrintf(verdana12, 30, 90, 0xFFFFFFFF, "Comment: %s", mp3info.comment);
		pgeFontPrintf(verdana12, 30, 105, 0xFFFFFFFF, "Genre: %s", mp3info.genretext);
		pgeFontPrintf(verdana12, 30, 120, 0xFFFFFFFF, "ID3 Version: %s", mp3info.id3version);
				
		// Start playing
		if(pgeControlsPressed(PGE_CTRL_CIRCLE))
			pgeMp3Stop();

		// Pause playing
		if(pgeControlsPressed(PGE_CTRL_SQUARE))
			pgeMp3Pause();
		
		// Play MP3		
		if(pgeControlsPressed(PGE_CTRL_TRIANGLE))
			pgeMp3Play("test.mp3");
			
		// Change loop
		if(pgeControlsPressed(PGE_CTRL_START))
		{
			loop ^= 1;
			pgeMp3Loop(loop);
		}
	
		// End drawing
		pgeGfxEndDrawing();

		// Swap buffer (wait for vysnc)
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);
	}
	
	pgeGfxShutdown();
	
	pgeExit();
	
	return 0;
}
