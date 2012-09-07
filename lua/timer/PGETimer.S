	.set noreorder

#include "pspstub.s"

	STUB_START "PGETimer",0x00090000,0x00080005
	STUB_FUNC  0x2921E6EC,pgeTimerCreate
	STUB_FUNC  0x4333CBC2,pgeTimerUpdate
	STUB_FUNC  0x9C8A6CC9,pgeTimerGetDeltaTime
	STUB_FUNC  0x023712EA,pgeTimerPeekDeltaTime
	STUB_FUNC  0x189A6EB4,pgeTimerGetTotalTime
	STUB_FUNC  0xEF08BA43,pgeTimerPause
	STUB_FUNC  0xA9FC531F,pgeTimerUnpause
	STUB_FUNC  0x6D4FB674,pgeTimerDestroy
	STUB_END
