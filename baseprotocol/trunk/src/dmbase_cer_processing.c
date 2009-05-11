

#include "dmbase_cer_processing.h"
#include "dmbase_data_types.h"
#include "dmbase_peerstatemachine.h"
#include "dmbase_parser.h"
#include "dmbase_msgvalidate.h"
#include "dmbase_dictionary.h"
#include "dmbase_realmtablemgmt.h"
#include "dmbase_appcallbackreg.h"
#include "dmbase_failover_failback.h"
#include "dmbase_avp.h"
#include "dmbase_psm_actions.h"

extern int g_nDiamBaseTraceID;

t_DiamAPIReturnVal DMBase_GetVendorAppInfo(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HAVP					hVendorAppAVP_i,
											t_DiamAppInfo			*poAppInfo_i)
{
	if(NULL == hDiamStackContext_io || NULL == hVendorAppAVP_i || NULL == poAppInfo_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
		return DMBase_Retval_Null_Pointer;
	}

	HAVPCOLLECTION hAVPCollection = hVendorAppAVP_i->hCollectionOfAVPs;
	HAVP	hAVP;

	DMBase_MemsetZero(poAppInfo_i, sizeof(t_DiamAppInfo));

    while(NULL != hAVPCollection)
    {
    	hAVP = NULL;
    	DMBase_SListGetNodeData(hDiamStackContext_io, hAVPCollection, (void**)&hAVP);
    	switch(hAVP->oAVPHeaderInst.unAVPCode)
    	{
			case DMBASE_AVP_ACCT_APPLICATION_ID:
				poAppInfo_i->unAppID = *((t_DiamUnsigned32*)hAVP->pData)->punUnsigned32;
				poAppInfo_i->oAppType = Accounting_Application;
				break;
			case DMBASE_AVP_AUTH_APPLICATION_ID:
				poAppInfo_i->unAppID = *((t_DiamUnsigned32*)hAVP->pData)->punUnsigned32;
				poAppInfo_i->oAppType = Authorization_Application;
				break;
			case DMBASE_AVP_VENDOR_ID:
				poAppInfo_i->unVendorID = *((t_DiamUnsigned32*)hAVP->pData)->punUnsigned32;
				break;
    	}
    	DMBase_SListGetNextNode(hDiamStackContext_io, hAVPCollection, &hAVPCollection);
    }
}

