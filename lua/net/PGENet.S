	.set noreorder

#include "pspstub.s"

	STUB_START "PGENet",0x00090000,0x00170005
	STUB_FUNC  0x4FD3E69E,pgeNetInit
	STUB_FUNC  0xA26FB2E4,pgeNetShutdown
	STUB_FUNC  0xEC2D2B90,pgeNetGetFile
	STUB_FUNC  0xEAD7F72C,pgeNetPostForm
	STUB_FUNC  0x41B676A5,pgeNetSwitchStatus
	STUB_FUNC  0x860720D8,pgeNetDisconnect
	STUB_FUNC  0x02AE963C,pgeNetIsConnected
	STUB_FUNC  0x8A0C3DFD,pgeNetGetLocalIp
	STUB_FUNC  0x5FC4F0BE,pgeNetResolveHost
	STUB_FUNC  0xEBA90740,pgeNetSocketCreate
	STUB_FUNC  0xACF9FC55,pgeNetSocketAccept
	STUB_FUNC  0x702360E3,pgeNetSocketBind
	STUB_FUNC  0x4735D0F1,pgeNetSocketListen
	STUB_FUNC  0x546F38E8,pgeNetSocketConnect
	STUB_FUNC  0x25AE85E8,pgeNetSocketSend
	STUB_FUNC  0xFABFE9D8,pgeNetSocketReceive
	STUB_FUNC  0x7970DF3F,pgeNetSocketClose
	STUB_FUNC  0xC9E36E25,pgeNetSocketSetClear
	STUB_FUNC  0x9E5BEA61,pgeNetSocketSetAdd
	STUB_FUNC  0xC9E36E25,pgeNetSocketSetClear
	STUB_FUNC  0x4951D220,pgeNetSocketSetRemove
	STUB_FUNC  0xC5727C16,pgeNetSocketSetIsMember
	STUB_FUNC  0x64BA3529,pgeNetSocketSetSelect
	STUB_END
