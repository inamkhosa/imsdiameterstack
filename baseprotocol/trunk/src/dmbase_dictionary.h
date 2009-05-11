/***************************************************************************
 *   Copyright (C) 2008 by simab                                           *
 *   simabshahid@advancedims.com                                           *
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
#ifndef DIAM_DICTIONARY_H
#define	DIAM_DICTIONARY_H


#include "dmbase_data_types.h"

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>


#define	DMBASE_AVP_DATATYPE_OCTETSTRING		"OctetString"
#define	DMBASE_AVP_DATATYPE_INTEGER32		"Integer32"
#define	DMBASE_AVP_DATATYPE_INTEGER64		"Integer64"
#define	DMBASE_AVP_DATATYPE_UNSIGNED32		"Unsigned32"
#define	DMBASE_AVP_DATATYPE_UNSIGNED64		"Unsigned64"
#define	DMBASE_AVP_DATATYPE_FLOAT32			"Float32"
#define	DMBASE_AVP_DATATYPE_FLOAT64			"Float64"
#define	DMBASE_AVP_DATATYPE_IPADDRESS		"Address"
#define	DMBASE_AVP_DATATYPE_TIME			"Time"
#define	DMBASE_AVP_DATATYPE_UTF8STRING		"UTF8String"
#define	DMBASE_AVP_DATATYPE_DMIDENTITY		"DiameterIdentity"
#define	DMBASE_AVP_DATATYPE_DMURI			"DiameterURI"
#define	DMBASE_AVP_DATATYPE_ENUMERATED		"Enumerated"
#define	DMBASE_AVP_DATATYPE_GROUPED			"Grouped"

	

#define	DMBASE_AVP_DICTFPTRS_ALL_NULL		{ NULL,NULL,NULL,NULL,NULL}

#define	DMBASE_NUM_OF_OCTETS_IN_32BIT		4

#define	DMBASE_NUM_OF_OCTETS_IN_INT64		8
#define	DMBASE_NUM_OF_OCTETS_IN_UINT64		8



   






/************Dictionary related Function************/


t_DiamAPIReturnVal DMBase_PopulateDictionaryFromFile( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                             t_DiamOctetString           oXMLDictionaryFileFullPath_i );

inline	_Bool	DMBase_IsSafeToAccessDictElement(t_AVPDictionaryElement* poDiamDict_i,
												 unsigned int	unAVPCode_i);

/*******************************************
*    ProtoTypes of   DMBase                *
*   AVP Data Validator Functions           *
*                                          *
********************************************
*/

        
t_DiamAPIReturnVal  DMBase_ValidateDiamUnsigned32    ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void*                       pData_i );

t_DiamAPIReturnVal  DMBase_ValidateDiamEnum          ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void*                       pData_i );

t_DiamAPIReturnVal  DMBase_ValidateDiamUTF8String    ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void*                       pData_i );

t_DiamAPIReturnVal  DMBase_ValidateDiamOctetString   ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void*                       pData_i );

t_DiamAPIReturnVal  DMBase_ValidateDiamUnsigned64    ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void*                       pData_i );

t_DiamAPIReturnVal  DMBase_ValidateDiamIdent         ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void*                       pData_i );

t_DiamAPIReturnVal  DMBase_ValidateDiamTime          ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void*                       pData_i );

t_DiamAPIReturnVal  DMBase_ValidateDiamIPAddress     ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void*                       pData_i );

t_DiamAPIReturnVal  DMBase_ValidateDiamURI           ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void*                       pData_i );     

t_DiamAPIReturnVal  DMBase_ValidateDiamInteger32     ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void*                       pData_i );           

t_DiamAPIReturnVal  DMBase_ValidateDiamInteger64      ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void*                       pData_i );

t_DiamAPIReturnVal  DMBase_ValidateDiamFloat32       ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void*                       pData_i );

t_DiamAPIReturnVal  DMBase_ValidateDiamFloat64       ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void*                       pData_i );


/*******************************************
*    ProtoTypes of   DMBase                *
*   AVP Memory Allocator Functions         *
*                                          *
********************************************
*/

t_DiamAPIReturnVal  DMBase_AVPAllocDiamOctetString( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                    void** 			         ppData_o, 
                                                    unsigned int             unSize_i,
													HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io );

