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
    GOSUB = 260,
    COLON = 261,
    NOP = 262,
    START_RAW_INSTRUCTION = 263,
    HEX_WORD = 264,
    HEX_VALUE = 265,
    ASSIGN = 266,
    INCREMENT = 267,
    WINDOW_OFFSET = 268,
    HEADER_BASE = 269,
    RETURN = 270,
    SET_BITS = 271,
    START_RESULT_ARRAY = 272,
    RIGHT_BRACKET = 273,
    ETH_HXS = 274,
    LLCSNAP_HXS = 275,
    VLAN_HXS = 276,
    PPPOE_HXS = 277,
    MPLS_HXS = 278,
    ARP_HXS = 279,
    IP_HXS = 280,
    IPV4_HXS = 281,
    IPV6_HXS = 282,
    GRE_HXS = 283,
    MINENCAP_HXS = 284,
    OTH_L3_HXS = 285,
    TCP_HXS = 286,
    UDP_HXS = 287,
    IPSEC_HXS = 288,
    SCTP_HXS = 289,
    DCCP_HXS = 290,
    OTH_L4_HXS = 291,
    GTP_HXS = 292,
    ESP_HXS = 293,
    OTH_L5_HXS = 294,
    FINAL_SHELL_HXS = 295,
    RETURN_SUB = 296,
    RETURN_HXS = 297,
    CLR_FAF = 298,
    SET_FAF = 299,
    END_PARSE = 300,
    CONCAT = 301,
    WR0 = 302,
    WR1 = 303,
    CLEAR = 304,
    ONESCOMP = 305,
    AND = 306,
    OR = 307,
    XOR = 308,
    SHIFT_LEFT = 309,
    SHIFT_RIGHT = 310,
    IF = 311,
    START_FRAME_WINDOW = 312,
    QUESTION = 313,
    PIPE = 314,
    AMPERSAND = 315,
    HXS = 316,
    BRIDGE = 317,
    START_PARAMETER_ARRAY = 318,
    EQUAL = 319,
    NOT_EQUAL = 320,
    GREATER_THAN = 321,
    LESS_THAN = 322,
    GREATER_THAN_EQUAL = 323,
    LESS_THAN_EQUAL = 324,
    OPEN_PAREN = 325,
    CLOSE_PAREN = 326,
    COMMA = 327,
    CONTEXT_LIST = 328,
    PLUS = 329,
    MINUS = 330,
    NXT_ETH_TYPE = 331,
    NXT_IP_PROTO = 332,
    NXT_TCPUDP_PORTS = 333,
    UINT6_TYPE = 334,
    UINT7_TYPE = 335,
    UINT8_TYPE = 336,
    UINT16_TYPE = 337,
    UINT32_TYPE = 338,
    UINT48_TYPE = 339,
    UINT64_TYPE = 340,
    DEC_VALUE = 341,
    FAF_ID = 342
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 5168 "sp_assembler.y" /* yacc.c:1909  */

          int   integer;
          char *string;
       

#line 148 "sp_assembler.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int _sp_assembler_yyparse (_sp_assembler_parser_context_t *_sp_assembler_context_p);

#endif /* !YY__SP_ASSEMBLER_YY_SP_ASSEMBLER_TAB_H_INCLUDED  */
