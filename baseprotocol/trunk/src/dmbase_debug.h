#ifndef	DMBASE_DEBUG_H
#define	DMBASE_DEBUG_H

#include "dmbase_dictionary.h"
#include "dmbase_message.h"
#include "dmbase_ampswrappers.h"
#include "dmbase_avp.h"

t_DiamAPIReturnVal	DMBase_Debug_DumpDiamMsgContents(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io ,
													 FILE*	poDumpFile_i ,
													 HDIAMETERMESSAGE hMsg_i );


t_DiamAPIReturnVal	DMBase_Debug_DumpAVPListContents(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io ,
													 FILE*	poDumpFile_i , 
													 DMBase_SList*	pListOfAVPs_i );


t_DiamAPIReturnVal	DMBase_Debug_DumpAVPContents(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io ,
												 FILE*	poDumpFile_i , 
												 HAVP hAVP_i );




int					DMBase_Debug_DumpBufferToFile ( unsigned char* pucBuff_i,
											unsigned int unBuffSize_i,
											char* pcDumpFile_i );

int					DMBase_Debug_LoadBufferFromFile ( unsigned char** ppucBuff_o,
									  unsigned int * punBuffSize_o , 
									  char* pcFileToLoad_i );

int					DMBase_Debug_DumpDictionaryToFile( char* pcDumpFileName_i,
									 t_AVPDictionaryElement* poDiamDict_i,
									   unsigned int unDictSize_i);


void				DMBase_Debug_PrintRawOctetString( unsigned char * pucRawOctStr_i,
										  unsigned int	unOctStrLen_i);


int					DMBase_Debug_Safefprintf( FILE* pfFile_i ,
											  const char* pcFormatString_i, ...);


#endif //#ifndef	DMBASE_DEBUG_H
