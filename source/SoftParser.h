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
 * File Name : SoftParser.h
 *
 * ===================================================================*/

#ifndef SP_H
#define SP_H

#include <string>

#include "Utils.h"
#include "spc.h"

/* Available HW Accelerators */
#define HW_ACCEL_WRIOP_INGRESS		"wriop_ingress"
#define HW_ACCEL_WRIOP_EGRESS		"wriop_egress"
#define HW_ACCEL_AIOP_INGRESS		"aiop_ingress"
#define HW_ACCEL_AIOP_EGRESS		"aiop_egress"
#define HW_ACCEL_AIOP				"aiop"

class CSoftParserTask;
class CExtension;

typedef enum ProtoType {
	PT_INVALID,
    PT_ETH,
    PT_LLC_SNAP,
    PT_VLAN,
    PT_VxLAN,
    PT_PPPOE_PPP,
    PT_MPLS,
	PT_ARP,
	PT_IP,
    PT_IPV4,
    PT_IPV6,
    PT_OTHER_L3,
    PT_GRE,
    PT_MINENCAP,
    PT_TCP,
    PT_UDP,
    PT_IPSEC_AH,
    PT_IPSEC_ESP,
    PT_SCTP,
    PT_DCCP,
    PT_OTHER_L4,
	PT_GTP,
	PT_ESP,
    PT_NEXT_ETH,
	PT_NEXT_IP,
	PT_NEXT_TCP,
    PT_NEXT_UDP,
	PT_OTHER_L5,
	PT_FINAL_SHELL,
    PT_RETURN,
    PT_END_PARSE,
    PT_NONE,   			/* Used to invoke SP before HW Parser: before Ethernet */
    PT_SP_PROTOCOL,		/* Another Soft Parser Protocol */
} ProtoType;

class CParameter
{
public:
	CParameter() :  offset(0), size(0), readOnly(false) 	{};

public:
	std::string		name;
	std::string		protocol;
	uint32_t		offset;
	uint32_t		size;
	bool			readOnly;
	uint8_t			value[PRS_PARAM_SIZE];
};

class CSoftParserResult
{
public:
    uint16_t                 base;                      /**< SW parser base bytes
                                                             must be larger than 0x40*/
    uint32_t                 size;                      /**< SW parser code size in bytes */
    uint8_t                  p_Code[MAX_SP_CODE_SIZE];  /**< SW parser code */
    std::vector<CExtension>  labelsTable;               /**< SW parser labels table */

public:
    CSoftParserResult();

    void setSize        (const uint32_t baseAddress1);
    void setBinary      (const uint8_t binary[], const uint32_t size);
    void setBaseAddresss(const uint16_t baseAddress);
    void setExtensions  (const std::vector <CExtension> extns);

};

class CCodeSection
{
public:
	CCodeSection() :  swOffset(SP_ASSEMBLER_BASE_ADDRESS) 	{};

public:
	uint32_t		swOffset;
	std::vector< std::string > parsers;
	std::vector< std::string > protocols;

	CSoftParserResult          spr;
};

class CSoftParserBlob
{
private:
    CSoftParserTask 		*task;
    bool					 cpuLE;		/**< TRUE if CPU is LE */

public:
    CSoftParserBlob();
    virtual ~CSoftParserBlob();

    void setTask(CSoftParserTask *taskdef);

#if 0
    void dumpHeader     (std::string path) const;
	void dumpBinary     (std::string path) const;
    std::string externProtoName (const ProtoType type);
#endif

    //----------------------------------------------------------------------
    //    Blob generation

private:
    uint32_t 	blob_size;

	uint16_t cpu_to_le16(uint16_t val16);
    uint32_t cpu_to_le32(uint32_t val32);
    void blob_write8(std::ofstream &dumpFile, uint8_t val);
    void blob_write_cpu_to_le16(std::ofstream &dumpFile, uint16_t val16);
    void blob_write_cpu_to_le32(std::ofstream &dumpFile, uint32_t val32);

    uint32_t blob_get_base_protocol(const ProtoType prevType);

    void blob_write_file_header(std::ofstream &dumpFile);
    void blob_write_blob_name(std::ofstream &dumpFile, const char *name);
    void blob_write_bytecode(std::ofstream &dumpFile, CCodeSection *codeSect);
    void blob_write_sp_profiles(std::ofstream &dumpFile, CCodeSection *codeSect);
    void blob_write_ex_array(std::ofstream &dumpFile);
    void blob_write_blob_size(std::ofstream &dumpFile);

public:
	void dumpBlob(std::string path);
	void dumpBlobHeader(std::string blobFile, std::string blobHeaderFile);

    //    end of Blob generation
    //----------------------------------------------------------------------
};

#endif // SP_H
