/* =====================================================================
 *
 * The MIT License (MIT)
 * Copyright 2018 NXP
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * File Name : ConfigReader.cpp
 *
 * ===================================================================*/

#include <string.h>
#include "ConfigReader.h"

#include "logger.hpp"
using namespace logger;


ConfigReader::ConfigReader ()
{
    spParameterOffset = 0;
}

// Aid function to retrieve XML element's attribute
std::string ConfigReader::getAttr( xmlNodePtr pNode, const char* attr )
{
    char* pAttr = (char*)xmlGetProp( pNode, (const xmlChar*)attr );
    std::string retStr;
    retStr.clear();

    if (pAttr != NULL)
    {
        char* pTmpAttr = pAttr;
        while (*pTmpAttr != '\0')
        {
            retStr.insert(retStr.end(), *pTmpAttr);
            pTmpAttr++;
        }
        xmlFree(pAttr);
    }

    return (retStr.size() != 0) ? retStr : "";
}

void ConfigReader::checkUnknownAttr ( xmlNodePtr pNode, int num, ...)
{
    va_list listPointer;
    _xmlAttr * attributes = pNode->properties;
    std::set <const xmlChar*, MyXMLCharComparator> allowedAttr;

    va_start(listPointer, num);
    for(signed int i = 0; i < num; i++ )
        allowedAttr.insert((const xmlChar*)va_arg(listPointer, const xmlChar*));
    va_end(listPointer);

    if (allowedAttr.empty())
        return;

    while (pNode->properties)
    {
        if (allowedAttr.find(pNode->properties->name) ==
            allowedAttr.end())
            CGenericErrorLine::printWarning(WARN_UNKNOWN_ATTRIBUTE,
                xmlGetLineNo(pNode), (char*)pNode->properties->name,
                (char*)pNode->name);
        pNode->properties=pNode->properties->next;
    }
    pNode->properties=attributes;
}

void ConfigReader::setTaskData( CTaskDef* pTaskData )
{
    task = pTaskData;
}

void ConfigReader::parseConfig( std::string filename )
{
    // LibXML preparations
    xmlInitParser();
    LIBXML_TEST_VERSION;
    xmlSetStructuredErrorFunc( &error, errorFuncHandler );
    xmlKeepBlanksDefault(0);

    // Parse the XML file
    LOG( DBG1 ) << ind(2) << "Start XML parsing of config file: " << filename << std::endl;
    xmlDocPtr doc = xmlParseFile( filename.c_str() );

    if ( !error.getErrorMsg().empty() ) {
        throw CGenericError( ERR_XML_PARSE_ERROR1, error.getErrorMsg() );
    }

    if ( 0 == doc ) {   // Was the parsing successful?
        throw CGenericError( ERR_CANT_OPEN_FILE, filename );
    }

    // Get the root node
    xmlNodePtr cur = xmlDocGetRootElement( doc );
    if ( 0 == cur ) {   // Is the document empty?
        xmlFreeDoc( doc );
        throw CGenericError( ERR_EMPTY_DOCUMENT, filename );
    }

    // Is the document of the correct type?
    if ( xmlStrcmp( cur->name, (const xmlChar *)"spconfig" ) ) {
        xmlFreeDoc( doc );
        throw CGenericError( ERR_EMPTY_DOCUMENT, filename );
    }

    // Make sure we process the right node
    if ( xmlStrcmp( cur->name, (const xmlChar*)"spconfig" ) ) {
        throw CGenericError( ERR_WRONG_TYPE1, (char*)cur->name );
    }

    // Parse children nodes
    cur = cur->xmlChildrenNode;
    while ( 0 != cur ) {
        // soc
        if ( !xmlStrcmp( cur->name, (const xmlChar*)"soc" ) ) {
        	parseSoc( cur );
        }
        // memorymap
        else if ( !xmlStrcmp( cur->name, (const xmlChar*)"memorymap" ) ) {
        	parseMemorymap( cur );
        }
        // device
        else if ( !xmlStrcmp( cur->name, (const xmlChar*)"device" ) ) {
            parseDevice( cur );
        }
        // parameters
        else if ( !xmlStrcmp( cur->name, (const xmlChar*)"parameters" ) ) {
        	parseParameters( cur );
        }
        // comment
        else if ( !xmlStrcmp( cur->name, (const xmlChar*)"comment" ) ||
                  !xmlStrcmp( cur->name, (const xmlChar*)"text" )  ) {
        }
        // other
        else {
            CGenericError::printWarning(WARN_UNEXPECTED_NODE,(char*)cur->name);
        }

        cur = cur->next;
    }

    xmlFreeDoc( doc );
    xmlCleanupParser();

    LOG( DBG1 ) << ind(-2) << "Done" << std::endl;
    LOG( DBG1 ) << std::endl;
}

