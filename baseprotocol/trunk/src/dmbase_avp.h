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
#ifndef	DIAM_AVP_H
#define DIAM_AVP_H

#include "dmbase_data_types.h"
#include "dmbase_dictionary.h"


#define     DMBASE_AVP_HDR_SIZE_WITHOUT_VNDR_ID_IN_BYTES    8
#define     DMBASE_AVP_HDR_SIZE_WITH_VNDR_ID_IN_BYTES       12
#define     DMBASE_AVP_DEFAULT_ERR_CODE                     -1
#define     DMBASE_VENDOR_ID_SIZE_IN_BYTES                   4

#define     DMBASE_AVP_V_BIT_IS_SET         				0x80
#define     DMBASE_AVP_V_BIT_SET_MASK       				0x80
#define     DMBASE_AVP_P_BIT_IS_SET         				0x20
#define     DMBASE_AVP_P_BIT_SET_MASK       				0x20
#define     DMBASE_AVP_M_BIT_IS_SET         				0x40
#define     DMBASE_AVP_M_BIT_SET_MASK       				0x40
#define		DMBASE_AVP_VENDOR_ID_NOT_USED					0xFFFFFFFF




t_DiamAPIReturnVal  DMBase_CreateAVP	 (HDIAMETERSTACKCONTEXT  hDiameterStackContext_io ,
										   HAVP*         		  phAVPHandle_o ,
										   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io,
										   unsigned int           unAVPCode_i ,
										   void*                  pvAVPData_i,
										   unsigned int 	      unDataSizeInBytes_i,
										   unsigned char		  ucFlags_i
										  );

//AVP Header Setters
t_DiamAPIReturnVal  DMBase_SetVendorIdInAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_o ,
                                unsigned int            unVendorID_i);

t_DiamAPIReturnVal  DMBase_SetAVPCodeInAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_o ,
                                unsigned int            unAVPCode_i);

t_DiamAPIReturnVal  DMBase_SetFlagsOctetInAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_o ,
                                unsigned char           ucFlags_i);

t_DiamAPIReturnVal  DMBase_SetAVPLengthInAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_o ,
                                unsigned int            unAVPLen_i);

t_DiamAPIReturnVal  DMBase_SetAVPData(
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_o ,
                                void*            		pvAVPData_i);


//AVP Header Getters

t_DiamAPIReturnVal  DMBase_GetAVPData(
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_i ,
                                void**            		ppvAVPData_o);

t_DiamAPIReturnVal  DMBase_GetVendorIdFromAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_o ,
                                unsigned int*           punVendorID_o);

t_DiamAPIReturnVal  DMBase_GetAVPCodeFromAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_o ,
                                unsigned int*            punAVPCode_o);

t_DiamAPIReturnVal  DMBase_GetFlagsOctetFromAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_o ,
                                unsigned char*          pucFlags_o);

t_DiamAPIReturnVal  DMBase_GetAVPLengthFromAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_o ,
                                unsigned int*            punAVPLen_o);


t_DiamAPIReturnVal  DMBase_SetAVPVendorID  (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                            HAVP           hAVPHandle_o ,
                                            unsigned int                unVendorID_i);

t_DiamAPIReturnVal  DMBase_CreateGroupedAVP(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io ,
                                            HAVP*          phGroupedAVPHandle_o,
											HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io,
                                            unsigned int                unGroupedAVPCode_i,
											unsigned char		  ucFlags_i);

t_DiamAPIReturnVal  DMBase_AddAVPToGroup   (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                            HAVP           hGroupedAVP_o ,
                                            HAVP           hAVPToAdd_i );

t_DiamAPIReturnVal  DMBase_DestroyAVP      (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                            HAVP*           phAVP_i);


t_DiamAPIReturnVal  DMBase_DestroyAVPCollection  (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                            HAVPCOLLECTION*   phCollOfAVPs_io);

t_DiamAPIReturnVal  DMBase_ConvertAVPCollectionToRawForm ( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io ,
                                                     unsigned char  ** ppRawDiameterMsg_o ,
                                                     HAVPCOLLECTION		hCollOfAVPs_i,
													 unsigned int unoffsetToWriteBuff_i);


t_DiamAPIReturnVal	DMBase_ConvertAVPToRaw ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io ,
											 HAVP hAVPToConvert_i,
											 unsigned char** ppRawBuff_o ,
											 unsigned int unOffsetToWriteBuff_i );

t_DiamAPIReturnVal	DMBase_CreateIntAVP(HDIAMETERSTACKCONTEXT hDiameterStackContext, unsigned int unAVPCode, HAVP* phIntAVP, int nIntValue,HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal DMBase_CreateInteger64AVP(HDIAMETERSTACKCONTEXT 	hDiameterStackContext,
											 unsigned int 			unAVPCode,
											 HAVP* 					phInteger64AVP,
											 long long 				llInteger64Value,
											 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal	DMBase_CreateUnsigned32AVP(HDIAMETERSTACKCONTEXT hDiameterStackContext, unsigned int unAVPCode, HAVP* phUnsigned32AVP,
                                        unsigned int unUnsigned32Value,HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal DMBase_CreateUnsigned64AVP(HDIAMETERSTACKCONTEXT hDiameterStackContext, unsigned int unAVPCode, HAVP* phUnsigned64AVP, unsigned long long unUnsigned64Value,
												HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal	DMBase_CreateEnumAVP(HDIAMETERSTACKCONTEXT hDiameterStackContext, unsigned int unAVPCode, HAVP* phEnumAVP,  int nEnumValue,HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal	DMBase_CreateOctetStringAVP(HDIAMETERSTACKCONTEXT hDiameterStackContext, unsigned int unAVPCode, HAVP* phOctetstringAVP,
                                        unsigned char* pucOctetString, unsigned int unSize,
										HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal	DMBase_CreateUTF8StringAVP(HDIAMETERSTACKCONTEXT hDiameterStackContext, unsigned int unAVPCode, HAVP* phUTF8StringAVP,
                                        unsigned char* pucUTF8String, unsigned int unSize,
										HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal DMBase_CreateIPAddressAVP(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
										unsigned int unAVPCode_i, HAVP* phIPAddrAVP_o,
                                        unsigned char* pucIPString_i, unsigned short usIPType_i,
                                        HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal	DMBase_GetAVP(HDIAMETERSTACKCONTEXT, unsigned int unAVPCode, HDIAMETERMESSAGE hDiamMsg_i ,HAVP* phAVP_io);

t_DiamAPIReturnVal	DMBase_GetAVPCountInCollection(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
					 unsigned int unAVPCode_i, HAVPCOLLECTION hCollOfAVPs_i ,
						unsigned int* punAVPCount_o );

t_DiamAPIReturnVal	DMBase_GetAVPFromGroup(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, unsigned int unAVPCode, HAVP hGroupedAVP ,HAVP* phAVP_io);

t_DiamAPIReturnVal	DMBase_GetAVPList(HDIAMETERSTACKCONTEXT, unsigned int unAVPCode, HDIAMETERMESSAGE hDiamMsg_i , DMBase_SList** ppListOfAVPs);

t_DiamAPIReturnVal	DMBase_DuplicateAVP(HDIAMETERSTACKCONTEXT, HAVP hOrignalAVP, HAVP* phNewAVP);

t_DiamAPIReturnVal	DMBase_AddAVPToCollection(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
											  HAVPCOLLECTION*	phCollOfAVPs_o,
											  HAVP hAVPToAdd_i);

int					DMBase_CallBack_FreeAVPNodeInAVPList(void** r_ppvData);

#endif // #ifndef DIAM_AVP_H
