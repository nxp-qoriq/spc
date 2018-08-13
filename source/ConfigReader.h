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
 * File Name : ConfigReader.h
 *
 * ===================================================================*/

#ifndef CFGREADER_H
#define CFGREADER_H

#include <libxml/parser.h>
#include "TaskDef.h"

class ConfigReader {
public:
	ConfigReader();
    void setTaskData( CTaskDef* pTaskData );
    void parseConfig( std::string filename );

    void parseSoc     	   (xmlNodePtr pNode );
    void parseMemorymap	   (xmlNodePtr pNode);
    void parseBytecode     (CCodeSection* engine, xmlNodePtr pNode );
    void parseParameters   (xmlNodePtr pNode );
    void parseParameter    (CParameter* param, xmlNodePtr pNode );
    void parseDevice       (xmlNodePtr pNode );
    void parseDevEngine    (xmlNodePtr pNode );

protected:
    static std::string getAttr( xmlNodePtr pNode, const char* attr );
    static void checkUnknownAttr( xmlNodePtr pNode, int num, ... );

private:
    CTaskDef* task;
    CGenericError error;
    uint32_t  spParameterOffset;
};

#endif // CFGREADER_H