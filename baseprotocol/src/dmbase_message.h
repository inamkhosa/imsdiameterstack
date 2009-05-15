/***************************************************************************
 *   Copyright (C) 2008 by simab   *
 *   simabshahid@advancedims.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef DIAM_MESSAGE_H
#define	DIAM_MESSAGE_H

#include "dmbase_data_types.h"
#include "dmbase_dictionary.h"

#define	DMBASE_BITMASK_SET_MSG_R_FLAG		0x80
#define	DMBASE_BITMASK_CLEAR_MSG_R_FLAG		0x7F
#define	DMBASE_BITMASK_SET_MSG_P_FLAG		0x40
#define	DMBASE_BITMASK_CLEAR_MSG_P_FLAG		0xBF
#define	DMBASE_BITMASK_SET_MSG_E_FLAG		0x20
#define	DMBASE_BITMASK_CLEAR_MSG_E_FLAG		0xDF
#define	DMBASE_BITMASK_SET_MSG_T_FLAG		0x10
#define	DMBASE_BITMASK_CLEAR_MSG_T_FLAG		0xEF

#define	DMBASE_MSG_HEADER_SIZE_IN_BYTES		20


#define     DMBASE_STATE_MAINTAINED                         0
#define     DMBASE_NO_STATE_MAINTAINED                      1


///Diameter classes of errors

//Informational
#define     DIAMETER_MULTI_ROUND_AUTH                       1001

//Success
#define     DIAMETER_SUCCESS                                2001
#define     DIAMETER_LIMITED_SUCCESS                        2002
//Protocol Errors
#define DIAMETER_COMMAND_UNSUPPORTED                        3001
#define DIAMETER_UNABLE_TO_DELIVER                          3002
#define DIAMETER_REALM_NOT_SERVED                           3003
#define DIAMETER_TOO_BUSY                                   3004
#define DIAMETER_LOOP_DETECTED                              3005
#define DIAMETER_REDIRECT_INDICATION                        3006
#define DIAMETER_APPLICATION_UNSUPPORTED                    3007
#define DIAMETER_INVALID_HDR_BITS                           3008
#define DIAMETER_INVALID_AVP_BITS                           3009
#define DIAMETER_UNKNOWN_PEER                               3010

// Transient Failures
#define DIAMETER_AUTHENTICATION_REJECTED                    4001
#define DIAMETER_OUT_OF_SPACE                               4002
#define ELECTION_LOST                                       4003

// Permanent Failures
#define DIAMETER_AVP_UNSUPPORTED                            5001
#define DIAMETER_UNKNOWN_SESSION_ID                         5002
#define DIAMETER_AUTHORIZATION_REJECTED                     5003
#define DIAMETER_INVALID_AVP_VALUE                          5004
#define DIAMETER_MISSING_AVP                                5005
#define DIAMETER_RESOURCES_EXCEEDED                         5006
#define DIAMETER_CONTRADICTING_AVPS                         5007
#define DIAMETER_AVP_NOT_ALLOWED                            5008
#define DIAMETER_AVP_OCCURS_TOO_MANY_TIMES                  5009
#define DIAMETER_NO_COMMON_APPLICATION                      5010
#define DIAMETER_UNSUPPORTED_VERSION                        5011
#define DIAMETER_UNABLE_TO_COMPLY                           5012
#define DIAMETER_INVALID_BIT_IN_HEADER                      5013
#define DIAMETER_INVALID_AVP_LENGTH                         5014
#define DIAMETER_INVALID_MESSAGE_LENGTH                     5015
#define DIAMETER_INVALID_AVP_BIT_COMBO                      5016
#define DIAMETER_NO_COMMON_SECURITY                         5017


//Diameter Common Message

#define DIAMETER_COMMON_MESSAGE_ID                  0

//Diameter Message Version Number

#define DIAMETER_VERSION_NUMBER_ONE                 1

#define DIAMETER_VERSION_NUMBER                     DIAMETER_VERSION_NUMBER_ONE


t_DiamAPIReturnVal DMBase_CreateDiameterMessage( 
						HDIAMETERSTACKCONTEXT   hDiameterStackContext_io , 
						HDIAMETERMESSAGE*       phDiaMsg_o ,
						unsigned char           ucDiaMsgVersion_i,
						unsigned int            unDiaMsgCommandCode_i,  
						unsigned int            unDiaMsgApplicationID_i ,
						unsigned char 			ucFlags_i,
						unsigned int  			unHopByHopID_i,
						unsigned int  			unEndToEndID_i);

t_DiamAPIReturnVal	DMBase_DuplicateDiameterMessage(HDIAMETERSTACKCONTEXT	hDiameterStackContext_io ,
							 HDIAMETERMESSAGE hOrignalMsg_i, HDIAMETERMESSAGE* phNewMsg_o);


t_DiamAPIReturnVal DMBase_AddAVPCollectionToDiameterMessage ( HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                                          HDIAMETERMESSAGE  hDiaMsg_o ,
                                                          HAVPCOLLECTION	hCollOfAVPs_i );  

t_DiamAPIReturnVal  DMBase_ConvertDiameterMessageToRawForm ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io , 
                                                     unsigned char  **                     ppRawDiameterMsg_o , 
                                                     HDIAMETERMESSAGE       hDiaMsgHandle_i );

t_DiamAPIReturnVal  DMBase_DestroyDiaMessage       ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                     HDIAMETERMESSAGE*        phDiaMsg_i);
                                                      

t_DiamAPIReturnVal  DMBase_GetTotalSizeOfAllAVPsInCollection ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io , 
                                                     HAVPCOLLECTION	hCollOfAVPs_i, 
                                                     unsigned int* punTotalSize_o );

/********************************************
*    ProtoTypes of   DMBase                 *
*   Message Header setter functions         *
*                                           *
*********************************************
*/             