t_DiamAPIReturnVal DMBase_AddDiamAppToCER  (	t_DiamCER* 		poDiamCER_io,
												unsigned int 	unAppId_i,
												unsigned int 	unVendorId_i,
												t_DiamAppType 	oAppType_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == poDiamCER_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
		return DMBase_Retval_Null_Pointer;
	}

	if(DMBASE_MAX_PEER_SUPPORTED_APP <= poDiamCER_io->unSupportedAppCount)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Maximum Supported Application count exceed.\n");
		return DMBase_Retval_Limit_Exceed;
	}

	poDiamCER_io->oSupportedApplications[poDiamCER_io->unSupportedAppCount].unAppID = unAppId_i;
	poDiamCER_io->oSupportedApplications[poDiamCER_io->unSupportedAppCount].unVendorID = unVendorId_i;
	poDiamCER_io->oSupportedApplications[poDiamCER_io->unSupportedAppCount].oAppType = oAppType_i;
	poDiamCER_io->unSupportedAppCount++;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_AddDiamAppToCEA  (	t_DiamCEA* 		poDiamCEA_io,
												unsigned int 	unAppId_i,
												unsigned int 	unVendorId_i,
												t_DiamAppType 	oAppType_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == poDiamCEA_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
		return DMBase_Retval_Null_Pointer;
	}

	if(DMBASE_MAX_PEER_SUPPORTED_APP <= poDiamCEA_io->unSupportedAppCount)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Maximum Supported Application count exceed.\n");
		return DMBase_Retval_Limit_Exceed;
	}

	poDiamCEA_io->oSupportedApplications[poDiamCEA_io->unSupportedAppCount].unAppID = unAppId_i;
	poDiamCEA_io->oSupportedApplications[poDiamCEA_io->unSupportedAppCount].unVendorID = unVendorId_i;
	poDiamCEA_io->oSupportedApplications[poDiamCEA_io->unSupportedAppCount].oAppType = oAppType_i;
	poDiamCEA_io->unSupportedAppCount++;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_ExtractCER(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
										HDIAMETERMESSAGE 		hDiamMsg_i,
										t_DiamCER* 				poDiamCER_io)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == hDiamStackContext_io || NULL == hDiamMsg_i || NULL == poDiamCER_io )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
		return DMBase_Retval_Null_Pointer;
	}

    HAVPCOLLECTION hAVPCollection = hDiamMsg_i->hCollectionOfAVPs;
    HAVP	hAVP;
    t_DiamAppInfo oDiamAppInfo;
    t_DiamAPIReturnVal oReturnValue = DMBase_Retval_Success;

    while(NULL != hAVPCollection)
    {
    	hAVP = NULL;
    	DMBase_SListGetNodeData(hDiamStackContext_io, hAVPCollection, (void**)&hAVP);
    	switch(hAVP->oAVPHeaderInst.unAVPCode)
    	{
			case DMBASE_AVP_ACCT_APPLICATION_ID:
				if(DMBase_Retval_Success != (oReturnValue = DMBase_AddDiamAppToCER(poDiamCER_io,
															*((t_DiamUnsigned32*)hAVP->pData)->punUnsigned32,
															0,
															Accounting_Application)))
				{
					DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to add application info.\n");
					goto ExitMe;
				}
				break;
			case DMBASE_AVP_AUTH_APPLICATION_ID:
				if(DMBase_Retval_Success != (oReturnValue = DMBase_AddDiamAppToCER(poDiamCER_io,
																*((t_DiamUnsigned32*)hAVP->pData)->punUnsigned32,
																0,
																Authorization_Application)))
				{
					DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to add application info.\n");
					goto ExitMe;
				}
				break;
			case DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID:
				if(DMBase_Retval_Success != (oReturnValue = DMBase_GetVendorAppInfo(hDiamStackContext_io, hAVP, &oDiamAppInfo)))
				{
					DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to get application info.\n");
					goto ExitMe;
				}
				if(DMBase_Retval_Success != (oReturnValue = DMBase_AddDiamAppToCER(poDiamCER_io,
																			oDiamAppInfo.unAppID,
																			oDiamAppInfo.unVendorID,
																			oDiamAppInfo.oAppType)))
				{
					DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to add application info.\n");
					goto ExitMe;
				}
				break;
    	}
    	DMBase_SListGetNextNode(hDiamStackContext_io, hAVPCollection, &hAVPCollection);
    }

    ExitMe:

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnValue;

}

t_DiamAPIReturnVal DMBase_ExtractCEA(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
										HDIAMETERMESSAGE 		hDiamMsg_i,
										t_DiamCEA* 				poDiamCEA_io)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == hDiamStackContext_io || NULL == hDiamMsg_i || NULL == poDiamCEA_io )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
		return DMBase_Retval_Null_Pointer;
	}

    HAVPCOLLECTION hAVPCollection = hDiamMsg_i->hCollectionOfAVPs;
    HAVP	hAVP;
    t_DiamAppInfo oDiamAppInfo;
    t_DiamAPIReturnVal oReturnValue = DMBase_Retval_Success;

    while(NULL != hAVPCollection)
    {
    	hAVP = NULL;
    	DMBase_SListGetNodeData(hDiamStackContext_io, hAVPCollection, (void**)&hAVP);
    	switch(hAVP->oAVPHeaderInst.unAVPCode)
    	{
			case DMBASE_AVP_ACCT_APPLICATION_ID:
				if(DMBase_Retval_Success != (oReturnValue = DMBase_AddDiamAppToCEA(poDiamCEA_io,
															*((t_DiamUnsigned32*)hAVP->pData)->punUnsigned32,
															0,
															Authorization_Application)))
				{
					DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to add application info.\n");
					goto ExitMe;
				}
				break;
			case DMBASE_AVP_AUTH_APPLICATION_ID:
				if(DMBase_Retval_Success != (oReturnValue = DMBase_AddDiamAppToCEA(poDiamCEA_io,
																*((t_DiamUnsigned32*)hAVP->pData)->punUnsigned32,
																0,
																Accounting_Application)))
				{
					DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to add application info.\n");
					goto ExitMe;
				}
				break;
			case DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID:
				if(DMBase_Retval_Success != (oReturnValue = DMBase_GetVendorAppInfo(hDiamStackContext_io, hAVP, &oDiamAppInfo)))
				{
					DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to get application info.\n");
					goto ExitMe;
				}
				if(DMBase_Retval_Success != (oReturnValue = DMBase_AddDiamAppToCEA(poDiamCEA_io,
																			oDiamAppInfo.unAppID,
																			oDiamAppInfo.unVendorID,
																			oDiamAppInfo.oAppType)))
				{
					DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to add application info.\n");
					goto ExitMe;
				}
				break;
    	}
    	DMBase_SListGetNextNode(hDiamStackContext_io, hAVPCollection, &hAVPCollection);
    }

    ExitMe:

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnValue;
}

