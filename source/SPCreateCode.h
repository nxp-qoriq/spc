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
 * File Name : SPCreateCode.h
 *
 * ===================================================================*/

#ifndef CREATECODE_H
#define CREATECODE_H

#include "SPIR.h"

class CCode;
class CProtocolCode;
class CRegOperand;

typedef enum BitOperator {
    BO_AND,
    BO_OR,
    BO_XOR
} BitOperator;

typedef enum CondOperator {
    CO_EQU,
    CO_NOTEQU,
    CO_GREATEREQU,
    CO_LESSEQU,
    CO_GREATER,
    CO_LESS
} CondOperator;

typedef enum OpType {
    OT_BITOP,
    OT_CONDOP,
    OT_HXS,
    OT_LABEL,
    OT_OBJ,
    OT_REG,
    OT_SHIFT,
    OT_TEXT,
    OT_VAL,
    OT_FAF
} PCodeOpType;

typedef enum Opcode {
    CASE1_DJ_WR_TO_WR,   // [OT_REG=WR0],   OT_HXS,         OT_LABEL,   OT_HXS,     OT_LABEL
    CASE2_DC_WR_TO_WR,   // [OT_REG=WR0],   OT_HXS,         OT_LABEL,   OT_HXS,     OT_LABEL
    CASE2_DJ_WR_TO_WR,   // [OT_REG=WR0],   OT_HXS,         OT_LABEL,   OT_HXS,     OT_LABEL, OT_HXS, OT_LABEL
    CASE3_DC_WR_TO_WR,   // [OT_REG=WR0],   OT_HXS,         OT_LABEL,   OT_HXS,     OT_LABEL, OT_HXS, OT_LABEL
    CASE3_DJ_WR_TO_WR,   // [OT_REG=WR0],   OT_HXS,         OT_LABEL,   OT_HXS,     OT_LABEL, OT_HXS, OT_LABEL, OT_HXS, OT_LABEL
    CASE4_DC_WR_TO_WR,   // [OT_REG=WR0],   OT_HXS,         OT_LABEL,   OT_HXS,     OT_LABEL, OT_HXS, OT_LABEL, OT_HXS, OT_LABEL
    COMPARE_WORKING_REGS,// OT_LABEL,       [OT_REG=WR0],   OT_CONDOP,  [OT_REG=WR1]
	GOSUB_COMPARE_WK_REGS,
    LABEL,               // OT_LABEL
    JMP,                 // OT_HXS,         OT_LABEL
    JMP_PROTOCOL_ETH,    // [OT_HXS=1]
    JMP_PROTOCOL_IP,     // [OT_HXS=1]
	JMP_PROTOCOL_TCPUDP, // [OT_HXS=1]
	GOSUB,
	RETURN_SUB,
    STORE_IV_TO_RA,      // OT_OBJ,         OT_VAL
    STORE_WR_TO_RA,      // OT_OBJ,         OT_REG
    LOAD_BYTES_RA_TO_WR, // OT_REG,         OT_SHIFT,       OT_OBJ
    LOAD_BYTES_PA_TO_WR, // OT_REG,         OT_SHIFT,       OT_OBJ
    LOAD_BITS_FW_TO_WR,  // OT_REG,         OT_SHIFT,       OT_OBJ
    LOAD_BITS_IV_TO_WR,  // OT_REG,         OT_SHIFT,       OT_VAL,     OT_VAL
	SET_FAF,
	CLR_FAF,
	JMP_FAF,
	GOSUB_FAF,
    ZERO_WR,             // OT_REG
    ADD_WR_WR_TO_WR,     // OT_REG,         OT_REG,         OT_REG
    SUB_WR_WR_TO_WR,     // OT_REG,         OT_REG,         OT_REG
    ADD_WR_IV_TO_WR,     // OT_REG,         OT_REG,         OT_VAL
    SUB_WR_IV_TO_WR,     // OT_REG,         OT_REG,         OT_VAL
    SHIFT_LEFT_WR_BY_SV, // OT_REG,         OT_VAL
    SHIFT_RIGHT_WR_BY_SV,// OT_REG,         OT_VAL
    BITWISE_WR_WR_TO_WR, // OT_REG,         [OT_REG=WR0],   OT_BITOP,   [OT_REG=WR1]
    BITWISE_WR_IV_TO_WR, // OT_REG,         OT_REG,         OT_BITOP,   OT_VAL
    LOAD_SV_TO_WO,       // [OT_REG=WO],    OT_VAL
    ADD_SV_TO_WO,        // [OT_REG=WO],    OT_VAL
    SET_WO_BY_WR,        // [OT_REG=WO],    OT_REG
    ADD_WO_BY_WR,        // [OT_REG=WO],    OT_REG
    ADVANCE_HB_BY_WO,    // [OT_REG=WO]
    ONES_COMP_WR1_TO_WR0,// [OT_REG=WR0],   [OT_REG=WR1]
    NOP,                 //
    INLINE_INSTR         // OT_TEXT
} Opcode;

