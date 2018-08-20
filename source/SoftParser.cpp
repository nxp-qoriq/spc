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
 * File Name : SoftParser.cpp
 *
 * ===================================================================*/

#include "SoftParser.h"
#include "logger.hpp"

using namespace logger;
using namespace std;


/**
 * softparser main routine
 *
 * 	@task: Task data definition
 * 	@filePath: Soft Parser XML file
 * 	@baseAddress: Soft Parser base address in bytes: must be larger than 0x40
 * 			- TODO: not used: it is by default
 * 	@genIntermCode: Generate intermediate code
 *
 */
void softparser(CTaskDef *task, std::string filePath, unsigned int baseAddress, bool genIntermCode)
{
    CIR               newIR;
    CCode             newCode;
    std::string       fileNoExt, baseName;
    unsigned char     binary1[CODE_SIZE] = {0};
    sp_label_list_t   *labels, *labelsIter;

    //TODO: baseAddress is coming zero because must be retrieved from XML or used default
    baseAddress = task->getBaseAddresss();

    //SW parser base in instruction counts (1 word = 2 bytes): must be larger than 0x20
    //baseAddress must be 4 bytes aligned (so it is divisible by 2)
    int spBase = baseAddress / 2;

    /*init tables*/
    RA::Instance().initRA();

    /* set paths*/
    int pos    = filePath.find(".xml");
    fileNoExt  = filePath.substr(0, pos);
    pos = fileNoExt.find_last_of("/\\");
    baseName   = fileNoExt.substr(pos + 1, fileNoExt.length() - pos - 1);

    bool debug_l2 = (LOG_GET_LEVEL() >= logger::DBG2);
    bool debug_l3 = (LOG_GET_LEVEL() >= logger::DBG3);

    if (genIntermCode)
    {
        newIR.setDumpIr(baseName + ".ir");
        newCode.setDumpCode(baseName + ".code");
        newCode.setDumpAsm(baseName + ".asm");
        task->dumpSpParsed(baseName + ".parsed");
    }

    newIR.setDebug(debug_l3);

    /*Parse, create IR and create asm*/
    newIR.createIR(task);
    newCode.createCode(newIR);

    /*assemble*/
    unsigned int actualCodeSize = assemble((char*)newCode.getAsmOutput().c_str(), binary1, &labels, debug_l2, spBase);

    /*return result*/
    std::vector <CExtension> extns;
    createExtensions(extns, newCode, labels);

    task->spr.setTask(task);
    task->spr.setBaseAddresss(baseAddress);
    task->spr.setBinary(binary1, sizeof(binary1));
    task->spr.setExtensions(extns);
    task->spr.setSize(actualCodeSize);

    if (genIntermCode)
    {
    	task->spr.dumpHeader(baseName + ".h");
    	task->spr.dumpBinary(baseName + ".bin");
    }
	task->spr.dumpBlob(baseName + ".spb");

    /* Free memory*/
    while (labels)
    {
        labelsIter = labels->next_p;
        free (labels->name);
        free (labels);
        labels = labelsIter;
    }
    newIR.deleteIR();
    task->deleteExecute();
    newCode.deleteCode();
}

unsigned int assemble (char* asmResult, unsigned char* binary, sp_label_list_t **labels, bool debug, int spBase)
{
	sp_label_list_t *localLabels = NULL;
    sp_assembler_options_t asmOptions;
    asmOptions.debug_level = sp_debug_none_e;
    asmOptions.program_space_base_address = spBase;
    asmOptions.suppress_warnings = 0;
    asmOptions.warnings_are_errors = 0;

    sp_error_code_t errorS =
        sp_assemble(asmResult, binary, &localLabels, &asmOptions, NULL);
    *labels = localLabels;
    if (errorS != sp_ok_e)
    {
        if (errorS == sp_max_instructions_exceeded_e)
            throw CGenericError (ERR_TOO_MANY_INSTR);
        else
        {
            std::string temp = "Code didn't assemble correctly. ";
            if (debug)
                temp += sp_get_error_string(errorS);
            throw CGenericError (ERR_INTERNAL_SP_ERROR, temp);
        }
    }
    /*Last 4 instructions must be zero*/
    else if(binary[CODE_SIZE-1] || binary[CODE_SIZE-2] ||
            binary[CODE_SIZE-3] || binary[CODE_SIZE-4] ||
            binary[CODE_SIZE-5] || binary[CODE_SIZE-6] ||
            binary[CODE_SIZE-7] || binary[CODE_SIZE-8])
        throw CGenericError (ERR_TOO_MANY_INSTR,
                     "Generated code should be 1-4 instructions shorter. ");

    return asmOptions.result_code_size;
}