//Message Header Setters

t_DiamAPIReturnVal  DMBase_SetHopByHopID ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_o,
                                           unsigned int                unDiaMsgHopByHopID_i);
t_DiamAPIReturnVal  DMBase_SetEndToEndID ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io ,
                                           HDIAMETERMESSAGE            ohDiaMsg_o ,
                                           unsigned int                unDiaMsgEndToEndID_i );
t_DiamAPIReturnVal  DMBase_SetDiaMsgRFlag( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_o,
                                           _Bool                       bFlagValue_i);
t_DiamAPIReturnVal  DMBase_SetDiaMsgPFlag( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                           HDIAMETERMESSAGE            hDiaMsg_o ,
                                           _Bool                       bFlagValue_i);                   
t_DiamAPIReturnVal  DMBase_SetDiaMsgEFlag( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_o ,
                                           _Bool                       bFlagValue_i);
t_DiamAPIReturnVal  DMBase_SetDiaMsgTFlag( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_o ,
                                           _Bool                       bFlagValue_i);

t_DiamAPIReturnVal  DMBase_SetDiaMsgFlagOctet( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_o ,
                                           unsigned char               ucFlagsVal_i    );


t_DiamAPIReturnVal  DMBase_SetDiaMsgVersion( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_o ,
                                           unsigned char               ucVersion_i    );


t_DiamAPIReturnVal  DMBase_SetDiaMsgAppId( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE        hDiaMsg_o ,
                                           unsigned int			   unAppId_i    );

t_DiamAPIReturnVal  DMBase_SetDiaMsgLength( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE        hDiaMsg_o ,
                                           unsigned int			   unMsgLen_i    );

t_DiamAPIReturnVal  DMBase_SetDiaMsgCmdCode( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE        hDiaMsg_o ,
                                           unsigned int			   unCmdCode_i    );


//Message header getters
t_DiamAPIReturnVal  DMBase_GetHopByHopIDFromDiamMsg ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_i,
                                           unsigned int*  punDiaMsgHopByHopID_o);

t_DiamAPIReturnVal  DMBase_GetEndToEndIDFromDiamMsg ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io ,
                                           HDIAMETERMESSAGE            hDiaMsg_i ,
                                           unsigned int* punDiaMsgEndToEndID_o );

t_DiamAPIReturnVal  DMBase_GetDiaMsgFlagOctetFromDiamMsg( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_i ,
                                           unsigned char*      pucFlagsVal_o    );


t_DiamAPIReturnVal  DMBase_GetDiaMsgVersionFromDiamMsg( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_i ,
                                           unsigned char*               pucVersion_o    );


t_DiamAPIReturnVal  DMBase_GetDiaMsgAppIdFromDiamMsg( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE        hDiaMsg_i ,
                                           unsigned int*			   punAppId_o    );

t_DiamAPIReturnVal  DMBase_GetDiaMsgLengthFromDiamMsg( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE        hDiaMsg_i ,
                                           unsigned int*		punMsgLen_o    );

t_DiamAPIReturnVal  DMBase_GetDiaMsgCmdCodeFromDiamMsg( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE        hDiaMsg_i ,
                                           unsigned int*			   punCmdCode_o    );

t_DiamAPIReturnVal  DMBase_AddAVPToDiameterMessage ( HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                                        HDIAMETERMESSAGE  hDiaMsg_o ,
                                                         HAVP hAVPToAdd_i )  ;

unsigned int        DMBase_GenerateHopByHopId();
unsigned int        DMBase_GenerateEndToEndId();

//AVP Allocator Utilities
t_DiamAPIReturnVal  DMBase_AVP_Malloc ( HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                         HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io ,
										unsigned int	unAllocSize_i,
                                        void**	ppvMemBuff_o )  ;

t_DiamAPIReturnVal  DMBase_AVP_Free ( HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                       HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io ,
									  void**		ppvMemToFree_i);

t_DiamAPIReturnVal  DMBase_Get_AllocationContext_ForMessage( 
									HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                     HDIAMETERMESSAGE  hDiaMsg_i,
									HMSGALLOCATIONCONTEXT*	phMsgAllocCtxt_o);


#endif // #ifndef DIAM_MESSAGE_H
