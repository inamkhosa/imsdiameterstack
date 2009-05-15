#include "dappcommon_xmlutils.h"



t_DappCommonReturnVal DappCommon_ValidateBufferXMLFromXSD
												(unsigned char* pucXMLBuff_i,
												 unsigned int	unLenOfXMLBuff_i,
												 unsigned char*	pucXSDFilePath_i
												  )
{

	t_DappCommonReturnVal	oRetVal  = DappCommon_Retval_Failure;

	if (NULL == pucXMLBuff_i) 
	{
		printf("\n\n ERROR pucXMLBuff_i is NULL");
		oRetVal =  DappCommon_Retval_Null_Pointer;
		goto ExitMe;
	}

	if (NULL == pucXSDFilePath_i) 
	{
		printf("\n\n ERROR pucXMLBuff_i is NULL");
		oRetVal =  DappCommon_Retval_Null_Pointer;
		goto ExitMe;
	}

    xmlSchemaParserCtxtPtr	poSchemaPrsCtxt = NULL;
	xmlSchemaPtr 			poXMLSchema = NULL;
	xmlSchemaValidCtxtPtr	poSchemaValidCtxt = NULL;
	int 					nResult;
	xmlDocPtr 				pXMLdocPtr = NULL;
	

	pXMLdocPtr = xmlParseMemory ( pucXMLBuff_i,unLenOfXMLBuff_i ) ;
	if ( NULL == pXMLdocPtr )
	{
		printf("\n\n ERROR : xmlParseMemory Failed and returned NULL");
		oRetVal =  DappCommon_Retval_Failure;
		goto ExitMe;
	}
		
	poSchemaPrsCtxt = xmlSchemaNewParserCtxt ( pucXSDFilePath_i );

	if ( NULL == poSchemaPrsCtxt )
	{
		printf("\n\n ERROR : xmlSchemaNewParserCtxt Failed and returned NULL");
		oRetVal =  DappCommon_Retval_Failure;
		goto ExitMe;
	}


    poXMLSchema = xmlSchemaParse ( poSchemaPrsCtxt );

	if ( NULL == poXMLSchema )
	{
		printf("\n\n ERROR : xmlSchemaParse Failed and returned NULL");
		oRetVal =  DappCommon_Retval_Failure;
		goto ExitMe;
	}
	
	poSchemaValidCtxt = xmlSchemaNewValidCtxt ( poXMLSchema );


	if ( NULL == poSchemaValidCtxt )
	{
		printf("\n\n ERROR : xmlSchemaNewValidCtxt Failed and returned NULL");
		oRetVal =  DappCommon_Retval_Failure;
		goto ExitMe;
	}

	nResult = xmlSchemaValidateDoc ( poSchemaValidCtxt, pXMLdocPtr );

	if ( nResult == 0 )
	{
		oRetVal = DappCommon_Retval_XML_Valid;
	}
	else if ( nResult > 0 )
	{
		oRetVal = DappCommon_Retval_XML_NotValid;
	}
	else
	{
		oRetVal = DappCommon_Retval_Failure;
	}


	ExitMe:

	if (NULL != poSchemaPrsCtxt) 
	{
		xmlSchemaFreeParserCtxt ( poSchemaPrsCtxt );
		poSchemaPrsCtxt = NULL;
	}

	if (NULL != poSchemaValidCtxt) 
	{
		xmlSchemaFreeValidCtxt ( poSchemaValidCtxt );
		poSchemaValidCtxt = NULL;
	}

	if (NULL != poXMLSchema) 
	{
		xmlSchemaFree ( poXMLSchema );
		poXMLSchema = NULL;
	}

	if (NULL != pXMLdocPtr) 
	{
		xmlFreeDoc(pXMLdocPtr);
		pXMLdocPtr = NULL;
	}
	



	return oRetVal;

}