void ConfigReader::parseSoc( xmlNodePtr pNode )
{
    // Make sure we process the right node
    if ( xmlStrcmp( pNode->name, (const xmlChar*)"soc" ) ) {
        throw CGenericError( ERR_WRONG_TYPE1, (char*)pNode->name );
    }

    LOG( DBG1 ) << ind(2) << "Parsing of XML node 'soc' named: '"
                << getAttr( pNode, "name" )
                << "' ... " << std::endl;

    // Get known attributes
    task->soc_name = getAttr(pNode, "name");
    task->soc_rev = getAttr(pNode, "rev");

    checkUnknownAttr(pNode, 2, "name", "rev");


    LOG( DBG1 ) << ind(-2) << "Done" << std::endl;
}


void ConfigReader::parseMemorymap(xmlNodePtr pNode)
{
    // Make sure we process the right node
    if ( xmlStrcmp( pNode->name, (const xmlChar*)"memorymap" ) ) {
        throw CGenericError( ERR_WRONG_TYPE1, (char*)pNode->name );
    }

    LOG( DBG1 ) << ind(2) << "Parsing of XML node 'memorymap': '"
                << "' ... " << std::endl;

    // Parse children nodes
    xmlNodePtr cur = pNode->xmlChildrenNode;
    while ( 0 != cur ) {

        if ( !xmlStrcmp( cur->name, (const xmlChar*)"bytecode" ) ) {
        	CCodeSection code;
        	parseBytecode( &code, cur );
            task->program.push_back(code);
        }
        // comment
        else if ( !xmlStrcmp( cur->name, (const xmlChar*)"comment" ) ||
                  !xmlStrcmp( cur->name, (const xmlChar*)"text" )  ) {
        }
        // other
        else {
            CGenericErrorLine::printWarning(WARN_UNEXPECTED_NODE,
                                          xmlGetLineNo(cur), (char*)cur->name);
        }

        cur = cur->next;
    }
}

void ConfigReader::parseBytecode(CCodeSection* codeSection, xmlNodePtr pNode )
{
    // Make sure we process the right node
    if ( xmlStrcmp( pNode->name, (const xmlChar*)"bytecode" ) ) {
        throw CGenericError( ERR_WRONG_TYPE1, (char*)pNode->name );
    }

    LOG( DBG1 ) << ind(2) << "Parsing of XML node 'bytecode' at offset: '"
                << getAttr( pNode, "offset" )
                << "' ... " << std::endl;

    // Get known attributes
    std::string sOffset = getAttr(pNode, "offset");
    if (sOffset.length() == 0 || sOffset.compare("auto") == 0) {
    	//first section BASE ADDRESS:
    	codeSection->swOffset = ASSEMBLER_BASE;

    	//TODO: for next sections should calculate available offset according to previous sections size

    }
    else {
    	codeSection->swOffset = strtol(sOffset.c_str(), NULL, 16);
    }

	//TODO: check the different sections base addresses don't overlap

    checkUnknownAttr(pNode, 1, "offset");

    // Parse children nodes
    xmlNodePtr cur = pNode->xmlChildrenNode;
    while ( 0 != cur ) {

        if ( !xmlStrcmp( cur->name, (const xmlChar*)"load-on-parser" ) ) {
        	//TODO: support several bytecode sections
        	CGenericErrorLine::printWarning(WARN_UNSUPPORTED, xmlGetLineNo(cur), (char*)cur->name);

        	//TODO: support also for: <load-on-parser name="all" />
        	//		if is missing then default is: "all"
        }
        else if ( !xmlStrcmp( cur->name, (const xmlChar*)"load-protocol" ) ) {
        	//TODO: support several bytecode sections
        	CGenericErrorLine::printWarning(WARN_UNSUPPORTED, xmlGetLineNo(cur), (char*)cur->name);

        	//TODO: check the protocols loaded are defined in NetPDL protocol definition file
        }
        // comment
        else if ( !xmlStrcmp( cur->name, (const xmlChar*)"comment" ) ||
                  !xmlStrcmp( cur->name, (const xmlChar*)"text" )  ) {
        }
        // other
        else {
            CGenericErrorLine::printWarning(WARN_UNEXPECTED_NODE,
                                          xmlGetLineNo(cur), (char*)cur->name);
        }

        cur = cur->next;
    }
}

