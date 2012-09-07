	.set noreorder

#include "pspstub.s"

	STUB_START "PGEControls",0x00090000,0x000D0005
	STUB_FUNC  0xFBA4DE02,pgeControlsUpdate
	STUB_FUNC  0x83F05437,pgeControlsEnable
	STUB_FUNC  0x7830E53E,pgeControlsDisable
	STUB_FUNC  0x750C1538,pgeControlsPressedAny
	STUB_FUNC  0xAE5A9CF4,pgeControlsHeldAny
	STUB_FUNC  0xB78506C3,pgeControlsReleasedAny
	STUB_FUNC  0xCC66BEE8,pgeControlsPressed
	STUB_FUNC  0xD097D3C9,pgeControlsHeld
	STUB_FUNC  0xB61A6261,pgeControlsReleased
	STUB_FUNC  0xF74BDDD4,pgeControlsAnalogX
	STUB_FUNC  0xF2DF419A,pgeControlsAnalogY
	STUB_FUNC  0x03BE0C41,pgeControlsAnalogAngle
	STUB_FUNC  0xDF6982F2,pgeControlsAnalogMag
	STUB_END
