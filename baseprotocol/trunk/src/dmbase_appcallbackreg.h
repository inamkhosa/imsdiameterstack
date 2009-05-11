
#ifndef DMBASE_APPCALLBACKREG_H
#define	DMBASE_APPCALLBACKREG_H

#include "dmbase_utility.h"
#include "dmbase_ampswrappers.h"
#include "dmbase_data_types.h"
#include "dmbase_message.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct __PeerCloseEventAppData
{
	HDIAMETERSTACKCONTEXT hDiamStackContext;
	HPEERTABLEENTRY 	  hPeer;
}t_PeerCloseEventAppData;

typedef t_DiamAPIReturnVal (*t_DiamAppMsgProcessorCallback)(HPEERTABLEENTRY		hPeer_i,
															HDIAMETERMESSAGE 	hDiamMsg_i,
															void* 				pvAppContext_i);

typedef void (*t_DiamPeerCloseEventCallback)(void*	pvAppContext_i, HPEERTABLEENTRY hPeer_i);

typedef struct __DiamAppMsgProcessorCallBackData
{
	t_DiamAppMsgProcessorCallback 	fpAppMsgProcessor;
	t_DiamPeerCloseEventCallback	fpPeerCloseEventCallback;
	void* 							pvAppContext;

}t_DiamAppMsgProcessorCallBackData;



t_DiamAPIReturnVal DMBase_RegisterApplicationCallback(	HDIAMETERSTACKCONTEXT 			hDiamStackContext_io,
														unsigned int 					unAppId_i,
														t_DiamAppMsgProcessorCallback 	fpAppMsgProcessor_i,
														t_DiamPeerCloseEventCallback	fpPeerCloseEventCallback_i,
														void* 							pvAppContext_i);

t_DiamAPIReturnVal DMBase_UnregisterApplicationCallback(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
														unsigned int 			unAppId_i);

t_DiamAPIReturnVal DMBase_ExecLocalProcessingCallback(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												unsigned int 			unAppId_i,
												HPEERTABLEENTRY 		hPeer_i,
												HDIAMETERMESSAGE 		hDiamMsg_i);

void DMBase_ExecuteAppPeerConnCloseCallback(HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
											HPEERTABLEENTRY			hPeerTableEntry_i);

void 	DMBase_PeerConnCloseCallback(	AMPS_HANDLE 			r_hAMPS_HANDLE,
										AMPS_APP_HANDLE 		r_hAMPS_APP_HANDLE,
										AMPS_APP_DATA_HANDLE 	r_hAMPS_APP_DATA_HANDLE);


#ifdef __cplusplus
}
#endif

#endif	/* __DIAMAPPCALLBACKREG_H__ */

