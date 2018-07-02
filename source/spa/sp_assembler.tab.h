/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY__SP_ASSEMBLER_YY_SP_ASSEMBLER_TAB_H_INCLUDED
# define YY__SP_ASSEMBLER_YY_SP_ASSEMBLER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int _sp_assembler_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ALPHA_NUMERIC_WORD = 258,
    JMP = 259,
    COLON = 260,
    NOP = 261,
    START_RAW_INSTRUCTION = 262,
    HEX_WORD = 263,
    HEX_VALUE = 264,
    ASSIGN = 265,
    INCREMENT = 266,
    WINDOW_OFFSET = 267,
    HEADER_BASE = 268,
    RETURN = 269,
    SET_BITS = 270,
    START_RESULT_ARRAY = 271,
    RIGHT_BRACKET = 272,
    ETH_HXS = 273,
    IPV4_HXS = 274,
    IPV6_HXS = 275,
    OTH_L3_HXS = 276,
    TCP_HXS = 277,
    UDP_HXS = 278,
    OTH_L4_HXS = 279,
    RETURN_HXS = 280,
    END_PARSE = 281,
    CONCAT = 282,
    WR0 = 283,
    WR1 = 284,
    CLEAR = 285,
    ONESCOMP = 286,
    AND = 287,
    OR = 288,
    XOR = 289,
    SHIFT_LEFT = 290,
    SHIFT_RIGHT = 291,
    IF = 292,
    START_FRAME_WINDOW = 293,
    QUESTION = 294,
    PIPE = 295,
    AMPERSAND = 296,
    HXS = 297,
    BRIDGE = 298,
    START_PARAMETER_ARRAY = 299,
    EQUAL = 300,
    NOT_EQUAL = 301,
    GREATER_THAN = 302,
    LESS_THAN = 303,
    GREATER_THAN_EQUAL = 304,
    LESS_THAN_EQUAL = 305,
    OPEN_PAREN = 306,
    CLOSE_PAREN = 307,
    COMMA = 308,
    CONTEXT_LIST = 309,
    PLUS = 310,
    MINUS = 311,
    NXT_ETH_TYPE = 312,
    NXT_IP_PROTO = 313,
    UINT6_TYPE = 314,
    UINT7_TYPE = 315,
    UINT8_TYPE = 316,
    UINT16_TYPE = 317,
    UINT32_TYPE = 318,
    UINT48_TYPE = 319,
    UINT64_TYPE = 320,
    DEC_VALUE = 321
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 4819 "sp_assembler.y" /* yacc.c:1909  */

          int   integer;
          char *string;
       

#line 127 "sp_assembler.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int _sp_assembler_yyparse (_sp_assembler_parser_context_t *_sp_assembler_context_p);

#endif /* !YY__SP_ASSEMBLER_YY_SP_ASSEMBLER_TAB_H_INCLUDED  */
