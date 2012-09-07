#ifndef __PGEINI_H__
#define __PGEINI_H__

typedef struct
{
	int browserused;

} pgeLuaIniFile;

void pgeLuaIniReadFile(const char *file, pgeLuaIniFile *ini);

#endif 
