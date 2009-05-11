

#ifndef DMBASE_PEER_MGMT_H
#define DMBASE_PEER_MGMT_H


#include "dmbase_data_types.h"
#include "dmbase_message.h"
#include "dmbase_transport_mgmt.h"

#ifdef __cplusplus
    extern "C" {
#endif


t_DiamAPIReturnVal DMBase_CreatePeerTable ( HDIAMETERSTACKCONTEXT  hDiamStackContext_io );

t_DiamAPIReturnVal DMBase_CreatePeerTableObject( HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
                                                 t_PeerTable**          ppoPeerTableObject_io);

t_DiamAPIReturnVal DMBase_PopulatePeerTable ( 	HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
												DMBase_SList*           poPeerList_i);

t_DiamAPIReturnVal DMBase_InsertPeerTableEntry(	HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
												HPEERTABLEENTRY			hPeerTableEntry_i);

t_DiamAPIReturnVal DMBase_LookUpPeerTableEntry(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												t_DiamOctetString 		oPeerIdentity_i,
												HPEERTABLEENTRY* 		phPeerTableEntry_o);

t_DiamAPIReturnVal DMBase_RemovePeerTableEntry(HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
												t_DiamOctetString*		poPeerIdentity_i);

t_DiamAPIReturnVal DMBase_ShowPeerTable(HDIAMETERSTACKCONTEXT	hDiamStackContext_io);

void DMBase_ShowPeerTableEntryCallback(	AMPS_HANDLE 			r_hAMPS_HANDLE,
										AMPS_APP_HANDLE 		r_hAMPS_APP_HANDLE,
										AMPS_APP_DATA_HANDLE 	r_hAMPS_APP_DATA_HANDLE);

t_DiamAPIReturnVal DMBase_CreatePeerTableEntry(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY*		phPeerTableEntry_io,
												t_DiamOctetString	   	oHostIdentity_i,
												t_DiamOctetString	   	oIPAddress_i,
												unsigned int          	unPort_i,
												t_PeerRole            	oConfiguredRole_i,
												_Bool                 	bIsStatic_i,
												_Bool                 	bIsTLSEnable_i,
												_Bool        			bIsWatchgogSupported_i,
												unsigned int			unWatchdogTimerDelay_i);

t_DiamAPIReturnVal DMBase_SetHostIdentityInPeerTableEntry ( HDIAMETERSTACKCONTEXT   hDiamStackContext_io,
                                                            HPEERTABLEENTRY         hPeerEntry_o,
                                                            t_DiamOctetString       oHostIdentity_i);

t_DiamAPIReturnVal DMBase_SetStateInPeerTableEntry ( HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
                                                     HPEERTABLEENTRY        hPeerEntry_o,
                                                     t_PeerState 			oPeerState_i);

t_DiamAPIReturnVal DMBase_SetPeerRoleInPeerTableEntry ( HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
                                                        HPEERTABLEENTRY     	hPeerEntry_o,
                                                        t_PeerRole 				oPeerRole_i);

t_DiamAPIReturnVal DMBase_SetStaticStatusInPeerTableEntry ( HDIAMETERSTACKCONTEXT   hDiamStackContext_io,
                                                            HPEERTABLEENTRY         hPeerEntry_o,
                                                            _Bool                   bIsStatic_i);

t_DiamAPIReturnVal DMBase_SetExpiryTimeInPeerTableEntry( HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
                                                         HPEERTABLEENTRY        hPeerEntry_o,
                                                         t_DiamTime             ExpiryTime_i );

t_DiamAPIReturnVal DMBase_SetTLSEnableStatusInPeerTableEntry( HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
                                                              HPEERTABLEENTRY 		hPeerEntry_o,
                                                              _Bool 				bIsTLSEnabled_i );

t_DiamAPIReturnVal DMBase_SetOptionalTLSDataInPeerTableEntry( HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                              HPEERTABLEENTRY       hPeerEntry_o,
                                                              t_TLSData             OptTLSData_i);

t_DiamAPIReturnVal DMBase_SetPeerConfiguredTransportObject(	HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
                                                            HPEERTABLEENTRY         hPeerEntry_o,
                                                            HTRANSPORTOBJECT		hTransportObj_i );

t_DiamAPIReturnVal DMBase_SetPeerInitiatorTransportObject( 	HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
															HPEERTABLEENTRY         hPeerEntry_o,
                                                            HTRANSPORTOBJECT		hTransportObj_i );

t_DiamAPIReturnVal DMBase_SetPeerResponderTransportObject( 	HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
															HPEERTABLEENTRY         hPeerEntry_o,
                                                            HTRANSPORTOBJECT		hTransportObj_i );

t_DiamAPIReturnVal DMBase_AddPeerSupportedApp(  HDIAMETERSTACKCONTEXT   hDiamStackContext_io,
												HPEERTABLEENTRY         hPeerEntry_o,
                                                t_DiamAppInfo			oSupportedApp_i);

t_DiamAPIReturnVal DMBase_ConnectToPeer(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
										HPEERTABLEENTRY 		hPeerTableEntry_io);

t_DiamAPIReturnVal DMBase_ConnectToPeerByName(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												t_DiamOctetString 		oPeerIdentity_i);

t_DiamAPIReturnVal DMBase_SendMessageToPeer(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeerTableEntry_io,
											HDIAMETERMESSAGE 		hDiamMsg_i);



#ifdef __cplusplus
   }
#endif

#endif /* DMBASE_PEER_MGMT_H */
