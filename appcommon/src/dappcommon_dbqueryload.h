#ifndef DAPPCOMMON_DBQUERYLOAD_H
#define	DAPPCOMMON_DBQUERYLOAD_H

#include "dmbase_data_types.h"
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "dappcommon_helpers.h"


typedef	struct	Dappcommon_DBQueryMap
{
	unsigned int		unQueryID;
	t_DiamOctetString	oQueryName;
	t_DiamOctetString	oQueryString;
	_Bool				bIsInit;
}t_Dappcommon_DBQueryMap;





t_DappCommonReturnVal ProcessQueryInfoNode (xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										t_Dappcommon_DBQueryMap*	poDBQueryMapArray_o,
										unsigned int	unDBMapArrSize_i
										 );



t_DappCommonReturnVal DappCommon_LoadDBQueryConfigFromFile(
										t_DiamOctetString oDBQueryConfigFile_i,
										t_Dappcommon_DBQueryMap*	poDBQueryMapArray_o,
										unsigned int	unDBMapArrSize_i
										);



									 


#endif //#ifndef DAPPCOMMON_DBQUERYLOAD_H