void createExtensions (std::vector<CExtension> &extns, CCode code, sp_label_list_t *labels)
{
	sp_label_list_t *labelsIter;
    for (unsigned int i=0; i<code.protocolsCode.size(); i++)
    {
        labelsIter = labels;
        while (labelsIter) {
            if (labelsIter->name == code.protocolsCode[i].label.name)
            {
                CExtension extension (code.protocolsCode[i].protocol.prevType,
                                      code.protocolsCode[i].protocol.prevproto,
                                      code.protocolsCode[i].protocol,
                                      labelsIter->byte_position);
                extns.push_back(extension);
                break;
            }
            labelsIter = labelsIter->next_p;
        }
        if (!labelsIter)
            throw CGenericError(ERR_INTERNAL_SP_ERROR, "Missing label");
    }
}

uint32_t CTaskDef::getBaseAddresss()
{
	if (program.empty())
		return SP_ASSEMBLER_BASE_ADDRESS;

	//TODO: ONLY one bytecode sections is supported for now:
	//  so take offset from the first section
	return program[0].swOffset;
}

void CTaskDef::enableProtocolOnInit(std::string protocol_name, std::string parser_name)
{
	for ( int i = 0; i < protocols.size(); i++ ) {
        if ( protocols[i].name == protocol_name ) {
        	protocols[i].parsers.push_back(parser_name);
        	break;
        }
	}
}

/*
   Detect CPU Endianness
   returns 1 if CPU is LE, 0 in case of BE
*/
int detectEndianness()
{
	unsigned int x = 1;
	char *c = (char*)&x;
	return (int)*c;
}

CSoftParseResult::CSoftParseResult()
{
	cpuLE = detectEndianness();
}

void CSoftParseResult::setTask(CTaskDef *taskdef)
{
	task = taskdef;
}

void CSoftParseResult::setBinary(const uint8_t binary1[], const uint32_t size)
{
    for (unsigned int i = 0; i < size; i++)
        this->p_Code[i] = binary1[i];
}

void CSoftParseResult::setBaseAddresss(const uint16_t baseAddress)
{
    this->base = baseAddress;
}

void CSoftParseResult::setSize(const uint32_t size1)
{
    this->size = size1;
}

void CSoftParseResult::setExtensions(const std::vector <CExtension> extns)
{
    this->numOfLabels = 0;
    for (unsigned int i=0; i<extns.size(); i++)
    {
        for ( unsigned int j = 0; j < extns[i].prevType.size(); j++ )
        {
            CExtension ext = extns[i];
            ext.prevType.clear();
            ext.prevType.push_back( extns[i].prevType[j] );
            ext.prevNames.clear();
            ext.prevNames.push_back( extns[i].prevNames[j] );
            this->labelsTable.push_back( ext );
            this->numOfLabels++;
        }
    }
}