void ConfigReader::parseParameters(xmlNodePtr pNode )
{
    // Make sure we process the right node
    if ( xmlStrcmp( pNode->name, (const xmlChar*)"parameters" ) ) {
        throw CGenericError( ERR_WRONG_TYPE1, (char*)pNode->name );
    }

    LOG( DBG1 ) << ind(2) << "Parsing of XML node 'parameters' '"
                << "' ... " << std::endl;

    // Parse children nodes
    xmlNodePtr cur = pNode->xmlChildrenNode;
    while ( 0 != cur ) {

        if ( !xmlStrcmp( cur->name, (const xmlChar*)"parameter" ) ) {
        	CParameter param;
        	parseParameter( &param, cur );
            task->parameters.push_back(param);
        }
        // comment
        else if ( !xmlStrcmp( cur->name, (const xmlChar*)"comment" ) ||
                  !xmlStrcmp( cur->name, (const xmlChar*)"text" )  ) {
        }
        // other
        else {
            CGenericErrorLine::printWarning(WARN_UNEXPECTED_NODE,
                                          xmlGetLineNo(cur), (char*)cur->name);
        }

        cur = cur->next;
    }
}

void ConfigReader::parseParameter(CParameter* param, xmlNodePtr pNode )
{
    // Make sure we process the right node
    if ( xmlStrcmp( pNode->name, (const xmlChar*)"parameter" ) ) {
        throw CGenericError( ERR_WRONG_TYPE1, (char*)pNode->name );
    }

    LOG( DBG1 ) << ind(2) << "Parsing of XML node 'parameter' named: '"
                << getAttr( pNode, "name" )
                << "' ... " << std::endl;

    // Get known attributes
    param->name = getAttr(pNode, "name");
    param->protocol = getAttr(pNode, "protocol");

    std::string sOffset = getAttr(pNode, "offset");
    if (sOffset.length() == 0 || sOffset.compare("auto") == 0) {
    	param->offset = spParameterOffset;
    }
    else {
    	if (sOffset.compare(0, 2, "0x") == 0)
    		param->offset = strtol(sOffset.c_str(), NULL, 16);
    	else
    		param->offset = strtol(sOffset.c_str(), NULL, 10);
    }
    spParameterOffset = param->offset;

    std::string sSize = getAttr(pNode, "size");
	if (sSize.compare(0, 2, "0x") == 0)
		param->size = strtol(sSize.c_str(), NULL, 16);
	else
		param->size = strtol(sSize.c_str(), NULL, 10);
	spParameterOffset += param->size;

	//TODO: check parameters don't overlap

	std::string sType = getAttr(pNode, "type");
	if (sType.length() == 0 || sType.compare("read-write") == 0)
		param->readOnly = false;
	else if (sType.compare("read-only") == 0)
		param->readOnly = true;
	else
		throw CGenericErrorLine(ERR_INVALID_ATTRIBUTE_VALUE, pNode->line, "type", "parameter");

	std::string sValue = getAttr(pNode, "value");
	memset(param->value, 0, PRS_PARAM_SIZE);
	if (sValue.length() == 0 || sValue.compare("auto") == 0) {
		memset(param->value, 0, PRS_PARAM_SIZE);
	}
	else {
		if (sValue.compare(0, 2, "0x") == 0) {
			for (int i = 0; i < (sValue.size()-2)/2; i++) {
				std::string str = sValue.substr(2 + i*2, 2);
				param->value[i] = strtol(str.c_str(), NULL, 16);
			}
		}
		else {
			param->value[0] = strtol(sValue.c_str(), NULL, 10);
		}
	}

    checkUnknownAttr(pNode, 6, "name", "protocol", "offset", "size", "value", "type");
}

