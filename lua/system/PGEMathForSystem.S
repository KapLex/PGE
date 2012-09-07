	.set noreorder

#include "pspstub.s"

	STUB_START "PGEMath",0x00090000,0x00010005
	STUB_FUNC  0x1BA84FF6,pgeMathFloor
	STUB_END
