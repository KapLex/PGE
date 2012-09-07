	.set noreorder

#include "pspstub.s"

	STUB_START "PGESystem",0x00090000,0x00010005
	STUB_FUNC  0xD222C7BB,pgeSystemGetPsid
	STUB_END