t_DiamAPIReturnVal  DMBase_AVPAllocDiamInteger32  ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                    void**                       ppData_o,
                                                    unsigned int                 unSize_i ,
													HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal  DMBase_AVPAllocDiamInteger64  ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                    void**                      ppData_o,
                                                    unsigned int                unSize_i ,
													HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal DMBase_AVPAllocDiamUnsigned32  ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                    void**                       ppData_o, 
                                                    unsigned int                 unSize_i,
													HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal DMBase_AVPAllocDiamUnsigned64  ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                    void**                       ppData_o, 
                                                    unsigned int                unSize_i,
													HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);                     

t_DiamAPIReturnVal DMBase_AVPAllocDiamFloat32     ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                    void**                       ppData_o,
                                                    unsigned int                unSize_i,
													HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal DMBase_AVPAllocDiamFloat64     ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                    void**                       ppData_o,
                                                    unsigned int                unSize_i,
													HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal DMBase_AVPAllocDiamIPAddress   ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                    void**                      ppData_o,
                                                    unsigned int                unSize_i,
													HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);


// for Time unsigned32 allocator will be used

// UTF8String Allocator function of OctetString will be used
     
     

/*******************************************
**   ProtoTypes of   DMBase                *
**  AVP Memory DeAllocator Functions       *
*                                          *
********************************************
*/
    

t_DiamAPIReturnVal  DMBase_AVPDeAllocDiamOctetString ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void **                       ppData_o,
													   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal  DMBase_AVPDeAllocDiamInteger32   ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void **                       ppData_o,
													   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal  DMBase_AVPDeAllocDiamInteger64   ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void **                       ppData_o,
													   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal  DMBase_AVPDeAllocDiamUnsigned32  ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void **                       ppData_o,
													   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal DMBase_AVPDeAllocDiamUnsigned64   ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void **                       ppData_o,
													   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);  

t_DiamAPIReturnVal DMBase_AVPDeAllocDiamFloat32      ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void **                       ppData_o,
													   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal DMBase_AVPDeAllocDiamFloat64      ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void **                       ppData_o,
													   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal DMBase_AVPDeAllocDiamIPAddress    ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                       void **                       ppData_o,
													   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);
// for Time unsigned32  DeAllocator will be used

// UTF8String DeAllocator function of OctetString will be used

/*******************************************
*   ProtoTypes of   DMBase                 *
*   Functions Returning Raw Data           *
    from  structured Data                  *
*                                          *
********************************************
*/

     
t_DiamAPIReturnVal  DMBase_GetDiamOctetStringRawData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                      void*                        pRawData_o, 
                                                      void*                        pStructData_i,
													  unsigned int				   unSizeOfRawBuff_i);

t_DiamAPIReturnVal  DMBase_GetDiamUnsigned32RawData (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                      void*                        pRawData_o, 
                                                      void*                        pStructData_i,
													  unsigned int				   unSizeOfRawBuff_i);

t_DiamAPIReturnVal  DMBase_GetDiamUnsigned64RawData ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                      void*                        pRawData_o, 
                                                      void*                        pStructData_i,
													  unsigned int				   unSizeOfRawBuff_i);

t_DiamAPIReturnVal  DMBase_GetDiamIPAddressRawData  ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                      void*                        pRawData_o, 
                                                      void*                        pStructData_i,
													  unsigned int				   unSizeOfRawBuff_i);

t_DiamAPIReturnVal  DMBase_GetDiamInteger32RawData  ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                      void*                        pRawData_o, 
                                                      void*                        pStructData_i,
													  unsigned int				   unSizeOfRawBuff_i);

t_DiamAPIReturnVal  DMBase_GetDiamInteger64RawData  ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                      void*                        pRawData_o, 
                                                      void*                        pStructData_i,
													  unsigned int				   unSizeOfRawBuff_i);

t_DiamAPIReturnVal  DMBase_GetDiamFloat32RawData    ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                      void*                        pRawData_o, 
                                                      void*                        pStructData_i,
													  unsigned int				   unSizeOfRawBuff_i);
													  
t_DiamAPIReturnVal  DMBase_GetDiamFloat64RawData    ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                      void*                        pRawData_o, 
                                                      void*                        pStructData_i,
													  unsigned int				   unSizeOfRawBuff_i);  



