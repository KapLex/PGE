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

#define PI   3.14159265358979f
#define PI_2 1.57079632679489f

int main(int argc, char*argv[])
{
	float xoffset, yoffset;
	float step;
	int i;

	xoffset = 240.0f;
	yoffset = 136.0f;
	
	// Init the controls
	pgeControlsInit(); 
	
	// Init graphics
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);
	
	pgeTexture *particleTex = pgeTextureLoad("particles.png", PGE_RAM);
	pgeTexture *chaoTex = pgeTextureLoad("russelchao.png", PGE_RAM);

	if(!particleTex || !chaoTex)
		sceKernelExitGame();
	
	// Init the Particle Systems
	pgeTimer *timer = pgeTimerCreate();
	
	pgeParticleSystem *psMovable = pgeParticleSystemLoad("preset0.pts", particleTex);
	pgeParticleSystemFireAt(psMovable, xoffset+10, yoffset+10);

	pgeParticleSystem *psChao = pgeParticleSystemLoad("preset1.pts", chaoTex);
	pgeParticleSystemFireAt(psChao, xoffset, yoffset);

	pgeParticleSystem *psExplode[4];
	for(i=0; i < 4; i++)
	{
		psExplode[i] = pgeParticleSystemLoad("preset2.pts", particleTex);
	}
	pgeParticleSystemMoveTo(psExplode[0], 0, 0, 1);
	pgeParticleSystemMoveTo(psExplode[1], 480, 0, 1);
	pgeParticleSystemMoveTo(psExplode[2], 480, 272, 1);
	pgeParticleSystemMoveTo(psExplode[3], 0, 272, 1);

	//printf("\nDebug Info\n");
	//printf("MOVABLE life: %f\n", psMovable->info.fLifetime);
	//printf("CHAO    life: %f\n", psChao->info.fLifetime);

	while(pgeRunning())
	{
		pgeTimerUpdate(timer);
		pgeParticleSystemUpdate(psMovable, timer->deltatime);
		pgeParticleSystemUpdate(psChao, timer->deltatime);
		for(i=0; i < 4; i++)	
		{
			pgeParticleSystemUpdate(psExplode[i], timer->deltatime);
		}
		
		// Update the controller data
		pgeControlsUpdate();

		// Start drawing
		pgeGfxStartDrawing();

		// Clear screen (black)
		pgeGfxClearScreen(0);

		pgeParticleSystemRender(psMovable);
		pgeParticleSystemRender(psChao);
		for(i=0; i < 4; i++)
		{
			pgeParticleSystemRender(psExplode[i]);
		}

		pgeGfxEndDrawing();

		// Swap buffer (wait for vysnc)
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);

		// Update parameters depending on buttons being held
		if (pgeControlsHeld(PGE_CTRL_SQUARE))
		{
			step = 10.0f;
		}
		else
		{
			step = 1.0f;
		}

		if (pgeControlsAnalogX() < -64)
		{
			xoffset -= step;
			pgeParticleSystemMoveTo(psMovable, xoffset, yoffset, 0);
		}
		if (pgeControlsAnalogX() > 64)
		{
			xoffset += step;
			pgeParticleSystemMoveTo(psMovable, xoffset, yoffset, 0);
		}
		if (pgeControlsAnalogY() < -64)
		{
			yoffset -= step;
			pgeParticleSystemMoveTo(psMovable, xoffset, yoffset, 0);
		}
		if (pgeControlsAnalogY() > 64)
		{
			yoffset += step;
			pgeParticleSystemMoveTo(psMovable, xoffset, yoffset, 0);
		}

		if (pgeControlsHeld(PGE_CTRL_CROSS))
		{
			for(i=0; i < 4; i++)
			{
				pgeParticleSystemFire(psExplode[i]);
			}
		}
	}
	
	// Shutdown graphics
	pgeGfxShutdown();
	
	pgeParticleSystemDestroy(psMovable);
	pgeParticleSystemDestroy(psChao);
	for(i=0; i < 4; i++)
	{
		pgeParticleSystemDestroy(psExplode[i]);
	}

	pgeExit();
	
	return 0;
}
