#ifndef	DMBASE_MSGVALIDATE_H
#define DMBASE_MSGVALIDATE_H

#include "dmbase_ampswrappers.h"
#include "dmbase_data_types.h"
#include "dmbase_message.h"

//defines

#define	DMBASE_MSG_CMD_CODE_ASR			274
#define	DMBASE_MSG_CMD_CODE_ASA			274
#define	DMBASE_MSG_CMD_CODE_ACR			271
#define	DMBASE_MSG_CMD_CODE_ACA			271
#define	DMBASE_MSG_CMD_CODE_CER			257
#define	DMBASE_MSG_CMD_CODE_CEA			257
#define	DMBASE_MSG_CMD_CODE_DWR			280
#define	DMBASE_MSG_CMD_CODE_DWA			280
#define	DMBASE_MSG_CMD_CODE_DPR			282
#define	DMBASE_MSG_CMD_CODE_DPA			282
#define	DMBASE_MSG_CMD_CODE_RAR			258
#define	DMBASE_MSG_CMD_CODE_RAA			258
#define	DMBASE_MSG_CMD_CODE_STR			275
#define	DMBASE_MSG_CMD_CODE_STA			275

#define	DMBASE_AVP_POSITION_DONT_CARE	0xFFFFFFFF	
#define	DMBASE_AVP_QUANTITY_DONT_CARE	0xFFFFFFFF	
#define	DMBASE_AVPCODE_UNINIT_PREV_VAL	0xFFFFFFFF	


//structures
typedef struct AVPValidateError
{
	unsigned int	unAVPCode;
	_Bool			bIsAVPPresent;
	unsigned int	unExpectedPosition;
	unsigned int	unActualPosition;
	unsigned int	unExpectedMinQuantity;
	unsigned int	unExpectedMaxQuantity;
	unsigned int	unActualQuantity;
} t_AVPValidateError;

typedef	struct AVPDetails
{
	unsigned int	unAVPCode;
	unsigned int	unAVPPosition;
	unsigned int	unAVPQuantity;
} t_AVPDetails;



//function prototypes
t_DiamAPIReturnVal	DMBase_ValidateAVP(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											   unsigned int	unAVPCode_i,
											   unsigned int	unExpectedPosition_i,
											   unsigned int	unExpectedMinQuantity_i,
		 									   unsigned int	unExpectedMaxQuantity_i,
											   DMBase_SList*	pListOfAVPDetails_i,
											   DMBase_SList**	ppListOFAVPErrors_o
											   );


t_DiamAPIReturnVal	DMBase_GetDetailsAboutAVPsInCollection(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
													HAVPCOLLECTION		hCollOfAVPs_i,
													DMBase_SList**	ppListAVPDetails_o);

t_DiamAPIReturnVal	DMBase_ValidateMsg_ASR( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_ASR_i,
											DMBase_SList**	ppListOfValidateErrors_o);

t_DiamAPIReturnVal	DMBase_ValidateMsg_ASA( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_ASA_i,
											DMBase_SList**	ppListOfValidateErrors_o);

t_DiamAPIReturnVal	DMBase_ValidateMsg_ACR( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_ACR_i,
											DMBase_SList**	ppListOfValidateErrors_o);

t_DiamAPIReturnVal	DMBase_ValidateMsg_ACA( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_ACA_i,
											DMBase_SList**	ppListOfValidateErrors_o);

t_DiamAPIReturnVal	DMBase_ValidateMsg_CER( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_CER_i,
											DMBase_SList**	ppListOfValidateErrors_o);

t_DiamAPIReturnVal	DMBase_ValidateMsg_CEA( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_CEA_i,
											DMBase_SList**	ppListOfValidateErrors_o);

t_DiamAPIReturnVal	DMBase_ValidateMsg_DWR( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_DWR_i,
											DMBase_SList**	ppListOfValidateErrors_o);

t_DiamAPIReturnVal	DMBase_ValidateMsg_DWA( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_DWA_i,
											DMBase_SList**	ppListOfValidateErrors_o);

t_DiamAPIReturnVal	DMBase_ValidateMsg_DPR( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_DPR_i,
											DMBase_SList**	ppListOfValidateErrors_o);

t_DiamAPIReturnVal	DMBase_ValidateMsg_DPA( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_DPA_i,
											DMBase_SList**	ppListOfValidateErrors_o);

t_DiamAPIReturnVal	DMBase_ValidateMsg_RAR( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_RAR_i,
											DMBase_SList**	ppListOfValidateErrors_o);

t_DiamAPIReturnVal	DMBase_ValidateMsg_RAA( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_RAA_i,
											DMBase_SList**	ppListOfValidateErrors_o);

t_DiamAPIReturnVal	DMBase_ValidateMsg_STR( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_STR_i,
											DMBase_SList**	ppListOfValidateErrors_o);

t_DiamAPIReturnVal	DMBase_ValidateMsg_STA( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											HDIAMETERMESSAGE	hMsg_STA_i,
											DMBase_SList**	ppListOfValidateErrors_o);

t_DiamAPIReturnVal      DMBase_GenerateProtocolErr(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io, 
                                                    HPEERTABLEENTRY hPeer, HDIAMETERMESSAGE hDiamMsgRcv_i, 
                                                    unsigned int unResCode, HAVPCOLLECTION hCollOfAVPs_i);

t_DiamAPIReturnVal      DMBase_GeneratePermanentFailure(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io, 
                                                    HPEERTABLEENTRY hPeer, HDIAMETERMESSAGE hDiamMsgRcv_i, 
                                                    unsigned int unResCode, HAVPCOLLECTION hCollOfFailedAVPs_i );


#endif// #ifndef	DMBASE_MSGVALIDATE_H