/*HXS*/
const  uint8_t HXS0 = 0x01;
const  uint8_t HXS1 = 0x02;
const  uint8_t HXS2 = 0x04;
const  uint8_t HXS3 = 0x08;

class COpFlags
{
  public:
    bool    used;
    bool    defined;

    COpFlags() : used(0), defined(0) {}
};


class COperand
{
public:
    OpType              kind;
    COpFlags flags;

    uint64_t            getValue()  const;
    CReg                getReg()    const;
    CRegOperand*        getRegOp()  const;
    bool                hasReg()    const;
    void                setDef (bool val);
    void                setUsed(bool val);
    virtual std::string getOperandName () const = 0;
    virtual ~COperand () {} ;
};

class CValueOperand : public COperand
{
public:
    uint64_t value;
    virtual std::string getOperandName () const;
};

class CRegOperand : public COperand
{
public:
    CReg    reg;
    virtual std::string getOperandName () const;
};

class CFafOperand : public COperand
{
public:
	CFaf    faf;
	virtual std::string getOperandName () const;
};

class CBitOperand : public COperand
{
public:
    BitOperator bitOperator;
    virtual std::string getOperandName () const;
};

class CCondOperand : public COperand
{
public:
    CondOperator condOperator;
    virtual std::string getOperandName () const;
};

class CLabelOperand : public COperand
{
public:
    CLabel label;
    CLabelOperand () {}
    CLabelOperand (CLabel label1) : label(label1) {}
    virtual std::string getOperandName () const;
};

class CObjOperand : public COperand
{
public:
    CObject object;
    CObjOperand ()  {}
    CObjOperand (CObject newObject) : object(newObject) {}
    virtual std::string getOperandName () const;
};

class CHxsOperand : public COperand
{
public:
    bool    hxsOp;
    static  CReg reg;
    virtual std::string getOperandName () const;
};

class CShiftOperand : public COperand
{
public:
    bool    shiftOp;
    virtual std::string getOperandName () const;
};

class CTextOperand : public COperand
{
public:
    std::string    text;
    virtual std::string getOperandName () const;
};

class CInstructionFlags
{
  public:
    bool ifFirstLabel;

    CInstructionFlags() : ifFirstLabel (0) {}
};

class CInstruction
{
  private:
    Opcode                          opcode;
    uint32_t                        noperands;
    std::vector <COperand*>         operands;
    CInstructionFlags               flags;
    std::string                     text;

    friend class CCode;
    friend class CProtocolCode;

    /* constructors*/
    CInstruction() : noperands(0), text("") {}

    /* revise functions */
    bool                canJump()   const;

  private:
    CInstruction(Opcode op) : opcode(op), noperands(0) {}
    CInstruction(Opcode op, COperand* operandA,      COperand* operandB=NULL,
                            COperand* operandC=NULL, COperand* operandD=NULL);

    /* get info*/
  public:
    std::string getOpcodeName   ();
	Opcode getOpcode();

    /* prepare code */
  private:
    void checkError         (int num...);
    void prepareAsm         (std::string &asmOutput);
    void prepareCode        (std::string &stringCode);

    /*delete / new*/
  public:
    void deleteInstruction  ();
};

class CProtocolCode {
  public:
    CProtocol                  protocol;
    CLabel                     label;
    std::vector <CInstruction> instructions;

