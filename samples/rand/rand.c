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

#define ITERATIONS 1000000

int main(int argc, char*argv[])
{
	int randint;
	int totalint = 0;
	
	float randfloat;
	float totalfloat = 0.0f;
	
	int i;
	
	for(i = 0; i < ITERATIONS; i++)
	{
		randint = pgeMathRandInt(0, 100);
		//printf("%d\n", randint);
		totalint += randint;
		
		randfloat = pgeMathRandf(100, 100);
		//printf("%g\n", randfloat);
		totalfloat += randfloat;
	}
	
	printf("Average float: %g\n", totalfloat/ITERATIONS);
	
	printf("Average int: %d\n", totalint/ITERATIONS);
	
	pgeExit();
	
	return 0;
}