t_DiamAPIReturnVal DMBase_CheckAppSupport(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
										 t_DiamAppInfo* 		poAppInfo_i,
										 _Bool* 				pbIsSupported_o)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     unsigned int unIndex;
     for(unIndex = 0; unIndex < hDiamStackContext_io->unSupportedAppCount; unIndex++)
     {
         if(hDiamStackContext_io->SupportedAppList[unIndex].unAppID == poAppInfo_i->unAppID &&
            hDiamStackContext_io->SupportedAppList[unIndex].oAppType == poAppInfo_i->oAppType &&
            hDiamStackContext_io->SupportedAppList[unIndex].unVendorID == poAppInfo_i->unVendorID)
         {
            *pbIsSupported_o = TRUE;
            break;
         }
     }
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_AddCommonAppInfoToPeerEntry(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
														HPEERTABLEENTRY 		hPeer_i,
														t_DiamCER* 				poCER)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	unsigned int unIndex = 0;
	_Bool bIsSupported = FALSE;

	for(; unIndex<poCER->unSupportedAppCount; unIndex++)
	{
		bIsSupported = FALSE;
		DMBase_CheckAppSupport(hDiamStackContext_io, &poCER->oSupportedApplications[unIndex] ,&bIsSupported);
		if(bIsSupported)
		{
			DMBase_AddPeerSupportedApp(	hDiamStackContext_io, hPeer_i, poCER->oSupportedApplications[unIndex]);
		}
	}

	if(0 == hPeer_i->unSupportedAppCount)
	{
	    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	    return DMBase_Retval_No_Commom_Application;
	}

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_CreateAppAVP(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
										HAVP*					phAppAVP,
										t_DiamAppInfo*			poAppInfo,
										HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	t_DiamAPIReturnVal oReturnValue;
	HAVP hVendorAppAVP = NULL;
	HAVP hVendorId	   = NULL;

	if(0 == poAppInfo->unVendorID)
	{
		unsigned int unAppAVPCode = (poAppInfo->oAppType == Accounting_Application ? DMBASE_AVP_ACCT_APPLICATION_ID:DMBASE_AVP_AUTH_APPLICATION_ID);
		if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateUnsigned32AVP( hDiamStackContext_io,
																				unAppAVPCode,
																				phAppAVP,
																			 	poAppInfo->unAppID,
																			 	hMsgAllocCtxt_io)))
		{
		 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Application AVP.\n");
		 goto ExitMe;
		}
	    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	    return DMBase_Retval_Success;
	}
	else
	{


		unsigned int unAppAVPCode = (poAppInfo->oAppType == Accounting_Application ? DMBASE_AVP_ACCT_APPLICATION_ID:DMBASE_AVP_AUTH_APPLICATION_ID);
		if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateUnsigned32AVP( hDiamStackContext_io,
																				unAppAVPCode,
																				&hVendorAppAVP,
																			 	poAppInfo->unAppID,
																			 	hMsgAllocCtxt_io)))
		{
		 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Application AVP.\n");
		 goto ExitMe;
		}

		if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateUnsigned32AVP( hDiamStackContext_io,
																				DMBASE_AVP_VENDOR_ID,
																				&hVendorId,
																			 	poAppInfo->unVendorID,
																			 	hMsgAllocCtxt_io)))
		{
		 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Vendor-Id AVP.\n");
		 goto ExitMe;
		}

		if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateGroupedAVP(hDiamStackContext_io,
																			phAppAVP,
																			hMsgAllocCtxt_io,
																			DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID,
																			0)))
		{
		 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Vendor-Specific-Application-ID AVP.\n");
		 goto ExitMe;
		}

		if(DMBase_Retval_Success != (oReturnValue = DMBase_AddAVPToGroup(hDiamStackContext_io, *phAppAVP, hVendorAppAVP)))
		{
		 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to add Vendor-Specific-Application-ID AVP.\n");
		 goto ExitMe;
		}
		if(DMBase_Retval_Success != (oReturnValue = DMBase_AddAVPToGroup(hDiamStackContext_io, *phAppAVP, hVendorId)))
		{
		 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to add Vendor-ID AVP.\n");
		 goto ExitMe;
		}

	    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	    return DMBase_Retval_Success;

	}

	ExitMe:
	DMBase_DestroyAVP(hDiamStackContext_io, &hVendorAppAVP);
	DMBase_DestroyAVP(hDiamStackContext_io, &hVendorId);
	DMBase_DestroyAVP(hDiamStackContext_io, phAppAVP);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnValue;
}



