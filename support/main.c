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

#include <pspsdk.h>
#include <pspkernel.h>
#include <string.h>
#include <psploadexec_kernel.h>
#include <pspthreadman_kernel.h>

PSP_MODULE_INFO("PGE Support", 0x1000, 1, 1);
PSP_HEAP_SIZE_KB(32);
PSP_NO_CREATE_MAIN_THREAD();

int pgeSupportLoadStartModule(const char *path)
{
    int k1 = pspSdkSetK1(0);
	
	int modid = sceKernelLoadModule(path, 0, NULL);
	
	if(modid < 0)
	{
		pspSdkSetK1(k1);
		
		return modid;
	}
	
	int status;
	
	int result = sceKernelStartModule(modid, 0, NULL, &status, NULL);
	
	if(result < 0)
	{
		pspSdkSetK1(k1);
		
		return result;
	}
	
	pspSdkSetK1(k1);
	
	return modid;
}

int pgeSupportStopUnloadModule(SceUID modid)
{
    int k1 = pspSdkSetK1(0);
	
	int status;
	
	int result = sceKernelStopModule(modid, 0, NULL, &status, NULL);
	
	if(result < 0)
	{
		pspSdkSetK1(k1);
		
		return result;
	}
	
	result = sceKernelUnloadModule(modid);
	
	pspSdkSetK1(k1);
	
	return result;
}

int pgeSupportExecEboot(const char *path)
{
	struct SceKernelLoadExecVSHParam param; 
	char argp[256]; 
	int args; 

	strcpy(argp, path); 
	args = strlen(path)+1; 

	memset(&param, 0, sizeof(param)); 
	param.size = sizeof(param); 
	param.args = args; 
	param.argp = argp; 
	param.key = "game"; 
	param.vshmain_args_size = 0; 
	param.vshmain_args = NULL;
	
	int k1 = pspSdkSetK1(0);
	sceKernelSuspendAllUserThreads(); 
	int ret = sceKernelLoadExecVSHMs2(path, &param);
	pspSdkSetK1(k1);
	
	return ret;
}

int module_start(SceSize args, void *argp)
{
	return 0;
}

int module_stop()
{
	return 0;
}
