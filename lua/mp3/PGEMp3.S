	.set noreorder

#include "pspstub.s"

	STUB_START "PGEMp3",0x00090000,0x00090005
	STUB_FUNC  0x789F2516,pgeMp3Play
	STUB_FUNC  0x3AED7E47,pgeMp3PlayMemory
	STUB_FUNC  0x91F731B2,pgeMp3Stop
	STUB_FUNC  0x0BAEEA09,pgeMp3Pause
	STUB_FUNC  0x74F2C568,pgeMp3Loop
	STUB_FUNC  0xEDCF3CD7,pgeMp3Volume
	STUB_FUNC  0xE96D3262,pgeMp3IsPlaying
	STUB_FUNC  0x23DCE55F,pgeMp3GetAudioData
	STUB_FUNC  0x39DC7702,pgeMp3GetInfo
	STUB_END