void CSoftParseResult::dumpHeader(std::string path) const
{
    std::ofstream dumpFile;
    dumpFile.open(path.c_str(), std::ios::out);
    dumpFile.setf(std::ios::uppercase);
    unsigned int i,j;

    dumpFile << "#define SOFT_PARSE_CODE                                    \\"
    << endl  << "{                                                          \\"
    << endl  << "    TRUE,                               /*Override*/       \\"
    << endl  << "    " << size
             << ",                               /*Size (in bytes)*/           \\"
    << endl  << "    " << "0x" << std::hex << base
             << ",                               /*Base (in bytes)*/           \\"
    << endl  << "    (uint8_t *)&(uint8_t[]){            /*Code*/           \\"
    << endl;

    for (j=0, i = (base - ASSEMBLER_BASE); ( i < CODE_SIZE - 4 ) && ( j < size ); i++, j++)
    {
        if (j%10 == 0 || i == (base - ASSEMBLER_BASE))
            dumpFile << "        ";
        dumpFile << "0x";
        if (p_Code[i]<0x10)
            dumpFile << "0";
        dumpFile << std::hex << (int)p_Code[i];
        if (i+1!=CODE_SIZE)
            dumpFile << ",";
        if ( ( (j+1)%10==0 ) || ( i+1==CODE_SIZE ) || ( j+1 >= size ) )
            dumpFile << " \\" << std::endl;
    }

    dumpFile << "    },                                                     \\"
    << endl  << "    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  /*swPrsParams*/    \\"
    << endl  << "     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  /*swPrsParams*/    \\"
    << endl  << "     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  /*swPrsParams*/    \\"
    << endl  << "     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  /*swPrsParams*/    \\"
    << endl  << "    " << (int)numOfLabels
             <<      ",                                  /*numOfLabels*/    \\"
    << endl  << "    {                                                      \\"
    << endl;

    for (i = 0; i < numOfLabels; i++)
    {
        dumpFile << "        {                                                  \\"
        << endl  << "            " << "0x" << hex << (2 * labelsTable[i].position)
                 <<              ",                       /*offset*/         \\"
        << endl  << "            " << externProtoName(labelsTable[i].prevType[0])
                 <<              ",           /*prevProto*/      \\"
        << endl  << "            " << (int)labelsTable[i].indexPerHdr
                 <<              ",                           /*index*/          \\"
        << endl  << "        },                                                 \\"
        << endl;
    }

    dumpFile << "    },                                                     \\"
    << endl  << "}" << endl;

	dumpFile.close();
}

void CSoftParseResult::dumpBinary(std::string path) const
{
    std::ofstream dumpFile;
    dumpFile.open(path.c_str(), std::ios::out | std::ios::binary);
	unsigned int i,j;

    for (j=0, i = (base - ASSEMBLER_BASE); ( i < CODE_SIZE - 4 ) && ( j < size ); i++, j++)
    {
        dumpFile.write((char*)&p_Code[i], 1);
    }

	dumpFile.close();
}

/*Find the protocol name which should be used in the softpare.h file*/
std::string CSoftParseResult::externProtoName(const ProtoType type)
{
    std::map< ProtoType, std::string >::iterator protocolsLabelsIterator;
    std::map< ProtoType, std::string> protocolsLabels;

    protocolsLabels[PT_NONE]      = "NET_PROT_NONE";
    protocolsLabels[PT_ETH]       = "NET_PROT_ETH";
    protocolsLabels[PT_LLC_SNAP]  = "NET_PROT_SNAP";
    protocolsLabels[PT_VLAN]      = "NET_PROT_VLAN";
    protocolsLabels[PT_PPPOE_PPP] = "NET_PROT_PPPOE";
    protocolsLabels[PT_MPLS]      = "NET_PROT_MPLS";
	protocolsLabels[PT_ARP]		  = "NET_PROT_ARP";
	protocolsLabels[PT_IP]        = "NET_PROT_IP";
    protocolsLabels[PT_IPV4]      = "NET_PROT_IPV4";
    protocolsLabels[PT_IPV6]      = "NET_PROT_IPV6";
    protocolsLabels[PT_GRE]       = "NET_PROT_GRE";
    protocolsLabels[PT_MINENCAP]  = "NET_PROT_MINENCAP";
    protocolsLabels[PT_TCP]       = "NET_PROT_TCP";
    protocolsLabels[PT_UDP]       = "NET_PROT_UDP";
    protocolsLabels[PT_IPSEC_AH]  = "NET_PROT_IPSEC_AH";
    protocolsLabels[PT_IPSEC_ESP] = "NET_PROT_IPSEC_ESP";
    protocolsLabels[PT_SCTP]      = "NET_PROT_SCTP";
    protocolsLabels[PT_DCCP]      = "NET_PROT_DCCP";
    protocolsLabels[PT_OTHER_L3]  = "NET_PROT_USER_DEFINED_L3";
    protocolsLabels[PT_OTHER_L4]  = "NET_PROT_USER_DEFINED_L4";
	protocolsLabels[PT_OTHER_L5]  = "NET_PROT_USER_DEFINED_L5";
	protocolsLabels[PT_GTP]       = "NET_PROT_GTP";
	protocolsLabels[PT_ESP]       = "NET_PROT_UDP_ENC_ESP";
	//TODO: not supported in mc net header net.h:
	//protocolsLabels[PT_FINAL_SHELL]  = "HEADER_TYPE_FINAL_SHELL";
    //protocolsLabels[PT_VxLAN]      = "NET_PROT_VxLAN";

	//TODO: should find correct protocol layer (for generated header file)
    protocolsLabels[PT_SP_PROTOCOL] = "NET_PROT_USER_DEFINED_L2";

    protocolsLabelsIterator = protocolsLabels.find(type);
    if (protocolsLabelsIterator == protocolsLabels.end())
        throw CGenericError (ERR_INTERNAL_SP_ERROR, "Unrecognized Protocol");
    else
        return protocolsLabels[type];
}

