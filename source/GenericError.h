/* =====================================================================
 *
 * The MIT License (MIT)
 * Copyright 2018,2021 NXP
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
 * File Name : GenericError.h
 *
 * ===================================================================*/

#ifndef GENERICERROR_H
#define GENERICERROR_H

#include <string>
#include <libxml/parser.h>

const int NO_LINE = -1;

void errorFuncHandler( void * ctx, xmlErrorPtr error );


class CGenericError {
  public:
    class CErrorElem
    {
      public:
        std::string str;

        CErrorElem(int i);
        CErrorElem(std::string str);
        CErrorElem(const char* chr);
        CErrorElem();
    };

  public:
    CGenericError() {};
    CGenericError(std::string error, CErrorElem="", CErrorElem="", CErrorElem="", CErrorElem="", CErrorElem="",
                  CErrorElem="",     CErrorElem="", CErrorElem="", CErrorElem="", CErrorElem="");

    void createMessage(std::string error, int line=0, CErrorElem elem1="", CErrorElem elem2="", CErrorElem elem3="", CErrorElem elem4="", CErrorElem elem5="",
                                                      CErrorElem elem6="", CErrorElem elem7="", CErrorElem elem8="", CErrorElem elem9="", CErrorElem elem10="");
    static void printWarning(std::string error,   CErrorElem elem1="", CErrorElem elem2="", CErrorElem elem3="", CErrorElem elem4="",
                             CErrorElem elem5="", CErrorElem elem6="", CErrorElem elem7="", CErrorElem elem8="", CErrorElem elem9="", CErrorElem elem10="");

    std::string getErrorMsg() const;

  public:
    static int  dontWarn;

  private:
    std::string msg;
};


class CGenericErrorLine : public CGenericError
{
  public:
      CGenericErrorLine(std::string error, int line,              CErrorElem elem1="", CErrorElem elem2="", CErrorElem elem3="", CErrorElem elem4="",
                        CErrorElem elem5="", CErrorElem elem6="", CErrorElem elem7="", CErrorElem elem8="", CErrorElem elem9="", CErrorElem elem10="");

      static void printWarning(std::string error, int line, CErrorElem elem1="", CErrorElem elem2="", CErrorElem elem3="", CErrorElem elem4="",
                               CErrorElem elem5="",         CErrorElem elem6="", CErrorElem elem7="", CErrorElem elem8="", CErrorElem elem9="", CErrorElem elem10="");
};


/* ----------------------ERRORS and WARNINGS-----------------------------*/

const std::string ERR_INTERNAL_ERROR         = "(Internal): %1";

const std::string WARN_UNEXPECTED_NODE       = "Unexpected/ignored node - %1";
const std::string WARN_UNKNOWN_ATTRIBUTE     = "Unknown attribute '%1' in '%2' element";
const std::string WARN_UNSUPPORTED           = "Unsupported element will be ignored: %1";
const std::string WARN_MORE_THAN32           = "Add, subtract operation are performed only on the 32 least significant bits ";
const std::string WARN_GPR2                  = "$GPR2 is used internally by the compiler. "
                                           "Use this variables at your own risk";

const std::string WARN_CANT_OPEN_FILE        = "File '%1' can't be opened";
const std::string WARN_NO_RECONFIG           = "Reconfiguration is not possible";
const std::string WARN_WRONG_HDR_INDEX       = "%1 '%2', fieldref '%3' has wrong header_index value. Ignored";
const std::string WARN_HDR_INDEX_NA          = "%1 '%2', fieldref '%3' has not applicable header_index value. Ignored";
const std::string WARN_EXTRACTION_BYTE_ALLIGN= "The extraction offset is not byte alligned in distribution '%1'";

