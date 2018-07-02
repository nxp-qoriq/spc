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
 * File Name : SPModel.cpp
 *
 * ===================================================================*/

#include <assert.h>
#include <string>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include "TaskDef.h"
#include "SPModel.h"



////////////////////////////////////////////////////////////////////////////////
/// Default constructor
////////////////////////////////////////////////////////////////////////////////
CFMCModel::CFMCModel()
{
}


////////////////////////////////////////////////////////////////////////////////
/// Create model by building the internal database
////////////////////////////////////////////////////////////////////////////////
bool CFMCModel::createModel( CTaskDef* pTaskDef )
{
    assert( pTaskDef );

    // For all engines: can be a for loop here
    createSoftParse( pTaskDef );

    return true;
}


////////////////////////////////////////////////////////////////////////////////
/// Converts SoftParse parameters provided throught XML file to the internal
/// softparse result structure
////////////////////////////////////////////////////////////////////////////////
void CFMCModel::createSoftParse( const CTaskDef* pTaskDef )
{
    const CSoftParseResult& taskSpr = pTaskDef->spr;

    if (taskSpr.softParseEnabled)
    {
        swPrs.override    = TRUE;
        swPrs.size        = taskSpr.size;
        swPrs.base        = taskSpr.base;
        swPrs.numOfLabels = taskSpr.numOfLabels;
        swPrs.p_Code      = spCode;

        // Copy SP code
        unsigned int i, j;
        memset( spCode, 0, CODE_SIZE );
        for ( i = 2*( taskSpr.base - ASSEMBLER_BASE ), j = 0; i < CODE_SIZE - 4; ++i, ++j ) {
            spCode[j] = taskSpr.p_Code[i];
        }

        // Copy SP parameters
        for ( i = 0; i < PRS_NUM_OF_HDRS; ++i ) {
            swPrs.swPrsDataParams[i] = 0;
        }

        // Copy SP label info
        for ( i = 0; i < swPrs.numOfLabels; ++i ) {
            swPrs.labelsTable[i].indexPerHdr =
                taskSpr.labelsTable[i].indexPerHdr;
            swPrs.labelsTable[i].instructionOffset =
                taskSpr.labelsTable[i].position;
            swPrs.labelsTable[i].hdr =
                getNetCommHeaderType(taskSpr.labelsTable[i].prevNames[0]);
            if ( swPrs.labelsTable[i].hdr == HEADER_TYPE_NONE ) {
                std::string shim_protocol =
                    pTaskDef->getShimNoFromCustom( taskSpr.labelsTable[i].prevNames[0] );
                if ( !shim_protocol.empty() ) { // Shim header is empty if custom protocol is not found
                    swPrs.labelsTable[i].hdr = getNetCommHeaderType( shim_protocol );
                }
                else {
                    // Header type HEADER_TYPE_NONE is not accepted as a valid value
                    throw CGenericError( ERR_UNKNOWN_PROTOCOL, taskSpr.labelsTable[i].prevNames[0] );
                }
            }
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
/// Returns NetComm header type as e_NetHeaderType
////////////////////////////////////////////////////////////////////////////////
e_NetHeaderType CFMCModel::getNetCommHeaderType( std::string protoname )
{
    std::map< std::string, e_NetHeaderType > net_types;
    net_types[ "ethernet" ]  = HEADER_TYPE_ETH;
    net_types[ "vlan" ]      = HEADER_TYPE_VLAN;
    net_types[ "llc_snap" ]  = HEADER_TYPE_LLC_SNAP;
    net_types[ "mpls" ]      = HEADER_TYPE_MPLS;
    net_types[ "ipv4" ]      = HEADER_TYPE_IPv4;
    net_types[ "ipv6" ]      = HEADER_TYPE_IPv6;
    net_types[ "ip" ]        = HEADER_TYPE_IP;
    net_types[ "tcp" ]       = HEADER_TYPE_TCP;
    net_types[ "udp" ]       = HEADER_TYPE_UDP;
    net_types[ "gre" ]       = HEADER_TYPE_GRE;
    net_types[ "pppoe" ]     = HEADER_TYPE_PPPoE;
    net_types[ "minencap" ]  = HEADER_TYPE_MINENCAP;
    net_types[ "sctp" ]      = HEADER_TYPE_SCTP;
    net_types[ "dccp" ]      = HEADER_TYPE_DCCP;
    net_types[ "ipsec_ah" ]  = HEADER_TYPE_IPSEC_AH;
    net_types[ "ipsec_esp" ] = HEADER_TYPE_IPSEC_ESP;
	net_types[ "otherl3" ]     = HEADER_TYPE_USER_DEFINED_L3;
	net_types[ "otherl4" ]     = HEADER_TYPE_USER_DEFINED_L4;
    net_types[ "shim1" ]     = HEADER_TYPE_USER_DEFINED_SHIM1;
    net_types[ "shim2" ]     = HEADER_TYPE_USER_DEFINED_SHIM2;
#ifdef FM_SHIM3_SUPPORT
    net_types[ "shim3" ]     = HEADER_TYPE_USER_DEFINED_SHIM3;
#endif /* FM_SHIM3_SUPPORT */


    if ( net_types.find( protoname ) != net_types.end() ) {
        return net_types[protoname];
    }

    return HEADER_TYPE_NONE;
}

