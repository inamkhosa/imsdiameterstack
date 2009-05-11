#include "dmbase_msgvalidate.h"

#include "dmbase_message.h"
#include "dmbase_ampswrappers.h"
#include "dmbase_parser.h"
#include "dmbase_avp.h"

extern	int g_nDiamBaseTraceID ;

t_DiamAPIReturnVal	DMBase_GetDetailsAboutAVPsInCollection(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
													HAVPCOLLECTION		hCollOfAVPs_i,
													DMBase_SList**	ppListAVPDetails_o)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hCollOfAVPs_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! pAVPList is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListAVPDetails_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListAVPDetails is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unPrevAVPCode = DMBASE_AVPCODE_UNINIT_PREV_VAL;
	unsigned int	unPrevAVPPosition = 0;
	unsigned int	unPrevAVPCount = 0;
	unsigned int	unCurrAVPCode =0;
	void*			pCurrData = NULL;
	DMBase_SList*	pCurrentNode = hCollOfAVPs_i;
	HAVP			hCurrAVP = NULL;
	t_AVPDetails*	poPrevAVPDetails = NULL;
	t_AVPDetails*	poCurrAVPDetails = NULL;
	unsigned int	unTotalAVPCount = 0;


	while (NULL != pCurrentNode)
	{
		poCurrAVPDetails = NULL;

		DMBase_SListGetNodeData(hDiameterStackContext_io, pCurrentNode, &pCurrData);
		hCurrAVP = ( HAVP) pCurrData;
		unTotalAVPCount ++;

		unCurrAVPCode = (hCurrAVP->oAVPHeaderInst).unAVPCode;

		if (unCurrAVPCode == unPrevAVPCode)
		{
			//increase count in previous one
			(poPrevAVPDetails->unAVPQuantity)++;
		}
		else
		{
			DMBase_Malloc(hDiameterStackContext_io,(void* )&poCurrAVPDetails,
						  sizeof ( t_AVPDetails) );
			DMBase_MemsetZero(poCurrAVPDetails , sizeof( t_AVPDetails));


			poCurrAVPDetails->unAVPCode = unCurrAVPCode;
			poCurrAVPDetails->unAVPPosition = unTotalAVPCount;
			poCurrAVPDetails->unAVPQuantity = 1;

			DMBase_AppendSList(hDiameterStackContext_io,
							   ppListAVPDetails_o,
							   (void*) poCurrAVPDetails);

			unPrevAVPCode = unCurrAVPCode;
			poPrevAVPDetails = poCurrAVPDetails;

		}

		DMBase_SListGetNextNode( hDiameterStackContext_io , pCurrentNode , &pCurrentNode);

	}//end while


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}