//----------------------------------------------------------------------
//    Blob generation

/* BLOB magic number */
#define BLOB_MAGIC_ID			0x53504243	/* SPBC */
#define BLOB_VER				0x01000000

#define SP_HW_REV_MAJOR		3
#define SP_HW_REV_MINOR		2


/*
 * There are 3 SP memories available:
Bit 31: load to WRIOP INGRESS parser memory
Bit 30: load to WRIOP EGRESS parser memory
Bit 29: load to AIOP parser memory
 */
#define LOAD_IN_WRIOP_INGRESS		0x80000000
#define LOAD_IN_WRIOP_EGRESS		0x40000000
#define LOAD_IN_AIOP				0x20000000


/* Profile configuration */
#define ENABLE_ON_WRIOP_INGRESS		0x80
#define ENABLE_ON_WRIOP_EGRESS		0x40
#define ENABLE_ON_AIOP_INGRESS		0x20
#define ENABLE_ON_AIOP_EGRESS		0x10


/* Available HW Accelerators */
#define HW_ACCEL_WRIOP_INGRESS		"wriop_ingress"
#define HW_ACCEL_WRIOP_EGRESS		"wriop_egress"
#define HW_ACCEL_AIOP_INGRESS		"aiop_ingress"
#define HW_ACCEL_AIOP_EGRESS		"aiop_egress"
#define HW_ACCEL_AIOP				"aiop"


#define PARAM_TYPE_READ_ONLY		0x01


#define BLOB_BASE_PROTO_INVALID					0
#define BLOB_BASE_PROTO_ETHERNET				1
#define BLOB_BASE_PROTO_LLC_SNAP				2
#define BLOB_BASE_PROTO_VLAN					3
#define BLOB_BASE_PROTO_PPPoE_PPP				4
#define BLOB_BASE_PROTO_MPLS					5
#define BLOB_BASE_PROTO_ARP						6
#define BLOB_BASE_PROTO_IP						7
#define BLOB_BASE_PROTO_IPv4					8
#define BLOB_BASE_PROTO_IPv6					9
#define BLOB_BASE_PROTO_GRE						10
#define BLOB_BASE_PROTO_MINENC					11
#define BLOB_BASE_PROTO_OTHER_LAYER_3			12
#define BLOB_BASE_PROTO_TCP						13
#define BLOB_BASE_PROTO_UDP						14
#define BLOB_BASE_PROTO_IPSEC					15
#define BLOB_BASE_PROTO_SCTP					16
#define BLOB_BASE_PROTO_DCCP					17
#define BLOB_BASE_PROTO_OTHER_LAYER_4			18
#define BLOB_BASE_PROTO_GTP						19
#define BLOB_BASE_PROTO_ESP						20
#define BLOB_BASE_PROTO_VxLAN					21
#define BLOB_BASE_PROTO_LAYER_5					30
#define BLOB_BASE_PROTO_FINAL_HEADER			31
#define BLOB_BASE_PROTO_FIRST_HEADER_IN_FRAME	256


static inline uint16_t SwapUint16(uint16_t val)
{
    return (uint16_t)(((val & 0x00FF) <<  8) |
                      ((val & 0xFF00) >>  8));
}

static inline uint32_t SwapUint32(uint32_t val)
{
    return (uint32_t)(((val & 0x000000FF) << 24) |
                      ((val & 0x0000FF00) <<  8) |
                      ((val & 0x00FF0000) >>  8) |
                      ((val & 0xFF000000) >> 24));
}

uint16_t CSoftParseResult::cpu_to_le16(uint16_t val16)
{
	if (cpuLE)
		return val16;
	return SwapUint16(val16);
}

uint32_t CSoftParseResult::cpu_to_le32(uint32_t val32)
{
	if (cpuLE)
		return val32;
	return SwapUint32(val32);
}

