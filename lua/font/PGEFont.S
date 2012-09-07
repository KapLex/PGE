	.set noreorder

#include "pspstub.s"

	STUB_START "PGEFont",0x00090000,0x00090005
	STUB_FUNC  0x4B49C6A3,pgeFontDestroy
	STUB_FUNC  0x362A808B,pgeFontLoad
	STUB_FUNC  0xECE8BE37,pgeFontLoadMemory
	STUB_FUNC  0xE768D82B,pgeFontActivate
	STUB_FUNC  0xDEB86999,pgeFontPrintf
	STUB_FUNC  0xD482219E,pgeFontPrintfCenter
	STUB_FUNC  0x10E68C8D,pgeFontMeasureText
	STUB_FUNC  0x4E0AC6B7,pgeFontGetHeight
	STUB_FUNC  0x67214EE0,pgeFontInit
	STUB_END
