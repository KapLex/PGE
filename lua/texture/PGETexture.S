	.set noreorder

#include "pspstub.s"

	STUB_START "PGETexture",0x00090000,0x00100005
	STUB_FUNC  0x24BBA381,pgeTextureDestroy
	STUB_FUNC  0x5CFFB1E7,pgeTextureLoad
	STUB_FUNC  0xEF4B2B10,pgeTextureLoadMemory
	STUB_FUNC  0xC3C1450C,pgeTextureCreate
	STUB_FUNC  0x4C7E96E3,pgeTextureActivate
	STUB_FUNC  0x08FD3AE7,pgeGfxDrawTexture
	STUB_FUNC  0x87E9FC54,pgeGfxDrawTextureEasy
	STUB_FUNC  0x61E99455,pgeGfxRenderToTexture
	STUB_FUNC  0x149441F6,pgeTextureSave
	STUB_FUNC  0x7B80DD8E,pgeTextureModeSet
	STUB_FUNC  0x27B22A3B,pgeTextureToRam
	STUB_FUNC  0x5FCE5E4E,pgeTextureToVram
	STUB_FUNC  0xA1D38123,pgeTextureSwizzle
	STUB_FUNC  0xF3E95279,pgeTextureUnswizzle
	STUB_FUNC  0x88A9BEA6,pgeTextureSetPixel
	STUB_FUNC  0x43B6F037,pgeTextureGetPixel
	STUB_END