void CSoftParseResult::blob_write_cpu_to_le16(std::ofstream &dumpFile, uint16_t val16)
{
	uint16_t le16 = cpu_to_le16(val16);
	dumpFile.write((char*)&le16, 2);
}

void CSoftParseResult::blob_write_cpu_to_le32(std::ofstream &dumpFile, uint32_t val32)
{
	uint32_t le32 = cpu_to_le32(val32);
	dumpFile.write((char*)&le32, 4);
}

void CSoftParseResult::blob_write8(std::ofstream &dumpFile, uint8_t val)
{
	dumpFile.write((char*)&val, 1);
}

uint32_t CSoftParseResult::blob_get_base_protocol(const ProtoType prevType)
{
	uint32_t base_proto = BLOB_BASE_PROTO_INVALID;

	//TODO: update protocols
	switch (prevType)
	{
	case PT_NONE:
		base_proto = BLOB_BASE_PROTO_FIRST_HEADER_IN_FRAME;
		break;
	case PT_SP_PROTOCOL:
		base_proto = BLOB_BASE_PROTO_INVALID;
		break;
	case PT_ETH:
		base_proto = BLOB_BASE_PROTO_ETHERNET;
		break;
	case PT_LLC_SNAP:
		base_proto = BLOB_BASE_PROTO_LLC_SNAP;
		break;
	case PT_VLAN:
		base_proto = BLOB_BASE_PROTO_VLAN;
		break;
	case PT_PPPOE_PPP:
		base_proto = BLOB_BASE_PROTO_PPPoE_PPP;
		break;
	case PT_MPLS:
		base_proto = BLOB_BASE_PROTO_MPLS;
		break;
	case PT_ARP:
		base_proto = BLOB_BASE_PROTO_ARP;
		break;
	case PT_IP:
		base_proto = BLOB_BASE_PROTO_IP;
		break;
	case PT_IPV4:
		base_proto = BLOB_BASE_PROTO_IPv4;
		break;
	case PT_IPV6:
		base_proto = BLOB_BASE_PROTO_IPv6;
		break;
	case PT_OTHER_L3:
		base_proto = BLOB_BASE_PROTO_OTHER_LAYER_3;
		break;
	case PT_GRE:
		base_proto = BLOB_BASE_PROTO_GRE;
		break;
	case PT_MINENCAP:
		base_proto = BLOB_BASE_PROTO_MINENC;
		break;
	case PT_TCP:
		base_proto = BLOB_BASE_PROTO_TCP;
		break;
	case PT_UDP:
		base_proto = BLOB_BASE_PROTO_UDP;
		break;
	//TODO
	case PT_IPSEC_AH:
		base_proto = BLOB_BASE_PROTO_IPSEC;
		break;
	//TODO
	case PT_IPSEC_ESP:
		base_proto = BLOB_BASE_PROTO_IPSEC;
		break;
	case PT_SCTP:
		base_proto = BLOB_BASE_PROTO_SCTP;
		break;
	case PT_DCCP:
		base_proto = BLOB_BASE_PROTO_DCCP;
		break;
	case PT_OTHER_L4:
		base_proto = BLOB_BASE_PROTO_OTHER_LAYER_4;
		break;
	case PT_GTP:
		base_proto = BLOB_BASE_PROTO_GTP;
		break;
	case PT_ESP:
		base_proto = BLOB_BASE_PROTO_ESP;
		break;
	case PT_VxLAN:
		base_proto = BLOB_BASE_PROTO_VxLAN;
		break;
	case PT_NEXT_ETH:
	case PT_NEXT_IP:
	case PT_NEXT_TCP:
	case PT_NEXT_UDP:
		base_proto = BLOB_BASE_PROTO_INVALID;
		break;
	case PT_OTHER_L5:
		base_proto = BLOB_BASE_PROTO_LAYER_5;
		break;
	case PT_FINAL_SHELL:
		base_proto = BLOB_BASE_PROTO_FINAL_HEADER;
		break;
	case PT_RETURN:
	case PT_END_PARSE:
		base_proto = BLOB_BASE_PROTO_INVALID;
		break;
	default:
		base_proto = BLOB_BASE_PROTO_INVALID;
		break;
	}
	return base_proto;
}

