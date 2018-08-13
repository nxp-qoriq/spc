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
 * File Name : FMCTaskDef.h
 *
 * ===================================================================*/

#ifndef TASKDEF_H
#define TASKDEF_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include <ostream>
#include <fstream>

/* For strtoull */
#include <stdlib.h>
#ifdef _MSC_VER
#define snprintf _snprintf
#define strtoull _strtoui64
#define strtoll _strtoi64
#endif

#include "GenericError.h"
#include "Utils.h"
#include "spc.h"

class CExecuteExpression;
class CExecuteSection;
class CProtocol;
class CLabel;
class CTaskDef;

/// A set of named numbers with fixed values
typedef std::map< std::string, unsigned int >           CConstants;
/// Iterator class for constant values container
typedef std::map< std::string, unsigned int >::iterator CConstantsIter;


typedef enum ExecuteInstructionType {
	IT_IF,
	IT_LOOP,
	IT_ACTION,
	IT_ASSIGN,
	IT_INLINE,
	IT_SWITCH,
	IT_GOSUB,
	IT_SETRESETFAF
} ExecuteInstructionType;

typedef enum ExecuteSectionType {
    INIT,
    BEFORE,
    AFTER,
    VERIFY,
    EMPTY /* EMPTY is used when the ExecuteSection class is accessed because
             of IN statement and not due to a new section*/
} ExecuteSectionType;


typedef enum ProtoType {
    PT_NONE,   			/* Used to invoke SP before HW Parser: before Ethernet */
    PT_ETH,
    PT_LLC_SNAP,
    PT_VLAN,
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
    PT_END_PARSE
} ProtoType;

class CField
{
  public:
    std::string type;
    std::string name;
    std::string size;
    std::string longname;
    std::string showtemplate;
    std::string mask;
    std::string plugin;
    std::string expr;
    std::string description;
    std::string endtoken;
    std::string begintoken;
    std::string endregex;
    std::string endoffset;
    std::string beginregex;
    std::string beginoffset;
    std::string bigendian;
    std::string comment;
    std::string align;
    std::string enddiscard;
    std::string offset;
};

typedef enum e_FmPcdExtractSource {
    ES_FROM_FRAME_START,          /**< KG & CC: Extract from beginning of frame */
    ES_FROM_DFLT_VALUE,           /**< KG only: Extract from a default value */
    ES_FROM_CURR_END_OF_PARSE,    /**< KG only: Extract from the point where parsing had finished */
    ES_FROM_KEY,                  /**< CC only: Field where saved KEY */
    ES_FROM_HASH,                 /**< CC only: Field where saved HASH */
    ES_FROM_PARSE_RESULT,         /**< KG & CC: Extract from the parser result */
    ES_FROM_ENQ_FQID,             /**< KG & CC: Extract from enqueue FQID */
    ES_FROM_FLOW_ID               /**< CC only: Field where saved Dequeue FQID */
} e_FmPcdExtractSource;

typedef enum e_FmPcdExtractAction {
    EA_NONE,                           /**< NONE  */
    EA_EXACT_MATCH,                    /**< Exact match on the selected extraction*/
    EA_INDEXED_LOOKUP                  /**< Indexed lookup on the selected extraction*/
} e_FmPcdExtractAction;

class CConfirmCustomExtractor
{
  public:
    virtual void getConfirmCustom( std::set< std::string >& custom_confirms ) const = 0;
};


class CExecuteSection : public CConfirmCustomExtractor
{
  public:
    std::vector< CExecuteExpression> executeExpressions;
    ExecuteSectionType               type;
    std::string                      when;
    std::string                      confirmCustom;
    int                              line;

    CExecuteSection     () : line(NO_LINE) {};
    CExecuteSection     (ExecuteSectionType type1) : type(type1), line(NO_LINE) {};
    void dumpSection    (std::ofstream &outFile, uint8_t spaces);
    void deleteSection  ();

    virtual void getConfirmCustom( std::set< std::string >& custom_confirms ) const;
};


class CExecuteAssign : public CConfirmCustomExtractor
{
  public:
    std::string     name;
    std::string     value;
    std::string     fwoffset;
    int             line;

    CExecuteAssign  () : line(NO_LINE) {};
    void dumpAssign (std::ofstream &outFile, uint8_t spaces);

    virtual void getConfirmCustom( std::set< std::string >& custom_confirms ) const {};
};

class CExecuteAction : public CConfirmCustomExtractor
{
  public:
    std::string     type;
    std::string     value;
    std::string     nextproto;
    std::string     advance;
    std::string     confirmCustom;
    int             line;

    CExecuteAction  () : line(NO_LINE) {};
    void dumpAction (std::ofstream &outFile, uint8_t spaces);

    virtual void getConfirmCustom( std::set< std::string >& custom_confirms ) const;
};

class CExecuteLoop : public CConfirmCustomExtractor
{
  public:
    std::string      type;
    std::string      expr;
    CExecuteSection  loopBody;
    int              line;

