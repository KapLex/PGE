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
#define KEYREPEAT 5
#define SAVEPRINTDELAY 100

pgeParticleSystem *ps;
pgeFont *ttf;

float validator[33][3] = {
	{0,9,1},							// preset
	{0,15,1},							// particle image
	{0,MAX_PARTICLES,1},	// number of emitted particles per second
	{0,100,0.1},					// system lifetime
	{0,1,1},							// continuous
	{0,5,0.01},						// particle lifetime min
	{0,5,0.01},						// particle lifetime max
	{0,2*PI,0.01},				// particle movement direction
	{0,2*PI,0.01},				// particle movement spreading
	{-300,300,0.1},				// particle speed min
	{-300,300,0.1},				// particle speed max
	{-100,100,0.1},				// gravity min
	{-100,100,0.1},				// gravity max
	{-100,100,0.1},					// radial accel min
	{-100,100,0.1},					// radial accel max
	{-100,100,0.1},					// tangential accel min
	{-100,100,0.1},					// tangential accel max
	{0.01,2,0.01},				// particle size start
	{0.01,2,0.01},				// particle size end
	{0,1,0.01},						// particle size variance
	{-50,50,0.1},						// particle spin start
	{-50,50,0.1},						// particle spin end
	{0,1,0.01},						// particle spin variance
	{0,1,0.01},						// particle color R start
	{0,1,0.01},						// particle color G start
	{0,1,0.01},						// particle color B start
	{0,1,0.01},						// particle color A start
	{0,1,0.01},						// particle color R start
	{0,1,0.01},						// particle color G start
	{0,1,0.01},						// particle color B start
	{0,1,0.01},						// particle color A start
	{0,1,0.01},						// particle color variance
	{0,1,0.01}						// particle alpha variance
};

// init default particle system values
void initParticleSystem()
{
	ps->info.nEmission = 50;
	ps->info.fLifetime = 10.0f;
	ps->info.fParticleLifeMin = 2.0f;
	ps->info.fParticleLifeMax = 3.0f;
	ps->info.fDirection = 0.0f;
	ps->info.fSpread = PI_2;
	ps->info.fSpeedMin = 1.0f;
	ps->info.fSpeedMax = 2.0f;
	ps->info.fGravityMin = 0.5f;
	ps->info.fGravityMax = 1.0f;
	ps->info.fRadialAccelMin = 0.0f;
	ps->info.fRadialAccelMax = 0.0f;
	ps->info.fTangentialAccelMin = 0.0f;
	ps->info.fTangentialAccelMax = 0.0f;
	ps->info.fSizeStart = 1.0f;
	ps->info.fSizeEnd = 0.5f;
	ps->info.fSizeVar = 0.2f;
	ps->info.fSpinStart = 0.0f;
	ps->info.fSpinEnd = 0.0f;
	ps->info.fSpinVar = 0.0f;
	ps->info.colColorStart = (pgeColorRGB){1.0f, 0.0f, 0.0f, 1.0f};
	ps->info.colColorEnd = (pgeColorRGB){0.0f, 1.0f, 0.0f, 0.2f};
	ps->info.fColorVar = 0.5f;
	ps->info.fAlphaVar = 0.1f;
}

// validated Increment of a value
void validatedInc(float *fVal, int index, int largestep, int warp)
{
	if(index >= 0 && index < 33)
	{
		if(largestep)
		{
			*fVal += validator[index][2]*10;
		}
		else
		{
			*fVal += validator[index][2];
		}
		if(*fVal > validator[index][1])
		{
			if(warp)
			{
				*fVal = validator[index][0];
			}
			else
			{
				*fVal = validator[index][1];
			}
		}
	}
}

// validated Decrement of a value
void validatedDec(float *fVal, int index, int largestep, int warp)
{
	if(index >= 0 && index < 33)
	{
		if(largestep)
		{
			*fVal -= validator[index][2]*10;
		}
		else
		{
			*fVal -= validator[index][2];
		}
		if(*fVal < validator[index][0])
		{
			if(warp)
			{
				*fVal = validator[index][1];
			}
			else
			{
				*fVal = validator[index][0];
			}
		}
	}
}

