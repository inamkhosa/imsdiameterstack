#ifndef DAPPCOMMON_XMLUTILS_H
#define	DAPPCOMMON_XMLUTILS_H

#include <libxml/xmlversion.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <libxml/debugXML.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>

#include "dappcommon_helpers.h"

t_DappCommonReturnVal DappCommon_ValidateBufferXMLFromXSD
												(unsigned char* pucXMLBuff_i,
												 unsigned int	unLenOfXMLBuff_i,
												 unsigned char*	pucXSDFilePath_i
												  );



#endif //#ifndef DAPPCOMMON_XMLUTILS_H
