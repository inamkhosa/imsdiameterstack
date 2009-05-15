
#ifndef __HEADER_INITCONFIGDIAMETER_H__
#define __HEADER_INITCONFIGDIAMETER_H__


#include "dmbase_data_types.h"
#include "dmbase_dictionary.h"
#include "dmbase_ampswrappers.h"



#ifdef __cplusplus
    extern "C" {
#endif

#define	DMBASE_DIC_FPTR_TAB_INDX_OCTETSTRING	0
#define	DMBASE_DIC_FPTR_TAB_INDX_INTEGER32		1
#define	DMBASE_DIC_FPTR_TAB_INDX_INTEGER64		2
#define	DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32		3
#define	DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED64		4
#define	DMBASE_DIC_FPTR_TAB_INDX_FLOAT32		5
#define	DMBASE_DIC_FPTR_TAB_INDX_FLOAT64		6
#define	DMBASE_DIC_FPTR_TAB_INDX_IPADDRESS		7
#define	DMBASE_DIC_FPTR_TAB_INDX_TIME			8
#define	DMBASE_DIC_FPTR_TAB_INDX_UTF8STRING		9
#define	DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY		10
#define	DMBASE_DIC_FPTR_TAB_INDX_DMURI			11
#define	DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED		12

t_DiamAPIReturnVal  DMBase_CreateDiameterContext(HDIAMETERSTACKCONTEXT* phDiameterContext_o);
t_DiamAPIReturnVal  DMBase_InitDiameterStack ( HDIAMETERSTACKCONTEXT  hDiameterContext_i, t_DiaStackInitData* poDiaStackInitParams_i);
t_DiamAPIReturnVal  DMBase_SetProductNameInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io , char* pchProdName_i);
t_DiamAPIReturnVal  DMBase_SetHostNameInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io , char* pchHostName_i);
t_DiamAPIReturnVal  DMBase_SetIPAddressInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io , char* pchHostIPAddr_i);
t_DiamAPIReturnVal  DMBase_SetRealmNameInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io , char* pchRealmName_i);
t_DiamAPIReturnVal  DMBase_SetVendorIDInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,unsigned int unVendorID_i);
t_DiamAPIReturnVal  DMBase_SetTcTimerInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,unsigned int unTcTimerVal_i);
t_DiamAPIReturnVal  DMBase_SetFrameworkHandleInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,FRAMEWORK_HANDLE	hFrameWorkHandle);
t_DiamAPIReturnVal  DMBase_AddAppInfoToSupportedAppsList(HDIAMETERSTACKCONTEXT hDiameterContext_io ,t_DiamAppInfo	oSupportedApp_i);
t_DiamAPIReturnVal  DMBase_CleanupDiameterStack ( HDIAMETERSTACKCONTEXT*  phDiameterContext_io);

t_DiamAPIReturnVal  DMBase_GetProductNameFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io , char** ppchProdName_o);
t_DiamAPIReturnVal  DMBase_GetHostNameFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io , char** ppchHostName_o);
t_DiamAPIReturnVal  DMBase_GetIPAddressFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io , char** ppchHostIPAddr_o);
t_DiamAPIReturnVal  DMBase_GetRealmNameFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io , char** ppchRealmName_o);
t_DiamAPIReturnVal  DMBase_GetVendorIDFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,unsigned int * punVendorID_o);
t_DiamAPIReturnVal  DMBase_GetTcTimerFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,unsigned int* punTcTimerVal_o);
t_DiamAPIReturnVal  DMBase_GetFrameworkHandleFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,FRAMEWORK_HANDLE*	phFrameWorkHandle_o);
t_DiamAPIReturnVal  DMBase_GetDictionaryObjectFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,t_DiamDictionary* poDiamDictionary_o);
t_DiamAPIReturnVal  DMBase_SetDictionaryObjectInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,t_DiamDictionary oDiamDictionary_i);

t_DiamAPIReturnVal  DMBase_InitialiseFunctionPointerMappingForDictionary(
								HDIAMETERSTACKCONTEXT hDiameterContext_io );

#ifdef __cplusplus
   }
#endif

#endif /* __HEADER_InitConfigDiameter_H__ */
  
