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
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);
	
	pgeFontInit();
	
	pgeControlsInit();
	
	int result = pgeUsbInit();
	
	if(result != 1)
		pgeExit();
		
	pgeFont *verdana12 = pgeFontLoad("./verdana.ttf", 12, PGE_FONT_SIZE_POINTS, PGE_RAM);
	
	if(!verdana12)
		pgeExit();
		
	int state;
	
	while(pgeRunning())
	{
		pgeControlsUpdate();
		
		pgeGfxStartDrawing();
		
		pgeGfxClearScreen(0);
		
		state = pgeUsbGetState();
		
		pgeFontActivate(verdana12);
		
		pgeFontPrintf(verdana12, 20, 20, 0xFFFFFFFF, "Press X to activate USB");
		
		pgeFontPrintf(verdana12, 20, 40, 0xFFFFFFFF, "Press O to deactivate USB");
		
		if(state & PGE_USB_ACTIVATED)
			pgeFontPrintf(verdana12, 20, 60, 0xFF00FF00, "USB activated");
			
		if(state & PGE_USB_CABLE_CONNECTED)
			pgeFontPrintf(verdana12, 20, 80, 0xFF00FF00, "Cable connected");
			
		if(state & PGE_USB_CONNECTION_ESTABLISHED)
			pgeFontPrintf(verdana12, 20, 100, 0xFF00FF00, "Connection established");
		
		if(pgeControlsPressed(PGE_CTRL_CROSS))
			pgeUsbActivate();
			
		if(pgeControlsPressed(PGE_CTRL_CIRCLE))
			pgeUsbDeactivate();
		
		pgeGfxEndDrawing();
		
		pgeGfxSwapBuffers(1);
	}
	
	pgeFontDestroy(verdana12);
	
	pgeUsbDeactivate();
	
	pgeUsbShutdown();
	
	pgeFontShutdown();
	
	pgeGfxShutdown();
	
	pgeControlsShutdown();
	
	pgeExit();

	return 0;
}