    /* revise functions */
    void reviseProtocolCode ();
    bool removeDoubleDefine();
    bool reviseClear        (uint32_t i);
    void insertInstruction  (uint32_t i, CInstruction instruction);
    void eraseInstruction   (uint32_t i);
};

class CCode
{
  public:
    std::vector <CProtocolCode > protocolsCode;
  private:
    std::string      asmOutput;
    std::string      codeOutput;
    std::ofstream    *asmFile;
    std::ofstream    *codeFile;
    uint8_t          gpr1Used;
    bool             chksumStored;  //chksumResult is stored in GPR2
    uint8_t          gpr2Used;      //GPR2 is currently live
    /*Process IR*/
  public:
    CCode() : asmFile(0), codeFile(0), chksumStored(0),
    		gpr1Used(0), gpr2Used(0) {}
    void createCode (CIR IR);
  private:
    void processStatement  (CStatement statement, CProtocolCode& code);
    void processAssign     (CENode* expression,   CProtocolCode& code);
    void processEndSection (CStatement statement, CProtocolCode& code);
    void processIf         (CENode* expression,   CLabel label, CProtocolCode& code);
    void processInline     (std::string data,     CProtocolCode& code);
    void processJump       (CStatement statement, CProtocolCode& code);
	void processFafJump    (CStatement statement, CProtocolCode& code);
	void processGosub	   (CStatement statement, CProtocolCode& code);
	void processRetsub	   (CStatement statement, CProtocolCode& code);
	void processSetFaf     (CStatement statement, CProtocolCode& code);
	void processResetFaf   (CStatement statement, CProtocolCode& code);
    void processSwitch     (CENode* expression,   CSwitchTable* switchTable, CProtocolCode& code);
    void processWROperation(CENode* expression,   CProtocolCode& code);
    void processChecksum   (CENode* expression,   CProtocolCode& code);
    void processConcat     (CENode* expression,   CProtocolCode& code);
    void processExpression (CENode* expression,   CProtocolCode& code);
    void processInt        (CENode* expression,   CProtocolCode& code);
    void processObject     (CENode* expression,   CProtocolCode& code);
    void findAndProcessChecksum  (CENode* expr,   CProtocolCode& code, bool &found);

    /* revise / prepare functions */
  private:
    void prepareEntireCode  ();
    void reviseEntireCode   ();

    /* dump functions*/
  public:
    void setDumpCode    (std::string path);
    void setDumpAsm     (std::string path);
    void dumpCode       ();
    void dumpAsm        ();

    /*result*/
  public:
    std::string getAsmOutput();

    /*new/delete functions*/
  public:
    static CBitOperand*    newBitOp        (BitOperator bitOp1);
    static CCondOperand*   newCondOp       (CondOperator condOp1);
    static CHxsOperand*    newHxsOp        (bool hxsOp1);
    static CLabelOperand*  newLabelOp      (CLabel label1);
    static CObjOperand*    newObjOp        (CObject *object1);
    static CRegOperand*    newRegOp        (CReg reg1);
    static CRegOperand*    newRegOp        (RegType type1);
	static CFafOperand*    newFafOp        (CFaf faf1);
	static CFafOperand*    newFafOp        (FafType type1);
	static CFafOperand*    newFafOp        (std::string name);
    static CShiftOperand*  newShiftOp      (bool shiftOp1);
    static CTextOperand*   newTextOp       (std::string text1);
    static CValueOperand*  newValueOp      (uint64_t valueOp1);
    void deleteCode ();
  private:
    void deletePaths();

    /*GPR1 functions*/
  private:
    void    freeGPR1          (uint8_t start, uint8_t end);
    bool    GPR1Used          (uint8_t start, uint8_t end);
    CObject getAndFreeGPR1    (uint8_t start, uint8_t end);
    CObject getAndAllocateGPR1(uint8_t start, uint8_t end, int line = NO_LINE);

    /*GPR2 functions*/
  private:
    void    freeGPR2          (uint8_t start, uint8_t end);
    bool    GPR2Used          (uint8_t start, uint8_t end);
    CObject getAndFreeGPR2    (uint8_t start, uint8_t end);
    CObject getAndAllocateGPR2(uint8_t start, uint8_t end, int line = NO_LINE);

