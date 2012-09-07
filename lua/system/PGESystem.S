	.set noreorder

#include "pspstub.s"

	STUB_START "PGESystem",0x00090000,0x000D0005
	STUB_FUNC  0xD8B57268,pgeSystemGetNickname
	STUB_FUNC  0xD222C7BB,pgeSystemGetPsid
	STUB_FUNC  0xE92053BE,pgeSystemGetLanguage
	STUB_FUNC  0x006D1DEC,pgeSystemGetMac
	STUB_FUNC  0x70D8B5E0,pgeSystemMsSize
	STUB_FUNC  0xD2723900,pgeSystemMsFreeSize
	STUB_FUNC  0x54480EE8,pgeSystemGetFreeRam
	STUB_FUNC  0xA1631416,pgeSystemSetCpu
	STUB_FUNC  0xBB26AF3A,pgeSystemGetBatteryPercent
	STUB_FUNC  0xBB1EA74C,pgeSystemGetBatteryTime
	STUB_FUNC  0xB23FCEF9,pgeSystemGetBatteryCharging
	STUB_FUNC  0x47251610,pgeSystemGetBatteryExists
	STUB_FUNC  0x669D4C5E,pgeSystemGetBatteryIsLow
	STUB_END