void CSoftParseResult::blob_write_file_header(std::ofstream &dumpFile)
{
	int sect_size;
	uint32_t sp_rev;

	//DEFAULT SoftParser Rev:
	uint32_t sp_rev_major = SP_HW_REV_MAJOR;
	uint32_t sp_rev_minor = SP_HW_REV_MINOR;

	if (task->soc_name.compare(0, 3, "LS2") == 0) {
		sp_rev_major = 3;
		sp_rev_minor = 1;
	}
	else if (task->soc_name.compare(0, 3, "LX2") == 0) {
		sp_rev_major = 3;
		sp_rev_minor = 2;
	}
	sp_rev = (sp_rev_major << 16) | sp_rev_minor;

	/* Calculate Section Size */
	sect_size = 16;

	/* MAGIC ID (LE) */
	blob_write_cpu_to_le32(dumpFile, BLOB_MAGIC_ID);

	/* BLOB_VER (LE) */
	blob_write_cpu_to_le32(dumpFile, BLOB_VER);

	/* SP_HW_REV (LE) */
	blob_write_cpu_to_le32(dumpFile, sp_rev);

	/* Length (4) - Blob length. Should be a multiple of 4.
	 * Now the length is unknown so write zero. */
	blob_write_cpu_to_le32(dumpFile, 0);

	//Update blob size
	blob_size += sect_size;
}

void CSoftParseResult::blob_write_blob_name(std::ofstream &dumpFile, const char *name)
{
	int i, sect_size, len, pad_len;

	len = (int)strlen(name);
	if (len % 4) {
		pad_len = 4 * (len / 4 + 1) - len;
	} else {
		pad_len = 0;
	}

	/* Calculate Section Size */
	sect_size = 16 +				/* Size (4) + TAG (4) + Reserved (8) */
				len + pad_len;		/* name length + pad */

	/* Section Size */
	blob_write_cpu_to_le32(dumpFile, sect_size);

	/* TAG */
	blob_write_cpu_to_le32(dumpFile, 0);

	/* Reserved (8) */
	blob_write_cpu_to_le32(dumpFile, 0);
	blob_write_cpu_to_le32(dumpFile, 0);

	/* Blob Name */
	for (i = 0; i < len; i++)
	{
		blob_write8(dumpFile, name[i]);
	}
	for (i = 0; i < pad_len; i++)
		blob_write8(dumpFile, 0);

	//Update blob size
	blob_size += sect_size;
}

void CSoftParseResult::blob_write_bytecode(std::ofstream &dumpFile)
{
	int i, sect_size, pad_size;
	uint32_t flags;

	//TODO: this prototype version works with only 1 Soft Parser protocol
	//TODO: change here when decide how to include multiple SP in blob:
	//		multiple SP in same section or in different sections
	//		for now: load in all where are enabled
	flags = 0;
	//TODO: this prototype version loads code in ALL parsers for now
	flags |= (LOAD_IN_WRIOP_INGRESS | LOAD_IN_WRIOP_EGRESS | LOAD_IN_AIOP);

	if (size % 4) {
		pad_size = 4 * (size / 4 + 1) - size;
	} else {
		pad_size = 0;
	}

	/* Calculate Section Size */
	sect_size = 16 +				/* Size (4) + TAG (4) + flags (4) + offset (4) */
				size + pad_size;	/* bytecode size + pad */

	/* Section Size */
	blob_write_cpu_to_le32(dumpFile, sect_size);

	/* TAG */
	blob_write_cpu_to_le32(dumpFile, 1);

	/* flags */
	blob_write_cpu_to_le32(dumpFile, flags);

	/* offset: Should be 4 bytes aligned
	 * Must be a multiple of 4 in the [0x40, 0xFFC) range */
	blob_write_cpu_to_le32(dumpFile, base);

	/* bytecode */
    for (i = 0; i < size; i++)
    	blob_write8(dumpFile, p_Code[i]);
	for (i = 0; i < pad_size; i++)
		blob_write8(dumpFile, 0);

	//Update blob size
	blob_size += sect_size;
}

