	.set noreorder

#include "pspstub.s"

	STUB_START "PGEAdhoc",0x00090000,0x00130005
	STUB_FUNC  0xA83E2A1B,pgeAdhocInit
	STUB_FUNC  0x981CAA2E,pgeAdhocShutdown
	STUB_FUNC  0x5B317D10,pgeAdhocConnect
	STUB_FUNC  0x548F180F,pgeAdhocGetState
	STUB_FUNC  0x1E3EAD20,pgeAdhocGetError
	STUB_FUNC  0x363ACD88,pgeAdhocPeerExists
	STUB_FUNC  0x98E74C20,pgeAdhocMatchingInit
	STUB_FUNC  0x918C8220,pgeAdhocMatchingStart
	STUB_FUNC  0x95CC0927,pgeAdhocMatchingAccept
	STUB_FUNC  0xCA590452,pgeAdhocMatchingDecline
	STUB_FUNC  0x37567B45,pgeAdhocMatchingShutdown
	STUB_FUNC  0xCA7AF8DD,pgeAdhocMatchingGetEvents
	STUB_FUNC  0xDE6CDFCB,pgeAdhocPtpHostStart
	STUB_FUNC  0xAB1A08E7,pgeAdhocPtpClientStart
	STUB_FUNC  0x797EF390,pgeAdhocPtpSend
	STUB_FUNC  0x21FA2152,pgeAdhocPtpReceive
	STUB_FUNC  0x93733AC1,pgeAdhocPtpFlush
	STUB_FUNC  0xA4E76DFB,pgeAdhocPtpHostShutdown
	STUB_FUNC  0xAAE1CC48,pgeAdhocPtpClientShutdown
	STUB_END
