/* =====================================================================
 *
 * The MIT License (MIT)
 * Copyright 2018-2019 NXP
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

    return true;
}

////////////////////////////////////////////////////////////////////////////////
/// Returns header type as enum net_prot
////////////////////////////////////////////////////////////////////////////////
enum net_prot CFMCModel::getHeaderType( std::string protoname )
{
    std::map< std::string, enum net_prot > net_types;
    net_types[ "none" ]  	 = NET_PROT_NONE;
    net_types[ "ethernet" ]  = NET_PROT_ETH;
    net_types[ "vlan" ]      = NET_PROT_VLAN;
    net_types[ "llc_snap" ]  = NET_PROT_LLC_SNAP;
    net_types[ "mpls" ]      = NET_PROT_MPLS;
    net_types[ "arp" ]         = NET_PROT_ARP;
    net_types[ "ipv4" ]      = NET_PROT_IPV4;
    net_types[ "ipv6" ]      = NET_PROT_IPV6;
    net_types[ "ip" ]        = NET_PROT_IP;
    net_types[ "tcp" ]       = NET_PROT_TCP;
    net_types[ "udp" ]       = NET_PROT_UDP;
    net_types[ "gre" ]       = NET_PROT_GRE;
    net_types[ "pppoe" ]     = NET_PROT_PPPOE;
    net_types[ "minencap" ]  = NET_PROT_MINENCAP;
    net_types[ "sctp" ]      = NET_PROT_SCTP;
    net_types[ "dccp" ]      = NET_PROT_DCCP;
    net_types[ "ipsec_ah" ]  = NET_PROT_IPSEC_AH;
    net_types[ "ipsec_esp" ] = NET_PROT_IPSEC_ESP;
	net_types[ "otherl3" ]     = NET_PROT_USER_DEFINED_L3;
	net_types[ "otherl4" ]     = NET_PROT_USER_DEFINED_L4;
	net_types[ "otherl5" ]     = NET_PROT_USER_DEFINED_L5;
    net_types[ "shim1" ]     = NET_PROT_USER_DEFINED_SHIM1;
    net_types[ "shim2" ]     = NET_PROT_USER_DEFINED_SHIM2;
#ifdef FM_SHIM3_SUPPORT
    net_types[ "shim3" ]     = NET_PROT_USER_DEFINED_SHIM3;
#endif /* FM_SHIM3_SUPPORT */
    net_types[ "gtp" ]          = NET_PROT_GTP;
    //TODO: non existent in net_prot:
    //net_types[ "vxlan" ]      = NET_PROT_VxLAN;
    //net_types[ "esp" ]          = NET_PROT_ESP;
    //net_types[ "finalshell" ]   = NET_PROT_FINAL_SHELL;


    if ( net_types.find( protoname ) != net_types.end() ) {
        return net_types[protoname];
    }

    return NET_PROT_DUMMY_LAST;
}

