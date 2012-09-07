	.set noreorder

#include "pspstub.s"

	STUB_START "PGEDir",0x00090000,0x00080005
	STUB_FUNC  0x68BFE5FA,pgeFileExistsDir
	STUB_FUNC  0x6410EE7E,pgeFileMkdir
	STUB_FUNC  0xAC8FF2E9,pgeFileRmdir
	STUB_FUNC  0x6C9308D2,pgeFileChdir
	STUB_FUNC  0x112E6D19,pgeFileGetCwd
	STUB_FUNC  0x7B0EABDE,pgeFileOpenDir
	STUB_FUNC  0x074E03E1,pgeFileCloseDir
	STUB_FUNC  0xE7C7E2FC,pgeFileReadDir
	STUB_END
