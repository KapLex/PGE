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
#include <math.h>
 
int main(int argc, char*argv[])
{
	int i;
	float	sinlmtime,   sinpgetime,
				sinhlmtime,  sinhpgetime,
				asinlmtime,  asinpgetime,
				coslmtime,   cospgetime,
				coshlmtime,  coshpgetime,
				acoslmtime,  acospgetime,
				tanlmtime,   tanpgetime,
				tanhlmtime,  tanhpgetime,
			 	atanlmtime,  atanpgetime,
				atan2lmtime, atan2pgetime,
				powlmtime,   powpgetime,
				explmtime,   exppgetime,
				sqrtlmtime,  sqrtpgetime,
				fmodlmtime,  fmodpgetime,
				isqrtlmtime, isqrtpgetime;

	pgeTimer *time;
 
	pspDebugScreenInit();
 
	// Init the controls
	pgeControlsInit();
 
	time = pgeTimerCreate();
 
	float res = 0;
 
	printf("\n");
	printf("Benchmarking...\n");
	pspDebugScreenPrintf("Benchmarking...");

	// Do Benchmark runs
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = sin(i); } sinlmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time); for(i=0; i < 10000; i++) { res = pgeMathSinf(i); } sinpgetime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = sinh(i); } sinhlmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time); for(i=0; i < 10000; i++) { res = pgeMathSinhf(i); } sinhpgetime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = asin(i); } asinlmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time); for(i=0; i < 10000; i++) { res = pgeMathAsinf(i); } asinpgetime = pgeTimerPeekDeltaTime(time);

	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = cos(i); } coslmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = pgeMathCosf(i); } cospgetime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = cosh(i); } coshlmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = pgeMathCoshf(i); } coshpgetime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = acos(i); } acoslmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = pgeMathAcosf(i); } acospgetime = pgeTimerPeekDeltaTime(time);

	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = tan(i); } tanlmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = pgeMathTanf(i); } tanpgetime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = tanh(i); } tanhlmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = pgeMathTanhf(i); } tanhpgetime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = atan(i); } atanlmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = pgeMathAtanf(i); } atanpgetime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = atan2(i, 1.337f); } atan2lmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 10000; i++) { res = pgeMathAtan2f(i, 1.337f); } atan2pgetime = pgeTimerPeekDeltaTime(time);


	pgeTimerUpdate(time);	for(i=0; i < 1000; i++) { res = pow(i, i); } powlmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 1000; i++) { res = pgeMathPowf(i, i); } powpgetime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 1000; i++) { res = exp(i); } explmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 1000; i++) { res = pgeMathExpf(i); } exppgetime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 1000; i++) { res = sqrt(i); } sqrtlmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 1000; i++) { res = pgeMathSqrtf(i); } sqrtpgetime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 1000; i++) { res = fmod(i, 1.337f); } fmodlmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 1000; i++) { res = pgeMathFmodf(i, 1.337f); } fmodpgetime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 1000; i++) { res = pgeMathInvSqrt(1.337f); } isqrtlmtime = pgeTimerPeekDeltaTime(time);
	pgeTimerUpdate(time);	for(i=0; i < 1000; i++) { res = pgeMathInvSqrtVFPU(1.337f); } isqrtpgetime = pgeTimerPeekDeltaTime(time);


	pgeTimerUpdate(time);
 
	printf("Sin  LM   Time = %f Cos   LM   Time = %f\n", sinlmtime,   coslmtime);
	printf("Sin  VFPU Time = %f Cos   VFPU Time = %f\n", sinpgetime,  cospgetime);
	printf("Sinh LM   Time = %f Cosh  LM   Time = %f\n", sinhlmtime,  coshlmtime);
	printf("Sinh VFPU Time = %f Cosh  VFPU Time = %f\n", sinhpgetime, coshpgetime);
	printf("Asin LM   Time = %f Acos  LM   Time = %f\n", asinlmtime,  acoslmtime);
	printf("Asin VFPU Time = %f Acos  VFPU Time = %f\n", asinpgetime, acospgetime);
	printf("Tan  LM   Time = %f Tanh  LM   Time = %f\n", tanlmtime,   tanhlmtime);
	printf("Tan  VFPU Time = %f Tanh  VFPU Time = %f\n", tanpgetime,  tanhpgetime);
	printf("Atan LM   Time = %f Atan2 LM   Time = %f\n", atanlmtime,  atan2lmtime);
	printf("Atan VFPU Time = %f Atan2 VFPU Time = %f\n", atanpgetime, atan2pgetime);
	printf("Pow  LM   Time = %f Exp   LM   Time = %f\n", powlmtime,   explmtime);
	printf("Pow  VFPU Time = %f Exp   VFPU Time = %f\n", powpgetime,  exppgetime);
	printf("Sqrt LM   Time = %f Fmod  LM   Time = %f\n", sqrtlmtime,  fmodlmtime);
	printf("Sqrt VFPU Time = %f Fmod  VFPU Time = %f\n", sqrtpgetime, fmodpgetime);
	printf("ISQR LM   Time = %f ISQR  VFPU Time = %f\n", isqrtlmtime, isqrtpgetime);
 
	pspDebugScreenSetXY(0, 0);
 
	// Print the analog values
	pspDebugScreenPrintf("Sin  LM   Time = %f   Cos   LM   Time = %f\n", sinlmtime,   coslmtime);
	pspDebugScreenPrintf("Sin  VFPU Time = %f   Cos   VFPU Time = %f\n\n", sinpgetime,  cospgetime);
	pspDebugScreenPrintf("Sinh LM   Time = %f   Cosh  LM   Time = %f\n", sinhlmtime,  coshlmtime);
	pspDebugScreenPrintf("Sinh VFPU Time = %f   Cosh  VFPU Time = %f\n\n", sinhpgetime, coshpgetime);
	pspDebugScreenPrintf("Asin LM   Time = %f   Acos  LM   Time = %f\n", asinlmtime,  acoslmtime);
	pspDebugScreenPrintf("Asin VFPU Time = %f   Acos  VFPU Time = %f\n\n", asinpgetime, acospgetime);
	pspDebugScreenPrintf("Tan  LM   Time = %f   Tanh  LM   Time = %f\n", tanlmtime,   tanhlmtime);
	pspDebugScreenPrintf("Tan  VFPU Time = %f   Tanh  VFPU Time = %f\n\n", tanpgetime,  tanhpgetime);
	pspDebugScreenPrintf("Atan LM   Time = %f   Atan2 LM   Time = %f\n", atanlmtime,  atan2lmtime);
	pspDebugScreenPrintf("Atan VFPU Time = %f   Atan2 VFPU Time = %f\n\n", atanpgetime, atan2pgetime);
	pspDebugScreenPrintf("Pow  LM   Time = %f   Exp   LM   Time = %f\n", powlmtime,   explmtime);
	pspDebugScreenPrintf("Pow  VFPU Time = %f   Exp   VFPU Time = %f\n\n", powpgetime,  exppgetime);
	pspDebugScreenPrintf("Sqrt LM   Time = %f   Fmod  LM   Time = %f\n", sqrtlmtime,  fmodlmtime);
	pspDebugScreenPrintf("Sqrt VFPU Time = %f   Fmod  VFPU Time = %f\n", sqrtpgetime, fmodpgetime);

	while(pgeRunning())
	{
		sceDisplayWaitVblankStart();
	}
 
	pgeExit();
 
	return 0;
}