void savePreset(int iPreset)
{
	char filename[20];
	sprintf(filename, "./preset%i.pts", iPreset);
	pgeFile *file = pgeFileOpen(filename, PGE_FILE_WRONLY|PGE_FILE_CREATE);
	if(file)
	{
		pgeFileWrite(file, &ps->info, sizeof(ps->info));
		pgeFileClose(file);
	}
}

int loadPreset(int iPreset, pgeTexture *tex)
{
	char filename[20];
	sprintf(filename, "./preset%i.pts", iPreset);
	return(pgeParticleSystemSetInfoFromFile(ps, filename, tex));
}

int main(int argc, char*argv[])
{
	float xoffset, yoffset;
	float fTemp;
	int iCurrentPreset = 0;
	int iCurrentItem = 0;
	int iMenuVisible = 0;
	int iRepeat = 0;
	int iScroll = 0;
	int iParticleImage = 0;

	char cSavePrint[20];
	int iSavePrintDelay = 0;

	// Init the font
	pgeFontInit();

	// Init the controls
	pgeControlsInit(); 
	
	// Init graphics
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);

	ttf = pgeFontLoad("./monaco.ttf", 9, PGE_FONT_SIZE_POINTS, PGE_VRAM);

	pgeTexture *image = pgeTextureLoad("particles.png", PGE_RAM);
	xoffset = 240.0f;
	yoffset = 136.0f;
	
	if(!image || !ttf)
		sceKernelExitGame();
	
	// Init the Particle Engine with a Sample
	pgeRect spriteRect;
	spriteRect.x = 0;
	spriteRect.y = 0;
	spriteRect.w = 32;
	spriteRect.h = 32;
	
	//pgeParticleSystemCreate(&ps, image, spriteRect);
	ps = pgeParticleSystemCreate(image, spriteRect);
	
	if(!loadPreset(iCurrentPreset, image))
	{
		initParticleSystem();	// init default particle system values
		pgeUtilsMsgDialogInit(PGE_UTILS_MSG_DIALOG_NO_OPTIONS, "PGE Particle Editor First time usage\n-----------------------------------------------\nWelcome to the PGE Particle Editor, here is the button configuration:\nAnalog: Move the particle system\nStart: Fire the particle system\nSelect: Open/Close the menu\nD-Pad Up/Down: Browse the menu\nD-Pad Left-Right: Change the values\nHold Square for larger steps in changing values\nTriangle: Save to current preset\nLeft Trigger: Bring up this help");
	}
	else
	{
		iParticleImage = 4 * ps->info.spriteRect.y / 32 + ps->info.spriteRect.x / 32;
		ps->info.spriteTexture = image;
		pgeParticleSystemMoveTo(ps, xoffset, yoffset, 1);
	}

	pgeParticleSystemFireAt(ps, xoffset, yoffset);

	pgeTimer *timer = pgeTimerCreate();

	while(pgeRunning())
	{
		pgeTimerUpdate(timer);
		pgeParticleSystemUpdate(ps, timer->deltatime);
	
		// Update the controller data
		pgeControlsUpdate();

		// Start drawing
		pgeGfxStartDrawing();

		pgeGfxClearScreen(0);	// Clear screen (black)

		pgeParticleSystemRender(ps);	// Render the particle system

		if(iSavePrintDelay > 0)
		{
			pgeFontActivate(ttf);
			pgeFontPrintf(ttf, 320, 260, 0xFFFFFFFF, cSavePrint);
			iSavePrintDelay--;
		}
		else
		{
			iSavePrintDelay = 0;
		}

		if(iMenuVisible)
		{
			pgeFontActivate(ttf);
			pgeFontPrintf(ttf, 0,   0-iScroll, iCurrentItem == 0 ? 0xFFFFFFFF : 0xFFA0A0A0, "Preset: %i", iCurrentPreset);
			pgeFontPrintf(ttf, 0,  10-iScroll, iCurrentItem == 1 ? 0xFFFFFFFF : 0xFFA0A0A0, "Particle Image: %i", iParticleImage);
			pgeFontPrintf(ttf, 0,  20-iScroll, iCurrentItem == 2 ? 0xFFFFFFFF : 0xFFA0A0A0, "Particle Emission: %i", ps->info.nEmission);
			pgeFontPrintf(ttf, 0,  30-iScroll, iCurrentItem == 3 ? 0xFFFFFFFF : 0xFFA0A0A0, "System Lifetime: %3.1f", ps->info.fLifetime);
			pgeFontPrintf(ttf, 0,  40-iScroll, iCurrentItem == 4 ? 0xFFFFFFFF : 0xFFA0A0A0, "Continuous System Lifetime: %s", ps->info.fLifetime == -1.0f ? "yes" : "no");
			pgeFontPrintf(ttf, 0,  50-iScroll, iCurrentItem == 5 ? 0xFFFFFFFF : 0xFFA0A0A0, "Particle Life MIN: %1.2f", ps->info.fParticleLifeMin);
			pgeFontPrintf(ttf, 0,  60-iScroll, iCurrentItem == 6 ? 0xFFFFFFFF : 0xFFA0A0A0, "Particle Life MAX: %1.2f", ps->info.fParticleLifeMax);
			pgeFontPrintf(ttf, 0,  70-iScroll, iCurrentItem == 7 ? 0xFFFFFFFF : 0xFFA0A0A0, "Direction: %1.2f", ps->info.fDirection);
			pgeFontPrintf(ttf, 0,  80-iScroll, iCurrentItem == 8 ? 0xFFFFFFFF : 0xFFA0A0A0, "Spread: %1.2f", ps->info.fSpread);
			pgeFontPrintf(ttf, 0,  90-iScroll, iCurrentItem == 9 ? 0xFFFFFFFF : 0xFFA0A0A0, "Speed MIN: %3.1f", ps->info.fSpeedMin);
			pgeFontPrintf(ttf, 0, 100-iScroll, iCurrentItem == 10 ? 0xFFFFFFFF : 0xFFA0A0A0, "Speed MAX: %3.1f", ps->info.fSpeedMax);
			pgeFontPrintf(ttf, 0, 110-iScroll, iCurrentItem == 11 ? 0xFFFFFFFF : 0xFFA0A0A0, "Gravity MIN: %3.1f", ps->info.fGravityMin);
			pgeFontPrintf(ttf, 0, 120-iScroll, iCurrentItem == 12 ? 0xFFFFFFFF : 0xFFA0A0A0, "Gravity MAX: %3.1f", ps->info.fGravityMax);
			pgeFontPrintf(ttf, 0, 130-iScroll, iCurrentItem == 13 ? 0xFFFFFFFF : 0xFFA0A0A0, "Radial Accel. MIN: %1.1f", ps->info.fRadialAccelMin);
			pgeFontPrintf(ttf, 0, 140-iScroll, iCurrentItem == 14 ? 0xFFFFFFFF : 0xFFA0A0A0, "Radial Accel. MAX: %1.1f", ps->info.fRadialAccelMax);
			pgeFontPrintf(ttf, 0, 150-iScroll, iCurrentItem == 15 ? 0xFFFFFFFF : 0xFFA0A0A0, "Tangent. Accel. MIN: %1.1f", ps->info.fTangentialAccelMin);
			pgeFontPrintf(ttf, 0, 160-iScroll, iCurrentItem == 16 ? 0xFFFFFFFF : 0xFFA0A0A0, "Tangent. Accel. MAX: %1.1f", ps->info.fTangentialAccelMax);
			pgeFontPrintf(ttf, 0, 170-iScroll, iCurrentItem == 17 ? 0xFFFFFFFF : 0xFFA0A0A0, "Particle Size Start: %1.2f", ps->info.fSizeStart);
			pgeFontPrintf(ttf, 0, 180-iScroll, iCurrentItem == 18 ? 0xFFFFFFFF : 0xFFA0A0A0, "Particle Size End: %1.2f", ps->info.fSizeEnd);
			pgeFontPrintf(ttf, 0, 190-iScroll, iCurrentItem == 19 ? 0xFFFFFFFF : 0xFFA0A0A0, "Particle Size Var.: %1.2f", ps->info.fSizeVar);
			pgeFontPrintf(ttf, 0, 200-iScroll, iCurrentItem == 20 ? 0xFFFFFFFF : 0xFFA0A0A0, "Particle Spin Start: %2.1f", ps->info.fSpinStart);
			pgeFontPrintf(ttf, 0, 210-iScroll, iCurrentItem == 21 ? 0xFFFFFFFF : 0xFFA0A0A0, "Particle Spin End: %2.1f", ps->info.fSpinEnd);
			pgeFontPrintf(ttf, 0, 220-iScroll, iCurrentItem == 22 ? 0xFFFFFFFF : 0xFFA0A0A0, "Particle Spin Var.: %1.2f", ps->info.fSpinVar);
			pgeFontPrintf(ttf, 0, 230-iScroll, iCurrentItem == 23 ? 0xFFFFFFFF : 0xFFA0A0A0, "Start Color R: %1.2f", ps->info.colColorStart.r);
			pgeFontPrintf(ttf, 0, 240-iScroll, iCurrentItem == 24 ? 0xFFFFFFFF : 0xFFA0A0A0, "Start Color G: %1.2f", ps->info.colColorStart.g);
			pgeFontPrintf(ttf, 0, 250-iScroll, iCurrentItem == 25 ? 0xFFFFFFFF : 0xFFA0A0A0, "Start Color B: %1.2f", ps->info.colColorStart.b);
			pgeFontPrintf(ttf, 0, 260-iScroll, iCurrentItem == 26 ? 0xFFFFFFFF : 0xFFA0A0A0, "Start Color A: %1.2f", ps->info.colColorStart.a);
			pgeFontPrintf(ttf, 0, 270-iScroll, iCurrentItem == 27 ? 0xFFFFFFFF : 0xFFA0A0A0, "End Color R: %1.2f", ps->info.colColorEnd.r);
			pgeFontPrintf(ttf, 0, 280-iScroll, iCurrentItem == 28 ? 0xFFFFFFFF : 0xFFA0A0A0, "End Color G: %1.2f", ps->info.colColorEnd.g);
			pgeFontPrintf(ttf, 0, 290-iScroll, iCurrentItem == 29 ? 0xFFFFFFFF : 0xFFA0A0A0, "End Color B: %1.2f", ps->info.colColorEnd.b);
			pgeFontPrintf(ttf, 0, 300-iScroll, iCurrentItem == 30 ? 0xFFFFFFFF : 0xFFA0A0A0, "End Color A: %1.2f", ps->info.colColorEnd.a);
			pgeFontPrintf(ttf, 0, 310-iScroll, iCurrentItem == 31 ? 0xFFFFFFFF : 0xFFA0A0A0, "Color Variance: %1.2f", ps->info.fColorVar);
			pgeFontPrintf(ttf, 0, 320-iScroll, iCurrentItem == 32 ? 0xFFFFFFFF : 0xFFA0A0A0, "Alpha Variance: %1.2f", ps->info.fAlphaVar);
		}

		pgeGfxEndDrawing();

		pgeUtilsMsgDialogUpdate();

		// Swap buffer (wait for vysnc)
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);

		// particle system movement via analog stick
		if (pgeControlsAnalogX() < -64)
		{
			xoffset -= 1;
			pgeParticleSystemMoveTo(ps, xoffset, yoffset, 0);
		}
		if (pgeControlsAnalogX() > 64)
		{
			xoffset += 1;
			pgeParticleSystemMoveTo(ps, xoffset, yoffset, 0);
		}
		if (pgeControlsAnalogY() < -64)
		{
			yoffset -= 1;
			pgeParticleSystemMoveTo(ps, xoffset, yoffset, 0);
		}
		if (pgeControlsAnalogY() > 64)
		{
			yoffset += 1;
			pgeParticleSystemMoveTo(ps, xoffset, yoffset, 0);
		}

		// fire the particle system via start button
		if (pgeControlsPressed(PGE_CTRL_START))
		{
			pgeParticleSystemFire(ps);
		}

		// switch menu visibility via Select button
		if(pgeControlsPressed(PGE_CTRL_SELECT))
		{
			iMenuVisible = iMenuVisible ? 0 : 1;
		}

		// bring up help screen via Left Trigger
		if(pgeControlsPressed(PGE_CTRL_LTRIGGER))
		{
			pgeUtilsMsgDialogInit(PGE_UTILS_MSG_DIALOG_NO_OPTIONS, "PGE Particle Editor Help\n--------------------------------\nButton configuration:\nAnalog: Move the particle system\nStart: Fire the particle system\nSelect: Open/Close the menu\nD-Pad Up/Down: Browse the menu\nD-Pad Left-Right: Change the values\nHold Square for larger steps in changing values\nTriangle: Save to current preset\nLeft Trigger: Bring up this help");
		}

		// save preset via Triangle Button
		if(pgeControlsPressed(PGE_CTRL_TRIANGLE))
		{
			savePreset(iCurrentPreset);
			sprintf(cSavePrint, "Saved preset%i.pts", iCurrentPreset);
			iSavePrintDelay = SAVEPRINTDELAY;
		}

		if(!pgeControlsHeldAny() && !pgeControlsHeld(PGE_CTRL_SQUARE))
		{
			iRepeat = KEYREPEAT;
		}
		else
		{
			iRepeat++;
		}
		
		if(iRepeat >= KEYREPEAT)
		{
			// browse menu if displayed
			if(iMenuVisible)
			{
				if(pgeControlsHeld(PGE_CTRL_UP))
				{
					iRepeat = 0;
					iCurrentItem--;
					if(iCurrentItem < 0)
					{
						iCurrentItem = 0;
					}
					if(iCurrentItem*10 - iScroll < 0)
					{
						iScroll = 0;
					}
				}
				if(pgeControlsHeld(PGE_CTRL_DOWN))
				{
					iRepeat = 0;
					iCurrentItem++;
					if(iCurrentItem > 32)
					{
						iCurrentItem = 32;
					}
					if(iCurrentItem*10 + iScroll > 260)
					{
						iScroll = 60;
					}
				}
				if(pgeControlsHeld(PGE_CTRL_RIGHT))
				{
					iRepeat = 0;
					int largestep = pgeControlsHeld(PGE_CTRL_SQUARE) ? 1 : 0;
					switch(iCurrentItem)
					{
					case 0:
						iCurrentPreset++;
						if(iCurrentPreset > 9)
						{
							iCurrentPreset = 0;
						}
						if(!loadPreset(iCurrentPreset, image))
						{
							initParticleSystem();
						}
						iParticleImage = 4 * ps->info.spriteRect.y / 32 + ps->info.spriteRect.x / 32;
						ps->info.spriteTexture = image;
						pgeParticleSystemMoveTo(ps, xoffset, yoffset, 1);
						pgeParticleSystemFireAt(ps, xoffset, yoffset);

						break;	
					case 1:
						// ! particle image
						iParticleImage++;
						if(iParticleImage > 15)
						{
							iParticleImage = 0;
						}
						ps->info.spriteRect.x = 32*(iParticleImage % 4);
						ps->info.spriteRect.y = 32*(iParticleImage / 4);
						break;	
					case 2:
						fTemp = (float)ps->info.nEmission;
						validatedInc(&fTemp, 2, largestep, 0);
						ps->info.nEmission = (int)fTemp;
						break;
					case 3:
						if(ps->info.fLifetime < 0.0f)
						{
							ps->info.fLifetime = 0;
						}
						else
						{
							validatedInc(&ps->info.fLifetime, 3, largestep, 0);
						}
						break;
					case 4:
						// ! Continuous
						ps->info.fLifetime = -1.0f;
						break;
					case 5:
						validatedInc(&ps->info.fParticleLifeMin, 5, largestep, 0);
						break;
					case 6:
						validatedInc(&ps->info.fParticleLifeMax, 6, largestep, 0);
						break;
					case 7:
						validatedInc(&ps->info.fDirection, 7, largestep, 0);
						break;
					case 8:
						validatedInc(&ps->info.fSpread, 8, largestep, 0);
						break;
					case 9:
						validatedInc(&ps->info.fSpeedMin, 9, largestep, 0);
						break;
					case 10:
						validatedInc(&ps->info.fSpeedMax, 10, largestep, 0);
						break;
					case 11:
						validatedInc(&ps->info.fGravityMin, 11, largestep, 0);
						break;
					case 12:
						validatedInc(&ps->info.fGravityMax, 12, largestep, 0);
						break;
					case 13:
						validatedInc(&ps->info.fRadialAccelMin, 13, largestep, 0);
						break;
					case 14:
						validatedInc(&ps->info.fRadialAccelMax, 14, largestep, 0);
						break;
					case 15:
						validatedInc(&ps->info.fTangentialAccelMin, 15, largestep, 0);
						break;
					case 16:
						validatedInc(&ps->info.fTangentialAccelMax, 16, largestep, 0);
						break;
					case 17:
						validatedInc(&ps->info.fSizeStart, 17, largestep, 0);
						break;
					case 18:
						validatedInc(&ps->info.fSizeEnd, 18, largestep, 0);
						break;
					case 19:
						validatedInc(&ps->info.fSizeVar, 19, largestep, 0);
						break;
					case 20:
						validatedInc(&ps->info.fSpinStart, 20, largestep, 0);
						break;
					case 21:
						validatedInc(&ps->info.fSpinEnd, 21, largestep, 0);
						break;
					case 22:
						validatedInc(&ps->info.fSpinVar, 22, largestep, 0);
						break;
					case 23:
						validatedInc(&ps->info.colColorStart.r, 23, largestep, 0);
						break;
					case 24:
						validatedInc(&ps->info.colColorStart.g, 24, largestep, 0);
						break;
					case 25:
						validatedInc(&ps->info.colColorStart.b, 25, largestep, 0);
						break;
					case 26:
						validatedInc(&ps->info.colColorStart.a, 26, largestep, 0);
						break;
					case 27:
						validatedInc(&ps->info.colColorEnd.r, 27, largestep, 0);
						break;
					case 28:
						validatedInc(&ps->info.colColorEnd.g, 28, largestep, 0);
						break;
					case 29:
						validatedInc(&ps->info.colColorEnd.b, 29, largestep, 0);
						break;
					case 30:
						validatedInc(&ps->info.colColorEnd.a, 30, largestep, 0);
						break;
					case 31:
						validatedInc(&ps->info.fColorVar, 31, largestep, 0);
						break;
					case 32:
						validatedInc(&ps->info.fAlphaVar, 32, largestep, 0);
						break;
					default:
						break;
					}
				}
			}

			if(pgeControlsHeld(PGE_CTRL_LEFT))
			{
				iRepeat = 0;
				int largestep = pgeControlsHeld(PGE_CTRL_SQUARE) ? 1 : 0;
				switch(iCurrentItem)
				{
				case 0:
					iCurrentPreset--;
					if(iCurrentPreset < 0)
					{
						iCurrentPreset = 9;
					}
					if(!loadPreset(iCurrentPreset, image))
					{
						initParticleSystem();
					}
					iParticleImage = 4 * ps->info.spriteRect.y / 32 + ps->info.spriteRect.x / 32;
					ps->info.spriteTexture = image;
					pgeParticleSystemMoveTo(ps, xoffset, yoffset, 1);
					pgeParticleSystemFireAt(ps, xoffset, yoffset);
					break;	
				case 1:
					// ! particle image
					iParticleImage--;
					if(iParticleImage < 0)
					{
						iParticleImage = 15;
					}
					ps->info.spriteRect.x = 32*(iParticleImage % 4);
					ps->info.spriteRect.y = 32*(iParticleImage / 4);
					break;	
				case 2:
					fTemp = (float)ps->info.nEmission;
					validatedDec(&fTemp, 2, largestep, 0);
					ps->info.nEmission = (int)fTemp;
					break;
				case 3:
					if(ps->info.fLifetime < 0.0f)
					{
						ps->info.fLifetime = 0;
					}
					else
					{
						validatedDec(&ps->info.fLifetime, 3, largestep, 0);
					}
					break;
				case 4:
					// ! Continuous
					ps->info.fLifetime = -1.0f;
					break;
				case 5:
					validatedDec(&ps->info.fParticleLifeMin, 5, largestep, 0);
					break;
				case 6:
					validatedDec(&ps->info.fParticleLifeMax, 6, largestep, 0);
					break;
				case 7:
					validatedDec(&ps->info.fDirection, 7, largestep, 0);
					break;
				case 8:
					validatedDec(&ps->info.fSpread, 8, largestep, 0);
					break;
				case 9:
					validatedDec(&ps->info.fSpeedMin, 9, largestep, 0);
					break;
				case 10:
					validatedDec(&ps->info.fSpeedMax, 10, largestep, 0);
					break;
				case 11:
					validatedDec(&ps->info.fGravityMin, 11, largestep, 0);
					break;
				case 12:
					validatedDec(&ps->info.fGravityMax, 12, largestep, 0);
					break;
				case 13:
					validatedDec(&ps->info.fRadialAccelMin, 13, largestep, 0);
					break;
				case 14:
					validatedDec(&ps->info.fRadialAccelMax, 14, largestep, 0);
					break;
				case 15:
					validatedDec(&ps->info.fTangentialAccelMin, 15, largestep, 0);
					break;
				case 16:
					validatedDec(&ps->info.fTangentialAccelMax, 16, largestep, 0);
					break;
				case 17:
					validatedDec(&ps->info.fSizeStart, 17, largestep, 0);
					break;
				case 18:
					validatedDec(&ps->info.fSizeEnd, 18, largestep, 0);
					break;
				case 19:
					validatedDec(&ps->info.fSizeVar, 19, largestep, 0);
					break;
				case 20:
					validatedDec(&ps->info.fSpinStart, 20, largestep, 0);
					break;
				case 21:
					validatedDec(&ps->info.fSpinEnd, 21, largestep, 0);
					break;
				case 22:
					validatedDec(&ps->info.fSpinVar, 22, largestep, 0);
					break;
				case 23:
					validatedDec(&ps->info.colColorStart.r, 23, largestep, 0);
					break;
				case 24:
					validatedDec(&ps->info.colColorStart.g, 24, largestep, 0);
					break;
				case 25:
					validatedDec(&ps->info.colColorStart.b, 25, largestep, 0);
					break;
				case 26:
					validatedDec(&ps->info.colColorStart.a, 26, largestep, 0);
					break;
				case 27:
					validatedDec(&ps->info.colColorEnd.r, 27, largestep, 0);
					break;
				case 28:
					validatedDec(&ps->info.colColorEnd.g, 28, largestep, 0);
					break;
				case 29:
					validatedDec(&ps->info.colColorEnd.b, 29, largestep, 0);
					break;
				case 30:
					validatedDec(&ps->info.colColorEnd.a, 30, largestep, 0);
					break;
				case 31:
					validatedDec(&ps->info.fColorVar, 31, largestep, 0);
					break;
				case 32:
					validatedDec(&ps->info.fAlphaVar, 32, largestep, 0);
					break;
				default:
					break;
				}
			}
		}
	}
	
	// Shutdown graphics
	pgeGfxShutdown();
	
	pgeExit();
	
	return 0;
}
