#ifndef DAPPCOMMON_HELPERS_H
#define	DAPPCOMMON_HELPERS_H


#include "dmbase_avp.h"
#include "dmbase_dictionary.h"
#include "dmbase_ampswrappers.h"

#define DAPPCOMMON_TLV_RECHEADER_SIZE		(3 * sizeof(unsigned int ))
#define DAPPCOMMON_TLV_RECTYPE_INT			1
#define DAPPCOMMON_TLV_RECTYPE_OCTSTRING	2

#define DAPPCOMMON_UUID_SIZE_IN_BYTES		37//allowing for null zero at end


typedef struct	Dappcommon_tlv_header
{
	unsigned int	unRecordType;
	unsigned int	unRecordLength;
	unsigned int	unAppSpecificTag;
} t_Dappcommon_tlv_header;


typedef enum DappCommonReturnVal
{
    DappCommon_Retval_Success,
    DappCommon_Retval_Failure,
    DappCommon_Retval_IncorrectParameters,
    DappCommon_Retval_Not_Found,
    DappCommon_Retval_Not_Supported,
    DappCommon_Retval_Null_Pointer,
	DappCommon_Retval_XML_NotValid,
	DappCommon_Retval_XML_Valid,
	DappCommon_Retval_InsufficientBuffer
}	t_DappCommonReturnVal;


t_DappCommonReturnVal DappCommon_GetOctStringFromTLVBuff(unsigned char* pucTLVBuff_i,
													   unsigned int unOffsetToTLVRecd_i,
													   unsigned char ** ppucOctStrRequired_o,
													   unsigned int * punLenOfOctStr_o,
													   unsigned int * punAppSpecificTag_o);

t_DappCommonReturnVal DappCommon_GetOctStringFromTLVBuff_AddNullTerm
													(unsigned char* pucTLVBuff_i,
													   unsigned int unOffsetToTLVRecd_i,
													   unsigned char ** ppucOctStrRequired_o,
													   unsigned int * punLenOfOctStr_o,
													   unsigned int * punAppSpecificTag_o);


t_DappCommonReturnVal DappCommon_GetIntFromTLVBuff(unsigned char* pucTLVBuff_i,
													   unsigned int unOffsetToTLVRecd_i,
													   unsigned int* punIntRequired_o ,
												   _Bool	bConvToHostOrder_i,
												   unsigned int * punAppSpecificTag_o);


t_DappCommonReturnVal DappCommon_AddOctStringToTLVBuff(unsigned char ** ppucOrigBuff_io,
											   unsigned int	unOrigBuffLen_i,
											   unsigned int * punNewOrigBuffLen_o,
											   unsigned int	unOffsetInOrigBuff_i,
											   unsigned char* puchOctStrToAdd_i,
												unsigned int unSizeOfOcStr_i,
											   unsigned int  unAppSpecificTag_i);


t_DappCommonReturnVal DappCommon_AddIntToTLVBuff(unsigned char ** ppucOrigBuff_io,
											   unsigned int	unOrigBuffLen_i,
											   unsigned int * punNewOrigBuffLen_o,
											   unsigned int	unOffsetInOrigBuff_i,
											   unsigned int unIntToAdd_i,
												 _Bool	bConvToNetOrder_i,
												 unsigned int  unAppSpecificTag_i);

t_DappCommonReturnVal DappCommon_Debug_DumpEntireTLVBuffer
											  (unsigned char *pucTLVBuff_i,
											   unsigned int	unTLVBuffLen_i,
											   unsigned int	unOffsetToStartOfTLVRecs_i
											   );



void	DappCommon_Debug_PrintRawOctetString( unsigned char * pucRawOctStr_i,
										  unsigned int	unOctStrLen_i);


t_DappCommonReturnVal DappCommon_Add_AVP_Data_ToTLVBuff
										(	HAVP				hAVP_ForData_i,
											unsigned char ** 	ppucOrigBuff_io,
											unsigned int		unOrigBuffLen_i,
											unsigned int * 		punNewOrigBuffLen_o,
											unsigned int		unOffsetInOrigBuff_i
										);

t_DappCommonReturnVal DappCommon_Make_AVP_FromTLVRecord
										(	HDIAMETERSTACKCONTEXT hDiamStackContext_i,
											HAVP*				phAVP_FromTLVRec_o,
											unsigned char* 		pucTLVBuff_i,
											unsigned int		unOffsetToTLVRecd_i,
											t_DiamDictionary*	poDiamDict_i,
											HMSGALLOCATIONCONTEXT	hMsgAllocContext_io
										);


t_DappCommonReturnVal DappCommon_GetOctString_ByAppTag_FromTLVBuff
									(unsigned char* pucTLVBuff_i,
									 unsigned int	unOffsetToStartOfTLVRecs_i,
									 unsigned char ** ppucOctStrRequired_o,
									 unsigned int * punLenOfOctStr_o,
									unsigned int 	unAppSpecificTag_i,
									 unsigned int	unTLVBuffLen_i);

t_DappCommonReturnVal DappCommon_GetInt_ByAppTag_FromTLVBuff
									(unsigned char* pucTLVBuff_i,
									 unsigned int	unOffsetToStartOfTLVRecs_i,
                                     unsigned int * punIntRequired_o,
									 unsigned int 	unAppSpecificTag_i,
									 unsigned int	unTLVBuffLen_i);


t_DappCommonReturnVal DappCommon_Make_AVP_ByAppTag_FromTLVBuff
										(	HDIAMETERSTACKCONTEXT hDiamStackContext_i,
											HAVP*				phAVP_FromTLVRec_o,
											unsigned char* 		pucTLVBuff_i,
											unsigned int		unLenofTLVBuff_i,
											unsigned int		unOffsetToStartOfTLVRecs_i,
											unsigned int		unAppSpecificTag_i,
											t_DiamDictionary*	poDiamDict_i,
											_Bool				bConvToHostOrdIfInt_i,
											HMSGALLOCATIONCONTEXT	hMsgAllocContext_io
										);



t_DappCommonReturnVal DappCommon_GetIntList_ByAppTag_FromTLVBuff(unsigned char* pucTLVBuff_i,
								 unsigned int	unOffsetToStartOfTLVRecs_i,
                                                                 DMBase_SList **ppoIntList,
								 unsigned int 	unAppSpecificTag_i,
								 unsigned int	unTLVBuffLen_i);

t_DappCommonReturnVal DappCommon_GetOctStringList_ByAppTag_FromTLVBuff(unsigned char* pucTLVBuff_i,
								   unsigned int	unOffsetToStartOfTLVRecs_i,
                                                                   DMBase_SList **ppoStringList,
                                                                   unsigned int 	unAppSpecificTag_i,
                                                                   unsigned int	unTLVBuffLen_i);

t_DappCommonReturnVal DappCommon_GiveNewUUID(
								   unsigned char* pucUUIDBuff_o,
								   unsigned int	unBuffLen_i);




#endif //#ifndef DAPPCOMMON_HELPERS_H









