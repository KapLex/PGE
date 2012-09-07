	.set noreorder

#include "pspstub.s"

	STUB_START "PGEFile",0x00090000,0x00040005
	STUB_FUNC  0xA3328395,pgeFileOpenMemory
	STUB_FUNC  0x59206796,pgeFileClose
	STUB_FUNC  0x6BD13ACF,pgeFileSeek
	STUB_FUNC  0x3E648839,pgeFileRead
	STUB_END