t_DiamAPIReturnVal DMBase_Create_CER_AVPs(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											t_DiamCER_AVPs*			poCER_AVPs_io,
											HMSGALLOCATIONCONTEXT   hMsgAllocCtxt_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    t_DiamAPIReturnVal oReturnValue;

    unsigned char *pucIPAddress = NULL;

    if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateOctetStringAVP(hDiamStackContext_io,
																			 DMBASE_AVP_ORIGIN_HOST,
																			 &poCER_AVPs_io->hOriginHost,
																			 hDiamStackContext_io->oHostName.pucOctetString,
																			 hDiamStackContext_io->oHostName.unNumOfOctets,
																			 hMsgAllocCtxt_io)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Origin-Host AVP.\n");
    	goto ExitMe;
    }

    if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateOctetStringAVP(hDiamStackContext_io,
																			 DMBASE_AVP_ORIGIN_REALM,
																			 &poCER_AVPs_io->hOriginRealm,
																			 hDiamStackContext_io->oRealmName.pucOctetString,
																			 hDiamStackContext_io->oRealmName.unNumOfOctets,
																			 hMsgAllocCtxt_io)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Origin-Realm AVP.\n");
    	goto ExitMe;
    }


    DMBase_GetIPAddressFromDiameterContext(hDiamStackContext_io, &pucIPAddress);

    if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateIPAddressAVP(hDiamStackContext_io,
																			 DMBASE_AVP_HOST_IP_ADDRESS,
																			 &poCER_AVPs_io->hHostIP,
																			 pucIPAddress,
																			 DMBASE_IANA_ADDR_FAMILY_IP_V4,
																			 hMsgAllocCtxt_io)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Host-IP-Address AVP.\n");
    	goto ExitMe;
    }

    //DMBase_Free(hDiamStackContext_io, (void**)&pucIPAddress);
    unsigned int unVendorID = 0;
    DMBase_GetVendorIDFromDiameterContext(hDiamStackContext_io, &unVendorID);

    if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateUnsigned32AVP( hDiamStackContext_io,
																			 DMBASE_AVP_VENDOR_ID,
																			 &poCER_AVPs_io->hVendorID,
																			 unVendorID,
																			 hMsgAllocCtxt_io)))
    {
   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Vendor-Id AVP.\n");
   	 goto ExitMe;
    }

    if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateOctetStringAVP(hDiamStackContext_io,
																			 DMBASE_AVP_PRODUCT_NAME,
																			 &poCER_AVPs_io->hProductName,
																			 hDiamStackContext_io->oProductName.pucOctetString,
																			 hDiamStackContext_io->oProductName.unNumOfOctets,
																			 hMsgAllocCtxt_io)))
    {
   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Product AVP.\n");
   	 goto ExitMe;
    }

    unsigned int unIndex = 0;

    for(; unIndex < hDiamStackContext_io->unSupportedAppCount;unIndex++)
    {
        if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateAppAVP(hDiamStackContext_io,
																		 &poCER_AVPs_io->oSupportedApplications[poCER_AVPs_io->unSupportedAppCount++] ,
																		 &hDiamStackContext_io->SupportedAppList[unIndex], hMsgAllocCtxt_io)))
        {
       	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Product AVP.\n");
       	 goto ExitMe;
        }
    }

    ExitMe:

    DMBase_Free(hDiamStackContext_io, (void**)&pucIPAddress);
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;


}

