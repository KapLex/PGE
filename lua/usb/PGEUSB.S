	.set noreorder

#include "pspstub.s"

	STUB_START "PGEUsb",0x00090000,0x00050005
	STUB_FUNC  0x951A1F77,pgeUsbInit
	STUB_FUNC  0x8D4D3E81,pgeUsbShutdown
	STUB_FUNC  0x4BB9AA43,pgeUsbActivate
	STUB_FUNC  0x514985E0,pgeUsbDeactivate
	STUB_FUNC  0x32195EA3,pgeUsbGetState
	STUB_END
