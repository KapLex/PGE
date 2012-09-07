	.set noreorder

#include "pspstub.s"

	STUB_START "PGEMath",0x00090000,0x00040005
	STUB_FUNC  0xFF80F637,pgeMathCos
	STUB_FUNC  0xD4992CB2,pgeMathSin
	STUB_FUNC  0x863525F6,pgeMathSincos
	STUB_FUNC  0x3EA6B075,pgeMathAbs
	STUB_END