    CExecuteLoop  () :                  line(NO_LINE) {}
    CExecuteLoop  (std::string expr1) : expr(expr1), line(NO_LINE) {}
    void dumpLoop (std::ofstream &outFile, uint8_t spaces);

    virtual void getConfirmCustom( std::set< std::string >& custom_confirms ) const;
};

class CExecuteIf : public CConfirmCustomExtractor
{
  public:
    std::string      expr;
    std::string      faf;
    CExecuteSection  ifTrue;
    CExecuteSection  ifFalse;
    int              line;
    bool             ifTrueValid;
    bool             ifFalseValid;

    CExecuteIf  () :                  ifTrueValid( false ), ifFalseValid( false ), line(NO_LINE) {}
    CExecuteIf  (std::string expr1) : ifTrueValid( false ), ifFalseValid( false ), expr(expr1), line(NO_LINE) {}
    void dumpIf (std::ofstream &outFile, uint8_t spaces);

    virtual void getConfirmCustom( std::set< std::string >& custom_confirms ) const;
};

class CExecuteInline : public CConfirmCustomExtractor
{
  public:
    std::string      data;
    int              line;

    CExecuteInline  () :                  data(""),    line(NO_LINE) {};
    CExecuteInline  (std::string data1) : data(data1), line(NO_LINE) {};
    void dumpInline (std::ofstream &outFile, uint8_t spaces);

    virtual void getConfirmCustom( std::set< std::string >& custom_confirms ) const {}
};

class CExecuteCase : public CConfirmCustomExtractor
{
  public:
    std::string     value;
    std::string     maxValue;
    CExecuteSection ifCase;
    int             line;
    bool            ifCaseValid;

    CExecuteCase     () : ifCaseValid( false ),value (""), maxValue(""), line(NO_LINE) {};
    void dumpCase    (std::ofstream &outFile, uint8_t spaces);

    virtual void getConfirmCustom( std::set< std::string >& custom_confirms ) const;
};

class CExecuteSwitch : public CConfirmCustomExtractor
{
  public:
    std::string                     expr;
    std::vector <CExecuteCase>      cases;
    CExecuteSection                 defaultCase;
    int                             line;
    bool                            defaultCaseValid;

    CExecuteSwitch     () : defaultCaseValid( false ), line(NO_LINE) {};
    void dumpSwitch    (std::ofstream &outFile, uint8_t spaces);

    virtual void getConfirmCustom( std::set< std::string >& custom_confirms ) const;
};

class CExecuteGosub : public CConfirmCustomExtractor
{
public:

	std::string      name;
	int              line;

	CExecuteGosub  () :                  line(NO_LINE) {};
	CExecuteGosub  (std::string name1) : name(name1), line(NO_LINE) {};
	void dumpGosub (std::ofstream &outFile, uint8_t spaces);

	virtual void getConfirmCustom( std::set< std::string >& custom_confirms ) const {};
};

class CExecuteSetresetfaf : public CConfirmCustomExtractor
{
public:

	std::string      name;
	bool			 faf;
	bool			 set;
	int              line;

	CExecuteSetresetfaf  () :                  line(NO_LINE) {};
	CExecuteSetresetfaf  (bool faf1, std::string name1, bool set1) : faf(faf1), name(name1), set(set1), line(NO_LINE) {};
	void dumpSetresetfaf (std::ofstream &outFile, uint8_t spaces);

	virtual void getConfirmCustom( std::set< std::string >& custom_confirms ) const {};
};

class CExecuteExpression : public CConfirmCustomExtractor
{
  public:
    ExecuteInstructionType type;
    CExecuteAction         actionInstr;
    CExecuteAssign         assignInstr;
    CExecuteIf             ifInstr;
    CExecuteLoop           loopInstr;
    CExecuteInline         inlineInstr;
    CExecuteSwitch         switchInstr;
	CExecuteGosub		   gosubInstr;
	CExecuteSetresetfaf	   setresetfafInstr;

    CExecuteExpression() {}
    CExecuteExpression(ExecuteInstructionType type1): type(type1) {}

    virtual void getConfirmCustom( std::set< std::string >& custom_confirms ) const;
};


class CExecuteCode : public CConfirmCustomExtractor
{
  public:
     std::vector< CExecuteSection> executeSections;

     virtual void getConfirmCustom( std::set< std::string >& custom_confirms ) const;
};


class CProtocol
{
  public:
    CProtocol () : line(NO_LINE) {};
    bool         FieldExists( const std::string fieldname) const;
    bool         GetFieldProperties( const std::string fieldname,
                                     uint32_t&         bitsize,
                                     uint32_t&         bitoffset ) const;
    bool         GetHeaderSize( uint32_t &size) const;
    bool         PossibleLayer4() const;
    static bool  PossibleLayer4( ProtoType pt );
    short        ProtocolLayer() const;
    static short ProtocolLayer( ProtoType pt );

