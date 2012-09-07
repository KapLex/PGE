	.set noreorder

#include "pspstub.s"

	STUB_START "PGEZip",0x00090000,0x00040005
	STUB_FUNC  0xC2B3EDEE,pgeZipOpen
	STUB_FUNC  0x151B6485,pgeZipClose
	STUB_FUNC  0x8F05AADE,pgeZipFileRead
	STUB_FUNC  0x48201BED,pgeZipExtract
	STUB_END