t_DiamAPIReturnVal DMBase_Create_CEA_AVPs(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											t_DiamCEA_AVPs*			poCEA_AVPs_io,
											HMSGALLOCATIONCONTEXT   hMsgAllocCtxt_io)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     t_DiamAPIReturnVal oReturnValue;
     unsigned char *pucIPAddress = NULL;

     if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateUnsigned32AVP( hDiamStackContext_io,
																			 DMBASE_AVP_RESULT_CODE,
																			 &poCEA_AVPs_io->hResultCode,
																			 DIAMETER_SUCCESS,
																			 hMsgAllocCtxt_io)))
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Result-Code AVP.\n");
    	 goto ExitMe;
     }

     if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateOctetStringAVP(hDiamStackContext_io,
																			 DMBASE_AVP_ORIGIN_HOST,
																			 &poCEA_AVPs_io->hOriginHost,
																			 hDiamStackContext_io->oHostName.pucOctetString,
																			 hDiamStackContext_io->oHostName.unNumOfOctets,
																			 hMsgAllocCtxt_io)))
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Origin-Host AVP.\n");
    	 goto ExitMe;
     }

     if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateOctetStringAVP(hDiamStackContext_io,
																			 DMBASE_AVP_ORIGIN_REALM,
																			 &poCEA_AVPs_io->hOriginRealm,
																			 hDiamStackContext_io->oRealmName.pucOctetString,
																			 hDiamStackContext_io->oRealmName.unNumOfOctets,
																			 hMsgAllocCtxt_io)))
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Origin-Realm AVP.\n");
    	 goto ExitMe;
     }

     DMBase_GetIPAddressFromDiameterContext(hDiamStackContext_io, &pucIPAddress);



     if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateIPAddressAVP(hDiamStackContext_io,
																			 DMBASE_AVP_HOST_IP_ADDRESS,
																			 &poCEA_AVPs_io->hHostIP,
																			 pucIPAddress,
																			 DMBASE_IANA_ADDR_FAMILY_IP_V4,
																			 hMsgAllocCtxt_io)))
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Host-IP-Address AVP.\n");
    	 goto ExitMe;
     }

     unsigned int unVendorID = 0;
     DMBase_GetVendorIDFromDiameterContext(hDiamStackContext_io, &unVendorID);

     if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateUnsigned32AVP( hDiamStackContext_io,
																			 DMBASE_AVP_VENDOR_ID,
																			 &poCEA_AVPs_io->hVendorID,
																			 unVendorID,
																			 hMsgAllocCtxt_io)))
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Vendor-Id AVP.\n");
    	 goto ExitMe;
     }

     if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateOctetStringAVP(hDiamStackContext_io,
																			 DMBASE_AVP_PRODUCT_NAME,
																			 &poCEA_AVPs_io->hProductName,
																			 hDiamStackContext_io->oProductName.pucOctetString,
																			 hDiamStackContext_io->oProductName.unNumOfOctets,
																			 hMsgAllocCtxt_io)))
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Product AVP.\n");
    	 goto ExitMe;
     }

     unsigned int unIndex = 0;

     for(; unIndex < hDiamStackContext_io->unSupportedAppCount;unIndex++)
     {
         if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateAppAVP(hDiamStackContext_io,
																		 &poCEA_AVPs_io->oSupportedApplications[poCEA_AVPs_io->unSupportedAppCount++] ,
																		 &hDiamStackContext_io->SupportedAppList[unIndex], hMsgAllocCtxt_io)))
         {
        	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create Product AVP.\n");
        	 goto ExitMe;
         }
     }

     ExitMe:

     DMBase_Free(hDiamStackContext_io, (void**)&pucIPAddress);
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}



