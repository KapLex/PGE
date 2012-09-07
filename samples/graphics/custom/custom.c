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

#define NUM_BUTTERFLY 100

typedef struct
{
	float x;
	float y;
	float z;
	float yi;
	float spinz;
	float spinzi;
	float flap;
	float fi;
	
} butterfly;

butterfly butterflies[NUM_BUTTERFLY];

void setButterfly(int loop)
{
	butterflies[loop].x = pgeMathRandf(-17.0f, 17.0f);								// Random x Value From -17.0f To 17.0f
	butterflies[loop].y = 18.0f;											// Set y Position To 18 (Off Top Of Screen)
	butterflies[loop].z = pgeMathRandf(-10.0f, -40.0f);				// z Is A Random Value From -10.0f To -40.0f
	butterflies[loop].spinzi = pgeMathRandf(-1.0f, 1.0f);				// spinzi Is A Random Value From -1.0f To 1.0f
	butterflies[loop].flap = 0.0f;										// flap Starts Off At 0.0f;
	butterflies[loop].fi = pgeMathRandf(0.05f, 0.15f);					// fi Is A Random Value From 0.05f To 0.15f
	butterflies[loop].yi = 0.001f + pgeMathRandf(0.0f, 0.1f);					// yi Is A Random Value From 0.001f To 0.101f
}

int main(int argc, char*argv[])
{
	// Init graphics
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);
	
	float tilt = 45.0f;
	
	int loop = 0;
	
	for(loop = 0;loop < NUM_BUTTERFLY;loop++)
		setButterfly(loop);
		
	pgeTexture *texture = pgeTextureLoad("butterfly.png", PGE_RAM);
	
	if(!texture)
		pgeExit();
		
	
	pgeGfxStartDrawing();
	
	pgeTextureModeSet(PGE_TEX_MODE_MODULATE);
	
	pgeGfxBlendModeSet(PGE_BLEND_MODE_TRANSPARENT);
	
	pgeGfxEndDrawing();
	
	unsigned int white = pgeGfxCreateColor(255, 255, 255, 255);

	while(pgeRunning())
	{
		// Start drawing
		pgeGfxStartDrawing();
		
		pgeGfxSetMode3D(60.0f);
		
		// Clear screen
		pgeGfxClearScreen(0);
		
		pgeTextureActivate(texture);
		
		for(loop = 0; loop < NUM_BUTTERFLY; loop++)
		{
			ScePspFVector3 pos = {butterflies[loop].x, butterflies[loop].y, butterflies[loop].z};
			ScePspFVector3 rot = {tilt/57.0f, 0.0f, butterflies[loop].spinz/57.0f};
			
			pgeVertTCV *vertices = (pgeVertTCV *) pgeGfxGetVertexMemory(6 * sizeof(pgeVertTCV));
			
			vertices[0].u = 1.0f;
			vertices[0].v = 1.0f;
			vertices[0].color = white;
			vertices[0].x = 1.0f;
			vertices[0].y = 1.0f;
			vertices[0].z = 0.0f;
			
			vertices[1].u = 0.0f;
			vertices[1].v = 1.0f;
			vertices[1].color = white;
			vertices[1].x = -1.0f;
			vertices[1].y = 1.0f;
			vertices[1].z = butterflies[loop].flap;
			
			vertices[2].u = 0.0f;
			vertices[2].v = 0.0f;
			vertices[2].color = white;
			vertices[2].x = -1.0f;
			vertices[2].y = -1.0f;
			vertices[2].z = 0.0f;
			
			vertices[3].u = 1.0f;
			vertices[3].v = 1.0f;
			vertices[3].color = white;
			vertices[3].x = 1.0f;
			vertices[3].y = 1.0f;
			vertices[3].z = 0.0f;
			
			vertices[4].u = 0.0f;
			vertices[4].v = 0.0f;
			vertices[4].color = white;
			vertices[4].x = -1.0f;
			vertices[4].y = -1.0f;
			vertices[4].z = 0.0f;
			
			vertices[5].u = 1.0f;
			vertices[5].v = 0.0f;
			vertices[5].color = 0xFFFFFFFF;
			vertices[5].x = 1.0f;
			vertices[5].y = -1.0f;
			vertices[5].z = butterflies[loop].flap;

			pgeGfxDrawCustom3D(&pos, &rot, PGE_PRIM_TRIANGLES, PGE_VERT_TCV, 2*3, vertices);
		
			butterflies[loop].y -= butterflies[loop].yi;
			butterflies[loop].spinz += butterflies[loop].spinzi;
			butterflies[loop].flap += butterflies[loop].fi;

			if(butterflies[loop].y < -18.0f)
				setButterfly(loop);

			if(butterflies[loop].flap > 1.0f || butterflies[loop].flap < -1.0f)
				butterflies[loop].fi =- butterflies[loop].fi;
		}

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
