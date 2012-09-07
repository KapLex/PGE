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

int loop = 1; // Looping flag

int main(int argc, char*argv[])
{
	// Init controls
	pgeControlsInit();
	
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);
	
	while(pgeRunning())
	{
		printf("Here\n");
		// Update controller data
		pgeControlsUpdate();
		
		char what[256];
		
		getcwd(what, 256);
		
		printf("%s\n", what);
		
		printf("Here2\n");
		pgeDir *thedir = pgeFileOpenDir(".");
		
		printf("Here3\n");
		
		if(thedir == NULL)
			printf("Error opening dir.");
			
		printf("Here4\n");
			
		if(pgeFileReadDir(thedir) <= 0)
			printf("Error reading dir.");
			
		printf("Here5\n");
		
		int i;
		
		for(i = 0;i < thedir->count;i++)
		{
			printf("Here6\n");
			printf("Count %d: Name %s: Size %d: Is dir? %d\n", i, thedir->entries[i].name, thedir->entries[i].size, thedir->entries[i].type);
		}
		
		break;
		
	}
	
	pgeGfxShutdown();
	
	pgeExit();
	
	return 0;
}
