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
 * File Name : TaskDef.h
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
#include "SoftParser.h"
#include "Utils.h"
#include "spc.h"


class CExecuteExpression;

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

class CConfirmCustomExtractor
{
  public:
	virtual ~CConfirmCustomExtractor();
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

    std::vector< std::string > parsers;

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

class CSoftParserTask
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
    std::vector< CProfile >  	 profiles;
    std::vector< CParser >  	 parsers;

    CSoftParserBlob				 spb;

  public:
    CSoftParserTask();
    virtual ~CSoftParserTask();

    void generateBlob(std::string filePath, bool genIntermCode);

    bool FieldExists       ( const std::string fullFieldName) const;
    bool GetFieldProperties( const std::string fullFieldName,
                             uint32_t&         bitSize,
                             uint32_t&         bitOffset ) const;
    bool findSpProtocol(std::string protocol_name) const;
    bool findSpProfile(std::string profile_name) const;

    void deleteExecute();
    void dumpSpParsed(std::string path);

    uint32_t getBaseAddresss(unsigned int index);
    void enableProfileOnParser(std::string profile_name, std::string parser_name);
};

#endif // TASKDEF_H