  public:
    ProtoType                  type;
    std::string                name;
    std::string                longname;
    std::string                showsumtemplate;
    std::string                comment;
    std::string                description;
    std::vector< std::string > prevproto;
    std::vector< ProtoType >   prevType;
    int                        line;
    std::vector< CField >      fields;
    CExecuteCode               executeCode;

    std::vector< std::string > engines;

};

class CLabel
{
  public:
    bool            isProto;    //  label is a protocol
    std::string     name;       //  label name
    ProtoType       protocol;   //  protocol type

    CLabel() :                  isProto(0)                 {}
    CLabel(std::string name1) : isProto(0), name(name1)    {}
    CLabel(ProtoType type)    : isProto(1), protocol(type) {}

    std::string getProtocolOutputName () const;
};

class CExtension
{
public:
    std::vector< ProtoType >   prevType;
    std::vector< std::string > prevNames;
    CProtocol	protocol;
    uint32_t position;
    uint8_t  indexPerHdr;

    CExtension(std::vector< ProtoType >& types, std::vector< std::string >& names, CProtocol prot, uint32_t pos) :
        prevType(types), prevNames(names), protocol(prot), position(pos), indexPerHdr(0) {}
};

const int ASSEMBLER_BASE = SP_ASSEMBLER_BASE_ADDRESS;
const int CODE_SIZE      = MAX_SP_CODE_SIZE; //4028 bytes


class CCodeSection
{
	public:
	CCodeSection() :  swOffset(ASSEMBLER_BASE) 	{};

	public:
		uint32_t		swOffset;
		std::vector< std::string > engines;
		std::vector< std::string > protocols;
};

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


class CSoftParseResult
{
public:
    CTaskDef 				*task;
    uint32_t                 size;                      /**< SW parser code size in bytes */
    uint16_t                 base;                      /**< SW parser base bytes
                                                             must be larger than 0x40*/
    bool					 cpuLE;						/**< TRUE if CPU is LE */
    uint8_t                  p_Code[CODE_SIZE];         /**< SW parser code */
    uint8_t                  swPrsDataParams[PRS_PARAM_SIZE];		/**< SW parser data (parameters) */
    uint8_t                  numOfLabels;               /**< Number of labels for SW parser. */
    std::vector <CExtension> labelsTable;               /**< SW parser labels table, containing
                                                             numOfLabels entries */

    CSoftParseResult();
    void setTask		(CTaskDef *taskdef);
    void setSize        (const uint32_t baseAddress1);
    void setBinary      (const uint8_t binary1[], const uint32_t size);
    void setBaseAddresss(const uint16_t baseAddress);
    void setExtensions  (const std::vector <CExtension> extns);
    void dumpHeader     (std::string path) const;
	void dumpBinary     (std::string path) const;
    static std::string externProtoName (const ProtoType type);


    //----------------------------------------------------------------------
    //    Blob generation

    uint32_t 	blob_size;

	uint16_t cpu_to_le16(uint16_t val16);
    uint32_t cpu_to_le32(uint32_t val32);
    void blob_write8(std::ofstream &dumpFile, uint8_t val);
    void blob_write_cpu_to_le16(std::ofstream &dumpFile, uint16_t val16);
    void blob_write_cpu_to_le32(std::ofstream &dumpFile, uint32_t val32);

    uint32_t blob_get_base_protocol(const ProtoType prevType);

    void blob_write_file_header(std::ofstream &dumpFile);
    void blob_write_blob_name(std::ofstream &dumpFile, const char *name);
    void blob_write_bytecode(std::ofstream &dumpFile);
    void blob_write_sp_profiles(std::ofstream &dumpFile);
    void blob_write_ex_array(std::ofstream &dumpFile);
    void blob_write_blob_size(std::ofstream &dumpFile);

	void dumpBlob(std::string path);

    //    end of Blob generation
    //----------------------------------------------------------------------

};


class CTaskDef
{
  public:
    std::string name;
    std::string version;
    std::string creator;
    std::string date;

    std::string pcdname;
    std::string pcdversion;
    std::string pcdcreator;
    std::string pcddate;

    std::string soc_name;
    std::string soc_rev;

    std::vector< CProtocol >     protocols;
    std::vector< CCodeSection >  program;
    std::vector< CParameter >  	 parameters;

    CSoftParseResult             spr;

  public:
    CTaskDef();
    ~CTaskDef();

    bool FieldExists       ( const std::string fullFieldName) const;
    bool GetFieldProperties( const std::string fullFieldName,
                             uint32_t&         bitSize,
                             uint32_t&         bitOffset ) const;
    std::string getShimNoFromCustom( const std::string protocol_name ) const;

    void deleteExecute  ();
    void dumpSpParsed   (std::string path);

    uint32_t getBaseAddresss();
    void enableProtocolOnInit(std::string protocol_name, std::string engine_name);

};

#endif // TASKDEF_H