const std::string ERR_SP_REQUIRED            = "Custom protocol file is required %1";
const std::string ERR_CANT_OPEN_FILE         = "The input file can't be found or opened: %1";
const std::string ERR_XML_PARSE_ERROR        = "%1(%2): %3";
const std::string ERR_XML_PARSE_ERROR1       = "%1";
const std::string ERR_EMPTY_DOCUMENT         = "The document is empty: %1";
const std::string ERR_WRONG_TYPE             = "The document type is wrong; unexpected root node %1";
const std::string ERR_WRONG_TYPE1            = "The document type is wrong; unexpected node is - %1";
const std::string ERR_UNREC_ACTION_TYPE      = "Unrecognized or improper action type \"%1\" in %2 '%3'";
const std::string ERR_NO_BITS_FOUND          = "No bits being set found in the mask";
const std::string ERR_FIELD_NOT_BIT_FIXED    = "Type attribute in field element must be 'bit' or 'fixed': %1";
const std::string ERR_UNKNOWN_PROTOCOL       = "The protocol or shim index is unknown for entity '%1'";



/*-------------------------Soft parser errors--------------------------*/
const std::string ERR_INTERNAL_SP_ERROR      = "Soft parser internal error: %1";
const std::string ERR_TOO_MANY_INSTR         = "Generated code is too large for softparser. "
                                               "The number of instructions in the softparser is limited, try shortening the xml: %1";

/*Expressions and parsing expressions error*/
const std::string ERR_EXPECTED_COND          = "Unexpected arithmetic expression, expecting logical expression inside 'if'/'loop': %1";
const std::string ERR_EXPECTED_COND_AND      = "Unexpected arithmetic expression, expecting logical expression"
                                           " before and after the 'and', 'or' logical operators";
const std::string ERR_EXPECTED_COND_NOT      = "The 'not' operator is only allowed on logical expressions"
                                           " (and, or, ge, gt, le, lt, ==, !=)";
const std::string ERR_UNEXPECTED_COND_SWITCH = "Unexpected logical expression, expecting arithmetic expression inside switch: %1";
const std::string ERR_UNEXPECTED_COND_ASSIGN = "Unexpected logical expression, expecting arithmetic expression in value attribute of assign element: %1";
const std::string ERR_UNEXPECTED_COND        = "Unexpected logical expression, expecting arithmetic expression";
const std::string ERR_LEXER_ERROR            = "Error parsing expression, problem occurred near %1";
const std::string ERR_UNRECOGNIZED_LEXER     = "Unrecognized string in expression: %1";
const std::string ERR_COMPLEX_EXPR           = "Expression is too complex: %1";

/*Attributes / Options*/
const std::string ERR_UNSUPPORTED_ACTION     = "Unsupported action type: %1";
const std::string ERR_UNKNOWN_ADVANCE_OPTION = "Unknown advance option, use 'yes' or 'no': %1";
const std::string ERR_ADVANCE_NOT_ALLOWED    = "The advance option cannot be set to 'yes' when returning to the hard parser "
                                               "(either by default or when 'return' is set in the nextproto attribute): %1";
const std::string ERR_ADVANCE_REQUIRED       = "Advance is required when jumping to after_eth or after_ip protocols: %1";
const std::string ERR_UNKNOWN_CONFIRM_OPTION = "Unknown confirm option, use 'yes' or 'no': %1";
const std::string ERR_UNKNOWN_CCUSTOM_OPTION = "Unknown confirm custom option, use 'shim1' 'shim2' or 'no': %1";
const std::string ERR_MISSING_ATTRIBUTE      = "Missing attribute: '%1' is required attribute for '%2' element: %3";
const std::string ERR_UNALLOWED_LVALUE_ASSIGN= "Name attribute in assign-variable element must be result array (RA) variable: %1";
const std::string ERR_UNSUPPORTED_LOOP_TYPE  = "'%1' is unsupported loop type";
const std::string ERR_CASE_NO_INT            = "Case element's value attribute must be an immediate integer: %1";
const std::string ERR_UNSUPPORTED_ATTRIBUTE_VALUE = "Unsupported attribute value: attribute '%1' has an unsupported value";
const std::string ERR_INVALID_ATTRIBUTE_VALUE = "Invalid attribute value: attribute '%1' has an invalid value for element '%2'";
const std::string ERR_FAF_NOT_USER_DEFINED 	 = "Incorrect FAF attribute: the value is not User Defined FAF";
const std::string ERR_UNDEFINED_PROTOCOL 	 = "Undefined protocol: the specified protocol '%1' is not defined in NetPDL file";

