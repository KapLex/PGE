	.set noreorder

#include "pspstub.s"

	STUB_START "pgesupport",0x40090000,0x00030005
	STUB_FUNC  0x036F996B,pgeSupportLoadStartModule
	STUB_FUNC  0x086C9810,pgeSupportStopUnloadModule
	STUB_FUNC  0x86D4EE5E,pgeSupportExecEboot
	STUB_END