/////////////////////////////////////////////////////////////////////////////
// CPDLReader::parseDevice
// Process the 'device' node of the NetPDL
/////////////////////////////////////////////////////////////////////////////
void ConfigReader::parseDevice( xmlNodePtr pNode )
{
    // Make sure we process the right node
    if ( xmlStrcmp( pNode->name, (const xmlChar*)"device" ) ) {
        throw CGenericError( ERR_WRONG_TYPE1, (char*)pNode->name );
    }

    checkUnknownAttr(pNode, 0);

    // Parse children nodes
    xmlNodePtr cur = pNode->xmlChildrenNode;
    while ( 0 != cur ) {
        // parser
        if ( !xmlStrcmp( cur->name, (const xmlChar*)"parser" ) ) {
        	parseDevParser( cur );
        }
        // comment
        else if ( !xmlStrcmp( cur->name, (const xmlChar*)"comment" ) ||
                  !xmlStrcmp( cur->name, (const xmlChar*)"text" )  ) {
        }
        // other
        else {
            CGenericErrorLine::printWarning(WARN_UNEXPECTED_NODE,
                                          xmlGetLineNo(cur), (char*)cur->name);
        }

        cur = cur->next;
    }
}

static std::string availableParsers[] = {
		HW_ACCEL_WRIOP_INGRESS,
		HW_ACCEL_WRIOP_EGRESS,
		HW_ACCEL_AIOP_INGRESS,
		HW_ACCEL_AIOP_EGRESS,
		HW_ACCEL_AIOP,
		""
};

void ConfigReader::parseDevParser(xmlNodePtr pNode)
{
	// Make sure we process the right node
    if ( xmlStrcmp( pNode->name, (const xmlChar*)"parser" ) ) {
        throw CGenericError( ERR_WRONG_TYPE1, (char*)pNode->name );
    }

    checkUnknownAttr(pNode, 1, "name");

    // Get known attributes
    std::string parser_name = getAttr(pNode, "name");

	if (parser_name == "")
		throw CGenericErrorLine(ERR_MISSING_ATTRIBUTE, pNode->line, "name", "parser");

    int i = 0;
    bool validParser = false;
    while (availableParsers[i].length() > 0) {
    	if (parser_name.compare(availableParsers[i]) == 0) {
    		validParser = true;
    		break;
    	}
    	i++;
    }
    if (!validParser)
    	throw CGenericErrorLine(ERR_INVALID_ATTRIBUTE_VALUE, pNode->line, "name", "parser");

    // Parse children nodes
    xmlNodePtr pCrtNode = pNode->xmlChildrenNode;
    while ( 0 != pCrtNode ) {
        // engine
        if ( !xmlStrcmp( pCrtNode->name, (const xmlChar*)"enable-on-init" ) ) {

            // Get known attributes
            std::string protocol_name = getAttr(pCrtNode, "protocol");
            checkUnknownAttr(pCrtNode, 1, "protocol");

            //check the protocol is defined in NetPDL file
            if (task->findSpProtocol(protocol_name))
            	task->enableProtocolOnInit(protocol_name, parser_name);
            else
            	throw CGenericErrorLine(ERR_UNDEFINED_PROTOCOL, pCrtNode->line, protocol_name);
        }
        // comment
        else if ( !xmlStrcmp( pCrtNode->name, (const xmlChar*)"comment" ) ||
                  !xmlStrcmp( pCrtNode->name, (const xmlChar*)"text" )  ) {
        }
        // other
        else {
            CGenericErrorLine::printWarning(WARN_UNEXPECTED_NODE,
                                          xmlGetLineNo(pCrtNode), (char*)pCrtNode->name);
        }

        pCrtNode = pCrtNode->next;
    }
}

