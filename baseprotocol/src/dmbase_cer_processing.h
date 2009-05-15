
#ifndef	DMBASE_CER_H
#define DMBASE_CER_H

#include "dmbase_data_types.h"

#define DMBASE_MAX_HOST_IP				 				 16
#define DMBASE_MAX_SUPPORTED_VENDOR_ID	 				 16

#define DMBASE_SMALL_STING				 				 32
#define DMBASE_STANDARD_STING			 				 64
#define DMBASE_LARGE_STING								128

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct __DiamCER
{
	unsigned char 	ucOriginHost[DMBASE_LARGE_STING];
	unsigned char 	ucOriginRealm[DMBASE_LARGE_STING];
	unsigned char 	oHostIP[DMBASE_MAX_HOST_IP][DMBASE_LARGE_STING];
	unsigned int	unHostIPCount;
	unsigned int 	unVendorId;
	unsigned char 	ucProductName[DMBASE_LARGE_STING];
	unsigned int	unOriginStateId;
	unsigned int 	oSupportedVendorId[DMBASE_MAX_SUPPORTED_VENDOR_ID];
	unsigned int	unSupportedVendorIdCount;
	t_DiamAppInfo	oSupportedApplications[DMBASE_MAX_PEER_SUPPORTED_APP];
	unsigned int 	unSupportedAppCount;


}t_DiamCER;

typedef struct __DiamCEA
{
	unsigned char 	ucOriginHost[DMBASE_LARGE_STING];
	unsigned char 	ucOriginRealm[DMBASE_LARGE_STING];
	unsigned char 	oHostIP[DMBASE_MAX_HOST_IP][DMBASE_LARGE_STING];
	unsigned int	unHostIPCount;
	unsigned int 	unVendorId;
	unsigned char 	ucProductName[DMBASE_LARGE_STING];
	unsigned int	unOriginStateId;
	unsigned int 	oSupportedVendorId[DMBASE_MAX_SUPPORTED_VENDOR_ID];
	unsigned int	unSupportedVendorIdCount;
	t_DiamAppInfo	oSupportedApplications[DMBASE_MAX_PEER_SUPPORTED_APP];
	unsigned int 	unSupportedAppCount;


}t_DiamCEA;

typedef struct __DiamCER_AVPs
{
	HAVP			hOriginHost;
	HAVP			hOriginRealm;
	HAVP			hHostIP;
	HAVP			hVendorID;
	HAVP			hProductName;
	HAVP 			oSupportedApplications[DMBASE_MAX_PEER_SUPPORTED_APP];
	unsigned int 	unSupportedAppCount;
}t_DiamCER_AVPs;

typedef struct __DiamCEA_AVPs
{
	HAVP 			hResultCode;
	HAVP			hOriginHost;
	HAVP			hOriginRealm;
	HAVP			hHostIP;
	HAVP			hVendorID;
	HAVP			hProductName;
	HAVP 			oSupportedApplications[DMBASE_MAX_PEER_SUPPORTED_APP];
	unsigned int 	unSupportedAppCount;
}t_DiamCEA_AVPs;

t_DiamAPIReturnVal DMBase_GetVendorAppInfo(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HAVP					hVendorAppAVP_i,
											t_DiamAppInfo			*poAppInfo_i);

t_DiamAPIReturnVal DMBase_AddDiamAppToCER  (	t_DiamCER* 		poDiamCER_io,
												unsigned int 	unAppId_i,
												unsigned int 	unVendorId_i,
												t_DiamAppType 	oAppType_i);

t_DiamAPIReturnVal DMBase_AddDiamAppToCEA  (	t_DiamCEA* 		poDiamCEA_io,
												unsigned int 	unAppId_i,
												unsigned int 	unVendorId_i,
												t_DiamAppType 	oAppType_i);

t_DiamAPIReturnVal DMBase_ExtractCER(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
										HDIAMETERMESSAGE 		hDiamMsg_i,
										t_DiamCER* 				poDiamCER_io);

t_DiamAPIReturnVal DMBase_ExtractCEA(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
										HDIAMETERMESSAGE 		hDiamMsg_i,
										t_DiamCEA* 				poDiamCEA_io);

t_DiamAPIReturnVal DMBase_CheckAppSupport(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
										 t_DiamAppInfo* 		poAppInfo_i,
										 _Bool* 				pbIsSupported_o);

t_DiamAPIReturnVal DMBase_CreateAppAVP(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
										HAVP*					phAppAVP,
										t_DiamAppInfo*			poAppInfo,
										HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal DMBase_Create_CER_AVPs(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											t_DiamCER_AVPs*			poCER_AVPs_io,
											HMSGALLOCATIONCONTEXT   hMsgAllocCtxt_io);

t_DiamAPIReturnVal DMBase_Create_CEA_AVPs(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											t_DiamCEA_AVPs*			poCEA_AVPs_io,
											HMSGALLOCATIONCONTEXT   hMsgAllocCtxt_io);

t_DiamAPIReturnVal DMBase_CreateCER(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
									HDIAMETERMESSAGE*		phCER_i,
									unsigned int 			unHopByHopID_i,
									unsigned int 			unEndToEndID_i);

t_DiamAPIReturnVal DMBase_CreateCEA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
									HDIAMETERMESSAGE*		phCEA_i,
									unsigned int 			unHopByHopID_i,
									unsigned int 			unEndToEndID_i);


#ifdef	__cplusplus
}
#endif

#endif //DMBASE_CER_H

