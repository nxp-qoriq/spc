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
 * File Name : FMCTaskDef.cpp
 *
 * ===================================================================*/

#include <iomanip>
#include <cstdlib>
#include <cstring>
#include "TaskDef.h"


bool
findConseqBits( uint64_t value, uint32_t& size, uint32_t& offset )
{
    if ( 0 == value ) return false;

    bool started = false;
    uint64_t mask = (uint64_t)1 << ( sizeof( value ) * 8 - 1 );
    for ( int i = 0; i < sizeof( value ) * 8; ++i ) {   // start from the left bit
        if ( ( !started ) && ( ( value & mask ) != 0 ) ) {
            offset = i;
            started = true;
        }
        if ( ( started ) && ( ( value & mask ) == 0 ) ) {
            size = i - offset;
            started = false;
            break;
        }
        mask >>= 1;
    }

    if ( started ) {
        size = sizeof( value ) * 8 - offset;
    }

    return true;
}

CTaskDef::CTaskDef(void)
{
}

CTaskDef::~CTaskDef(void)
{
}



bool
CTaskDef::FieldExists( const std::string fullFieldName) const
{
    bool     bRet = false;
    uint32_t bitSize;
    uint32_t bitOffset;

    // Find the protocol
    std::string protocol_name = fullFieldName.substr( 0, fullFieldName.find_last_of( "." ) );
    for ( unsigned int j = 0; j < protocols.size(); ++j ) {
        if ( protocols[j].name == protocol_name ) {   // Found?
            if ( protocols[j].GetFieldProperties(
                    fullFieldName.substr( fullFieldName.find_last_of( "." ) + 1 ),
                    bitSize, bitOffset ) ) {
                bRet = true;
            }
            break;
        }
    }

    return bRet;
}


bool
CTaskDef::GetFieldProperties( const std::string fullFieldName,
                              uint32_t&         bitSize,
                              uint32_t&         bitOffset ) const
{
    bool bRet = false;

    if ( !FieldExists( fullFieldName ) ) {
        throw CGenericError( ERR_UNRECOGNIZED_FIELD, fullFieldName );
    }

    // Find the protocol and get the field's length
    std::string protocol_name = fullFieldName.substr( 0, fullFieldName.find_last_of( "." ) );
    for ( unsigned int j = 0; j < protocols.size(); ++j ) {
        if ( protocols[j].name == protocol_name ) {   // Found?
            if ( protocols[j].GetFieldProperties(
                    fullFieldName.substr( fullFieldName.find_last_of( "." ) + 1 ),
                    bitSize, bitOffset ) ) {
                bRet = true;
            }
            break;
        }
    }

    return bRet;
}


std::string
CTaskDef::getShimNoFromCustom( const std::string protocol_name ) const
{
    std::string result = "";
    unsigned int i;

    for ( i = 0; i < protocols.size(); ++i ) {
        if ( protocols[i].name == protocol_name ) {   // Found?
            break;
        }
    }
    if ( i >= protocols.size() ) {
        return result;
    }

    std::set< std::string > custom_confirms;
    protocols[i].executeCode.getConfirmCustom( custom_confirms );

    if ( custom_confirms.size() != 0 ) {
        result = *custom_confirms.begin();
    }

    return result;
}


/*Gets the size of the protocol's header according to its fields*/
bool
CProtocol::GetHeaderSize( uint32_t& size ) const
{
    uint32_t max=0;
    for (unsigned int i=0; i<fields.size(); i++)
    {
        uint32_t bitsize=0, bitOffset;
        if (!GetFieldProperties(fields[i].name, bitsize, bitOffset))
            return 0;
        if (bitsize+bitOffset > max)
            max = bitsize+bitOffset;
    }
    /*bits to bytes*/
    size = max/8;
    if (max%8 != 0)
        size++;
    return 1;
}

bool
CProtocol::FieldExists( const std::string fieldname) const
{
    std::vector< CField >::const_iterator fieldit;
    for ( fieldit = fields.begin();
          fieldit != fields.end();
          ++fieldit )
    {
        if ( fieldit->name == fieldname )
            return 1;
    }
    return 0;
}