t_DiamAPIReturnVal DMBase_CreateCER(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
									HDIAMETERMESSAGE*		phCER_i,
									unsigned int 			unHopByHopID_i,
									unsigned int 			unEndToEndID_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	t_DiamCER_AVPs	oCER_AVPs;
	t_DiamAPIReturnVal oReturnValue;
	DMBase_MemsetZero(&oCER_AVPs, sizeof(t_DiamCER_AVPs));

    if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateDiameterMessage(hDiamStackContext_io,
																			 phCER_i,
																			 DIAMETER_VERSION_NUMBER,
																			 DMBASE_MSG_CMD_CODE_CEA,
																			 DIAMETER_COMMON_MESSAGE_ID,
																			 0,
																			 unHopByHopID_i,
																			 unEndToEndID_i)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create message.\n");
    	goto ExitMe;
    }

    DMBase_SetDiaMsgRFlag(hDiamStackContext_io, *phCER_i,1);

	HMSGALLOCATIONCONTEXT hMsgAllocCtxt = NULL;
	DMBase_Get_AllocationContext_ForMessage(hDiamStackContext_io, *phCER_i, &hMsgAllocCtxt);

    if(DMBase_Retval_Success != (oReturnValue = DMBase_Create_CER_AVPs(	hDiamStackContext_io,
																		&oCER_AVPs, hMsgAllocCtxt)))
    {
	   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to Create AVPs.\n");
	   	 goto ExitMe;
    }

	HAVPCOLLECTION hAVPCollection = NULL;

	if(DMBase_Retval_Success != (oReturnValue = DMBase_AppendSList(hDiamStackContext_io,
																	&hAVPCollection,
																	oCER_AVPs.hOriginHost)))
	{
	   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to append AVP.\n");
	   	 goto ExitMe;
	}

	if(DMBase_Retval_Success != (oReturnValue = DMBase_AppendSList(hDiamStackContext_io,
																	&hAVPCollection,
																	oCER_AVPs.hOriginRealm)))
	{
	   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to append AVP.\n");
	   	 goto ExitMe;
	}

	if(DMBase_Retval_Success != (oReturnValue = DMBase_AppendSList(hDiamStackContext_io,
																	&hAVPCollection,
																	oCER_AVPs.hHostIP)))
	{
	   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to append AVP.\n");
	   	 goto ExitMe;
	}

	if(DMBase_Retval_Success != (oReturnValue = DMBase_AppendSList(hDiamStackContext_io,
																	&hAVPCollection,
																	oCER_AVPs.hVendorID)))
	{
	   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to append AVP.\n");
	   	 goto ExitMe;
	}

	if(DMBase_Retval_Success != (oReturnValue = DMBase_AppendSList(hDiamStackContext_io,
																	&hAVPCollection,
																	oCER_AVPs.hProductName)))
	{
	   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to append AVP.\n");
	   	 goto ExitMe;
	}

	unsigned int unIndex = 0;
	for(; unIndex < oCER_AVPs.unSupportedAppCount; unIndex++)
	{
		if(DMBase_Retval_Success != (oReturnValue = DMBase_AppendSList(hDiamStackContext_io,
																		&hAVPCollection,
																		oCER_AVPs.oSupportedApplications[unIndex])))
		{
			 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to append AVP.\n");
			 goto ExitMe;
		}
	}


    if(DMBase_Retval_Success != (oReturnValue = DMBase_AddAVPCollectionToDiameterMessage(hDiamStackContext_io,
																						*phCER_i,
																						hAVPCollection)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create message.\n");
    	goto ExitMe;
    }


    ExitMe:

    if(DMBase_Retval_Success != oReturnValue)
    {
    	DMBase_DestroyDiaMessage(hDiamStackContext_io, phCER_i);
    	DMBase_SListFree(hDiamStackContext_io, &hAVPCollection, NULL);
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnValue;

}

t_DiamAPIReturnVal DMBase_CreateCEA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
									HDIAMETERMESSAGE*		phCEA_i,
									unsigned int 			unHopByHopID_i,
									unsigned int 			unEndToEndID_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	t_DiamCEA_AVPs	oCEA_AVPs;
	t_DiamAPIReturnVal oReturnValue;
	DMBase_MemsetZero(&oCEA_AVPs, sizeof(t_DiamCEA_AVPs));

    if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateDiameterMessage(hDiamStackContext_io,
																			 phCEA_i,
																			 DIAMETER_VERSION_NUMBER,
																			 DMBASE_MSG_CMD_CODE_CEA,
																			 DIAMETER_COMMON_MESSAGE_ID,
																			 0,
																			 unHopByHopID_i,
																			 unEndToEndID_i)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create message.\n");
    	goto ExitMe;
    }

	HMSGALLOCATIONCONTEXT hMsgAllocCtxt = NULL;
	DMBase_Get_AllocationContext_ForMessage(hDiamStackContext_io, *phCEA_i, &hMsgAllocCtxt);



    if(DMBase_Retval_Success != (oReturnValue = DMBase_Create_CEA_AVPs(	hDiamStackContext_io,
																		&oCEA_AVPs, hMsgAllocCtxt)))
    {
	   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to Create AVPs.\n");
	   	 goto ExitMe;
    }

	HAVPCOLLECTION hAVPCollection = NULL;

	if(DMBase_Retval_Success != (oReturnValue = DMBase_AppendSList(hDiamStackContext_io,
																	&hAVPCollection,
																	oCEA_AVPs.hResultCode)))
	{
	   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to append AVP.\n");
	   	 goto ExitMe;
	}

	if(DMBase_Retval_Success != (oReturnValue = DMBase_AppendSList(hDiamStackContext_io,
																	&hAVPCollection,
																	oCEA_AVPs.hOriginHost)))
	{
	   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to append AVP.\n");
	   	 goto ExitMe;
	}

	if(DMBase_Retval_Success != (oReturnValue = DMBase_AppendSList(hDiamStackContext_io,
																	&hAVPCollection,
																	oCEA_AVPs.hOriginRealm)))
	{
	   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to append AVP.\n");
	   	 goto ExitMe;
	}

	if(DMBase_Retval_Success != (oReturnValue = DMBase_AppendSList(hDiamStackContext_io,
																	&hAVPCollection,
																	oCEA_AVPs.hHostIP)))
	{
	   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to append AVP.\n");
	   	 goto ExitMe;
	}

	if(DMBase_Retval_Success != (oReturnValue = DMBase_AppendSList(hDiamStackContext_io,
																	&hAVPCollection,
																	oCEA_AVPs.hProductName)))
	{
	   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to append AVP.\n");
	   	 goto ExitMe;
	}

	unsigned int unIndex = 0;
	for(; unIndex < oCEA_AVPs.unSupportedAppCount; unIndex++)
	{
		if(DMBase_Retval_Success != (oReturnValue = DMBase_AppendSList(hDiamStackContext_io,
																		&hAVPCollection,
																		oCEA_AVPs.oSupportedApplications[unIndex])))
		{
			 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to append AVP.\n");
			 goto ExitMe;
		}
	}



    if(DMBase_Retval_Success != (oReturnValue = DMBase_AddAVPCollectionToDiameterMessage(hDiamStackContext_io,
																						*phCEA_i,
																						hAVPCollection)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create message.\n");
    	goto ExitMe;
    }


    ExitMe:

    if(DMBase_Retval_Success != oReturnValue)
    {
    	DMBase_DestroyDiaMessage(hDiamStackContext_io, phCEA_i);
    	DMBase_SListFree(hDiamStackContext_io, &hAVPCollection, NULL);
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnValue;



}