t_DiamAPIReturnVal	DMBase_ValidateMsg_ASR( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_ASR_i,
											DMBase_SList**	ppListOfValidateErrors_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hMsg_ASR_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hMsg_ASR_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOfValidateErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfValidateErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unMsgCmdCode = 0;


     if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									hMsg_ASR_i,&unMsgCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

	//Validate Message Header first

	if (DMBASE_MSG_CMD_CODE_ASR != unMsgCmdCode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! command code is not ASR , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_R_FLAG != (DMBASE_BITMASK_SET_MSG_R_FLAG & hMsg_ASR_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," R bit is not set in  ASR header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_P_FLAG != (DMBASE_BITMASK_SET_MSG_P_FLAG & hMsg_ASR_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," P bit is not set in  ASR header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	//Validate AVPs now
	DMBase_SList*		pListOfAVPDetails = NULL;
	t_DiamAPIReturnVal	oDiamRetVal;
	DMBase_SList*		pListOfValidateErrors = NULL;

	oDiamRetVal = DMBase_GetDetailsAboutAVPsInCollection(hDiameterStackContext_io,
												   hMsg_ASR_i->hCollectionOfAVPs,
												   &pListOfAVPDetails);


	//checking for session ID AVP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_SESSION_ID,
											  1,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_ORIGIN_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_DESTINATION_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_DESTINATION_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_DESTINATION_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_DESTINATION_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_AUTH_APPLICATION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_AUTH_APPLICATION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_USER_NAME
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_USER_NAME,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ORIGIN_STATE_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_STATE_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_PROXY_INFO
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_PROXY_INFO,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ROUTE_RECORD
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ROUTE_RECORD,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	*ppListOfValidateErrors_o = pListOfValidateErrors;

	//free the AVP Details list here

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_ValidateMsg_ASA( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_ASA_i,
											DMBase_SList**	ppListOfValidateErrors_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hMsg_ASA_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hMsg_ASA_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOfValidateErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfValidateErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unMsgCmdCode = 0;

	if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									hMsg_ASA_i,&unMsgCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

	//Validate Message Header first

	if (DMBASE_MSG_CMD_CODE_ASA != unMsgCmdCode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! command code is not ASA , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_CLEAR_MSG_R_FLAG != (DMBASE_BITMASK_CLEAR_MSG_R_FLAG & hMsg_ASA_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," R bit is not clear in  ASA header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_P_FLAG != (DMBASE_BITMASK_SET_MSG_P_FLAG & hMsg_ASA_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," P bit is not set in  ASR header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	//Validate AVPs now
	DMBase_SList*		pListOfAVPDetails = NULL;
	t_DiamAPIReturnVal	oDiamRetVal;
	DMBase_SList*		pListOfValidateErrors = NULL;

	oDiamRetVal = DMBase_GetDetailsAboutAVPsInCollection(hDiameterStackContext_io,
												   hMsg_ASA_i->hCollectionOfAVPs,
												   &pListOfAVPDetails);


	//checking for session ID AVP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_SESSION_ID,
											  1,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_RESULT_CODE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_RESULT_CODE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


		//checking for DMBASE_AVP_USER_NAME
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_USER_NAME,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ORIGIN_STATE_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_STATE_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ERROR_MESSAGE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ERROR_MESSAGE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ERROR_REPORTING_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ERROR_REPORTING_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_FAILED_AVP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_FAILED_AVP,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_REDIRECT_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_REDIRECT_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_REDIRECT_HOST_USAGE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_REDIRECT_HOST_USAGE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_REDIRECT_MAX_CACHE_TIME
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_REDIRECT_MAX_CACHE_TIME,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_PROXY_INFO
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_PROXY_INFO,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	*ppListOfValidateErrors_o = pListOfValidateErrors;

	//free the AVP Details list here

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}


t_DiamAPIReturnVal	DMBase_ValidateMsg_ACR( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_ACR_i,
											DMBase_SList**	ppListOfValidateErrors_o)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hMsg_ACR_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hMsg_ACR_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOfValidateErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfValidateErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unMsgCmdCode = 0;

	if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									hMsg_ACR_i,&unMsgCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

	//Validate Message Header first

	if (DMBASE_MSG_CMD_CODE_ACR != unMsgCmdCode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! command code is not ACR , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_R_FLAG != (DMBASE_BITMASK_SET_MSG_R_FLAG & hMsg_ACR_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," R bit is not clear in  ACR header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_P_FLAG != (DMBASE_BITMASK_SET_MSG_P_FLAG & hMsg_ACR_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," P bit is not set in  ACR header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	//Validate AVPs now
	DMBase_SList*		pListOfAVPDetails = NULL;
	t_DiamAPIReturnVal	oDiamRetVal;
	DMBase_SList*		pListOfValidateErrors = NULL;

	oDiamRetVal = DMBase_GetDetailsAboutAVPsInCollection(hDiameterStackContext_io,
												   hMsg_ACR_i->hCollectionOfAVPs,
												   &pListOfAVPDetails);


	//checking for session ID AVP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_SESSION_ID,
											  1,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_ORIGIN_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


		//checking for DMBASE_AVP_DESTINATION_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_DESTINATION_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ACCOUNTING_RECORD_TYPE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCOUNTING_RECORD_TYPE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ACCOUNTING_RECORD_NUMBER
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCOUNTING_RECORD_NUMBER,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ACCT_APPLICATION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCT_APPLICATION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


		//checking for DMBASE_AVP_USER_NAME
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_USER_NAME,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ACCOUNTING_SESSION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCOUNTING_SESSION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ACCT_MULTI_SESSION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCT_MULTI_SESSION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ACCT_INTERIM_INTERVAL
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCT_INTERIM_INTERVAL,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_STATE_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_STATE_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_EVENT_TIMESTAMP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_EVENT_TIMESTAMP,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_PROXY_INFO
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_PROXY_INFO,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ROUTE_RECORD
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ROUTE_RECORD,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	*ppListOfValidateErrors_o = pListOfValidateErrors;

	//free the AVP Details list here

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;


}

t_DiamAPIReturnVal	DMBase_ValidateMsg_ACA( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_ACA_i,
											DMBase_SList**	ppListOfValidateErrors_o)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hMsg_ACA_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hMsg_ACA_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOfValidateErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfValidateErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unMsgCmdCode = 0;

	if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									hMsg_ACA_i,&unMsgCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }


	//Validate Message Header first

	if (DMBASE_MSG_CMD_CODE_ACA != unMsgCmdCode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! command code is not ACA , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_CLEAR_MSG_R_FLAG != (DMBASE_BITMASK_CLEAR_MSG_R_FLAG & hMsg_ACA_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," R bit is not clear in  ACA header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_P_FLAG != (DMBASE_BITMASK_SET_MSG_P_FLAG & hMsg_ACA_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," P bit is not set in  ACA header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	//Validate AVPs now
	DMBase_SList*		pListOfAVPDetails = NULL;
	t_DiamAPIReturnVal	oDiamRetVal;
	DMBase_SList*		pListOfValidateErrors = NULL;

	oDiamRetVal = DMBase_GetDetailsAboutAVPsInCollection(hDiameterStackContext_io,
												   hMsg_ACA_i->hCollectionOfAVPs,
												   &pListOfAVPDetails);


	//checking for session ID AVP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_SESSION_ID,
											  1,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_RESULT_CODE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_RESULT_CODE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


		//checking for DMBASE_AVP_ACCOUNTING_RECORD_TYPE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCOUNTING_RECORD_TYPE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ACCOUNTING_RECORD_NUMBER
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCOUNTING_RECORD_NUMBER,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ACCT_APPLICATION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCT_APPLICATION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


		//checking for DMBASE_AVP_USER_NAME
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_USER_NAME,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ACCOUNTING_SESSION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCOUNTING_SESSION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ACCT_MULTI_SESSION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCT_MULTI_SESSION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ERROR_REPORTING_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ERROR_REPORTING_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ACCT_INTERIM_INTERVAL
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCT_INTERIM_INTERVAL,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_STATE_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_STATE_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_EVENT_TIMESTAMP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_EVENT_TIMESTAMP,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_PROXY_INFO
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_PROXY_INFO,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	*ppListOfValidateErrors_o = pListOfValidateErrors;

	//free the AVP Details list here

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}


t_DiamAPIReturnVal	DMBase_ValidateMsg_CER( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_CER_i,
											DMBase_SList**	ppListOfValidateErrors_o)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hMsg_CER_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hMsg_CER_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOfValidateErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfValidateErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unMsgCmdCode = 0;

	if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									hMsg_CER_i,&unMsgCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

	//Validate Message Header first

	if (DMBASE_MSG_CMD_CODE_CER != unMsgCmdCode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! command code is not CER , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_R_FLAG != (DMBASE_BITMASK_SET_MSG_R_FLAG & hMsg_CER_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," R bit is not set in  CER header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_CLEAR_MSG_P_FLAG != (DMBASE_BITMASK_CLEAR_MSG_P_FLAG & hMsg_CER_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," P bit is not clear in  CER header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	//Validate AVPs now
	DMBase_SList*		pListOfAVPDetails = NULL;
	t_DiamAPIReturnVal	oDiamRetVal;
	DMBase_SList*		pListOfValidateErrors = NULL;

	oDiamRetVal = DMBase_GetDetailsAboutAVPsInCollection(hDiameterStackContext_io,
												   hMsg_CER_i->hCollectionOfAVPs,
												   &pListOfAVPDetails);


	//checking for DMBASE_AVP_ORIGIN_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_ORIGIN_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_HOST_IP_ADDRESS
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_HOST_IP_ADDRESS,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_VENDOR_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_VENDOR_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


		//checking for DMBASE_AVP_PRODUCT_NAME
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_PRODUCT_NAME,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ORIGIN_STATE_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_STATE_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_SUPPORTED_VENDOR_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_SUPPORTED_VENDOR_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_INBAND_SECURITY_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_INBAND_SECURITY_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ACCT_APPLICATION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCT_APPLICATION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_FIRMWARE_REVISION
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_FIRMWARE_REVISION,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	*ppListOfValidateErrors_o = pListOfValidateErrors;

	//free the AVP Details list here

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;

}

t_DiamAPIReturnVal	DMBase_ValidateMsg_CEA( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_CEA_i,
											DMBase_SList**	ppListOfValidateErrors_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hMsg_CEA_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hMsg_CEA_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOfValidateErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfValidateErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unMsgCmdCode = 0;

	if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									hMsg_CEA_i,&unMsgCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

	//Validate Message Header first

	if (DMBASE_MSG_CMD_CODE_CEA != unMsgCmdCode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! command code is not CEA , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_CLEAR_MSG_R_FLAG != (DMBASE_BITMASK_CLEAR_MSG_R_FLAG & hMsg_CEA_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," R bit is not clear in  CEA header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_CLEAR_MSG_P_FLAG != (DMBASE_BITMASK_CLEAR_MSG_P_FLAG & hMsg_CEA_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," P bit is not clear in  CEA header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	//Validate AVPs now
	DMBase_SList*		pListOfAVPDetails = NULL;
	t_DiamAPIReturnVal	oDiamRetVal;
	DMBase_SList*		pListOfValidateErrors = NULL;

	oDiamRetVal = DMBase_GetDetailsAboutAVPsInCollection(hDiameterStackContext_io,
												   hMsg_CEA_i->hCollectionOfAVPs,
												   &pListOfAVPDetails);

	//checking for DMBASE_AVP_RESULT_CODE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_RESULT_CODE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_ORIGIN_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_HOST_IP_ADDRESS
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_HOST_IP_ADDRESS,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_VENDOR_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_VENDOR_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


		//checking for DMBASE_AVP_PRODUCT_NAME
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_PRODUCT_NAME,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ORIGIN_STATE_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_STATE_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ERROR_MESSAGE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ERROR_MESSAGE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_FAILED_AVP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_FAILED_AVP,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_SUPPORTED_VENDOR_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_SUPPORTED_VENDOR_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_AUTH_APPLICATION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_AUTH_APPLICATION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_INBAND_SECURITY_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_INBAND_SECURITY_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ACCT_APPLICATION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ACCT_APPLICATION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_FIRMWARE_REVISION
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_FIRMWARE_REVISION,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	*ppListOfValidateErrors_o = pListOfValidateErrors;

	//free the AVP Details list here

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}


t_DiamAPIReturnVal	DMBase_ValidateMsg_DWR( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_DWR_i,
											DMBase_SList**	ppListOfValidateErrors_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hMsg_DWR_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hMsg_DWR_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOfValidateErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfValidateErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unMsgCmdCode = 0;

	if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									hMsg_DWR_i,&unMsgCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

	//Validate Message Header first

	if (DMBASE_MSG_CMD_CODE_DWR != unMsgCmdCode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! command code is not DWR , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_R_FLAG != (DMBASE_BITMASK_SET_MSG_R_FLAG & hMsg_DWR_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," R bit is not set in  DWR header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_CLEAR_MSG_P_FLAG != (DMBASE_BITMASK_CLEAR_MSG_P_FLAG & hMsg_DWR_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," P bit is not clear in  DWR header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	//Validate AVPs now
	DMBase_SList*		pListOfAVPDetails = NULL;
	t_DiamAPIReturnVal	oDiamRetVal;
	DMBase_SList*		pListOfValidateErrors = NULL;

	oDiamRetVal = DMBase_GetDetailsAboutAVPsInCollection(hDiameterStackContext_io,
												   hMsg_DWR_i->hCollectionOfAVPs,
												   &pListOfAVPDetails);


	//checking for DMBASE_AVP_ORIGIN_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_STATE_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_STATE_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	*ppListOfValidateErrors_o = pListOfValidateErrors;

	//free the AVP Details list here

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_ValidateMsg_DWA( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_DWA_i,
											DMBase_SList**	ppListOfValidateErrors_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hMsg_DWA_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hMsg_DWA_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOfValidateErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfValidateErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unMsgCmdCode = 0;
	if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									hMsg_DWA_i,&unMsgCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }
	//Validate Message Header first

	if (DMBASE_MSG_CMD_CODE_DWA != unMsgCmdCode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! command code is not DWA , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_CLEAR_MSG_R_FLAG != (DMBASE_BITMASK_CLEAR_MSG_R_FLAG & hMsg_DWA_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," R bit is not clear in  DWA header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_CLEAR_MSG_P_FLAG != (DMBASE_BITMASK_CLEAR_MSG_P_FLAG & hMsg_DWA_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," P bit is not clear in  DWA header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	//Validate AVPs now
	DMBase_SList*		pListOfAVPDetails = NULL;
	t_DiamAPIReturnVal	oDiamRetVal;
	DMBase_SList*		pListOfValidateErrors = NULL;

	oDiamRetVal = DMBase_GetDetailsAboutAVPsInCollection(hDiameterStackContext_io,
												   hMsg_DWA_i->hCollectionOfAVPs,
												   &pListOfAVPDetails);

	//checking for DMBASE_AVP_RESULT_CODE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_RESULT_CODE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ERROR_MESSAGE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ERROR_MESSAGE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_FAILED_AVP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_FAILED_AVP,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
	   										  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_STATE_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_STATE_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	*ppListOfValidateErrors_o = pListOfValidateErrors;

	//free the AVP Details list here

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}


t_DiamAPIReturnVal	DMBase_ValidateMsg_DPR( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_DPR_i,
											DMBase_SList**	ppListOfValidateErrors_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hMsg_DPR_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hMsg_DPR_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOfValidateErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfValidateErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unMsgCmdCode = 0;

	if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									hMsg_DPR_i,&unMsgCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

	//Validate Message Header first

	if (DMBASE_MSG_CMD_CODE_DPR != unMsgCmdCode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! command code is not DPR , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_R_FLAG != (DMBASE_BITMASK_SET_MSG_R_FLAG & hMsg_DPR_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," R bit is not set in  DPR header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_CLEAR_MSG_P_FLAG != (DMBASE_BITMASK_CLEAR_MSG_P_FLAG & hMsg_DPR_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," P bit is not clear in  DPR header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	//Validate AVPs now
	DMBase_SList*		pListOfAVPDetails = NULL;
	t_DiamAPIReturnVal	oDiamRetVal;
	DMBase_SList*		pListOfValidateErrors = NULL;

	oDiamRetVal = DMBase_GetDetailsAboutAVPsInCollection(hDiameterStackContext_io,
												   hMsg_DPR_i->hCollectionOfAVPs,
												   &pListOfAVPDetails);



	//checking for DMBASE_AVP_ORIGIN_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


		//checking for DMBASE_AVP_DISCONNECT_CAUSE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_DISCONNECT_CAUSE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	*ppListOfValidateErrors_o = pListOfValidateErrors;

	//free the AVP Details list here

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_ValidateMsg_DPA( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_DPA_i,
											DMBase_SList**	ppListOfValidateErrors_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hMsg_DPA_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hMsg_DPA_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOfValidateErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfValidateErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unMsgCmdCode = 0;

	if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									hMsg_DPA_i,&unMsgCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

	//Validate Message Header first

	if (DMBASE_MSG_CMD_CODE_DPA != unMsgCmdCode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! command code is not DPA , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_CLEAR_MSG_R_FLAG != (DMBASE_BITMASK_CLEAR_MSG_R_FLAG & hMsg_DPA_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," R bit is not clear in  DPA header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_CLEAR_MSG_P_FLAG != (DMBASE_BITMASK_CLEAR_MSG_P_FLAG & hMsg_DPA_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," P bit is not clear in  DPA header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	//Validate AVPs now
	DMBase_SList*		pListOfAVPDetails = NULL;
	t_DiamAPIReturnVal	oDiamRetVal;
	DMBase_SList*		pListOfValidateErrors = NULL;

	oDiamRetVal = DMBase_GetDetailsAboutAVPsInCollection(hDiameterStackContext_io,
												   hMsg_DPA_i->hCollectionOfAVPs,
												   &pListOfAVPDetails);

	//checking for DMBASE_AVP_RESULT_CODE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_RESULT_CODE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_ERROR_MESSAGE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ERROR_MESSAGE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_FAILED_AVP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_FAILED_AVP,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	*ppListOfValidateErrors_o = pListOfValidateErrors;

	//free the AVP Details list here

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_ValidateMsg_RAR( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_RAR_i,
											DMBase_SList**	ppListOfValidateErrors_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hMsg_RAR_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hMsg_RAR_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOfValidateErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfValidateErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unMsgCmdCode = 0;

	if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									hMsg_RAR_i,&unMsgCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

	//Validate Message Header first

	if (DMBASE_MSG_CMD_CODE_RAR != unMsgCmdCode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! command code is not RAR , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_R_FLAG != (DMBASE_BITMASK_SET_MSG_R_FLAG & hMsg_RAR_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," R bit is not clear in  RAR header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_P_FLAG != (DMBASE_BITMASK_SET_MSG_P_FLAG & hMsg_RAR_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," P bit is not set in  RAR header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	//Validate AVPs now
	DMBase_SList*		pListOfAVPDetails = NULL;
	t_DiamAPIReturnVal	oDiamRetVal;
	DMBase_SList*		pListOfValidateErrors = NULL;

	oDiamRetVal = DMBase_GetDetailsAboutAVPsInCollection(hDiameterStackContext_io,
												   hMsg_RAR_i->hCollectionOfAVPs,
												   &pListOfAVPDetails);


	//checking for session ID AVP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_SESSION_ID,
											  1,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_ORIGIN_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


		//checking for DMBASE_AVP_DESTINATION_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_DESTINATION_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_DESTINATION_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_DESTINATION_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_AUTH_APPLICATION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_AUTH_APPLICATION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_RE_AUTH_REQUEST_TYPE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_RE_AUTH_REQUEST_TYPE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_USER_NAME
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_USER_NAME,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_ORIGIN_STATE_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_STATE_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_PROXY_INFO
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_PROXY_INFO,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ROUTE_RECORD
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ROUTE_RECORD,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	*ppListOfValidateErrors_o = pListOfValidateErrors;

	//free the AVP Details list here

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_ValidateMsg_RAA( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_RAA_i,
											DMBase_SList**	ppListOfValidateErrors_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hMsg_RAA_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hMsg_RAA_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOfValidateErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfValidateErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unMsgCmdCode = 0;


	if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									hMsg_RAA_i,&unMsgCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

	//Validate Message Header first

	if (DMBASE_MSG_CMD_CODE_RAA != unMsgCmdCode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! command code is not RAA , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_CLEAR_MSG_R_FLAG != (DMBASE_BITMASK_CLEAR_MSG_R_FLAG & hMsg_RAA_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," R bit is not clear in  RAA header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_P_FLAG != (DMBASE_BITMASK_SET_MSG_P_FLAG & hMsg_RAA_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," P bit is not set in  RAA header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	//Validate AVPs now
	DMBase_SList*		pListOfAVPDetails = NULL;
	t_DiamAPIReturnVal	oDiamRetVal;
	DMBase_SList*		pListOfValidateErrors = NULL;

	oDiamRetVal = DMBase_GetDetailsAboutAVPsInCollection(hDiameterStackContext_io,
												   hMsg_RAA_i->hCollectionOfAVPs,
												   &pListOfAVPDetails);


	//checking for session ID AVP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_SESSION_ID,
											  1,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_RESULT_CODE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_RESULT_CODE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


		//checking for DMBASE_AVP_USER_NAME
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_USER_NAME,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ORIGIN_STATE_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_STATE_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ERROR_MESSAGE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ERROR_MESSAGE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ERROR_REPORTING_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ERROR_REPORTING_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_FAILED_AVP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_FAILED_AVP,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_REDIRECT_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_REDIRECT_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_REDIRECT_HOST_USAGE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_REDIRECT_HOST_USAGE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_REDIRECT_MAX_CACHE_TIME
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_REDIRECT_MAX_CACHE_TIME,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_PROXY_INFO
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_PROXY_INFO,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	*ppListOfValidateErrors_o = pListOfValidateErrors;

	//free the AVP Details list here

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}




t_DiamAPIReturnVal	DMBase_ValidateMsg_STR( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_STR_i,
											DMBase_SList**	ppListOfValidateErrors_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hMsg_STR_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hMsg_STR_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOfValidateErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfValidateErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unMsgCmdCode = 0;


	if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									hMsg_STR_i,&unMsgCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

	//Validate Message Header first

	if (DMBASE_MSG_CMD_CODE_STR != unMsgCmdCode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! command code is not STR , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_R_FLAG != (DMBASE_BITMASK_SET_MSG_R_FLAG & hMsg_STR_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," R bit is not clear in  STR header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_P_FLAG != (DMBASE_BITMASK_SET_MSG_P_FLAG & hMsg_STR_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," P bit is not set in  STR header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	//Validate AVPs now
	DMBase_SList*		pListOfAVPDetails = NULL;
	t_DiamAPIReturnVal	oDiamRetVal;
	DMBase_SList*		pListOfValidateErrors = NULL;

	oDiamRetVal = DMBase_GetDetailsAboutAVPsInCollection(hDiameterStackContext_io,
												   hMsg_STR_i->hCollectionOfAVPs,
												   &pListOfAVPDetails);


	//checking for session ID AVP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_SESSION_ID,
											  1,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_ORIGIN_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


		//checking for DMBASE_AVP_DESTINATION_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_DESTINATION_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_AUTH_APPLICATION_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_AUTH_APPLICATION_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_TERMINATION_CAUSE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_TERMINATION_CAUSE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_USER_NAME
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_USER_NAME,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_DESTINATION_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_DESTINATION_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_CLASS
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_CLASS,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_STATE_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_STATE_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_PROXY_INFO
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_PROXY_INFO,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ROUTE_RECORD
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ROUTE_RECORD,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	*ppListOfValidateErrors_o = pListOfValidateErrors;

	//free the AVP Details list here

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_ValidateMsg_STA( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_STA_i,
											DMBase_SList**	ppListOfValidateErrors_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hMsg_STA_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hMsg_STA_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOfValidateErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfValidateErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unMsgCmdCode = 0;


	if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									hMsg_STA_i,&unMsgCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

	//Validate Message Header first

	if (DMBASE_MSG_CMD_CODE_STA != unMsgCmdCode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! command code is not STA , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_CLEAR_MSG_R_FLAG != (DMBASE_BITMASK_CLEAR_MSG_R_FLAG & hMsg_STA_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," R bit is not clear in  STA header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	if (DMBASE_BITMASK_SET_MSG_P_FLAG != (DMBASE_BITMASK_SET_MSG_P_FLAG & hMsg_STA_i->oDiaHeader.ucFlags)  )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," P bit is not set in  STA header flags , leaving\n");
        return DMBase_Retval_InvalidMsgHeader;
	}

	//Validate AVPs now
	DMBase_SList*		pListOfAVPDetails = NULL;
	t_DiamAPIReturnVal	oDiamRetVal;
	DMBase_SList*		pListOfValidateErrors = NULL;

	oDiamRetVal = DMBase_GetDetailsAboutAVPsInCollection(hDiameterStackContext_io,
												   hMsg_STA_i->hCollectionOfAVPs,
												   &pListOfAVPDetails);


	//checking for session ID AVP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_SESSION_ID,
											  1,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_RESULT_CODE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_RESULT_CODE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_ORIGIN_REALM
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_REALM,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  1,
	   										  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


		//checking for DMBASE_AVP_USER_NAME
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_USER_NAME,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_CLASS
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_CLASS,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);



		//checking for DMBASE_AVP_ERROR_MESSAGE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ERROR_MESSAGE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ERROR_REPORTING_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ERROR_REPORTING_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_FAILED_AVP
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_FAILED_AVP,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

		//checking for DMBASE_AVP_ORIGIN_STATE_ID
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_ORIGIN_STATE_ID,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_REDIRECT_HOST
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_REDIRECT_HOST,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_REDIRECT_HOST_USAGE
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_REDIRECT_HOST_USAGE,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	//checking for DMBASE_AVP_REDIRECT_MAX_CACHE_TIME
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_REDIRECT_MAX_CACHE_TIME,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  1,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);


	//checking for DMBASE_AVP_PROXY_INFO
	oDiamRetVal = DMBase_ValidateAVP(hDiameterStackContext_io,
											 DMBASE_AVP_PROXY_INFO,
											  DMBASE_AVP_POSITION_DONT_CARE,
	   										  0,
		   									  DMBASE_AVP_QUANTITY_DONT_CARE,
											 pListOfAVPDetails,
											 &pListOfValidateErrors);

	*ppListOfValidateErrors_o = pListOfValidateErrors;

	//free the AVP Details list here

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_ValidateAVP(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
									   unsigned int		unAVPCode_i,
									   unsigned int		unExpectedPosition_i,
									   unsigned int		unExpectedMinQuantity_i,
									   unsigned int		unExpectedMaxQuantity_i,
									   DMBase_SList*	pListOfAVPDetails_i,
									   DMBase_SList**	ppListOFAVPErrors_o
									   )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == pListOfAVPDetails_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! pListOfAVPDetails_i is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppListOFAVPErrors_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOFAVPErrors_o is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	//checking for special  case first
	if ( ( 0 == unExpectedMinQuantity_i) &&
		 ( DMBASE_AVP_QUANTITY_DONT_CARE == unExpectedMaxQuantity_i)
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
		return DMBase_Retval_Success;
	}

	void*			pCurrData = NULL;
	unsigned int	unCurrIndex = 0;
	DMBase_SList*	pCurrentNode = pListOfAVPDetails_i;
	_Bool			bFound = 0;
	t_AVPDetails*	pCurrAVPDetail = NULL;

	while (NULL != pCurrentNode)
	{

		DMBase_SListGetNodeData(hDiameterStackContext_io, pCurrentNode, &pCurrData);

		pCurrAVPDetail = (t_AVPDetails*) pCurrData;

		if (unAVPCode_i ==  pCurrAVPDetail->unAVPCode)
		{
				bFound = 1;
				break;
		}

		DMBase_SListGetNextNode( hDiameterStackContext_io , pCurrentNode , &pCurrentNode);

	}//end while

	//checking for optional avp case
	if ( (0 == bFound) && ( 0 ==unExpectedMinQuantity_i ) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
		return DMBase_Retval_Success;
	}

	_Bool	bError = 0;
	t_AVPValidateError*		poValidateError = NULL;

	//check for existence
	if ( 0 == bFound)
	{
		bError = 1;
		DMBase_Malloc(hDiameterStackContext_io,(void*) &poValidateError,
		  						sizeof( t_AVPValidateError));

		DMBase_MemsetZero(poValidateError , sizeof( t_AVPValidateError) );

		poValidateError->unAVPCode = unAVPCode_i;
		poValidateError->bIsAVPPresent = 0;

	}
	else
	{
		//checking for position
		if (DMBASE_AVP_POSITION_DONT_CARE != unExpectedPosition_i)
		{
			if (unExpectedPosition_i != pCurrAVPDetail->unAVPPosition)
			{
				bError = 1;
				DMBase_Malloc(hDiameterStackContext_io,(void*) &poValidateError,
		  						sizeof( t_AVPValidateError));

				DMBase_MemsetZero(poValidateError , sizeof( t_AVPValidateError) );

				poValidateError->bIsAVPPresent = 1;
				poValidateError->unActualPosition = pCurrAVPDetail->unAVPPosition;
				poValidateError->unExpectedPosition = unExpectedPosition_i;
			}
		}

		//checking for quantity
		if (
			(pCurrAVPDetail->unAVPQuantity < unExpectedMinQuantity_i)
			||
			(pCurrAVPDetail->unAVPQuantity > unExpectedMaxQuantity_i)
		   )
		{
			if (0 == bError)
			{
				bError = 1 ;
				DMBase_Malloc(hDiameterStackContext_io,(void*) &poValidateError,
								sizeof( t_AVPValidateError));

				DMBase_MemsetZero(poValidateError , sizeof( t_AVPValidateError) );

			}

			poValidateError->bIsAVPPresent = 1;
			poValidateError->unActualQuantity = pCurrAVPDetail->unAVPQuantity;
			poValidateError->unExpectedMinQuantity = unExpectedMinQuantity_i;
			poValidateError->unExpectedMaxQuantity = unExpectedMaxQuantity_i;

		}

	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	if ( ( 1== bError) || ( 0 == bFound ) )
	{
		DMBase_AppendSList(hDiameterStackContext_io,ppListOFAVPErrors_o,
						          (void*) poValidateError);

		return DMBase_Retval_Failure;
	}

	return DMBase_Retval_Success;


}


t_DiamAPIReturnVal      DMBase_GenerateProtocolErr(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
                                                    HPEERTABLEENTRY hPeer, HDIAMETERMESSAGE hDiamMsgRcv_i,
                                                    unsigned int unResCode, HAVPCOLLECTION hCollOfAVPs_i)
{

    unsigned int unCommandCode =0;

     if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									   hDiamMsgRcv_i,&unCommandCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }


    unsigned int unAppID = hDiamMsgRcv_i->oDiaHeader.unApplicationID;
    unsigned char ucFlags = hDiamMsgRcv_i->oDiaHeader.ucFlags;

    HDIAMETERMESSAGE hAnsMsg = NULL;
    DMBase_SList*	pAVPList = NULL;
    HAVP hTempAVP = NULL;

    DMBase_CreateDiameterMessage(hDiameterStackContext_io, &hAnsMsg, 1, unCommandCode, unAppID , 0, hDiamMsgRcv_i->oDiaHeader.unHopByHopID, hDiamMsgRcv_i->oDiaHeader.unEndToEndID);
    hAnsMsg->oDiaHeader.ucFlags = ucFlags;
    DMBase_SetDiaMsgRFlag(hDiameterStackContext_io, hAnsMsg,0);
    DMBase_SetDiaMsgEFlag(hDiameterStackContext_io, hAnsMsg,1);

	 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt = NULL;
	 if (DMBase_Retval_Success !=  DMBase_Get_AllocationContext_ForMessage(hDiameterStackContext_io,
			 hAnsMsg,&hMsgAllocCtxt)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_Get_AllocationContext_ForMessage Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

    HAVP hAVPSessionID = NULL;
    DMBase_GetAVP(hDiameterStackContext_io, DMBASE_AVP_SESSION_ID, hDiamMsgRcv_i, &hAVPSessionID);
    if(NULL != hAVPSessionID)
    {
        t_DiamOctetString* poSessionID = (t_DiamOctetString*)hAVPSessionID->pData;
        DMBase_CreateOctetStringAVP(hDiameterStackContext_io, DMBASE_AVP_SESSION_ID,
                &hTempAVP, poSessionID->pucOctetString, poSessionID->unNumOfOctets,hMsgAllocCtxt);
        DMBase_AppendSList(hDiameterStackContext_io, &pAVPList, (void*)hTempAVP);

    }

    hTempAVP = NULL;
    DMBase_CreateUTF8StringAVP(hDiameterStackContext_io,
            DMBASE_AVP_ORIGIN_HOST,
            &hTempAVP,
            hDiameterStackContext_io->oHostName.pucOctetString,
            hDiameterStackContext_io->oHostName.unNumOfOctets,hMsgAllocCtxt );
    DMBase_AppendSList(hDiameterStackContext_io, &pAVPList, (void*)hTempAVP);

    hTempAVP = NULL;
    DMBase_CreateUTF8StringAVP(hDiameterStackContext_io,
            DMBASE_AVP_ORIGIN_REALM,
            &hTempAVP,
            hDiameterStackContext_io->oRealmName.pucOctetString,
            hDiameterStackContext_io->oRealmName.unNumOfOctets ,hMsgAllocCtxt );
    DMBase_AppendSList(hDiameterStackContext_io, &pAVPList, (void*)hTempAVP);

    hTempAVP = NULL;
    DMBase_CreateEnumAVP(hDiameterStackContext_io, DMBASE_AVP_RESULT_CODE, &hTempAVP, unResCode,hMsgAllocCtxt);
    DMBase_AppendSList(hDiameterStackContext_io, &pAVPList, (void*)hTempAVP);

    if(NULL != hCollOfAVPs_i)
    {
        DMBase_SList* poTempAVPsList = hCollOfAVPs_i;

        for(; NULL != poTempAVPsList; DMBase_SListGetNextNode(hDiameterStackContext_io, poTempAVPsList, &poTempAVPsList))
        {
            hTempAVP = NULL;
            DMBase_SListGetNodeData(hDiameterStackContext_io, poTempAVPsList, (void**)&hTempAVP);
            DMBase_AppendSList(hDiameterStackContext_io, &pAVPList, (void*)hTempAVP);
        }
    }
    DMBase_AddAVPCollectionToDiameterMessage(hDiameterStackContext_io, hAnsMsg, pAVPList);

    DMBase_SendMessageToPeer(hDiameterStackContext_io, hPeer, hAnsMsg);
    DMBase_DestroyDiaMessage(hDiameterStackContext_io, &hAnsMsg);
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal      DMBase_GeneratePermanentFailure(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
                                                    HPEERTABLEENTRY hPeer, HDIAMETERMESSAGE hDiamMsgRcv_i,
                                                    unsigned int unResCode, HAVPCOLLECTION hCollOfFailedAVPs_i )
{

    unsigned int unCommandCode = 0;


     if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									   hDiamMsgRcv_i,&unCommandCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

    unsigned int unAppID = hDiamMsgRcv_i->oDiaHeader.unApplicationID;
    unsigned char ucFlags = hDiamMsgRcv_i->oDiaHeader.ucFlags;

    HDIAMETERMESSAGE hAnsMsg = NULL;
    DMBase_SList*	pAVPList = NULL;
    HAVP hTempAVP = NULL;

    DMBase_CreateDiameterMessage(hDiameterStackContext_io, &hAnsMsg, 1, unCommandCode, unAppID , 0, hDiamMsgRcv_i->oDiaHeader.unHopByHopID, hDiamMsgRcv_i->oDiaHeader.unEndToEndID);
    hAnsMsg->oDiaHeader.ucFlags = ucFlags;
    DMBase_SetDiaMsgRFlag(hDiameterStackContext_io, hAnsMsg,0);

	 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt = NULL;
	 if (DMBase_Retval_Success !=  DMBase_Get_AllocationContext_ForMessage(hDiameterStackContext_io,
			 hAnsMsg,&hMsgAllocCtxt)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_Get_AllocationContext_ForMessage Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }

    HAVP hAVPSessionID = NULL;
    DMBase_GetAVP(hDiameterStackContext_io, DMBASE_AVP_SESSION_ID, hDiamMsgRcv_i, &hAVPSessionID);
    if(NULL != hAVPSessionID)
    {
        t_DiamOctetString* poSessionID = (t_DiamOctetString*)hAVPSessionID->pData;
        DMBase_CreateOctetStringAVP(hDiameterStackContext_io, DMBASE_AVP_SESSION_ID,
                &hTempAVP, poSessionID->pucOctetString, poSessionID->unNumOfOctets,hMsgAllocCtxt);
        DMBase_AppendSList(hDiameterStackContext_io, &pAVPList, (void*)hTempAVP);

    }

    hTempAVP = NULL;
    DMBase_CreateUTF8StringAVP(hDiameterStackContext_io,
            DMBASE_AVP_ORIGIN_HOST,
            &hTempAVP,
            hDiameterStackContext_io->oHostName.pucOctetString,
            hDiameterStackContext_io->oHostName.unNumOfOctets ,hMsgAllocCtxt);
    DMBase_AppendSList(hDiameterStackContext_io, &pAVPList, (void*)hTempAVP);

    hTempAVP = NULL;
    DMBase_CreateUTF8StringAVP(hDiameterStackContext_io,
            DMBASE_AVP_ORIGIN_REALM,
            &hTempAVP,
            hDiameterStackContext_io->oRealmName.pucOctetString,
            hDiameterStackContext_io->oRealmName.unNumOfOctets ,hMsgAllocCtxt );
    DMBase_AppendSList(hDiameterStackContext_io, &pAVPList, (void*)hTempAVP);

    hTempAVP = NULL;
    DMBase_CreateEnumAVP(hDiameterStackContext_io, DMBASE_AVP_RESULT_CODE, &hTempAVP, unResCode,hMsgAllocCtxt);
    DMBase_AppendSList(hDiameterStackContext_io, &pAVPList, (void*)hTempAVP);

    if(NULL != hCollOfFailedAVPs_i)
    {
        hTempAVP = NULL;
        DMBase_CreateGroupedAVP(hDiameterStackContext_io,&hTempAVP,hMsgAllocCtxt, DMBASE_AVP_FAILED_AVP, 0);

        DMBase_SList* poTempAVPsList = hCollOfFailedAVPs_i;

        for(; NULL != poTempAVPsList; DMBase_SListGetNextNode(hDiameterStackContext_io, poTempAVPsList, &poTempAVPsList))
        {
            HAVP hFailedAVP = NULL;
            DMBase_SListGetNodeData(hDiameterStackContext_io, poTempAVPsList, (void**)&hFailedAVP);
            DMBase_AddAVPToGroup(hDiameterStackContext_io, hTempAVP, hFailedAVP);
        }

        DMBase_AppendSList(hDiameterStackContext_io, &pAVPList, (void*)hTempAVP);
    }

    DMBase_AddAVPCollectionToDiameterMessage(hDiameterStackContext_io, hAnsMsg, pAVPList);

    DMBase_SendMessageToPeer(hDiameterStackContext_io, hPeer, hAnsMsg);
    DMBase_DestroyDiaMessage(hDiameterStackContext_io, &hAnsMsg);
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}