/*******************************************
*   ProtoTypes of   DMBase                 *
*   Functions Returning Raw Data           *
    from  structured Data                  *
*                                          *
********************************************
*/

     
t_DiamAPIReturnVal  DMBase_GetDiamOctetStringStructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                         void*                          pRawData_i, 
                                                         void**                         ppStructData_o,
                                                         unsigned int                   unRawBuffSize_i,
														 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal  DMBase_GetDiamUnsigned32StructData ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                         void*                          pRawData_i, 
                                                         void**                         ppStructData_o,
                                                         unsigned int                   unSize_i,
														 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal  DMBase_GetDiamUnsigned64StructData ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                         void*                          pRawData_i, 
                                                         void**                          ppStructData_o,
                                                         unsigned int                   unSize_i,
														 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal  DMBase_GetDiamIPAddressStructData  ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                         void*                          pRawData_i, 
                                                         void**                         ppStructData_o,
                                                         unsigned int                   unSize_i,
														 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal  DMBase_GetDiamInteger32StructData  ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                         void*                          pRawData_i, 
                                                         void**                         ppStructData_o,
                                                         unsigned int                   unSize_i,
														 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal  DMBase_GetDiamInteger64StructData  ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                         void*                          pRawData_i, 
                                                         void**                         ppStructData_o,
                                                         unsigned int                   unSize_i,
														 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal  DMBase_GetDiamFloat32StructData    ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                         void*                          pRawData_i, 
                                                         void**                         ppStructData_o,
                                                         unsigned int                   unSize_i,
														 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal  DMBase_GetDiamFloat64StructData    ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                         void*                          pRawData_i, 
                                                         void**                         ppStructData_o,
                                                         unsigned int                   unSize_i,
														 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);  


t_DiamAPIReturnVal AddElementToDictionary ( t_AVPDictionaryElement* poDestDictElem_o,
	 											   t_AVPDictionaryElement* poSrcDictElem_i );


t_DiamAPIReturnVal DMBase_DeleteDictElem ( t_AVPDictionaryElement oAVPDictElem );

t_DiamAPIReturnVal DMBase_LookupFuncPtrsFromMapTable (HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
											   t_DiamOctetString  oAVPDataType ,  
												t_AVPDictionaryFunctionPtrs*  poAVPDictFptrs_o );

t_DiamAPIReturnVal	DMBase_InitBaseProtocolDictionaryElements();
void 				ProcessAVPNode (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,xmlDocPtr poXmlDoc, xmlNodePtr poXMLNode) ;
void 				ProcessFlagActionsNode (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,xmlDocPtr poXmlDoc, xmlNodePtr poXMLNode , t_AVPDictionaryElement* poDictElem_o);
void 				ProcessFlagRulesNode (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,xmlDocPtr poXmlDoc, xmlNodePtr poXMLNode,  t_AVPDictionaryElement* poDictElem_o) ;

t_DiamAPIReturnVal	DMBase_IsTypeOctetStringOrDerived ( HDIAMETERSTACKCONTEXT    hDiameterStackContext_io,
														unsigned int	unAVPCode_i,
														_Bool*	pbIsOctstDer_o);


t_DiamAPIReturnVal	DMBase_DumpDiamOctetStringStructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                        void*                        pStructData_i, 
                                                        unsigned int                 unDataSize_i
														, FILE* pfFilePtr_i);

t_DiamAPIReturnVal	DMBase_DumpDiamInteger32StructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                        void*                        pStructData_i, 
                                                        unsigned int                 unDataSize_i
														, FILE* pfFilePtr_i);

t_DiamAPIReturnVal	DMBase_DumpDiamInteger64StructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                        void*                        pStructData_i, 
                                                        unsigned int                 unDataSize_i
														, FILE* pfFilePtr_i);


t_DiamAPIReturnVal	DMBase_DumpDiamUnsigned32StructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                        void*                        pStructData_i, 
                                                        unsigned int                 unDataSize_i
														, FILE* pfFilePtr_i);


t_DiamAPIReturnVal	DMBase_DumpDiamUnsigned64StructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                        void*                        pStructData_i, 
                                                        unsigned int                 unDataSize_i
														, FILE* pfFilePtr_i);


t_DiamAPIReturnVal	DMBase_DumpDiamFloat32StructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                        void*                        pStructData_i, 
                                                        unsigned int                 unDataSize_i
														, FILE* pfFilePtr_i);


t_DiamAPIReturnVal	DMBase_DumpDiamFloat64StructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                        void*                        pStructData_i, 
                                                        unsigned int                 unDataSize_i
														, FILE* pfFilePtr_i);


t_DiamAPIReturnVal	DMBase_DumpDiamIPAddressStructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                        void*                        pStructData_i, 
                                                        unsigned int                 unDataSize_i
														, FILE* pfFilePtr_i);



#endif //#ifndef DIAM_DICTIONARY_H
     
