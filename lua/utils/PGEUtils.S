	.set noreorder

#include "pspstub.s"

	STUB_START "PGEUtils",0x00090000,0x000E0005
	STUB_FUNC  0x5003673F,pgeUtilsNetDialogInit
	STUB_FUNC  0x38E0C632,pgeUtilsNetDialogUpdate
	STUB_FUNC  0x19103BFA,pgeUtilsBrowserInit
	STUB_FUNC  0x58D4AB89,pgeUtilsBrowserUpdate
	STUB_FUNC  0xD79A0BA2,pgeUtilsAdhocDialogInit
	STUB_FUNC  0xD9F1FAA8,pgeUtilsAdhocDialogUpdate
	STUB_FUNC  0xCDA380A2,pgeUtilsMsgDialogInit
	STUB_FUNC  0x8A5A2956,pgeUtilsMsgDialogErrorInit
	STUB_FUNC  0x5F152C9D,pgeUtilsMsgDialogUpdate
	STUB_FUNC  0x1E0FEE13,pgeUtilsMsgDialogAbort
	STUB_FUNC  0x3D9508AD,pgeUtilsOskInit
	STUB_FUNC  0x1BCAF1EB,pgeUtilsOskUpdate
	STUB_FUNC  0x8AE303A5,pgeUtilsSavedataInit
	STUB_FUNC  0xAD736BAB,pgeUtilsSavedataUpdate
	STUB_END
