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

#ifndef YY_YY_SPEXPR_HPP_INCLUDED
# define YY_YY_SPEXPR_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OBJECT = 258,
    VARIABLE = 259,
    SUB_VARIABLE = 260,
    FIELD = 261,
    PROTOCOL = 262,
    PROTOCOL_FIELD = 263,
    HEADERSIZE = 264,
    DEFAULT_HEADER_SIZE = 265,
    VARIABLE_A = 266,
    SUB_VARIABLE_A = 267,
    FIELD_A = 268,
    PROTOCOL_FIELD_A = 269,
    ACCESS_ERROR = 270,
    DEC = 271,
    HEX = 272,
    BIN = 273,
    OPEN_PARENTHESIS = 274,
    CLOSE_PARENTHESIS = 275,
    OPEN_BRACKET = 276,
    CLOSE_BRACKET = 277,
    COMMA = 278,
    END = 279,
    OR = 280,
    AND = 281,
    GREATER = 282,
    GREATEREQU = 283,
    LESS = 284,
    LESSEQU = 285,
    EQU = 286,
    NOTEQU = 287,
    SHR = 288,
    SHL = 289,
    CONCAT = 290,
    BIT_AND = 291,
    XOR = 292,
    BIT_OR = 293,
    PLUS = 294,
    MINUS = 295,
    ADD_CARRY = 296,
    NOT = 297,
    BIT_NOT = 298,
    CHECKSUM = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 41 "SPExpr.y" /* yacc.c:1909  */

    uint64_t number;
    CENode   *node;

#line 104 "SPExpr.hpp" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SPEXPR_HPP_INCLUDED  */
