#ifndef __HEADER_DIAUTILITY_H__
#define __HEADER_DIAUTILITY_H__

#include "AMPS_API.h"
#include "dmbase_data_types.h"

#ifdef __cplusplus
    extern "C" {
#endif


t_DiamAPIReturnVal DMBase_GetDiamStrLength ( int*               nLength_io,
                                             t_DiamOctetString* poDiamString_i);

t_DiamAPIReturnVal DMBase_CopyDiamString ( t_DiamOctetString*  poDiamStringDest,
                                           t_DiamOctetString*  poDiamStringSource);

t_DiamAPIReturnVal DMBase_CopyDiamStringAssumeNoNullTerm ( t_DiamOctetString*  poDiamStringDest,
                                           t_DiamOctetString*  poDiamStringSource);

t_DiamAPIReturnVal DMBase_AppendDiamStringToDiamString ( t_DiamOctetString*    poDiamStringDest,
                                                         t_DiamOctetString*    poDiamStringSource);

t_DiamAPIReturnVal DMBase_AppendCharStringToDiamString ( t_DiamOctetString*    poDiamStringDest,
                                                         char*                 pcStringSource);

int                DMBase_CompareDiamString ( t_DiamOctetString*    poDiamString1,
                                              t_DiamOctetString*    poDiamString2);

t_DiamAPIReturnVal DMBase_DeleteDiamString ( t_DiamOctetString*    poDiamString);

t_DiamAPIReturnVal DMBase_IntToDiamString ( int                nNumber,
                                            t_DiamOctetString* poDiamString);

t_DiamAPIReturnVal DMBase_FloatToDiamString ( float                fNumber,
                                              t_DiamOctetString*   poDiamString);

t_DiamAPIReturnVal DMBase_BoolToDiamString ( _Bool                 bFlag,
                                             t_DiamOctetString*    poDiamString);

t_DiamAPIReturnVal DMBase_MemsetZero( void* pvMemorypointer_i,
                                      int   nSize_i);

t_DiamAPIReturnVal DMBase_CopyCharArrayToDiamString(t_DiamOctetString *poDiamStringDest ,char* pcSrcBuff);

int DMBase_CopyDiamStrToNSizedCharArray(unsigned char       *pucDest,
                                        unsigned int        unDestCharArraySize,
                                        t_DiamOctetString   oSrcDiamStr);
int DMBase_CopyNChar(unsigned char *pucDest, unsigned char *pucSrc, unsigned int unCount);
int DMBase_CopyNCharToNCharArray(unsigned char *pucDest_o, unsigned int unDestSize_i,
									unsigned char *pucSrc_i, unsigned int unCount_i);

t_DiamAPIReturnVal DMBase_IsDiamStringEmpty ( t_DiamOctetString     oDiamStringDest_i,
                                              _Bool*	pbIsStringEmpty            );



inline	unsigned int 		DMBase_Convert3BytesToUInt( unsigned char * puc3Bytes_io);
inline	t_DiamAPIReturnVal 	DMBase_ConvertUIntTo3Bytes( unsigned int unToConvert_i ,
														 unsigned char * puc3Bytes_o);
inline	t_DiamAPIReturnVal	DMBase_Convert3ByteFromHtoN_Order( unsigned char * puc3Bytes_io );
inline	t_DiamAPIReturnVal	DMBase_Convert3ByteFromNtoH_Order( unsigned char * puc3Bytes_io );
inline t_DiamAPIReturnVal 	DMBase_ConvertUIntTo3BytesAndFromHostToNetOrder(
														unsigned int unToConvert_i ,
														unsigned char * puc3Bytes_o);

inline t_DiamAPIReturnVal 	DMBase_ConvertUIntTo3BytesAndFromNetToHostOrder(
														unsigned int unToConvert_i ,
														unsigned char * puc3Bytes_o);

inline	t_DiamAPIReturnVal 	DMBase_GiveUIntInNetOrderFor3Bytes(
							unsigned char * puc3Bytes_i , unsigned int* punInt_o);



inline	t_DiamAPIReturnVal 	DMBase_GiveUIntInHostOrderFor3Bytes(
							 unsigned char * puc3Bytes_i , unsigned int* punInt_o);

t_DiamAPIReturnVal DMBase_SetStringInHashTableKey( t_DiamHashTableKey*	poHashTableKey_io,
		                                                 unsigned char*		pucStringContent_i);

t_DiamAPIReturnVal DMBase_SetIntegerInHashTableKey( t_DiamHashTableKey*	poHashTableKey_io,
		                                                 unsigned int			unContent_i);

t_DiamAPIReturnVal DMBase_HostToNetworkLongLong( HDIAMETERSTACKCONTEXT  hDiameterContext_io,
											  unsigned long long ullToConvert_i,
											  unsigned long long * pullConvertedLong_o);

t_DiamAPIReturnVal DMBase_NetworkToHostLongLong( HDIAMETERSTACKCONTEXT  hDiameterContext_io,
											  unsigned long long ullToConvert_i,
											  unsigned long long * pullConvertedLong_o);

#ifdef __cplusplus
   }
#endif


#endif /* __HEADER_DIAUTILITY_H__ */
