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
	int localversion = 12;
	
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);
	
	pgeNetInit();
	
	pgeControlsInit();
	
	pgeUtilsNetDialogInit();
	
	char buffer[2];
	
	while(pgeRunning())
	{
		pgeGfxStartDrawing();
		
		pgeGfxClearScreen(0);
		
		pgeGfxEndDrawing();
		
		int result = pgeUtilsNetDialogUpdate();
		
		if(result != -1)
			break;
			
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);
	}
	
	pgeNetGetFile("http://www.luaplayer.org/update.txt", "update.txt");
	
	pgeFile *file = pgeFileOpen("update.txt", PGE_FILE_RDONLY);
	
	int currentversion = 0;
	
	pgeFileRead(file, &buffer, 2);
	
	currentversion = atoi(buffer);
		
	if(localversion < currentversion)
	{
		int urllength = 0;
		
		pgeFileSeek(file, 1, PGE_FILE_CUR);
		
		pgeFileRead(file, buffer, 2);
		
		urllength = atoi(buffer);
		
		char *url = malloc(urllength + 1);
		
		if(!url)
			printf("Error allocating!\n");
			
		pgeFileSeek(file, 1, PGE_FILE_CUR);
		
		pgeFileRead(file, url, urllength);
		
		pgeNetGetFile(url, "update.zip");
	
		pgeZip *thezip = pgeZipOpen("update.zip");
	
		pgeZipExtract(thezip, NULL);
	
		pgeZipClose(thezip);
		
		pgeFileRemove("update.txt");
		
		pgeFileRemove("update.zip");
	}
	
	pgeNetShutdown();

	pgeExit();

	return 0;
}