bool
CProtocol::GetFieldProperties( const std::string fieldname,
                               uint32_t&         bitsize,
                               uint32_t&         bitoffset ) const
{
    bool bRet = true;

    bitsize   = 0;
    bitoffset = 0;

    bool     prev_was_bit           = false;
    bool     prev_last_bit_mask_one = false;
    uint32_t prev_size              = 0;

    std::vector< CField >::const_iterator fieldit;
    for ( fieldit = fields.begin();
          fieldit != fields.end();
          ++fieldit ) {

        // Only 'fixed' and 'bit' field definitions are supported
        uint32_t fsize   = std::strtoul( fieldit->size.c_str(), 0, 0 ) * 8;
        uint32_t foffset = 0;

        bool     offset_provided = !fieldit->offset.empty();
        uint32_t offset          = std::strtoul( fieldit->offset.c_str(), 0, 0 );

        if ( fieldit->type == "fixed" ) {
            if ( offset_provided ) {
                bitoffset = offset;
            }
            else {
                bitoffset  += prev_size;
            }
            bitsize     = fsize;
            prev_was_bit = false;
        }
        else if ( fieldit->type == "bit" ) {
            if ( offset_provided ) {
                bitoffset = offset;
            }
            else {
                if ( prev_last_bit_mask_one || !prev_was_bit ) {
                    bitoffset  += prev_size;
                }
            }

            bool isOK =
                findConseqBits( strtoull( fieldit->mask.c_str(), 0, 0 ),
                                bitsize, foffset );
            foffset -= sizeof(uint64_t)*8 - fsize;
            if ( !isOK ) {
                throw CGenericError( ERR_NO_BITS_FOUND );
            }
            prev_was_bit = true;

            /*If the last bit in the mask is one we move to the next byte range*/
            if ( strtoull( fieldit->mask.c_str(), 0, 0 ) & 0x1 )
                prev_last_bit_mask_one = true;
            else
                prev_last_bit_mask_one = false;
        }

        if ( fieldit->name == fieldname ) { // Is the field found?
            if ( prev_was_bit ) {           // Adjust the offset if it is the 'bit'
                bitoffset += foffset;
            }
            break;
        }
        prev_size = fsize;
    }

    if ( fieldit == fields.end() ) {    // Is it the end of the list?
        bRet = false;                   // The field was not found then
    }

    return bRet;
}

/*Return true if the previous protocol could be a layer 4 protocol*/
bool CProtocol::PossibleLayer4() const
{
    return PossibleLayer4(prevType[0]);
}

/*Return true if the specified protocol could be a layer 4 protocol*/
bool CProtocol::PossibleLayer4(ProtoType pt)
{
    if ((CProtocol::ProtocolLayer(pt) == 4) || (pt==PT_NEXT_IP))
        return true;
    return false;
}

/*Returns layer number (2/3/4) for previous protocol and 0 otherwise*/
short CProtocol::ProtocolLayer() const
{
    return ProtocolLayer(prevType[0]);
}

/*Returns layer number (2/3/4) for known protocols and 0 otherwise*/
short CProtocol::ProtocolLayer(ProtoType      pt)
{
    switch (pt) {
        case    PT_ETH:
        case    PT_LLC_SNAP:
        case    PT_VLAN:
        case    PT_PPPOE_PPP:
        case    PT_MPLS:
		case    PT_ARP:
            return 2;
        case    PT_IP:
		case    PT_IPV4:
        case    PT_IPV6:
        case    PT_OTHER_L3:
        case    PT_GRE:
        case    PT_MINENCAP:
            return 3;
        case    PT_TCP:
        case    PT_UDP:
        case    PT_IPSEC_AH:
        case    PT_IPSEC_ESP:
        case    PT_SCTP:
        case    PT_DCCP:
        case    PT_OTHER_L4:
             return 4;
		case    PT_GTP:
		case    PT_ESP:
		case    PT_OTHER_L5:
		case    PT_FINAL_SHELL:
			return 5;
    }
    return 0;
}



