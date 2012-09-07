	.set noreorder

#include "pspstub.s"

	STUB_START "PGEMath",0x00090000,0x00020005
	STUB_FUNC  0x688ECB01,pgeMathAtan
	STUB_FUNC  0x5F4DC593,pgeMathSqrt
	STUB_END