/*Wrong protocol/variable/fields*/
const std::string ERR_UNSUPPORTED_PROTOCOL   = "Unsupported protocol: %1";
const std::string ERR_CANT_ACCESS_PROTOCOL   = "Can not access protocol %1";
const std::string ERR_UNRECOGNIZED_OBJECT    = "Unrecognized variable: %1";
const std::string ERR_UNRECOGNIZED_OBJ_DOT   = "A variable can not have '.' in its name"
                                               " if you are referring to a field please remove the $ prefix: %1";
const std::string ERR_UNRECOGNIZED_FIELD     = "Unrecognized field: %1";
const std::string ERR_HEADER_SIZE_MISSING    = "Header size is missing and can't be retrieved from the protocol's fields";

/*Wrongs buffer[ access / too large variables */
const std::string ERR_INVALID_INDEX          = "Invalid character in buffer index, only numbers allowed: %1";
const std::string ERR_FW_SIZE_MISSING        = "Size must be larger than 0 when accessing FW: %1";
const std::string ERR_FW_SIZE_LARGE          = "Cannot load from FW, maximum size of frame header is 255 bytes: %1";
const std::string ERR_PA_SIZE_MISSING        = "Size must be larger than 0 when accessing PA: %1";
const std::string ERR_PA_SIZE_LARGE          = "Parameter array (PA) contains 64 bytes,"
                                               " cannot access bytes in an offset larger than 64: %1";
const std::string ERR_BUFFER_ACCESS_TOO_LARGE= "Can not access more than 8 bytes in a buffer: %1";
const std::string ERR_VAR_ACCESS_TOO_LARGE   = "Can not access specified bytes in buffer. The size of variable %1 is %2 you tried to access %3.";
const std::string ERR_VAR_TOO_LARGE          = "Variable is too large (over 8 bytes), index of bytes should be specified: %1";
const std::string ERR_FIELD_TOO_LARGE        = "Field is too large (over 8 bytes), try accessing FW directly"
                                               " or changing the field's definition in the format element: %1";
const std::string ERR_BIT_FIELD_LARGER8      = "A bit field cannot be larger than 8 bytes, "
                                               "either split to several fields or change type to fixed: %1";
const std::string ERR_ACCESS_BYTE_IN_FIELD   = "Accessing specific bytes in protocol field is not allowed: %1";

/* Errors in xml syntax */
const std::string ERR_IF_NO_TRUE             = "An if element must have an if-true child element: %1";
const std::string ERR_AFTER_BEFORE_BEFORE    = "'Before' section appears after an 'after' section";
const std::string ERR_MULTIPLE_BEFORE        = "Multiple before sections are not supported";
const std::string ERR_MULTIPLE_AFTER         = "Multiple after sections are not supported";
const std::string ERR_SWITCH_EARLY_DEFAULT   = "Default condition can only appear after all other cases in switch";
const std::string ERR_SWITCH_NO_CASE         = "Switch element without a case: %1";
const std::string ERR_BEFORE_OTHER_PREV      = "Before element is now allowed when the previous protocol is %1";

/* Incorrect configuration Errors in config xml */
const std::string ERR_PROTOCOL_NOT_LOADED    = "Protocol '%2' needed by Profile '%1' is not loaded in a bytecode section on all parsers this profile is used";

/* Errors in operations or immediate values*/
const std::string ERR_SHIFT_BY_IMM           = "Shift only allowed by an immediate value";
const std::string ERR_SHIFT_BY_VALUE         = "Shift by value larger than 64 is not allowed";
const std::string ERR_CONCAT_VALUE           = "Concat operation allowed only directly on a variable or number (and not on an expression)";
const std::string ERR_ADDC_SIZE              = "Addc should only be performed on 16 bit variables";
const std::string ERR_CHECKSUM_FIRST         = "Checksum's first parameter must be equal or smaller than 0xffff";
const std::string ERR_CHECKSUM_SECOND_THIRD  = "Checksum's second and third parameters must be equal or smaller than 256";
const std::string ERR_INTEGER_RANGE          = "Integer is out of range, should be smaller than 0xffffffff: %1";

#endif // GENERICERROR_H
