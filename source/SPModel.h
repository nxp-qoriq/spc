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
 * File Name : SPModel.h
 *
 * ===================================================================*/

#ifndef SPMODEL_H
#define SPMODEL_H

#include <string>
#include <vector>
#include <set>
#include <map>

#include "spc.h"

const unsigned int MAX_CODE_SIZE = MAX_SP_CODE_SIZE;


// Forward declarations
class CTaskDef;


////////////////////////////////////////////////////////////////////////////////
/// FMC PCD model and database class
////////////////////////////////////////////////////////////////////////////////
class CFMCModel
{
public:
    /// Default constructor
    CFMCModel();

    /// Create model by building the internal database
    bool createModel( CTaskDef* m_pTaskDef );

    // Service functions
    static enum net_prot  getHeaderType( std::string protoname );


public:

    t_PrsSwParams 		swPrs;
    unsigned char      spCode[MAX_CODE_SIZE];

private:
    void     createSoftParse( const CTaskDef* pTaskDef );

};

#endif // SPMODEL_H