void CSoftParseResult::blob_write_sp_profiles(std::ofstream &dumpFile)
{
	int sect_size = 0, profile_cfg, i, j;
	uint8_t	flags, nameSize;
	char profile_name[9];

	/* Count the number of profiles configured */
	profile_cfg = 0;
	for (i = 0; i < numOfLabels; i++)
	{
		uint32_t baseProtocol = blob_get_base_protocol(labelsTable[i].prevType[0]);

		//skip invalid protocols
		if (baseProtocol == BLOB_BASE_PROTO_INVALID)
			continue;

		profile_cfg++;
	}

	/* Calculate Section Size */
	sect_size = 16 +				/* Size (4) + TAG (4) + Reserved (8) */
				16 * profile_cfg;	/* profile cfg */

	/* Section Size */
	blob_write_cpu_to_le32(dumpFile, sect_size);

	/* TAG */
	blob_write_cpu_to_le32(dumpFile, 2);

	/* Reserved (8) */
	blob_write_cpu_to_le32(dumpFile, 0);
	blob_write_cpu_to_le32(dumpFile, 0);

	/* Profiles configuration */
	for (i = 0; i < numOfLabels; i++)
	{
		uint32_t baseProtocol = blob_get_base_protocol(labelsTable[i].prevType[0]);

		//skip invalid protocols
		if (baseProtocol == BLOB_BASE_PROTO_INVALID)
			continue;

		/* Profiles cfg - name (8) */
		memset(profile_name, 0, 9);

		nameSize = strlen(labelsTable[i].protocol.name.c_str());
		if (nameSize > 8) {
			CGenericError::printWarning("Protocol name is too long (maximum limit is 8 characters)");
			nameSize = 8;
		}
		memcpy(profile_name, labelsTable[i].protocol.name.c_str(), nameSize);
		for (j = 0; j < 8; j++)
			blob_write8(dumpFile, profile_name[j]);

		/* Profiles cfg - flags (1) */
		flags = 0;
	    std::vector< std::string >::const_iterator it;
	    for ( it = labelsTable[i].protocol.parsers.begin();
	          it != labelsTable[i].protocol.parsers.end();
	          ++it )
	    {
	    	std::string parser = *it;

	        if (parser.compare(HW_ACCEL_WRIOP_INGRESS) == 0) {
	        	flags |= ENABLE_ON_WRIOP_INGRESS;
	        }
	        else if (parser.compare(HW_ACCEL_WRIOP_EGRESS) == 0) {
	        	flags |= ENABLE_ON_WRIOP_EGRESS;
	        }
	        else if (parser.compare(HW_ACCEL_AIOP_INGRESS) == 0) {
	        	flags |= ENABLE_ON_AIOP_INGRESS;
	        }
	        else if (parser.compare(HW_ACCEL_AIOP_EGRESS) == 0) {
	        	flags |= ENABLE_ON_AIOP_EGRESS;
	        }
			else if (parser.compare(HW_ACCEL_AIOP) == 0) {
				flags |= (ENABLE_ON_AIOP_INGRESS | ENABLE_ON_AIOP_EGRESS);
			}
	    }
		blob_write8(dumpFile, flags);

		/* Reserved (1) */
		blob_write8(dumpFile, 0);

		/* Seq start entry point (2) */
		blob_write_cpu_to_le16(dumpFile, (uint16_t)(2 * labelsTable[i].position));

		/* Base protocol (4) */
		blob_write_cpu_to_le32(dumpFile, baseProtocol);
	}

	//Update blob size
	blob_size += sect_size;
}