    /*Create instructions. These functions aren't really necessary
    (besides createCase) since they all call just call the generic
    CInstruction construction.
    HOWEVER, they should be used since they prevent errors in compile-time,
    by unallowing using the wrong operands in specific instructions*/
  public:
    static CInstruction createCOMPARE_WORKING_REGS  (CLabelOperand* opA, CCondOperand*  opB);
	static CInstruction createGOSUB_COMPARE_WK_REGS (CLabelOperand* opA, CCondOperand*  opB);
    static CInstruction createLABEL                 (CLabelOperand* opA);
    static CInstruction createJMP                   (CHxsOperand*   opA, CLabelOperand* opB);
    static CInstruction createJMP_PROTOCOL_ETH      ();
    static CInstruction createJMP_PROTOCOL_IP       ();
	static CInstruction createJMP_PROTOCOL_TCPUDP   ();
	static CInstruction createGOSUB                 (CLabelOperand* opA);
	static CInstruction createRETURN_SUB			();
    static CInstruction createSTORE_IV_TO_RA        (CObjOperand*   opA, CValueOperand* opB);
    static CInstruction createSTORE_WR_TO_RA        (CObjOperand*   opA, CRegOperand*   opB);
    static CInstruction createLOAD_BYTES_RA_TO_WR   (CRegOperand*   opA, CShiftOperand* opB,    CObjOperand*    opC);
    static CInstruction createLOAD_BYTES_PA_TO_WR   (CRegOperand*   opA, CShiftOperand* opB,    CObjOperand*    opC);
    static CInstruction createLOAD_BITS_FW_TO_WR    (CRegOperand*   opA, CShiftOperand* opB,    CObjOperand*    opC);
    static CInstruction createLOAD_BITS_IV_TO_WR    (CRegOperand*   opA, CShiftOperand* opB,    CValueOperand*  opC,    CValueOperand* opD);
    static CInstruction createZERO_WR               (CRegOperand*   opA);
    static CInstruction createADD_WR_WR_TO_WR       (CRegOperand*   opA, CRegOperand*   opB,    CRegOperand*    opC);
    static CInstruction createSUB_WR_WR_TO_WR       (CRegOperand*   opA, CRegOperand*   opB,    CRegOperand*    opC);
    static CInstruction createADD_WR_IV_TO_WR       (CRegOperand*   opA, CRegOperand*   opB,    CValueOperand*  opC);
    static CInstruction createSUB_WR_IV_TO_WR       (CRegOperand*   opA, CRegOperand*   opB,    CValueOperand*  opC);
    static CInstruction createSHIFT_LEFT_WR_BY_SV   (CRegOperand*   opA, CValueOperand* opB);
    static CInstruction createSHIFT_RIGHT_WR_BY_SV  (CRegOperand*   opA, CValueOperand* opB);
    static CInstruction createBITWISE_WR_WR_TO_WR   (CRegOperand*   opA, CBitOperand*   opB);
    static CInstruction createBITWISE_WR_IV_TO_WR   (CRegOperand*   opA, CRegOperand*   opB,    CBitOperand*    opC,    CValueOperand* opD);
    static CInstruction createLOAD_SV_TO_WO         (CValueOperand* opA);
    static CInstruction createADD_SV_TO_WO          (CValueOperand* opA);
    static CInstruction createSET_WO_BY_WR          (CRegOperand*   opA);
    static CInstruction createADD_WO_BY_WR          (CRegOperand*   opA);
    static CInstruction createADVANCE_HB_BY_WO      ();
    static CInstruction createONES_COMP_WR1_TO_WR0  ();
    static CInstruction createNOP                   ();
    static CInstruction createInlineInstr           (CTextOperand*  opA);
    static CInstruction createCaseInstr             (Opcode op, uint8_t hxses, std::vector <CLabel> labels);
	static CInstruction createSET_FAF				(CFafOperand*	opA);
	static CInstruction createCLR_FAF				(CFafOperand*	opA);
	static CInstruction createJMP_FAF				(CLabelOperand* opA, CFafOperand*	opB);
	static CInstruction createGOSUB_FAF				(CLabelOperand* opA, CFafOperand*	opB);
  private:
    void addInstr(CInstruction instr, CProtocolCode& code);
};


#endif // CREATECODE_H