void CExecuteSection::deleteSection()
{
    uint32_t i, j;
    for (i = 0; i < executeExpressions.size(); i++)
    {
        CExecuteExpression executeExpression = executeExpressions[i]; //executeCode.executeSections[j];
        if (executeExpression.ifInstr.ifTrueValid)
        {
            executeExpression.ifInstr.ifTrue.deleteSection();
            executeExpression.ifInstr.ifTrueValid = false;
        }
        if (executeExpression.ifInstr.ifFalseValid)
        {
            executeExpression.ifInstr.ifFalse.deleteSection();
            executeExpression.ifInstr.ifFalseValid = false;
        }
        if (!executeExpression.switchInstr.cases.empty())
        {
            for (j=0; j < executeExpression.switchInstr.cases.size(); j++)
            {
                if (executeExpression.switchInstr.cases[j].ifCaseValid)
                {
                    executeExpression.switchInstr.cases[j].ifCase.
                        deleteSection();
                    executeExpression.switchInstr.cases[j].ifCaseValid = false;
                }
            }
            if (executeExpression.switchInstr.defaultCaseValid)
            {
                executeExpression.switchInstr.defaultCase.deleteSection();
                executeExpression.switchInstr.defaultCaseValid = false;
            }
        }       /*finished switches*/
    }           /*finished expressions*/
                /*end of function*/
}


void CTaskDef::deleteExecute()
{
    uint32_t i, j;
    for (i = 0; i < protocols.size(); i++)
    {
        CExecuteCode executeCode  = protocols[i].executeCode;
        for (j = 0; j < executeCode.executeSections.size(); j++)
        {
            CExecuteSection executeSection =  executeCode.executeSections[j];
            executeSection.deleteSection();
        }
    }
}


void
CExecuteAction::getConfirmCustom( std::set< std::string >& custom_confirms ) const
{
    if ( !confirmCustom.empty() && ( confirmCustom != "no" ) ) {
        custom_confirms.insert( confirmCustom );
    }
}


void
CExecuteIf::getConfirmCustom( std::set< std::string >& custom_confirms ) const
{
    if ( ifTrueValid ) {
        ifTrue.getConfirmCustom( custom_confirms );
    }
    if ( ifFalseValid ) {
        ifFalse.getConfirmCustom( custom_confirms );
    }
}


void
CExecuteLoop::getConfirmCustom( std::set< std::string >& custom_confirms ) const
{
    loopBody.getConfirmCustom( custom_confirms );
}


void
CExecuteCase::getConfirmCustom( std::set< std::string >& custom_confirms ) const
{
    if ( ifCaseValid ) {
        ifCase.getConfirmCustom( custom_confirms );
    }
}


void
CExecuteSwitch::getConfirmCustom( std::set< std::string >& custom_confirms ) const
{
    for ( unsigned int i = 0; i < cases.size(); ++i ) {
        cases[i].getConfirmCustom( custom_confirms );
    }

    if ( defaultCaseValid ) {
        defaultCase.getConfirmCustom( custom_confirms );
    }
}


void
CExecuteSection::getConfirmCustom( std::set< std::string >& custom_confirms ) const
{
    if ( !confirmCustom.empty() && ( confirmCustom != "no" ) ) {
        custom_confirms.insert( confirmCustom );
    }

    for ( unsigned int i = 0; i < executeExpressions.size(); ++i ) {
        executeExpressions[i].getConfirmCustom( custom_confirms );
    }
}


void
CExecuteExpression::getConfirmCustom( std::set< std::string >& custom_confirms ) const
{
    switch ( type ) {
        case IT_ACTION:
            actionInstr.getConfirmCustom( custom_confirms );
            break;
        case IT_ASSIGN:
            assignInstr.getConfirmCustom( custom_confirms );
            break;
        case IT_IF:
            ifInstr.getConfirmCustom( custom_confirms );
            break;
        case IT_INLINE:
            inlineInstr.getConfirmCustom( custom_confirms );
            break;
        case IT_SWITCH:
            switchInstr.getConfirmCustom( custom_confirms );
            break;
    }
}


void
CExecuteCode::getConfirmCustom( std::set< std::string >& custom_confirms ) const
{
    for ( unsigned int i = 0; i < executeSections.size(); ++i ) {
        executeSections[i].getConfirmCustom( custom_confirms );
    }
}