void CSoftParseResult::blob_write_ex_array(std::ofstream &dumpFile)
{
	int sect_size = 0, i, j, nameSize;
	int paramNo = task->parameters.size();
	int parSize, entry_size, param_size = 0, pad_len;
	uint8_t	flags;
	bool zeroValue;
	char name[9];

	//Do not generate parameters section if there is no parameter
	if (paramNo == 0)
		return;

	//calculate sp parameters size
	param_size = 0;
	for (i = 0; i < paramNo; i++) {

		/* calculate entry-size */
		entry_size = 	2 +  /* entry-size (2) */
						2 +  /* param-offset (2) */
						2 +  /* param-size (2) */
						1 +  /* flags (1) */
						1 +  /* Reserved (1) */
						8 +  /* profile-name (8) */
						8;   /* param-name (8) */

		zeroValue = true;
		for (j = 0; j < PRS_PARAM_SIZE; j++) {
			if (task->parameters[i].value[j] != 0) {
				zeroValue = false;
				break;
			}
		}
		if (!zeroValue) {
			parSize = task->parameters[i].size;
			if (parSize % 4) {
				pad_len = 4 * (parSize / 4 + 1) - parSize;
			} else {
				pad_len = 0;
			}
			entry_size += (parSize + pad_len);
		}

		param_size += entry_size;
	}

	/* Calculate Section Size */
	sect_size = 16 +			/* Size (4) + TAG (4) + Reserved (8) */
				param_size;		/* parameters passed to soft parser */

	/* Section Size */
	blob_write_cpu_to_le32(dumpFile, sect_size);

	/* TAG = 3 */
	blob_write_cpu_to_le32(dumpFile, 3);

	/* Reserved (8) */
	blob_write_cpu_to_le32(dumpFile, 0);
	blob_write_cpu_to_le32(dumpFile, 0);

	//sp parameters
	for (i = 0; i < paramNo; i++) {

		/* calculate entry-size */
		entry_size = 	2 +  /* entry-size (2) */
						2 +  /* param-offset (2) */
						2 +  /* param-size (2) */
						1 +  /* flags (1) */
						1 +  /* Reserved (1) */
						8 +  /* profile-name (8) */
						8;   /* param-name (8) */

		zeroValue = true;
		for (j = 0; j < PRS_PARAM_SIZE; j++) {
			if (task->parameters[i].value[j] != 0) {
				zeroValue = false;
				break;
			}
		}
		if (!zeroValue) {
			parSize = task->parameters[i].size;
			if (parSize % 4) {
				pad_len = 4 * (parSize / 4 + 1) - parSize;
			} else {
				pad_len = 0;
			}
			entry_size += (parSize + pad_len);
		}

		/* entry-size (2) */
		blob_write_cpu_to_le16(dumpFile, (uint16_t)entry_size);

		/* param-offset (2) */
		blob_write_cpu_to_le16(dumpFile, (uint16_t)task->parameters[i].offset);

		/* param-size (2) */
		blob_write_cpu_to_le16(dumpFile, (uint16_t)task->parameters[i].size);

		/* flags (1) */
		flags = 0;
		if (task->parameters[i].readOnly)
			flags |= PARAM_TYPE_READ_ONLY;
		blob_write8(dumpFile, flags);

		/* Reserved (1) */
		blob_write8(dumpFile, 0);

		/* profile-name (8) */
		memset(name, 0, 9);

		nameSize = strlen(task->parameters[i].protocol.c_str());
		if (nameSize > 8) {
			CGenericError::printWarning("Protocol name is too long (maximum limit is 8 characters)");
			nameSize = 8;
		}
		memcpy(name, task->parameters[i].protocol.c_str(), nameSize);
		for (j = 0; j < 8; j++)
			blob_write8(dumpFile, name[j]);

		/* param-name (8) */
		memset(name, 0, 9);

		nameSize = strlen(task->parameters[i].name.c_str());
		if (nameSize > 8) {
			CGenericError::printWarning("Parameter name is too long (maximum limit is 8 characters)");
			nameSize = 8;
		}
		memcpy(name, task->parameters[i].name.c_str(), nameSize);
		for (j = 0; j < 8; j++)
			blob_write8(dumpFile, name[j]);

		/* value (n*4) */
		if (!zeroValue) {
			for (j = 0; j < parSize; j++)
				blob_write8(dumpFile, task->parameters[i].value[j]);
			for (j = 0; j < pad_len; j++)
				blob_write8(dumpFile, 0);
		}
	}

	//Update blob size
	blob_size += sect_size;
}

void CSoftParseResult::blob_write_blob_size(std::ofstream &dumpFile)
{
	dumpFile.seekp(12);
	blob_write_cpu_to_le32(dumpFile, blob_size);
}

void CSoftParseResult::dumpBlob(std::string path)
{
    std::ofstream dumpFile;
    dumpFile.open(path.c_str(), std::ios::out | std::ios::binary);

    blob_size = 0;

    /* File header */
    blob_write_file_header(dumpFile);

    /* Blob name */
    blob_write_blob_name(dumpFile, task->name.c_str());

    /* Bytecode */
    blob_write_bytecode(dumpFile);

    /* SP Profiles */
    blob_write_sp_profiles(dumpFile);

    /* Examination array */
    blob_write_ex_array(dumpFile);

    /* Blob size */
    blob_write_blob_size(dumpFile);

	dumpFile.close();
}

//    end of Blob generation
//----------------------------------------------------------------------

