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
    VxLAN_HXS = 277,
    PPPOE_HXS = 278,
    MPLS_HXS = 279,
    ARP_HXS = 280,
    IP_HXS = 281,
    IPV4_HXS = 282,
    IPV6_HXS = 283,
    GRE_HXS = 284,
    MINENCAP_HXS = 285,
    OTH_L3_HXS = 286,
    TCP_HXS = 287,
    UDP_HXS = 288,
    IPSEC_HXS = 289,
    SCTP_HXS = 290,
    DCCP_HXS = 291,
    OTH_L4_HXS = 292,
    GTP_HXS = 293,
    ESP_HXS = 294,
    OTH_L5_HXS = 295,
    FINAL_SHELL_HXS = 296,
    RETURN_SUB = 297,
    RETURN_HXS = 298,
    CLR_FAF = 299,
    SET_FAF = 300,
    END_PARSE = 301,
    CONCAT = 302,
    WR0 = 303,
    WR1 = 304,
    CLEAR = 305,
    ONESCOMP = 306,
    AND = 307,
    OR = 308,
    XOR = 309,
    SHIFT_LEFT = 310,
    SHIFT_RIGHT = 311,
    IF = 312,
    START_FRAME_WINDOW = 313,
    QUESTION = 314,
    PIPE = 315,
    AMPERSAND = 316,
    HXS = 317,
    BRIDGE = 318,
    START_PARAMETER_ARRAY = 319,
    EQUAL = 320,
    NOT_EQUAL = 321,
    GREATER_THAN = 322,
    LESS_THAN = 323,
    GREATER_THAN_EQUAL = 324,
    LESS_THAN_EQUAL = 325,
    OPEN_PAREN = 326,
    CLOSE_PAREN = 327,
    COMMA = 328,
    CONTEXT_LIST = 329,
    PLUS = 330,
    MINUS = 331,
    NXT_ETH_TYPE = 332,
    NXT_IP_PROTO = 333,
    NXT_TCPUDP_PORTS = 334,
    UINT6_TYPE = 335,
    UINT7_TYPE = 336,
    UINT8_TYPE = 337,
    UINT16_TYPE = 338,
    UINT32_TYPE = 339,
    UINT48_TYPE = 340,
    UINT64_TYPE = 341,
    DEC_VALUE = 342,
    FAF_ID = 343
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 5186 "sp_assembler.y" /* yacc.c:1909  */

          int   integer;
          char *string;
       

#line 149 "sp_assembler.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int _sp_assembler_yyparse (_sp_assembler_parser_context_t *_sp_assembler_context_p);

#endif /* !YY__SP_ASSEMBLER_YY_SP_ASSEMBLER_TAB_H_INCLUDED  */
