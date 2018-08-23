/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         _sp_assembler_yyparse
#define yylex           _sp_assembler_yylex
#define yyerror         _sp_assembler_yyerror
#define yydebug         _sp_assembler_yydebug
#define yynerrs         _sp_assembler_yynerrs


/* Copy the first part of user declarations.  */
#line 14 "sp_assembler.y" /* yacc.c:339  */

#ifndef _MSC_VER
#include <inttypes.h>  /* For standard int types and print format macros */
#include <stdbool.h>   /* For the bool type */
#endif

#include <errno.h>     /* For errno */
#include <stdlib.h>    /* For strtoull */
#ifdef _MSC_VER
#define _STDLIB_H
#endif
#include <string.h>    /* For strdup */

#include "sp_private.h"

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif

/* ---------------------------------------------------------------------------
 * Some defines that will make the grammar easier to read
 * ---------------------------------------------------------------------------*/

/* An action that take no parameters other than the context. */
#define _SP_PROC_TOK_P0(action_ok)                \
   if (!action_ok(_sp_assembler_context_p))       \
   {                                                \
      return (1);                                   \
   }

/* An action that takes the context and 1 parameter that must be freed
 * (lexical analyzer allocated the memory while collecting tokens).
 */
#define _SP_PROC_TOK_P1(action_ok, p1)            \
   if (!action_ok(_sp_assembler_context_p, p1))   \
   {                                                \
      free p1;                                      \
      return (1);                                   \
   }                                                \
   free p1;

/* An action that takes the context and 2 parameters that must be freed
 * (lexical analyzer allocated the memory while collecting tokens).
 */
#define _SP_PROC_TOK_P2(action_ok, p1, p2)            \
   if (!action_ok(_sp_assembler_context_p, p1, p2))   \
   {                                                    \
      free p1;                                          \
      free p2;                                          \
      return (1);                                       \
   }                                                    \
   free p1;                                             \
   free p2;

/* An action that takes the context and 3 parameters that must be freed
 * (lexical analyzer allocated the memory while collecting tokens).
 */
#define _SP_PROC_TOK_P3(action_ok, p1, p2, p3)            \
   if (!action_ok(_sp_assembler_context_p, p1, p2, p3))   \
   {                                                        \
      free p1;                                              \
      free p2;                                              \
      free p3;                                              \
      return (1);                                           \
   }                                                        \
   free p1;                                                 \
   free p2;                                                 \
   free p3;

/* An action that takes the context and 4 parameters that must be freed
 * (lexical analyzer allocated the memory while collecting tokens).
 */
#define _SP_PROC_TOK_P4(action_ok, p1, p2, p3, p4)            \
   if (!action_ok(_sp_assembler_context_p, p1, p2, p3, p4))   \
   {                                                            \
      free p1;                                                  \
      free p2;                                                  \
      free p3;                                                  \
      free p4;                                                  \
      return (1);                                               \
   }                                                            \
   free p1;                                                     \
   free p2;                                                     \
   free p3;                                                     \
   free p4;

/* An action that takes the context and 5 parameters that must be freed
 * (lexical analyzer allocated the memory while collecting tokens).
 */
#define _SP_PROC_TOK_P5(action_ok, p1, p2, p3, p4, p5)            \
   if (!action_ok(_sp_assembler_context_p, p1, p2, p3, p4, p5))   \
   {                                                                \
      free p1;                                                      \
      free p2;                                                      \
      free p3;                                                      \
      free p4;                                                      \
      free p5;                                                      \
      return (1);                                                   \
   }                                                                \
   free p1;                                                         \
   free p2;                                                         \
   free p3;                                                         \
   free p4;                                                         \
   free p5;

/* ---------------------------------------------------------------------------
 * Constants 
 * ---------------------------------------------------------------------------*/

#define MAX_RA_DECIMAL_INDEX_SIZE      3
#define MAX_RESULT_ARRAY_BYTE_INDEX    0x7f 
#define MAX_PARAMETER_ARRAY_BYTE_INDEX 0x3f 
#define MAX_FRAME_WINDOW_BYTE_INDEX    0x0f 
#define MAX_FRAME_WINDOW_BIT_INDEX     0x7f 

/* ---------------------------------------------------------------------------
 * Lexical Analyzer declarations
 * ---------------------------------------------------------------------------*/

int _sp_assembler_yylex (void                             *lval_p,
                           _sp_assembler_parser_context_t *context_p);

/* ---------------------------------------------------------------------------
 * Action declarations
 * ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------
 * Action for label
 *
 * Parameters:
 *    ctx_p - Parse context
 *    str_p - String containing label name.
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_label_action(_sp_assembler_parser_context_t *ctx_p,
                               char                             *str_p)
{
   _sp_label_t                 *label_p;
   _sp_assembler_instruction_t *instr_p;
   char                          *full_label_p;

   /* The context holds a hash table for all labels.  Each label object
    * in the hash table holds the program counter for the instruction
    * which follows the label.
    */

   /* Build the label name */
   full_label_p = (char *)calloc(strlen(str_p) + 1, 1);

   if (full_label_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");

      free (full_label_p); /* ROEE fixed mem leak*/
      return (false);
   }

   strcat(full_label_p, str_p);

#ifdef PROTOCOL_START_ADDR_4_BYTE_ALIGNMENT
   /* Align protocols start address at 2 instructions words (4 byte alignment) */
   /* Check if this label is the start of a new protocol */
   if (strncmp(full_label_p, "START_", 6) == 0)
   {
	   /* Check if next_program_counter is not multiple of 2 */
	   if (ctx_p->next_program_counter % 2 == 1)
	   {
		   // Insert a NOP instruction to align new protocol label
		   if (_sp_nop_action(ctx_p) == false)
		   {
			   free (full_label_p);
			   return (false);
		   }
	   }
   }
#endif //PROTOCOL_START_ADDR_4_BYTE_ALIGNMENT

   /* Store label in a hash table */
   label_p = _sp_new_label(full_label_p,
                             ctx_p->next_program_counter);

   if (label_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");

      free (full_label_p); /* ROEE fixed mem leak*/
      return (false);
   }

   if (!htbl_insert(ctx_p->label_table_p,
                    &(label_p->htbl_entry)))
   {
      _sp_destroy_label(label_p);

      _sp_assembler_yyerror(ctx_p,
                              "Label already exists.");
      free (full_label_p); /* ROEE fixed mem leak*/
      return (false);
   }

   instr_p = _sp_new_instruction(_sp_assembler_label_e,
                                   ctx_p);

   if (instr_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      free (full_label_p); /* ROEE fixed mem leak*/
      return (false);
   }

   /* Label is just a place holder, not an actual instruction. */
   instr_p->num_valid_hw_words = 0;

   instr_p->jump_label1_p = strdup(str_p);

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(instr_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   free (full_label_p); /* ROEE fixed mem leak*/
   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for five words
 *
 * Parameters:
 *    ctx_p  - Parse context
 *    str1_p - String containing hex value
 *    str2_p - String containing hex value
 *    str3_p - String containing hex value
 *    str4_p - String containing hex value
 *    str5_p - String containing hex value
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_five_hex_words_action(_sp_assembler_parser_context_t *ctx_p,
                                        char                             *str1_p,
                                        char                             *str2_p,
                                        char                             *str3_p,
                                        char                             *str4_p,
                                        char                             *str5_p)
{
   ctx_p->raw_str_p[0] = strdup(str1_p);
   ctx_p->raw_str_p[1] = strdup(str2_p);
   ctx_p->raw_str_p[2] = strdup(str3_p);
   ctx_p->raw_str_p[3] = strdup(str4_p);
   ctx_p->raw_str_p[4] = strdup(str5_p);

   if (ctx_p->raw_str_p[0] == NULL ||
       ctx_p->raw_str_p[1] == NULL ||
       ctx_p->raw_str_p[2] == NULL ||
       ctx_p->raw_str_p[3] == NULL ||
       ctx_p->raw_str_p[4] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      return (false);
   }

   ctx_p->num_immediate_values = 4;

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for four words
 *
 * Parameters:
 *    ctx_p  - Parse context
 *    str1_p - String containing hex value
 *    str2_p - String containing hex value
 *    str3_p - String containing hex value
 *    str4_p - String containing hex value
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_four_hex_words_action(_sp_assembler_parser_context_t *ctx_p,
                                        char                             *str1_p,
                                        char                             *str2_p,
                                        char                             *str3_p,
                                        char                             *str4_p)
{
   ctx_p->raw_str_p[0] = strdup(str1_p);
   ctx_p->raw_str_p[1] = strdup(str2_p);
   ctx_p->raw_str_p[2] = strdup(str3_p);
   ctx_p->raw_str_p[3] = strdup(str4_p);

   if (ctx_p->raw_str_p[0] == NULL ||
       ctx_p->raw_str_p[1] == NULL ||
       ctx_p->raw_str_p[2] == NULL ||
       ctx_p->raw_str_p[3] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      return (false);
   }

   ctx_p->num_immediate_values = 3;

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for three words
 *
 * Parameters:
 *    ctx_p  - Parse context
 *    str1_p - String containing hex value
 *    str2_p - String containing hex value
 *    str3_p - String containing hex value
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_three_hex_words_action(_sp_assembler_parser_context_t *ctx_p,
                                         char                             *str1_p,
                                         char                             *str2_p,
                                         char                             *str3_p)
{
   ctx_p->raw_str_p[0] = strdup(str1_p);
   ctx_p->raw_str_p[1] = strdup(str2_p);
   ctx_p->raw_str_p[2] = strdup(str3_p);

   if (ctx_p->raw_str_p[0] == NULL ||
       ctx_p->raw_str_p[1] == NULL ||
       ctx_p->raw_str_p[2] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      return (false);
   }

   ctx_p->num_immediate_values = 2;

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for two words
 *
 * Parameters:
 *    ctx_p  - Parse context
 *    str1_p - String containing hex value
 *    str2_p - String containing hex value
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_two_hex_words_action(_sp_assembler_parser_context_t *ctx_p,
                                       char                             *str1_p,
                                       char                             *str2_p)
{
   ctx_p->raw_str_p[0] = strdup(str1_p);
   ctx_p->raw_str_p[1] = strdup(str2_p);

   if (ctx_p->raw_str_p[0] == NULL ||
       ctx_p->raw_str_p[1] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      return (false);
   }

   ctx_p->num_immediate_values = 1;

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for one word
 *
 * Parameters:
 *    ctx_p  - Parse context
 *    str1_p - String containing hex value
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_one_hex_word_action(_sp_assembler_parser_context_t *ctx_p,
                                      char                             *str1_p)
{
   ctx_p->raw_str_p[0] = strdup(str1_p);

   if (ctx_p->raw_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      return (false);
   }

   ctx_p->num_immediate_values = 0;

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for raw instruction
 *
 * Parameters:
 *    ctx_p - Parse context
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_raw_instruction_action(_sp_assembler_parser_context_t *ctx_p)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;
   int32_t                        count;

   object_p = _sp_new_instruction(_sp_assembler_raw_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   for (count = 0; count < ctx_p->num_immediate_values + 1; count++)
   {
      len = strlen(ctx_p->raw_str_p[count]);

      if (len > 0)
      {
         object_p->hw_words_str_p[count] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[count] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            return (false);
         }

         strncpy(object_p->hw_words_str_p[count],
                 ctx_p->raw_str_p[count],
                 len);

         object_p->hw_words_p[count] = (uint16_t)strtol(ctx_p->raw_str_p[count],
                                                        NULL,
                                                        0);
      }
   }

   object_p->num_valid_hw_words = ctx_p->num_immediate_values + 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for jmp label
 *
 * Parameters:
 *    ctx_p - Parse context
 *    str_p - String containing label name.
 *    hxs   - Header examination sequence?
 *    gosub - Gosub behavior
 *    faf    - Frame Attribute Flag
 *    faf_id - Frame Attribute Flag identifier to use if faf is true. 
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_jmp_label_action(_sp_assembler_parser_context_t *ctx_p,
                                   char                             *str_p,
                                   bool                              hxs,
                                   bool                              gosub,
                                   bool                              faf,
                                   int                               faf_id)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;
   char                           jmp_faf_hxs_bit_p[] = " | 0x80";
   char                           jmp_faf_pre_id_p[]  = " | ";
   char                           hxs_bit_p[]         = " | 0x1";

   /* 1 immediate value for jump instruction - the destination*/
   ctx_p->num_immediate_values = 1;

   object_p = _sp_new_instruction(_sp_assembler_jump_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   object_p->gosub = gosub;

   if (faf)
   {
      if (hxs)
      {
         len = strlen(_SP_INSTR_CODE_JMP_FAF_STR) +
               strlen(jmp_faf_hxs_bit_p)            +
               strlen(jmp_faf_pre_id_p)             +
               strlen(_SP_INSTR_CODE_NOP_STR)     +  // All codes the same length
               1;
   
         object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);
   
         if (object_p->hw_words_str_p[0] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }
   
         snprintf(object_p->hw_words_str_p[0],
                  len,
                  "%s%s%s0x%04x",
                  _SP_INSTR_CODE_JMP_FAF_STR,
                  jmp_faf_hxs_bit_p,
                  jmp_faf_pre_id_p,
                  faf_id);
   
         object_p->hw_words_p[0] = _SP_INSTR_CODE_JMP_FAF | _SP_INSTR_MOD_JMP_FAF_HXS | faf_id;
      }
      else
      {
         len = strlen(_SP_INSTR_CODE_JMP_FAF_STR) +
               strlen(jmp_faf_pre_id_p)             +
               strlen(_SP_INSTR_CODE_NOP_STR)     +  // All codes the same length
               1;

         object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[0] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }

         snprintf(object_p->hw_words_str_p[0],
                  len,
                  "%s%s0x%04x",
                  _SP_INSTR_CODE_JMP_FAF_STR,
                  jmp_faf_pre_id_p,
                  faf_id);

         object_p->hw_words_p[0] = _SP_INSTR_CODE_JMP_FAF | faf_id;
      }
   }
   else
   {
	   if (hxs)
	   {
	      len = strlen(_SP_INSTR_CODE_JUMP_STR) +
	            strlen(hxs_bit_p)                 +
	            1;
	
	      object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);
	
	      if (object_p->hw_words_str_p[0] == NULL)
	      {
	         _sp_assembler_yyerror(ctx_p,
	                                 "Failed to allocate string.");
	         _sp_destroy_instruction(object_p);
	         return (false);
	      }
	
	      snprintf(object_p->hw_words_str_p[0],
	               len,
	               "%s%s",
	               _SP_INSTR_CODE_JUMP_STR,
	               hxs_bit_p);
	
	      object_p->hw_words_p[0] = _SP_INSTR_CODE_JUMP | _SP_INSTR_MOD_JMP_HXS;
	   }
	   else
	   {
	      len = strlen(_SP_INSTR_CODE_JUMP_STR) + 1;
	
	      object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);
	
	      if (object_p->hw_words_str_p[0] == NULL)
	      {
	         _sp_assembler_yyerror(ctx_p,
	                                 "Failed to allocate string.");
	         _sp_destroy_instruction(object_p);
	         return (false);
	      }
	
	      snprintf(object_p->hw_words_str_p[0],
	               len,
	               "%s",
	               _SP_INSTR_CODE_JUMP_STR);
	
	      object_p->hw_words_p[0] = _SP_INSTR_CODE_JUMP;
	   }
	}

   object_p->hxs                = hxs;
   object_p->num_valid_hw_words = 2;

   object_p->jump_label1_p      = strdup(str_p);

   if (object_p->jump_label1_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for jmp label if wr0 <operator> wr1
 *
 * Parameters:
 *    ctx_p      - Parse context
 *    str_p      - String containing label name.
 *    operator_p - Operator. (==, !=, <=, >=, <, >)
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_jmp_label_if_wr0_wr1_action(_sp_assembler_parser_context_t *ctx_p,
                                              char                             *str_p,
                                              uint16_t                          operator,
                                              bool                              gosub)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;
   char                           or_str_p[] = " | ";

   /* 1 immediate value for jump destination. */
   ctx_p->num_immediate_values = 1;

   object_p = _sp_new_instruction(_sp_assembler_compare_working_regs_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   object_p->gosub = gosub;

   len = strlen(_SP_INSTR_CODE_COMPARE_WORKING_REGS_STR) +
         strlen(or_str_p)                                  +
         6                                                 + /* 0xNNNN */
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s0x%04x",
            _SP_INSTR_CODE_COMPARE_WORKING_REGS_STR,
            or_str_p,
            operator);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_COMPARE_WORKING_REGS | operator;

   object_p->num_valid_hw_words = 2;
   object_p->function           = (uint8_t)operator;

   object_p->jump_label1_p      = strdup(str_p);

   if (object_p->jump_label1_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for case 1 default jump
 *
 * Parameters:
 *    ctx_p    - Parse context
 *    str1_p   - String containing label 1 name.
 *    str2_p   - String containing label 2 name.
 *    hxs      - Header examination sequence?
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_jmp_label_case1dj_action(_sp_assembler_parser_context_t *ctx_p,
                                           char                             *str1_p,
                                           char                             *str2_p,
                                           bool                              hxs_1,
                                           bool                              hxs_2,
                                           bool                              gosub)
{
   _sp_assembler_instruction_t *object_p;
   char                           or_str_p[]            = " | ";
   char                           hxs_1_not_set_str_p[] = " 0";
   char                           hxs_2_not_set_str_p[] = " (0 << 1)";
   char                           hxs_1_set_str_p[]     = " 1";
   char                           hxs_2_set_str_p[]     = " (1 << 1)";
   char                          *hxs_1_str_p;
   char                          *hxs_2_str_p;
   uint32_t                       len;

   /* Set the number of immediate values this instruction will take. */
   ctx_p->num_immediate_values = 2;

   object_p = _sp_new_instruction(_sp_assembler_case1_dj_wr_to_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   object_p->gosub = gosub;

   /* Bit layout of this instruction:
    *
    * 0000 0000 0000 10AB GL<label 1> GL<label 2>
    *
    * A - HXS for label 2  -> G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    * B - HXS for label 1  -> G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    */

   if (hxs_1)
   {
      hxs_1_str_p = hxs_1_set_str_p;
   }
   else
   {
      hxs_1_str_p = hxs_1_not_set_str_p;
   }

   if (hxs_2)
   {
      hxs_2_str_p = hxs_2_set_str_p;
   }
   else
   {
      hxs_2_str_p = hxs_2_not_set_str_p;
   }

   len = strlen(_SP_INSTR_CODE_CASE1_DJ_WR_TO_WR_STR) +
         strlen(or_str_p)                               +
         strlen(hxs_1_str_p)                            +
         strlen(or_str_p)                               +
         strlen(hxs_2_str_p)                            +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s%s%s",
            _SP_INSTR_CODE_CASE1_DJ_WR_TO_WR_STR,
            or_str_p,
            hxs_2_str_p,
            or_str_p,
            hxs_1_str_p
           );

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_CASE1_DJ_WR_TO_WR |
                             (hxs_2 << 1)                       |
                             hxs_1;

   object_p->hxs_1              = hxs_1;
   object_p->hxs_2              = hxs_2;
   object_p->num_valid_hw_words = 3;

   object_p->jump_label1_p = strdup(str1_p);

   if (object_p->jump_label1_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   object_p->jump_label2_p = strdup(str2_p);

   if (object_p->jump_label2_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for case 2 default continue
 *
 * Parameters:
 *    ctx_p    - Parse context
 *    str1_p   - String containing label 1 name.
 *    str2_p   - String containing label 2 name.
 *    hxs      - Header examination sequence?
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_jmp_label_case2dc_action(_sp_assembler_parser_context_t *ctx_p,
                                           char                             *str1_p,
                                           char                             *str2_p,
                                           bool                              hxs_1,
                                           bool                              hxs_2,
                                           bool                              gosub)
{
   _sp_assembler_instruction_t *object_p;
   char                           or_str_p[]            = " | ";
   char                           hxs_1_not_set_str_p[] = " 0";
   char                           hxs_2_not_set_str_p[] = " (0 << 1)";
   char                           hxs_1_set_str_p[]     = " 1";
   char                           hxs_2_set_str_p[]     = " (1 << 1)";
   char                          *hxs_1_str_p;
   char                          *hxs_2_str_p;
   uint32_t                       len;

   /* Set the number of immediate values this instruction will take. */
   ctx_p->num_immediate_values = 2;

   object_p = _sp_new_instruction(_sp_assembler_case2_dc_wr_to_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   object_p->gosub = gosub;

   /* Bit layout of this instruction:
    *
    * 0000 0000 0000 11AB GL<label 1> GL<label 2>
    *
    * A - HXS for label 2 -> G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    * B - HXS for label 1 -> G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    */

   if (hxs_1)
   {
      hxs_1_str_p = hxs_1_set_str_p;
   }
   else
   {
      hxs_1_str_p = hxs_1_not_set_str_p;
   }

   if (hxs_2)
   {
      hxs_2_str_p = hxs_2_set_str_p;
   }
   else
   {
      hxs_2_str_p = hxs_2_not_set_str_p;
   }

   len = strlen(_SP_INSTR_CODE_CASE2_DC_WR_TO_WR_STR) +
         strlen(or_str_p)                               +
         strlen(hxs_1_str_p)                            +
         strlen(or_str_p)                               +
         strlen(hxs_2_str_p)                            +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s%s%s",
            _SP_INSTR_CODE_CASE2_DC_WR_TO_WR_STR,
            or_str_p,
            hxs_2_str_p,
            or_str_p,
            hxs_1_str_p
           );

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_CASE2_DC_WR_TO_WR |
                             (hxs_2 << 1)                       |
                             hxs_1;

   object_p->hxs_1              = hxs_1;
   object_p->hxs_2              = hxs_2;
   object_p->num_valid_hw_words = 3;

   object_p->jump_label1_p = strdup(str1_p);

   if (object_p->jump_label1_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   object_p->jump_label2_p = strdup(str2_p);

   if (object_p->jump_label2_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for case 2 default jump
 *
 * Parameters:
 *    ctx_p    - Parse context
 *    str1_p   - String containing label 1 name.
 *    str2_p   - String containing label 2 name.
 *    str3_p   - String containing label 3 name.
 *    hxs      - Header examination sequence?
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_jmp_label_case2dj_action(_sp_assembler_parser_context_t *ctx_p,
                                           char                             *str1_p,
                                           char                             *str2_p,
                                           char                             *str3_p,
                                           bool                              hxs_1,
                                           bool                              hxs_2,
                                           bool                              hxs_3,
                                           bool                              gosub)
{
   _sp_assembler_instruction_t *object_p;
   char                           or_str_p[]            = " | ";
   char                           hxs_1_not_set_str_p[] = " 0";
   char                           hxs_2_not_set_str_p[] = " (0 << 1)";
   char                           hxs_3_not_set_str_p[] = " (0 << 2)";
   char                           hxs_1_set_str_p[]     = " 1";
   char                           hxs_2_set_str_p[]     = " (1 << 1)";
   char                           hxs_3_set_str_p[]     = " (1 << 2)";
   char                          *hxs_1_str_p;
   char                          *hxs_2_str_p;
   char                          *hxs_3_str_p;
   uint32_t                       len;

   /* Set the number of immediate values this instruction will take. */
   ctx_p->num_immediate_values = 3;

   object_p = _sp_new_instruction(_sp_assembler_case2_dj_wr_to_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   object_p->gosub = gosub;

   /* Bit layout of this instruction:
    *
    * 0000 0000 0001 0ABC <label 1> <label 2> <label 3>
    *
    * A - HXS for label 3 -> G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    * B - HXS for label 2 -> G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    * C - HXS for label 1 -> G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    */

   if (hxs_1)
   {
      hxs_1_str_p = hxs_1_set_str_p;
   }
   else
   {
      hxs_1_str_p = hxs_1_not_set_str_p;
   }

   if (hxs_2)
   {
      hxs_2_str_p = hxs_2_set_str_p;
   }
   else
   {
      hxs_2_str_p = hxs_2_not_set_str_p;
   }

   if (hxs_3)
   {
      hxs_3_str_p = hxs_3_set_str_p;
   }
   else
   {
      hxs_3_str_p = hxs_3_not_set_str_p;
   }

   len = strlen(_SP_INSTR_CODE_CASE2_DJ_WR_TO_WR_STR) +
         strlen(or_str_p)                               +
         strlen(hxs_1_str_p)                            +
         strlen(or_str_p)                               +
         strlen(hxs_2_str_p)                            +
         strlen(or_str_p)                               +
         strlen(hxs_3_str_p)                            +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s%s%s%s%s",
            _SP_INSTR_CODE_CASE2_DJ_WR_TO_WR_STR,
            or_str_p,
            hxs_3_str_p,
            or_str_p,
            hxs_2_str_p,
            or_str_p,
            hxs_1_str_p
           );

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_CASE2_DJ_WR_TO_WR |
                             (hxs_3 << 2)                       |
                             (hxs_2 << 1)                       |
                             hxs_1;

   object_p->hxs_1              = hxs_1;
   object_p->hxs_2              = hxs_2;
   object_p->hxs_3              = hxs_3;
   object_p->num_valid_hw_words = 4;

   object_p->jump_label1_p = strdup(str1_p);

   if (object_p->jump_label1_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   object_p->jump_label2_p = strdup(str2_p);

   if (object_p->jump_label2_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   object_p->jump_label3_p = strdup(str3_p);

   if (object_p->jump_label3_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for case 3 default continue
 *
 * Parameters:
 *    ctx_p    - Parse context
 *    str1_p   - String containing label 1 name.
 *    str2_p   - String containing label 2 name.
 *    str3_p   - String containing label 3 name.
 *    hxs      - Header examination sequence?
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_jmp_label_case3dc_action(_sp_assembler_parser_context_t *ctx_p,
                                           char                             *str1_p,
                                           char                             *str2_p,
                                           char                             *str3_p,
                                           bool                              hxs_1,
                                           bool                              hxs_2,
                                           bool                              hxs_3,
                                           bool                              gosub)
{
   _sp_assembler_instruction_t *object_p;
   char                           or_str_p[]            = " | ";
   char                           hxs_1_not_set_str_p[] = " 0";
   char                           hxs_2_not_set_str_p[] = " (0 << 1)";
   char                           hxs_3_not_set_str_p[] = " (0 << 2)";
   char                           hxs_1_set_str_p[]     = " 1";
   char                           hxs_2_set_str_p[]     = " (1 << 1)";
   char                           hxs_3_set_str_p[]     = " (1 << 2)";
   char                          *hxs_1_str_p;
   char                          *hxs_2_str_p;
   char                          *hxs_3_str_p;
   uint32_t                       len;

   /* Set the number of immediate values this instruction will take. */
   ctx_p->num_immediate_values = 3;

   object_p = _sp_new_instruction(_sp_assembler_case3_dc_wr_to_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   object_p->gosub = gosub;

   /* Bit layout of this instruction:
    *
    * 0000 0000 0001 1ABC <label 1> <label 2> <label 3>
    *
    * A - HXS for label 3 -> G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    * B - HXS for label 2 -> G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    * C - HXS for label 1 -> G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    */

   if (hxs_1)
   {
      hxs_1_str_p = hxs_1_set_str_p;
   }
   else
   {
      hxs_1_str_p = hxs_1_not_set_str_p;
   }

   if (hxs_2)
   {
      hxs_2_str_p = hxs_2_set_str_p;
   }
   else
   {
      hxs_2_str_p = hxs_2_not_set_str_p;
   }

   if (hxs_3)
   {
      hxs_3_str_p = hxs_3_set_str_p;
   }
   else
   {
      hxs_3_str_p = hxs_3_not_set_str_p;
   }

   len = strlen(_SP_INSTR_CODE_CASE3_DC_WR_TO_WR_STR) +
         strlen(or_str_p)                               +
         strlen(hxs_1_str_p)                            +
         strlen(or_str_p)                               +
         strlen(hxs_2_str_p)                            +
         strlen(or_str_p)                               +
         strlen(hxs_3_str_p)                            +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s%s%s%s%s",
            _SP_INSTR_CODE_CASE3_DC_WR_TO_WR_STR,
            or_str_p,
            hxs_3_str_p,
            or_str_p,
            hxs_2_str_p,
            or_str_p,
            hxs_1_str_p
           );

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_CASE3_DC_WR_TO_WR |
                             (hxs_3 << 2)                       |
                             (hxs_2 << 1)                       |
                             hxs_1;

   object_p->hxs_1              = hxs_1;
   object_p->hxs_2              = hxs_2;
   object_p->hxs_3              = hxs_3;
   object_p->num_valid_hw_words = 4;

   object_p->jump_label1_p = strdup(str1_p);

   if (object_p->jump_label1_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   object_p->jump_label2_p = strdup(str2_p);

   if (object_p->jump_label2_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   object_p->jump_label3_p = strdup(str3_p);

   if (object_p->jump_label3_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for case 3 default jump
 *
 * Parameters:
 *    ctx_p    - Parse context
 *    str1_p   - String containing label 1 name.
 *    str2_p   - String containing label 2 name.
 *    str3_p   - String containing label 3 name.
 *    hxs      - Header examination sequence?
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_jmp_label_case3dj_action(_sp_assembler_parser_context_t *ctx_p,
                                           char                             *str1_p,
                                           char                             *str2_p,
                                           char                             *str3_p,
                                           char                             *str4_p,
                                           bool                              hxs_1,
                                           bool                              hxs_2,
                                           bool                              hxs_3,
                                           bool                              hxs_4,
                                           bool                              gosub)
{
   _sp_assembler_instruction_t *object_p;
   char                           or_str_p[]            = " | ";
   char                           hxs_1_not_set_str_p[] = " 0";
   char                           hxs_2_not_set_str_p[] = " (0 << 1)";
   char                           hxs_3_not_set_str_p[] = " (0 << 2)";
   char                           hxs_4_not_set_str_p[] = " (0 << 3)";
   char                           hxs_1_set_str_p[]     = " 1";
   char                           hxs_2_set_str_p[]     = " (1 << 1)";
   char                           hxs_3_set_str_p[]     = " (1 << 2)";
   char                           hxs_4_set_str_p[]     = " (1 << 3)";
   char                          *hxs_1_str_p;
   char                          *hxs_2_str_p;
   char                          *hxs_3_str_p;
   char                          *hxs_4_str_p;
   uint32_t                       len;

   /* Set the number of immediate values this instruction will take. */
   ctx_p->num_immediate_values = 4;

   object_p = _sp_new_instruction(_sp_assembler_case3_dj_wr_to_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   object_p->gosub = gosub;

   /* Bit layout of this instruction:
    *
    * 0000 0000 0010 ABCD <label 1> <label 2> <label 3> <label 4>
    *
    * A - HXS for label 4 G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    * B - HXS for label 3 G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    * C - HXS for label 2 G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    * D - HXS for label 1 G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    */

   if (hxs_1)
   {
      hxs_1_str_p = hxs_1_set_str_p;
   }
   else
   {
      hxs_1_str_p = hxs_1_not_set_str_p;
   }

   if (hxs_2)
   {
      hxs_2_str_p = hxs_2_set_str_p;
   }
   else
   {
      hxs_2_str_p = hxs_2_not_set_str_p;
   }

   if (hxs_3)
   {
      hxs_3_str_p = hxs_3_set_str_p;
   }
   else
   {
      hxs_3_str_p = hxs_3_not_set_str_p;
   }

   if (hxs_4)
   {
      hxs_4_str_p = hxs_4_set_str_p;
   }
   else
   {
      hxs_4_str_p = hxs_4_not_set_str_p;
   }

   len = strlen(_SP_INSTR_CODE_CASE3_DJ_WR_TO_WR_STR) +
         strlen(or_str_p)                               +
         strlen(hxs_1_str_p)                            +
         strlen(or_str_p)                               +
         strlen(hxs_2_str_p)                            +
         strlen(or_str_p)                               +
         strlen(hxs_3_str_p)                            +
         strlen(or_str_p)                               +
         strlen(hxs_4_str_p)                            +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s%s%s%s%s%s%s",
            _SP_INSTR_CODE_CASE3_DJ_WR_TO_WR_STR,
            or_str_p,
            hxs_4_str_p,
            or_str_p,
            hxs_3_str_p,
            or_str_p,
            hxs_2_str_p,
            or_str_p,
            hxs_1_str_p
           );

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_CASE3_DJ_WR_TO_WR |
                             (hxs_4 << 3)                       |
                             (hxs_3 << 2)                       |
                             (hxs_2 << 1)                       |
                             hxs_1;

   object_p->hxs_1              = hxs_1;
   object_p->hxs_2              = hxs_2;
   object_p->hxs_3              = hxs_3;
   object_p->hxs_4              = hxs_4;
   object_p->num_valid_hw_words = 5;

   object_p->jump_label1_p = strdup(str1_p);

   if (object_p->jump_label1_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   object_p->jump_label2_p = strdup(str2_p);

   if (object_p->jump_label2_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   object_p->jump_label3_p = strdup(str3_p);

   if (object_p->jump_label3_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   object_p->jump_label4_p = strdup(str4_p);

   if (object_p->jump_label4_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for case 4 default continue
 *
 * Parameters:
 *    ctx_p    - Parse context
 *    str1_p   - String containing label 1 name.
 *    str2_p   - String containing label 2 name.
 *    str3_p   - String containing label 3 name.
 *    hxs      - Header examination sequence?
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_jmp_label_case4dc_action(_sp_assembler_parser_context_t *ctx_p,
                                           char                             *str1_p,
                                           char                             *str2_p,
                                           char                             *str3_p,
                                           char                             *str4_p,
                                           bool                              hxs_1,
                                           bool                              hxs_2,
                                           bool                              hxs_3,
                                           bool                              hxs_4,
                                           bool                              gosub)
{
   _sp_assembler_instruction_t *object_p;
   char                           or_str_p[]            = " | ";
   char                           hxs_1_not_set_str_p[] = " 0";
   char                           hxs_2_not_set_str_p[] = " (0 << 1)";
   char                           hxs_3_not_set_str_p[] = " (0 << 2)";
   char                           hxs_4_not_set_str_p[] = " (0 << 3)";
   char                           hxs_1_set_str_p[]     = " 1";
   char                           hxs_2_set_str_p[]     = " (1 << 1)";
   char                           hxs_3_set_str_p[]     = " (1 << 2)";
   char                           hxs_4_set_str_p[]     = " (1 << 3)";
   char                          *hxs_1_str_p;
   char                          *hxs_2_str_p;
   char                          *hxs_3_str_p;
   char                          *hxs_4_str_p;
   uint32_t                       len;

   /* Set the number of immediate values this instruction will take. */
   ctx_p->num_immediate_values = 4;

   object_p = _sp_new_instruction(_sp_assembler_case4_dc_wr_to_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   object_p->gosub = gosub;

   /* Bit layout of this instruction:
    *
    * 0000 0000 0011 ABCD <label 1> <label 2> <label 3> <label 4>
    *
    * A - HXS for label 4 G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    * B - HXS for label 3 G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    * C - HXS for label 2 G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    * D - HXS for label 1 G(gosub if set)[0], L(relative if set)[1], jump dest [5:15]
    */

   if (hxs_1)
   {
      hxs_1_str_p = hxs_1_set_str_p;
   }
   else
   {
      hxs_1_str_p = hxs_1_not_set_str_p;
   }

   if (hxs_2)
   {
      hxs_2_str_p = hxs_2_set_str_p;
   }
   else
   {
      hxs_2_str_p = hxs_2_not_set_str_p;
   }

   if (hxs_3)
   {
      hxs_3_str_p = hxs_3_set_str_p;
   }
   else
   {
      hxs_3_str_p = hxs_3_not_set_str_p;
   }

   if (hxs_4)
   {
      hxs_4_str_p = hxs_4_set_str_p;
   }
   else
   {
      hxs_4_str_p = hxs_4_not_set_str_p;
   }

   len = strlen(_SP_INSTR_CODE_CASE4_DC_WR_TO_WR_STR) +
         strlen(or_str_p)                               +
         strlen(hxs_1_str_p)                            +
         strlen(or_str_p)                               +
         strlen(hxs_2_str_p)                            +
         strlen(or_str_p)                               +
         strlen(hxs_3_str_p)                            +
         strlen(or_str_p)                               +
         strlen(hxs_4_str_p)                            +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s%s%s%s%s%s%s",
            _SP_INSTR_CODE_CASE4_DC_WR_TO_WR_STR,
            or_str_p,
            hxs_4_str_p,
            or_str_p,
            hxs_3_str_p,
            or_str_p,
            hxs_2_str_p,
            or_str_p,
            hxs_1_str_p
           );

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_CASE4_DC_WR_TO_WR |
                             (hxs_4 << 3)                       |
                             (hxs_3 << 2)                       |
                             (hxs_2 << 1)                       |
                             hxs_1;

   object_p->hxs_1              = hxs_1;
   object_p->hxs_2              = hxs_2;
   object_p->hxs_3              = hxs_3;
   object_p->hxs_4              = hxs_4;
   object_p->num_valid_hw_words = 5;

   object_p->jump_label1_p = strdup(str1_p);

   if (object_p->jump_label1_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   object_p->jump_label2_p = strdup(str2_p);

   if (object_p->jump_label2_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   object_p->jump_label3_p = strdup(str3_p);

   if (object_p->jump_label3_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   object_p->jump_label4_p = strdup(str4_p);

   if (object_p->jump_label4_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate label object.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for nop
 *
 * Parameters:
 *    ctx_p - Parse context
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_nop_action(_sp_assembler_parser_context_t *ctx_p)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;

   /* No immediate values */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_nop_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   len = strlen(_SP_INSTR_CODE_NOP_STR) + 1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s",
            _SP_INSTR_CODE_NOP_STR);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_NOP;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for Advance Header Base by Window Offset
 *
 * Parameters:
 *    ctx_p - Parse context
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_advance_hb_by_wo_action(_sp_assembler_parser_context_t *ctx_p)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;

   /* No immediate values */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_advance_hb_by_wo_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   len = strlen(_SP_INSTR_CODE_ADVANCE_HB_BY_WO_STR) + 1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s",
            _SP_INSTR_CODE_ADVANCE_HB_BY_WO_STR);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_ADVANCE_HB_BY_WO;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for result array range
 *
 * Parameters:
 *    ctx_p     - Parse context
 *    start_idx - Start index of result array range.
 *    end_idx   - End index of result array range.
 *
 * Returns:
 *   string - NULL means error, otherwise returns a string of form xxx:yyy
 * ---------------------------------------------------------------------------*/
static bool _sp_result_array_range_action(_sp_assembler_parser_context_t *ctx_p,
                                            int32_t                           start_idx,
                                            int32_t                           end_idx,
                                            bool                              is_gprv)
{
   if (is_gprv)
   {
      if (start_idx > 15)
      {
         _sp_assembler_yyerror(ctx_p,
                                 "General purpose register start index out of bounds");

         return (false);
      }

      if (end_idx > 15)
      {
         _sp_assembler_yyerror(ctx_p,
                                 "General purpose register end index out of bounds");

         return (false);
      }
   }

   if (start_idx < 0)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Result Array start index out of bounds");

      return (false);
   }

   if (end_idx < 0)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Result Array end index out of bounds");

      return (false);
   }

   if (start_idx > MAX_RESULT_ARRAY_BYTE_INDEX)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Result Array start index out of bounds");

      return (false);
   }

   if (end_idx   > MAX_RESULT_ARRAY_BYTE_INDEX)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Result Array end index out of bounds");

      return (false);
   }

   if (start_idx > end_idx)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Result Array start index > end index");

      return (false);
   }

   if (end_idx - start_idx > 7)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Result Array (end index - start index) > 7");

      return (false);
   }

   ctx_p->range_start = start_idx;
   ctx_p->range_end   = end_idx;

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for load bytes from result array to working register.
 *
 * Parameters:
 *    ctx_p      - Parse context.
 *    wr         - Working register.
 *    is_assign  - Boolean value that is true if assign, false if concat.
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_load_bytes_ra_to_wr_action(_sp_assembler_parser_context_t *ctx_p,
                                             uint8_t                           wr,
                                             bool                              is_assign)
{
   char                           wr0_str_p[]           = " | 0";
   char                           wr1_str_p[]           = " | 1";
   char                          *wr_str_p;
   char                           assign_str_p[]        = " | 0x0000";
   char                           concat_str_p[]        = " | 0x0800";
   char                          *funcion_str_p;
   char                           range_end_str_p[]     = " | (0x0000 << 4)";
   char                           num_bytes_str_p[]     = " | (0x0000 << 1)";
   uint32_t                       len;
   _sp_assembler_instruction_t *object_p;
   uint32_t                       shift = 0;

   /* No immediate value words */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_load_bytes_ra_to_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   /* Bit layout of this instruction:
    *
    * 0011 SJJJ JJJJ KKKW
    *
    * S - Shift
    * J - End of register range
    * K - Number of bytes - 1 to load
    * W - Working register (0 or 1)
    */

   /* Set working register */
   if (wr == 0)
   {
      object_p->working_register = 0;
      wr_str_p = wr0_str_p;
   }
   else
   {
      object_p->working_register = 1;
      wr_str_p = wr1_str_p;
   }

   /* Set function */
   if (is_assign)
   {
      object_p->is_assign = true;
      funcion_str_p = assign_str_p;
      shift = 0;
   }
   else
   {
      object_p->is_assign = false;
      funcion_str_p = concat_str_p;
      shift = 1;
   }

   /* Set range */
   object_p->range_start = ctx_p->range_start;
   object_p->range_end   = ctx_p->range_end;

   len = strlen(range_end_str_p) + 1;

   /* Range end */
   snprintf(range_end_str_p,
            len,
            " | (0x%04x << 4)",
            object_p->range_end);

   len = strlen(num_bytes_str_p) + 1;

   /* Num bytes - 1 */
   snprintf(num_bytes_str_p,
            len,
            " | (0x%04x << 1)",
            (object_p->range_end - object_p->range_start));

   len = strlen(_SP_INSTR_CODE_LOAD_BYTES_RA_TO_WR_STR) +
         strlen(funcion_str_p)                            +
         strlen(range_end_str_p)                          +
         strlen(num_bytes_str_p)                          +
         strlen(wr_str_p)                                 +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");

      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s%s%s",
            _SP_INSTR_CODE_LOAD_BYTES_RA_TO_WR_STR,
            funcion_str_p,
            range_end_str_p,
            num_bytes_str_p,
            wr_str_p);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_LOAD_BYTES_RA_TO_WR           |
                             (shift << 11)                                  |
                             (ctx_p->range_end << 4)                        |
                             ((ctx_p->range_end - ctx_p->range_start) << 1) |
                             wr;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for store working register to result array.
 *
 * Parameters:
 *    ctx_p - Parse context.
 *    wr    - Working register.
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_store_wr_to_ra_action(_sp_assembler_parser_context_t *ctx_p,
                                        uint8_t                           wr)
{
   char                           wr0_str_p[]           = " | 0";
   char                           wr1_str_p[]           = " | 1";
   char                          *wr_str_p;
   char                           range_end_str_p[]     = " | (0x0000 << 1)";
   char                           num_bytes_str_p[]     = " | (0x0000 << 8)";
   uint32_t                       len;
   _sp_assembler_instruction_t *object_p;

   /* No immediate value words */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_store_wr_to_ra_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   /* Bit layout of this instruction:
    *
    * 0010 1SSS TTTT TTTW
    *
    * S - Number of bytes - 1 to store
    * T - End of register range
    * W - Working register (0 or 1)
    */

   /* Set working register */
   if (wr == 0)
   {
      object_p->working_register = 0;
      wr_str_p = wr0_str_p;
   }
   else
   {
      object_p->working_register = 1;
      wr_str_p = wr1_str_p;
   }

   /* Set range */
   object_p->range_start = ctx_p->range_start;
   object_p->range_end   = ctx_p->range_end;

   len = strlen(range_end_str_p) + 1;

   /* Range end */
   snprintf(range_end_str_p,
            len,
            " | (0x%04x << 1)",
            object_p->range_end);

   len = strlen(num_bytes_str_p) + 1;

   /* Num bytes - 1 */
   snprintf(num_bytes_str_p,
            len,
            " | (0x%04x << 8)",
            (object_p->range_end - object_p->range_start));

   len = strlen(_SP_INSTR_CODE_STORE_WR_TO_RA_STR) +
         strlen(num_bytes_str_p)                     +
         strlen(range_end_str_p)                     +
         strlen(wr_str_p)                            +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");

      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s%s",
            _SP_INSTR_CODE_STORE_WR_TO_RA_STR,
            num_bytes_str_p,
            range_end_str_p,
            wr_str_p);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_STORE_WR_TO_RA                |
                             ((ctx_p->range_end - ctx_p->range_start) << 8) |
                             (ctx_p->range_end << 1)                        |
                             wr;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for store immediate value to result array.
 *
 * Parameters:
 *    ctx_p      - Parse context.
 *    iv_p       - String containing immediate value
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_store_iv_to_ra_action(_sp_assembler_parser_context_t *ctx_p,
                                        char                             *iv_p)
{
   char                           or_str_p[]           = " | ";
   char                           start_shift_str_p[]  = " | (";
   char                           end_shift_7_str_p[] = " << 7)";
   uint32_t                       len;
   uint64_t                       immediate_value      = 0;
   uint16_t                       word_1;
   uint16_t                       word_2;
   uint16_t                       word_3;
   uint16_t                       word_4;
   uint8_t                        iv_word_size         = 0;
   uint8_t                        num_iv_words         = 0;
   uint8_t                        num_iv_bytes         = 0;

   _sp_assembler_instruction_t *object_p;

   num_iv_bytes = ctx_p->range_end - ctx_p->range_start + 1;

   switch (num_iv_bytes)
   {
      case 1:
      case 2:
         num_iv_words = 1;
         ctx_p->num_immediate_values = 1;

         break;

      case 3:
      case 4:
         num_iv_words = 2;
         ctx_p->num_immediate_values = 2;
         break;

      case 5:
      case 6:
         num_iv_words = 3;
         ctx_p->num_immediate_values = 3;
         break;

      case 7:
      case 8:
         num_iv_words = 4;
         ctx_p->num_immediate_values = 4;
         break;

      default:
         _sp_assembler_yyerror(ctx_p,
                                 "INTERNAL ERROR: Default case in _sp_store_iv_to_ra_action");
         return (false);
         break;
   }

   object_p = _sp_new_instruction(_sp_assembler_store_iv_to_ra_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   /* Set range */
   object_p->range_start = ctx_p->range_start;
   object_p->range_end   = ctx_p->range_end;

   /* Check if the immediate value starts with "0x". If it does then
    * convert the value and fill in the appropriate number of immediate
    * value words based on the range requested.
    * Otherwise, this is a plan id enum.
    */
   if (strncmp(iv_p, "0x", 2) == 0)
   {
      immediate_value = (uint64_t)strtoull(iv_p, NULL, 0);

      len = 6 + /* 0xNNNN */
            1;

      word_1 =  immediate_value        & 0xffff;
      word_2 = (immediate_value >> 16) & 0xffff;
      word_3 = (immediate_value >> 32) & 0xffff;
      word_4 = (immediate_value >> 48) & 0xffff;

      if (num_iv_words == 1)
      {
         object_p->num_valid_hw_words = 2;
         iv_word_size                 = 0;

         object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[1] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }

         snprintf(object_p->hw_words_str_p[1],
                  len,
                  "0x%04x",
                  word_1);

         object_p->hw_words_p[1] = word_1;
      }
      else if (num_iv_words == 2)
      {
         object_p->num_valid_hw_words = 3;
         iv_word_size                 = 1;

         object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[2] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[1] == NULL ||
             object_p->hw_words_str_p[2] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }

         snprintf(object_p->hw_words_str_p[1],
                  len,
                  "0x%04x",
                  word_1);

         snprintf(object_p->hw_words_str_p[2],
                  len,
                  "0x%04x",
                  word_2);

         object_p->hw_words_p[1] = word_1;
         object_p->hw_words_p[2] = word_2;
      }
      else if (num_iv_words == 3)
      {
         object_p->num_valid_hw_words = 4;
         iv_word_size                 = 2;

         object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[2] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[3] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[1] == NULL ||
             object_p->hw_words_str_p[2] == NULL ||
             object_p->hw_words_str_p[3] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }

         snprintf(object_p->hw_words_str_p[1],
                  len,
                  "0x%04x",
                  word_1);

         snprintf(object_p->hw_words_str_p[2],
                  len,
                  "0x%04x",
                  word_2);

         snprintf(object_p->hw_words_str_p[3],
                  len,
                  "0x%04x",
                  word_3);

         object_p->hw_words_p[1] = word_1;
         object_p->hw_words_p[2] = word_2;
         object_p->hw_words_p[3] = word_3;
      }
      else
      {
         object_p->num_valid_hw_words = 5;
         iv_word_size                 = 3;

         object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[2] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[3] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[4] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[1] == NULL ||
             object_p->hw_words_str_p[2] == NULL ||
             object_p->hw_words_str_p[3] == NULL ||
             object_p->hw_words_str_p[4] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }

         snprintf(object_p->hw_words_str_p[1],
                  len,
                  "0x%04x",
                  word_1);

         snprintf(object_p->hw_words_str_p[2],
                  len,
                  "0x%04x",
                  word_2);

         snprintf(object_p->hw_words_str_p[3],
                  len,
                  "0x%04x",
                  word_3);

         snprintf(object_p->hw_words_str_p[4],
                  len,
                  "0x%04x",
                  word_4);

         object_p->hw_words_p[1] = word_1;
         object_p->hw_words_p[2] = word_2;
         object_p->hw_words_p[3] = word_3;
         object_p->hw_words_p[4] = word_4;
      }
   }
   else
   {
      /* There will always be 1 word with the enum in it.
       * All subsequent words will be 0x0000.
       */
      len = strlen(iv_p) + 1;

      object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);

      if (object_p->hw_words_str_p[1] == NULL)
      {
         _sp_assembler_yyerror(ctx_p,
                                 "Failed to allocate string.");
         _sp_destroy_instruction(object_p);
         return (false);
      }

      snprintf(object_p->hw_words_str_p[1],
               len,
               "%s",
               iv_p);

      object_p->hw_words_p[1] = 0;

      if (num_iv_words == 1)
      {
         object_p->num_valid_hw_words = 2;
      }
      else if (num_iv_words == 2)
      {
         len = 6 + /* 0xNNNN */
               1;

         object_p->hw_words_str_p[2] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[2] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }

         snprintf(object_p->hw_words_str_p[2],
                  len,
                  "0x0000");

         object_p->hw_words_p[1] = 0;
         object_p->hw_words_p[2] = 0;

         object_p->num_valid_hw_words = 3;
      }
      else if (num_iv_words == 3)
      {
         len = 6 + /* 0xNNNN */
               1;

         object_p->hw_words_str_p[2] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[3] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[2] == NULL ||
             object_p->hw_words_str_p[3] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }

         snprintf(object_p->hw_words_str_p[2],
                  len,
                  "0x0000");

         snprintf(object_p->hw_words_str_p[3],
                  len,
                  "0x0000");

         object_p->hw_words_p[1] = 0;
         object_p->hw_words_p[2] = 0;
         object_p->hw_words_p[3] = 0;

         object_p->num_valid_hw_words = 4;
      }
      else
      {
         len = 6 + /* 0xNNNN */
               1;

         object_p->hw_words_str_p[2] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[3] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[4] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[2] == NULL ||
             object_p->hw_words_str_p[3] == NULL ||
             object_p->hw_words_str_p[4] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }

         snprintf(object_p->hw_words_str_p[2],
                  len,
                  "0x0000");

         snprintf(object_p->hw_words_str_p[3],
                  len,
                  "0x0000");

         snprintf(object_p->hw_words_str_p[4],
                  len,
                  "0x0000");

         object_p->hw_words_p[1] = 0;
         object_p->hw_words_p[2] = 0;
         object_p->hw_words_p[3] = 0;
         object_p->hw_words_p[4] = 0;

         object_p->num_valid_hw_words = 5;
      }
   }

   /* Bit layout of this instruction:
    *
    * 0000 10SS STTT TTTT
    *
    * S - Number of bytes - 1 to store
    * T - End of register range
    */
   len = strlen(_SP_INSTR_CODE_STORE_IV_TO_RA_STR) +
         strlen(start_shift_str_p)                   +
         6                                           + /* 0xNNNN */
         strlen(end_shift_7_str_p)                   +
         strlen(or_str_p)                            +
         6                                           + /* 0xNNNN */
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s0x%04x%s%s0x%04x",
            _SP_INSTR_CODE_STORE_IV_TO_RA_STR,
            start_shift_str_p,
            num_iv_bytes - 1,
            end_shift_7_str_p,
            or_str_p,
            object_p->range_end
           );

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_STORE_IV_TO_RA |
                             ((num_iv_bytes - 1) << 7)       |
                             object_p->range_end;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for load specific value to window offset
 *
 * Parameters:
 *    ctx_p      - Parse context.
 *    str_p      - String containing hex value.
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_load_sv_to_wo_action(_sp_assembler_parser_context_t *ctx_p,
                                       char                             *str_p)
{
   _sp_assembler_instruction_t *object_p;
   char                           or_str_p[] = " | ";
   uint32_t                       len;
   uint32_t                       specific_value;

   specific_value = strtol(str_p, NULL, 0);

   /* No immediate value words */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_load_sv_to_wo_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   /* Bit layout of this instruction:
    *
    * 0000 0110 VVVV VVVV
    *
    * V - Specific value.
    */

   len = strlen(_SP_INSTR_CODE_LOAD_SV_TO_WO_STR) +
         strlen(or_str_p)                           +
         strlen(str_p)                              +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s",
            _SP_INSTR_CODE_LOAD_SV_TO_WO_STR,
            or_str_p,
            str_p);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_LOAD_SV_TO_WO |
                             specific_value;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for add specific value to window offset
 *
 * Parameters:
 *    ctx_p      - Parse context.
 *    str_p      - String containing hex value.
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_add_sv_to_wo_action(_sp_assembler_parser_context_t *ctx_p,
                                      char                             *str_p)
{
   char                           or_str_p[] = " | ";
   uint32_t                       len;
   _sp_assembler_instruction_t *object_p;
   uint32_t                       specific_value;

   specific_value = strtol(str_p, NULL, 0);


   /* No immediate value words */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_add_sv_to_wo_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   /* Bit layout of this instruction:
    *
    * 0000 0111 VVVV VVVV
    *
    * V - Specific value.
    */
   len = strlen(_SP_INSTR_CODE_ADD_SV_TO_WO_STR) +
         strlen(or_str_p)                          +
         strlen(str_p)                             +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s",
            _SP_INSTR_CODE_ADD_SV_TO_WO_STR,
            or_str_p,
            str_p);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_ADD_SV_TO_WO |
                             specific_value;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for modifying window offset by a working register
 *
 * Parameters:
 *    ctx_p      - Parse context.
 *    add        - True for add, false for set
 *    wr         - Working register number (0/1)
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_modify_wo_by_wr_action(_sp_assembler_parser_context_t *ctx_p,
                                         bool                              add,
                                         uint8_t                           wr)
{
   char                           wr0_str_p[] = " | 0x0";
   char                           wr1_str_p[] = " | 0x1";
   char                          *wr_str_p;
   char                           add_str_p[] = " | 0x2";
   char                           set_str_p[] = " | 0x0";
   char                          *mod_str_p;
   uint32_t                       len;
   _sp_assembler_instruction_t *object_p;

   /* No immediate value words */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_modify_wo_by_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   if (add)
   {
      mod_str_p = add_str_p;
   }
   else
   {
      mod_str_p = set_str_p;
   }

   if (wr == 0)
   {
      wr_str_p = wr0_str_p;
   }
   else
   {
      wr_str_p = wr1_str_p;
   }

   object_p->working_register = wr;

   /* Bit layout of this instruction:
    *
    * 0000 0000 1000 00AW
    *
    * A - Add or set
    * W - Working register
    */
   len = strlen(_SP_INSTR_CODE_MODIFY_WO_BY_WR_STR) +
         strlen(mod_str_p)                            +
         strlen(wr_str_p)                             +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s",
            _SP_INSTR_CODE_MODIFY_WO_BY_WR_STR,
            mod_str_p,
            wr_str_p);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_MODIFY_WO_BY_WR |
                             (add << 1)                       |
                             wr;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for clear working register.
 *
 * Parameters:
 *    ctx_p - Parse context.
 *    wr    - Working register.
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_zero_wr_action(_sp_assembler_parser_context_t *ctx_p,
                                 uint8_t                           wr)
{
   _sp_assembler_instruction_t *object_p;
   char                          *wr_str_p;
   char                           wr_0_str_p[] = " | 0x0";
   char                           wr_1_str_p[] = " | 0x1";
   uint32_t                       len;

   /* No immediate value words */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_zero_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   /* Bit layout of this instruction:
    *
    * 0000 0000 0000 010W
    *
    * W - Working register (0 or 1)
    */

   if (wr == 0)
   {
      wr_str_p = wr_0_str_p;
   }
   else
   {
      wr_str_p = wr_1_str_p;
   }

   len = strlen(_SP_INSTR_CODE_ZERO_WR_STR) +
         strlen(wr_str_p)                     +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s",
            _SP_INSTR_CODE_ZERO_WR_STR,
            wr_str_p);

   object_p->working_register = wr;

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_ZERO_WR | wr;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for onescomp
 *
 * Parameters:
 *    ctx_p - Parse context
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_ones_comp_wr1_to_wr0_action(_sp_assembler_parser_context_t *ctx_p)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;

   /* No immediate value words */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_ones_comp_wr1_to_wr0_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   len = strlen(_SP_INSTR_CODE_ONES_COMP_WR1_TO_WR0_STR) + 1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s",
            _SP_INSTR_CODE_ONES_COMP_WR1_TO_WR0_STR);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_ONES_COMP_WR1_TO_WR0;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for bitwise working register to working register operation
 *
 * Parameters:
 *    ctx_p    - Parse context
 *    wr       - Working register to place result in.
 *    function - Function to be used
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_bitwise_wr_wr_to_wr_action(_sp_assembler_parser_context_t *ctx_p,
                                             uint8_t                           wr,
                                             uint8_t                           function)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;
   char                           or_str_p[]          = " | ";
   char                          *wr_str_p;
   char                           wr_0_str_p[]        = " | 0x0";
   char                           wr_1_str_p[]        = " | 0x1";
   char                           start_shift_str_p[] = " (";
   char                           end_shift_1_str_p[] = " << 1)";

   /* No immediate value words */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_bitwise_wr_wr_to_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   /* Bit layout of this instruction:
    *
    * 0000 0000 0111 0FFW
    *
    * F - Function (AND/OR/XOR)
    * W - Working register (0 or 1)
    */

   if (wr == 0)
   {
      wr_str_p = wr_0_str_p;
   }
   else
   {
      wr_str_p = wr_1_str_p;
   }

   len = strlen(_SP_INSTR_CODE_BITWISE_WR_WR_TO_WR_STR) +
         strlen(or_str_p)                                 +
         strlen(start_shift_str_p)                        +
         6                                                + /* 0xNNNN */
         strlen(end_shift_1_str_p)                        +
         strlen(wr_str_p)                                 +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s0x%04x%s%s",
            _SP_INSTR_CODE_BITWISE_WR_WR_TO_WR_STR,
            or_str_p,
            start_shift_str_p,
            function,
            end_shift_1_str_p,
            wr_str_p);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_BITWISE_WR_WR_TO_WR |
                             (function << 1)                      |
                             wr;

   object_p->working_register = wr;
   object_p->function         = function;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for bitwise immediate value to working register operation
 *
 * Parameters:
 *    ctx_p     - Parse context
 *    target_wr - Working register to place result in
 *    source_wr - Working register to operate on with immediate value
 *    function  - Function to be used
 *    iv_p      - Immediate value
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_bitwise_wr_iv_to_wr_action(_sp_assembler_parser_context_t *ctx_p,
                                             uint8_t                           target_wr,
                                             uint8_t                           source_wr,
                                             uint8_t                           function,
                                             char                             *iv_p)
{
   _sp_assembler_instruction_t *object_p;
   char                           start_shift_str_p[] = " | (";
   char                           end_shift_3_str_p[] = " << 3)";
   char                           end_shift_1_str_p[] = " << 1)";
   char                           tgt_wr_0_str_p[]    = " | (0x0 << 5)";
   char                           tgt_wr_1_str_p[]    = " | (0x1 << 5)";
   char                           src_wr_0_str_p[]    = " | 0x0";
   char                           src_wr_1_str_p[]    = " | 0x1";
   char                          *src_wr_str_p;
   char                          *tgt_wr_str_p;
   uint32_t                       len;
   uint64_t                       immediate_value      = 0;
   uint16_t                       word_1;
   uint16_t                       word_2;
   uint16_t                       word_3;
   uint16_t                       word_4;
   uint8_t                        iv_word_size         = 0;

   if (source_wr == 0)
   {
      src_wr_str_p = src_wr_0_str_p;
   }
   else
   {
      src_wr_str_p = src_wr_1_str_p;
   }

   if (target_wr == 0)
   {
      tgt_wr_str_p = tgt_wr_0_str_p;
   }
   else
   {
      tgt_wr_str_p = tgt_wr_1_str_p;
   }

   /* This instruction is always 4 immediate value words */
   ctx_p->num_immediate_values   = 4;

   object_p = _sp_new_instruction(_sp_assembler_bitwise_wr_iv_to_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   /* Assume immediate value is always 64 bits as the user
    * will be performing the operation over the whole register.
    * This means all immediate values are padded on the left with 0
    * and the function is performed on the entire source WR. */
   object_p->num_valid_hw_words  = 5;
   iv_word_size                  = 3;

   /* Check if the immediate value starts with "0x". If it does then
    * convert the value. Otherwise, this is a plan id enum.
    */
   if (strncmp(iv_p, "0x", 2) == 0)
   {
      errno = 0;

      immediate_value = (uint64_t)strtoull(iv_p, NULL, 0);

      if (errno != 0)
      {
         _sp_assembler_yyerror(ctx_p,
                                 "Failed to convert immediate value.");
         _sp_destroy_instruction(object_p);
         return (false);
      }

      len = 6 + /* 0xNNNN */
            1;

      word_1 =  immediate_value        & 0xffff;
      word_2 = (immediate_value >> 16) & 0xffff;
      word_3 = (immediate_value >> 32) & 0xffff;
      word_4 = (immediate_value >> 48) & 0xffff;

      object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);
      object_p->hw_words_str_p[2] = (char *)calloc(len + 1, 1);
      object_p->hw_words_str_p[3] = (char *)calloc(len + 1, 1);
      object_p->hw_words_str_p[4] = (char *)calloc(len + 1, 1);

      object_p->hw_words_p[1] = word_1;
      object_p->hw_words_p[2] = word_2;
      object_p->hw_words_p[3] = word_3;
      object_p->hw_words_p[4] = word_4;

      if (object_p->hw_words_str_p[1] == NULL ||
          object_p->hw_words_str_p[2] == NULL ||
          object_p->hw_words_str_p[3] == NULL ||
          object_p->hw_words_str_p[4] == NULL)
      {
         _sp_assembler_yyerror(ctx_p,
                                 "Failed to allocate string.");
         _sp_destroy_instruction(object_p);
         return (false);
      }

      snprintf(object_p->hw_words_str_p[1],
               len,
               "0x%04x",
               word_1);

      snprintf(object_p->hw_words_str_p[2],
               len,
               "0x%04x",
               word_2);

      snprintf(object_p->hw_words_str_p[3],
               len,
               "0x%04x",
               word_3);

      snprintf(object_p->hw_words_str_p[4],
               len,
               "0x%04x",
               word_4);
   }
   else
   {
      len = strlen(iv_p) + 1;

      object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);

      if (object_p->hw_words_str_p[1] == NULL)
      {
         _sp_assembler_yyerror(ctx_p,
                                 "Failed to allocate string.");
         _sp_destroy_instruction(object_p);
         return (false);
      }

      snprintf(object_p->hw_words_str_p[1],
               len,
               "%s",
               iv_p);

      /* Pad other immediate value words with 0 */

      len = 6 + /* 0xNNNN */
            1;

      object_p->hw_words_str_p[2] = (char *)calloc(len + 1, 1);
      object_p->hw_words_str_p[3] = (char *)calloc(len + 1, 1);
      object_p->hw_words_str_p[4] = (char *)calloc(len + 1, 1);

      /* HW opcodes */
      object_p->hw_words_p[1] = 0;
      object_p->hw_words_p[2] = 0;
      object_p->hw_words_p[3] = 0;
      object_p->hw_words_p[4] = 0;

      if (object_p->hw_words_str_p[1] == NULL ||
          object_p->hw_words_str_p[2] == NULL ||
          object_p->hw_words_str_p[3] == NULL)
      {
         _sp_assembler_yyerror(ctx_p,
                                 "Failed to allocate string.");
         _sp_destroy_instruction(object_p);
         return (false);
      }

      snprintf(object_p->hw_words_str_p[2],
               len,
               "0x0000");

      snprintf(object_p->hw_words_str_p[3],
               len,
               "0x0000");

      snprintf(object_p->hw_words_str_p[4],
               len,
               "0x0000");
   }

   /* Bit layout of this instruction:
    *
    * 0000 0000 11VI IFFW
    *
    * V - Target working register (0 or 1)
    * I - Immediate value size
    * F - Function (OR/AND/XOR)
    * W - Source working register (0 or 1)
    */

   len = strlen(_SP_INSTR_CODE_BITWISE_WR_IV_TO_WR_STR) +
         strlen(tgt_wr_str_p)                             +
         strlen(start_shift_str_p)                        +
         6                                                + /* 0xNNNN */
         strlen(end_shift_3_str_p)                        +
         strlen(start_shift_str_p)                        +
         6                                                + /* 0xNNNN */
         strlen(end_shift_1_str_p)                        +
         strlen(src_wr_str_p)                             +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s0x%04x%s%s0x%04x%s%s",
            _SP_INSTR_CODE_BITWISE_WR_IV_TO_WR_STR,
            tgt_wr_str_p,
            start_shift_str_p,
            iv_word_size,
            end_shift_3_str_p,
            start_shift_str_p,
            function,
            end_shift_1_str_p,
            src_wr_str_p);

   object_p->hw_words_p[0] = _SP_INSTR_CODE_BITWISE_WR_IV_TO_WR |
                             (target_wr << 5)                     |
                             (iv_word_size << 3)                  |
                             (function << 1)                      |
                             source_wr;

   object_p->target_working_register = target_wr;
   object_p->source_working_register = source_wr;
   object_p->function                = function;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));


   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for addsub working register to working register operation
 *
 * Parameters:
 *    ctx_p         - Parse context
 *    target        - Working register to place result
 *    left_operand  - Left operand of operation
 *    function      - Function to be used
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_addsub_wr_wr_to_wr_action(_sp_assembler_parser_context_t *ctx_p,
                                            uint8_t                           target,
                                            uint8_t                           left_operand,
                                            uint8_t                           function)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;
   char                          *target_str_p;
   char                           target_0_str_p[]    = " | 0x0";
   char                           target_1_str_p[]    = " | 0x4";
   char                          *function_str_p;
   char                           add_str_p[]         = " | 0x0";
   char                           sub_str_p[]         = " | 0x2";
   char                          *left_op_str_p;
   char                           left_0_str_p[]      = " | 0x0";
   char                           left_1_str_p[]      = " | 0x1";

   /* No immediate value words */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_addsub_wr_wr_to_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   /* Bit layout of this instruction:
    *
    * 0000 0000 0100 1VOL
    *
    * V - Target working register
    * O - Operation (0 add, 1 subtract)
    * L - Left operand (other working register is the right operand)
    */

   if (target == 0)
   {
      target_str_p = target_0_str_p;
   }
   else
   {
      target_str_p = target_1_str_p;
   }

   if (function == 0)
   {
      function_str_p = add_str_p;
   }
   else
   {
      function_str_p = sub_str_p;
   }

   if (left_operand == 0)
   {
      left_op_str_p = left_0_str_p;
   }
   else
   {
      left_op_str_p = left_1_str_p;
   }

   len = strlen(_SP_INSTR_CODE_ADDSUB_WR_WR_TO_WR_STR) +
         strlen(target_str_p)                            +
         strlen(function_str_p)                          +
         strlen(left_op_str_p)                           +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s%s",
            _SP_INSTR_CODE_ADDSUB_WR_WR_TO_WR_STR,
            target_str_p,
            function_str_p,
            left_op_str_p);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_ADDSUB_WR_WR_TO_WR |
                             (target << 2)                       |
                             (function << 1)                     |
                             left_operand;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for addsub immediate value to working register operation
 *
 * Parameters:
 *    ctx_p         - Parse context
 *    target        - Working register to place result
 *    source        - Working register to use as source operand
 *    function      - Function to be used
 *    iv_p          - Immediate value
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_addsub_wr_iv_to_wr_action(_sp_assembler_parser_context_t *ctx_p,
                                            uint8_t                           target,
                                            uint8_t                           source,
                                            uint8_t                           function,
                                            char                             *iv_p)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;
   char                          *size_str_p;
   char                           size16_str_p[]      = " | 0x0";
   char                           size32_str_p[]      = " | 0x8";
   char                          *target_str_p;
   char                           target_0_str_p[]    = " | 0x0";
   char                           target_1_str_p[]    = " | 0x4";
   char                          *function_str_p;
   char                           add_str_p[]         = " | 0x0";
   char                           sub_str_p[]         = " | 0x2";
   char                          *source_str_p;
   char                           source_0_str_p[]    = " | 0x0";
   char                           source_1_str_p[]    = " | 0x1";
   uint64_t                       immediate_value     = 0;
   uint16_t                       word_1;
   uint16_t                       word_2;
   uint32_t                       size = 0;

   /* Check if the immediate value starts with "0x". If it does then
    * convert the value and base the number of immediate value words
    * on that.  Otherwise, this is a plan id enum which is 1 byte so
    * only use 1 immediate value word.
    */
   if (strncmp(iv_p, "0x", 2) == 0)
   {
      errno = 0;
   
      immediate_value = (uint64_t)strtoull(iv_p, NULL, 0);

      if (errno != 0)
      {
         _sp_assembler_yyerror(ctx_p,
                                 "Failed to convert immediate value.");
         return (false);
      }

      if (immediate_value < 0x10000)
      {
         size_str_p = size16_str_p;
         ctx_p->num_immediate_values = 1;
         size = 0;
      }
      else if (immediate_value < 0x100000000ULL)
      {
         size_str_p = size32_str_p;
         ctx_p->num_immediate_values = 2;
         size = 1;
      }
      else
      {
         _sp_assembler_yyerror(ctx_p,
                                 "Immediate value > 32 bits. Not allowed for this instruction.");
         return (false);
      }
   }
   else
   {
      size_str_p = size16_str_p;
      ctx_p->num_immediate_values = 1;
      size = 0;
   }

   if (target == 0)
   {
      target_str_p = target_0_str_p;
   }
   else
   {
      target_str_p = target_1_str_p;
   }

   if (source == 0)
   {
      source_str_p = source_0_str_p;
   }
   else
   {
      source_str_p = source_1_str_p;
   }

   object_p = _sp_new_instruction(_sp_assembler_addsub_wr_wr_to_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   /* Bit layout of this instruction:
    *
    * 0000 0000 0101 SVOW
    *
    * S - Size of immediate value (0 -> 16 bytes, 1 -> 32 bytes)
    * V - Target working register
    * O - Operation (0 add, 1 subtract)
    * W - Working register to use as operand
    */

   if (target == 0)
   {
      target_str_p = target_0_str_p;
   }
   else
   {
      target_str_p = target_1_str_p;
   }

   if (function == 0)
   {
      function_str_p = add_str_p;
   }
   else
   {
      function_str_p = sub_str_p;
   }

   if (source == 0)
   {
      source_str_p = source_0_str_p;
   }
   else
   {
      source_str_p = source_1_str_p;
   }

   len = strlen(_SP_INSTR_CODE_ADDSUB_WR_IV_TO_WR_STR) +
         strlen(size_str_p)                              +
         strlen(target_str_p)                            +
         strlen(function_str_p)                          +
         strlen(source_str_p)                            +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s%s%s",
            _SP_INSTR_CODE_ADDSUB_WR_IV_TO_WR_STR,
            size_str_p,
            target_str_p,
            function_str_p,
            source_str_p);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_ADDSUB_WR_IV_TO_WR |
                             (size << 3)                         |
                             (target << 2)                       |
                             (function << 1)                     |
                             source;

   if (strncmp(iv_p, "0x", 2) == 0)
   {
      len = 6 + /* 0xNNNN */
            1;

      word_1 =  immediate_value        & 0xffff;
      word_2 = (immediate_value >> 16) & 0xffff;

      if (ctx_p->num_immediate_values == 1)
      {
         object_p->num_valid_hw_words = 2;

         object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[1] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }

         snprintf(object_p->hw_words_str_p[1],
                  len,
                  "0x%04x",
                  word_1);

         object_p->hw_words_p[1] = word_1;
      }
      else
      {
         object_p->num_valid_hw_words = 3;

         object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[2] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[1] == NULL ||
             object_p->hw_words_str_p[2] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }

         snprintf(object_p->hw_words_str_p[1],
                  len,
                  "0x%04x",
                  word_1);

         snprintf(object_p->hw_words_str_p[2],
                  len,
                  "0x%04x",
                  word_2);

         object_p->hw_words_p[1] = word_1;
         object_p->hw_words_p[2] = word_2;
      }
   }
   else
   {
      object_p->num_valid_hw_words = 2;

      len = strlen(iv_p) + 1;

      object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);

      if (object_p->hw_words_str_p[1] == NULL)
      {
         _sp_assembler_yyerror(ctx_p,
                                 "Failed to allocate string.");
         _sp_destroy_instruction(object_p);
         return (false);
      }

      snprintf(object_p->hw_words_str_p[1],
               len,
               "%s",
               iv_p);

         object_p->hw_words_p[1] = 0;
   }

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   free (iv_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for shift left working register by specific value.
 *
 * Parameters:
 *    ctx_p - Parse context
 *    wr    - Working register
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_bitwise_shift_left_wr_by_sv_action(_sp_assembler_parser_context_t *ctx_p,
                                                     uint8_t                           wr,
                                                     char                             *sv_p)
{
   _sp_assembler_instruction_t *object_p;
   uint8_t                        specific_value;
   char                           start_shift_str_p[] = " | (";
   char                           end_shift_1_str_p[] = " << 1)";
   char                           wr_0_str_p[]        = " | 0x0";
   char                           wr_1_str_p[]        = " | 0x1";
   char                          *wr_str_p;
   uint32_t                       len;

   errno = 0;

   specific_value = (uint8_t)strtoul(sv_p, NULL, 0);

   if (errno != 0)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to convert immediate value.");
      return (false);
   }

   if (specific_value == 0)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Shift left value of 0 is not allowed.");
      return (false);
   }

   if (specific_value > 64)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Shift left value too large.");
      return (false);
   }

   /* Specific value is stored as val - 1 in instruction */
   specific_value--;

   /* No immediate value words */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_shift_left_wr_by_sv_e,
                                    ctx_p);
   
   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }
   
   /* Bit layout of this instruction:
    *
    * 0000 0001 0ZZZ ZZZW
    *
    * W - Working register (0 or 1)
    * Z - Specific value - 1
    */
   
   object_p->working_register = wr;
   
   if (wr == 0)
   {
      wr_str_p = wr_0_str_p;
   }
   else
   {
      wr_str_p = wr_1_str_p;
   }

   len = strlen(_SP_INSTR_CODE_SHIFT_LEFT_WR_BY_SV_STR) +
         strlen(start_shift_str_p)                        +
         6                                                + /* 0xNNNN */
         strlen(end_shift_1_str_p)                        +
         strlen(wr_str_p)                                 +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s0x%04x%s%s",
            _SP_INSTR_CODE_SHIFT_LEFT_WR_BY_SV_STR,
            start_shift_str_p,
            specific_value,
            end_shift_1_str_p,
            wr_str_p);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_SHIFT_LEFT_WR_BY_SV |
                             (specific_value << 1)                |
                             wr;

   object_p->num_valid_hw_words = 1;
   
   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for shift right working register by specific value.
 *
 * Parameters:
 *    ctx_p - Parse context
 *    wr    - Working register
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_bitwise_shift_right_wr_by_sv_action(_sp_assembler_parser_context_t *ctx_p,
                                                      uint8_t                           wr,
                                                      char                             *sv_p)
{
   _sp_assembler_instruction_t *object_p;
   uint8_t                        specific_value;
   char                           start_shift_str_p[] = " | (";
   char                           end_shift_1_str_p[] = " << 1)";
   char                           wr_0_str_p[]        = " | 0x0";
   char                           wr_1_str_p[]        = " | 0x1";
   char                          *wr_str_p;
   uint32_t                       len;

   errno = 0;

   specific_value = (uint8_t)strtoul(sv_p, NULL, 0);

   if (errno != 0)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to convert immediate value.");
      return (false);
   }

   if (specific_value == 0)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Shift right value 0 is not allowed.");
      return (false);
   }

   if (specific_value > 64)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Shift right value too large.");
      return (false);
   }

   /* Specific value is stored as val - 1 in instruction */
   specific_value--;

   /* No immediate value words */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_shift_right_wr_by_sv_e,
                                    ctx_p);
   
   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }
   
   /* Bit layout of this instruction:
    *
    * 0000 0001 1ZZZ ZZZW
    *
    * W - Working register (0 or 1)
    * Z - Specific value - 1
    */
   
   object_p->working_register = wr;
   
   if (wr == 0)
   {
      wr_str_p = wr_0_str_p;
   }
   else
   {
      wr_str_p = wr_1_str_p;
   }

   len = strlen(_SP_INSTR_CODE_SHIFT_RIGHT_WR_BY_SV_STR) +
         strlen(start_shift_str_p)                         +
         6                                                 + /* 0xNNNN */
         strlen(end_shift_1_str_p)                         +
         strlen(wr_str_p)                                  +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s0x%04x%s%s",
            _SP_INSTR_CODE_SHIFT_RIGHT_WR_BY_SV_STR,
            start_shift_str_p,
            specific_value,
            end_shift_1_str_p,
            wr_str_p);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_SHIFT_RIGHT_WR_BY_SV |
                             (specific_value << 1)                |
                             wr;

   object_p->num_valid_hw_words = 1;
   
   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for load bits immediate value to working register.
 *
 * Parameters:
 *    ctx_p      - Parse context.
 *    wr         - Working register.
 *    iv_p       - String containing immediate value.
 *    num_bits   - Number of bits to load.
 *    is_assign  - Assignment (true) or concat (false).
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_load_bits_iv_to_wr_action(_sp_assembler_parser_context_t *ctx_p,
                                            uint8_t                           wr,
                                            char                             *iv_p,
                                            uint8_t                           num_bits,
                                            bool                              is_assign)
{
   uint32_t                       auto_num_bits         = 0;
   _sp_assembler_instruction_t *object_p;
   char                           start_shift_str_p[]  = " | (";
   char                           end_shift_1_str_p[]  = " << 1)";
   char                           assign_str_p[]       = " | (0x0 << 7)";
   char                           concat_str_p[]       = " | (0x1 << 7)";
   char                          *func_str_p;
   char                           wr_0_str_p[]         = " | 0x0";
   char                           wr_1_str_p[]         = " | 0x1";
   char                          *wr_str_p;
   uint32_t                       len;
   uint64_t                       immediate_value      = 0;
   uint16_t                       word_1;
   uint16_t                       word_2;
   uint16_t                       word_3;
   uint16_t                       word_4;
   uint32_t                       shift = 0;

   /* Check if the immediate value starts with "0x". If it does then
    * convert the value and base the number of immediate value words
    * on that.  Otherwise, this is a plan id enum which is 1 byte so
    * only use 1 immediate value word.
    */
   if (strncmp(iv_p, "0x", 2) == 0)
   {
      errno = 0;
   
      immediate_value = (uint64_t)strtoull(iv_p, NULL, 0);

      if (errno != 0)
      {
         _sp_assembler_yyerror(ctx_p,
                                 "Failed to convert immediate value.");
         return (false);
      }

      if (immediate_value < 0x10000)
      {
         auto_num_bits = 16;
      }
      else if (immediate_value < 0x100000000ULL)
      {
         auto_num_bits = 32;
      }
      else if (immediate_value < 0x1000000000000ULL)
      {
         auto_num_bits = 48;
      }
      else
      {
         auto_num_bits = 64;
      }
   }
   else
   {
      auto_num_bits = 16;
   }

   if (wr == 0)
   {
      wr_str_p = wr_0_str_p;
   }
   else
   {
      wr_str_p = wr_1_str_p;
   }

   /* Use automatic value for number of bits if none supplied. */
   if (num_bits == 0)
   {
      num_bits = auto_num_bits;
   }

   /* Immediate value words */
   if (num_bits < 17)
   {
      ctx_p->num_immediate_values = 1;
   }
   else if (num_bits < 33)
   {
      ctx_p->num_immediate_values = 2;
   }
   else if (num_bits < 49)
   {
      ctx_p->num_immediate_values = 3;
   }
   else
   {
      ctx_p->num_immediate_values = 4;
   }

   object_p = _sp_new_instruction(_sp_assembler_load_bits_iv_to_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   if (is_assign)
   {
      func_str_p = assign_str_p;
      object_p->is_assign = true;
      shift = 0;
   }
   else
   {
      func_str_p = concat_str_p;
      object_p->is_assign = false;
      shift = 1;
   }

   /* Check if the immediate value starts with "0x". If it does then
    * convert the value and base the number of immediate value words
    * on that.  Otherwise, this is a plan id enum which is 1 byte so
    * only use 1 immediate value word.
    */
   if (strncmp(iv_p, "0x", 2) == 0)
   {
      len = 6 + /* 0xNNNN */
            1;

      word_1 =  immediate_value        & 0xffff;
      word_2 = (immediate_value >> 16) & 0xffff;
      word_3 = (immediate_value >> 32) & 0xffff;
      word_4 = (immediate_value >> 48) & 0xffff;

      if (num_bits <= 16)
      {
         object_p->num_valid_hw_words = 2;

         object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[1] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }

         snprintf(object_p->hw_words_str_p[1],
                  len,
                  "0x%04x",
                  word_1);

         object_p->hw_words_p[1] = word_1;
      }
      else if (num_bits <= 32)
      {
         object_p->num_valid_hw_words = 3;

         object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[2] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[1] == NULL ||
             object_p->hw_words_str_p[2] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }

         snprintf(object_p->hw_words_str_p[1],
                  len,
                  "0x%04x",
                  word_1);

         snprintf(object_p->hw_words_str_p[2],
                  len,
                  "0x%04x",
                  word_2);

         object_p->hw_words_p[1] = word_1;
         object_p->hw_words_p[2] = word_2;
      }
      else if (num_bits <= 48)
      {
         object_p->num_valid_hw_words = 4;

         object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[2] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[3] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[1] == NULL ||
             object_p->hw_words_str_p[2] == NULL ||
             object_p->hw_words_str_p[3] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }

         snprintf(object_p->hw_words_str_p[1],
                  len,
                  "0x%04x",
                  word_1);

         snprintf(object_p->hw_words_str_p[2],
                  len,
                  "0x%04x",
                  word_2);

         snprintf(object_p->hw_words_str_p[3],
                  len,
                  "0x%04x",
                  word_3);

         object_p->hw_words_p[1] = word_1;
         object_p->hw_words_p[2] = word_2;
         object_p->hw_words_p[3] = word_3;
      }
      else
      {
         object_p->num_valid_hw_words = 5;

         object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[2] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[3] = (char *)calloc(len + 1, 1);
         object_p->hw_words_str_p[4] = (char *)calloc(len + 1, 1);

         if (object_p->hw_words_str_p[1] == NULL ||
             object_p->hw_words_str_p[2] == NULL ||
             object_p->hw_words_str_p[3] == NULL ||
             object_p->hw_words_str_p[4] == NULL)
         {
            _sp_assembler_yyerror(ctx_p,
                                    "Failed to allocate string.");
            _sp_destroy_instruction(object_p);
            return (false);
         }

         snprintf(object_p->hw_words_str_p[1],
                  len,
                  "0x%04x",
                  word_1);

         snprintf(object_p->hw_words_str_p[2],
                  len,
                  "0x%04x",
                  word_2);

         snprintf(object_p->hw_words_str_p[3],
                  len,
                  "0x%04x",
                  word_3);

         snprintf(object_p->hw_words_str_p[4],
                  len,
                  "0x%04x",
                  word_4);

         object_p->hw_words_p[1] = word_1;
         object_p->hw_words_p[2] = word_2;
         object_p->hw_words_p[3] = word_3;
         object_p->hw_words_p[4] = word_4;
      }
   }
   else
   {
      if (num_bits > 16)
      {
         _sp_assembler_yyerror(ctx_p,
                                 "Bit size too large. Can only load 16 bits from an id.");
         _sp_destroy_instruction(object_p);
         return (false);
      }

      object_p->num_valid_hw_words = 2;

      len = strlen(iv_p) + 1;

      object_p->hw_words_str_p[1] = (char *)calloc(len + 1, 1);

      if (object_p->hw_words_str_p[1] == NULL)
      {
         _sp_assembler_yyerror(ctx_p,
                                 "Failed to allocate string.");
         _sp_destroy_instruction(object_p);
         return (false);
      }

      snprintf(object_p->hw_words_str_p[1],
               len,
               "%s",
               iv_p);

      object_p->hw_words_p[1] = 0;
   }

   /* Bit layout of this instruction:
    *
    * 0000 0010 SNNN NNNW
    *
    * S - Assign or concat
    * N - Number of bits
    * W - Working register
    */

   len = strlen(_SP_INSTR_CODE_LOAD_BITS_IV_TO_WR_STR) +
         strlen(func_str_p)                              +
         strlen(start_shift_str_p)                       +
         6                                               + /* 0xNNNN */
         strlen(end_shift_1_str_p)                       +
         strlen(wr_str_p)                                +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s0x%04x%s%s",
            _SP_INSTR_CODE_LOAD_BITS_IV_TO_WR_STR,
            func_str_p,
            start_shift_str_p,
            num_bits - 1,          /* coded as 0 -> 63 for 1 -> 64 */
            end_shift_1_str_p,
            wr_str_p);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_LOAD_BITS_IV_TO_WR |
                             (shift << 7)                        |
                             ((num_bits - 1) << 1)               |
                             wr;

   object_p->num_bits = num_bits;
   object_p->working_register = wr;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for load bytes parameter array to working register.
 *
 * Parameters:
 *    ctx_p       - Parse context.
 *    wr          - Working register.
 *    start_range - Start of parameter array range.
 *    end_range   - End of parameter array range.
 *    is_assign   - Assignment (true) or concat (false).
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_load_bytes_pa_to_wr_action(_sp_assembler_parser_context_t *ctx_p,
                                             uint8_t                           wr,
                                             uint32_t                          range_start,
                                             uint32_t                          range_end,
                                             bool                              is_assign)
{
   _sp_assembler_instruction_t *object_p;
   char                           wr0_str_p[]           = " | 0x0";
   char                           wr1_str_p[]           = " | 0x1";
   char                           assign_str_p[]        = " | (0x0 << 10)";
   char                           concat_str_p[]        = " | (0x1 << 10)";
   char                          *wr_str_p;
   char                          *func_str_p;
   char                           range_end_str_p[]     = " | (0x0000 << 4)";
   char                           num_bytes_str_p[]     = " | (0x0000 << 1)";
   uint32_t                       len;
   uint32_t                       shift = 0;

   if (range_start > MAX_PARAMETER_ARRAY_BYTE_INDEX)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Parameter Array start index out of bounds");

      return (false);
   }

   if (range_end   > MAX_PARAMETER_ARRAY_BYTE_INDEX)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Parameter Array end index out of bounds");

      return (false);
   }

   if (range_start > range_end)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Parameter Array start index > end index");

      return (false);
   }

   if (range_end - range_start > 7)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Parameter Array (end index - start index) > 7");

      return (false);
   }

   /* No immediate value words */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_load_bytes_pa_to_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   /* Bit layout of this instruction:
    *
    * 0001 0SJJ JJJJ KKKW
    *
    * S - Assign or concat
    * J - End of range
    * K - Number of bytes - 1
    * W - Working register
    */

   /* Assign or concat */
   if (is_assign)
   {
      func_str_p = assign_str_p;
      object_p->is_assign = true;
      shift = 0;
   }
   else
   {
      func_str_p = concat_str_p;
      object_p->is_assign = false;
      shift = 1;
   }

   /* Set working register */
   if (wr == 0)
   {
      object_p->working_register = 0;
      wr_str_p = wr0_str_p;
   }
   else
   {
      object_p->working_register = 1;
      wr_str_p = wr1_str_p;
   }

   /* Set range */
   object_p->range_start = range_start;
   object_p->range_end   = range_end;

   len = strlen(range_end_str_p) + 1;

   /* Range end */
   snprintf(range_end_str_p,
            len,
            " | (0x%04x << 4)",
            object_p->range_end);

   len = strlen(num_bytes_str_p) + 1;

   /* Num bytes - 1 */
   snprintf(num_bytes_str_p,
            len,
            " | (0x%04x << 1)",
            (object_p->range_end - object_p->range_start));

   len = strlen(_SP_INSTR_CODE_LOAD_BYTES_PA_TO_WR_STR) +
         strlen(func_str_p)                               +
         strlen(range_end_str_p)                          +
         strlen(num_bytes_str_p)                          +
         strlen(wr_str_p)                                 +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");

      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s%s%s",
            _SP_INSTR_CODE_LOAD_BYTES_PA_TO_WR_STR,
            func_str_p,
            range_end_str_p,
            num_bytes_str_p,
            wr_str_p);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_LOAD_BYTES_PA_TO_WR |
                             (shift << 10)                        |
                             (range_end << 4)                     |
                             ((range_end - range_start) << 1)     |
                             wr;

   object_p->working_register   = wr;
   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for load bits frame window to working register.
 *
 * Parameters:
 *    ctx_p       - Parse context.
 *    wr          - Working register.
 *    range_start - Start of frame window range.
 *    range_end   - End of frame window range.
 *    is_assign   - Assignment (true) or concat (false).
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_load_bits_fw_to_wr_action(_sp_assembler_parser_context_t *ctx_p,
                                            uint8_t                           wr,
                                            uint32_t                          range_start,
                                            uint32_t                          range_end,
                                            bool                              is_assign)
{
   _sp_assembler_instruction_t *object_p;
   char                           wr0_str_p[]           = " | 0x0";
   char                           wr1_str_p[]           = " | 0x1";
   char                           assign_str_p[]        = " | (0x0 << 14)";
   char                           concat_str_p[]        = " | (0x1 << 14)";
   char                          *wr_str_p;
   char                          *func_str_p;
   char                           range_end_str_p[]     = " | (0x0000 << 7)";
   char                           num_bytes_str_p[]     = " | (0x0000 << 1)";
   uint32_t                       len;
   uint32_t                       shift = 0;

   if (range_start > MAX_FRAME_WINDOW_BIT_INDEX)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Frame Window start index out of bounds");

      return (false);
   }

   if (range_end   > MAX_FRAME_WINDOW_BIT_INDEX)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Frame Window end index out of bounds");

      return (false);
   }

   if (range_start > range_end)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Frame Window start index > end index");

      return (false);
   }

   if (range_end - range_start > 63)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Frame Window (end index - start index) > 63");

      return (false);
   }

   /* No immediate value words */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_load_bits_fw_to_wr_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   /* Bit layout of this instruction:
    *
    * 1SMM MMMM MNNN NNNW
    *
    * S - Assign or concat
    * M - End of range
    * N - Number of bytes - 1
    * W - Working register
    */

   /* Assign or concat */
   if (is_assign)
   {
      func_str_p = assign_str_p;
      object_p->is_assign = true;
      shift = 0;
   }
   else
   {
      func_str_p = concat_str_p;
      object_p->is_assign = false;
      shift = 1;
   }

   /* Set working register */
   if (wr == 0)
   {
      object_p->working_register = 0;
      wr_str_p = wr0_str_p;
   }
   else
   {
      object_p->working_register = 1;
      wr_str_p = wr1_str_p;
   }

   /* Set range */
   object_p->range_start = range_start;
   object_p->range_end   = range_end;

   len = strlen(range_end_str_p) + 1;

   /* Range end */
   snprintf(range_end_str_p,
            len,
            " | (0x%04x << 7)",
            object_p->range_end);

   len = strlen(num_bytes_str_p) + 1;

   /* Num bytes - 1 */
   snprintf(num_bytes_str_p,
            len,
            " | (0x%04x << 1)",
            (object_p->range_end - object_p->range_start));

   len = strlen(_SP_INSTR_CODE_LOAD_BITS_FW_TO_WR_STR) +
         strlen(func_str_p)                              +
         strlen(range_end_str_p)                         +
         strlen(num_bytes_str_p)                         +
         strlen(wr_str_p)                                +
         1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");

      _sp_destroy_instruction(object_p);
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s%s%s%s%s",
            _SP_INSTR_CODE_LOAD_BITS_FW_TO_WR_STR,
            func_str_p,
            range_end_str_p,
            num_bytes_str_p,
            wr_str_p);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_LOAD_BITS_FW_TO_WR |
                             (shift << 14)                       |
                             (range_end << 7)                    |
                             ((range_end - range_start) << 1)    |
                             wr;

   object_p->working_register   = wr;
   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for jmp_nxt_eth_type
 *
 * Parameters:
 *    ctx_p - Parse context
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_jmp_nxt_eth_type_action(_sp_assembler_parser_context_t *ctx_p)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;

   /* No immediate values */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_jmp_nxt_eth_type_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   len = strlen(_SP_INSTR_CODE_JMP_NXT_ETH_TYPE_STR) + 1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s",
            _SP_INSTR_CODE_JMP_NXT_ETH_TYPE_STR);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_JMP_NXT_ETH_TYPE;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for jmp_nxt_ip_proto
 *
 * Parameters:
 *    ctx_p - Parse context
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_jmp_nxt_ip_proto_action(_sp_assembler_parser_context_t *ctx_p)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;

   /* No immediate values */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_jmp_nxt_ip_proto_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   len = strlen(_SP_INSTR_CODE_JMP_NXT_IP_PROTO_STR) + 1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s",
            _SP_INSTR_CODE_JMP_NXT_IP_PROTO_STR);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_JMP_NXT_IP_PROTO;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for jmp_nxt_tcpudp_ports
 *
 * Parameters:
 *    ctx_p - Parse context
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_jmp_nxt_tcpudp_ports_action(_sp_assembler_parser_context_t *ctx_p)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;

   /* No immediate values */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_jmp_nxt_tcpudp_ports_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   len = strlen(_SP_INSTR_CODE_JMP_NXT_TCPUDP_PORTS_STR) + 1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s",
            _SP_INSTR_CODE_JMP_NXT_TCPUDP_PORTS_STR);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_JMP_NXT_TCPUDP_PORTS;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for define_variable
 *
 * Parameters:
 *    ctx_p      - Parse context
 *    var_type   - Variable type
 *    var_name_p - Variable name
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_define_variable_action(_sp_assembler_parser_context_t *ctx_p,
                                         _sp_assembler_variable_type_t   var_type,
                                         char                             *var_name_p)
{
   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for return_sub
 *
 * Parameters:
 *    ctx_p      - Parse context
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_return_sub_action(_sp_assembler_parser_context_t *ctx_p)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;

   /* No immediate values */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_return_sub_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   len = strlen(_SP_INSTR_CODE_RETURN_SUB_STR) + 1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s",
            _SP_INSTR_CODE_RETURN_SUB_STR);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_RETURN_SUB;

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}


/* ---------------------------------------------------------------------------
 * Action for clr_faf
 *
 * Parameters:
 *    ctx_p      - Parse context
 *    faf_id     - Frame Attribute Flag identifier
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_clr_faf_action(_sp_assembler_parser_context_t *ctx_p,
                                 int                               faf_id)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;
   char                           faf_id_str_p[] = " | 0xJJJJ";

   /* No immediate values */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_set_clr_faf_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   // Set_Clr_FAF
   // 0000 0011 CJJJ JJJJ

   len = strlen(_SP_INSTR_CODE_SET_CLR_FAF_STR) +
         strlen(faf_id_str_p)                     + 1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s | 0x%04x",
            _SP_INSTR_CODE_SET_CLR_FAF_STR,
            faf_id);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_SET_CLR_FAF;

   // c is already set to 0
   // Set j = faf_id
   object_p->hw_words_p[0] |= (0x007f & faf_id);

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}

/* ---------------------------------------------------------------------------
 * Action for set_faf
 *
 * Parameters:
 *    ctx_p      - Parse context
 *    faf_id     - Frame Attribute Flag identifier
 *
 * Returns:
 *   Bool - True means action succeeded.
 *          False means action did not succeed.
 * ---------------------------------------------------------------------------*/
static bool _sp_set_faf_action(_sp_assembler_parser_context_t *ctx_p,
                                 int                               faf_id)
{
   _sp_assembler_instruction_t *object_p;
   uint32_t                       len;
   char                           faf_id_str_p[] = " | 0x0080 | 0xNNNN";

   /* No immediate values */
   ctx_p->num_immediate_values = 0;

   object_p = _sp_new_instruction(_sp_assembler_set_clr_faf_e,
                                    ctx_p);

   if (object_p == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate instruction object.");
      return (false);
   }

   // Set_Clr_FAF
   // 0000 0011 CJJJ JJJJ

   len = strlen(_SP_INSTR_CODE_SET_CLR_FAF_STR) +
         strlen(faf_id_str_p)                     + 1;

   object_p->hw_words_str_p[0] = (char *)calloc(len + 1, 1);

   if (object_p->hw_words_str_p[0] == NULL)
   {
      _sp_assembler_yyerror(ctx_p,
                              "Failed to allocate string.");
      return (false);
   }

   snprintf(object_p->hw_words_str_p[0],
            len,
            "%s | 0x0080 | 0x%04x",
            _SP_INSTR_CODE_SET_CLR_FAF_STR,
            faf_id);

   /* HW opcode */
   object_p->hw_words_p[0] = _SP_INSTR_CODE_SET_CLR_FAF;

   // Set c = 1
   // Set j = faf_id
   object_p->hw_words_p[0] |= 0x0080;
   object_p->hw_words_p[0] |= (0x007f & faf_id);

   object_p->num_valid_hw_words = 1;

   dll_add_to_back(&(ctx_p->instruction_list),
                   &(object_p->dll_node));

   /* Clear context values */
   _sp_clear_ctx_instruction_values(ctx_p);

   return (true);
}


#line 5214 "sp_assembler.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "sp_assembler.tab.h".  */
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
#line 5186 "sp_assembler.y" /* yacc.c:355  */

          int   integer;
          char *string;
       

#line 5349 "sp_assembler.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int _sp_assembler_yyparse (_sp_assembler_parser_context_t *_sp_assembler_context_p);

#endif /* !YY__SP_ASSEMBLER_YY_SP_ASSEMBLER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 5363 "sp_assembler.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   333

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  89
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  160
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  258

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   343

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,  5299,  5299,  5300,  5303,  5304,  5305,  5306,  5307,  5308,
    5309,  5310,  5311,  5312,  5313,  5314,  5315,  5316,  5317,  5318,
    5319,  5320,  5321,  5322,  5323,  5324,  5325,  5326,  5327,  5328,
    5331,  5333,  5335,  5337,  5339,  5341,  5343,  5347,  5353,  5357,
    5361,  5365,  5369,  5373,  5377,  5379,  5381,  5383,  5385,  5389,
    5391,  5393,  5395,  5397,  5399,  5401,  5403,  5405,  5407,  5409,
    5411,  5413,  5415,  5417,  5419,  5421,  5423,  5425,  5427,  5429,
    5431,  5433,  5435,  5437,  5441,  5444,  5447,  5450,  5453,  5456,
    5459,  5463,  5467,  5471,  5475,  5480,  5485,  5490,  5495,  5500,
    5505,  5509,  5511,  5513,  5517,  5520,  5523,  5526,  5529,  5533,
    5537,  5541,  5545,  5549,  5554,  5559,  5564,  5569,  5574,  5580,
    5584,  5588,  5590,  5594,  5596,  5600,  5602,  5606,  5608,  5612,
    5616,  5620,  5624,  5628,  5630,  5634,  5638,  5642,  5646,  5648,
    5652,  5654,  5656,  5658,  5660,  5664,  5666,  5668,  5670,  5672,
    5674,  5678,  5680,  5684,  5688,  5692,  5694,  5698,  5700,  5704,
    5708,  5712,  5714,  5716,  5718,  5722,  5724,  5726,  5728,  5732,
    5734
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ALPHA_NUMERIC_WORD", "JMP", "GOSUB",
  "COLON", "NOP", "START_RAW_INSTRUCTION", "HEX_WORD", "HEX_VALUE",
  "ASSIGN", "INCREMENT", "WINDOW_OFFSET", "HEADER_BASE", "RETURN",
  "SET_BITS", "START_RESULT_ARRAY", "RIGHT_BRACKET", "ETH_HXS",
  "LLCSNAP_HXS", "VLAN_HXS", "VxLAN_HXS", "PPPOE_HXS", "MPLS_HXS",
  "ARP_HXS", "IP_HXS", "IPV4_HXS", "IPV6_HXS", "GRE_HXS", "MINENCAP_HXS",
  "OTH_L3_HXS", "TCP_HXS", "UDP_HXS", "IPSEC_HXS", "SCTP_HXS", "DCCP_HXS",
  "OTH_L4_HXS", "GTP_HXS", "ESP_HXS", "OTH_L5_HXS", "FINAL_SHELL_HXS",
  "RETURN_SUB", "RETURN_HXS", "CLR_FAF", "SET_FAF", "END_PARSE", "CONCAT",
  "WR0", "WR1", "CLEAR", "ONESCOMP", "AND", "OR", "XOR", "SHIFT_LEFT",
  "SHIFT_RIGHT", "IF", "START_FRAME_WINDOW", "QUESTION", "PIPE",
  "AMPERSAND", "HXS", "BRIDGE", "START_PARAMETER_ARRAY", "EQUAL",
  "NOT_EQUAL", "GREATER_THAN", "LESS_THAN", "GREATER_THAN_EQUAL",
  "LESS_THAN_EQUAL", "OPEN_PAREN", "CLOSE_PAREN", "COMMA", "CONTEXT_LIST",
  "PLUS", "MINUS", "NXT_ETH_TYPE", "NXT_IP_PROTO", "NXT_TCPUDP_PORTS",
  "UINT6_TYPE", "UINT7_TYPE", "UINT8_TYPE", "UINT16_TYPE", "UINT32_TYPE",
  "UINT48_TYPE", "UINT64_TYPE", "DEC_VALUE", "FAF_ID", "$accept", "input",
  "instruction", "variable_type", "define_variable", "label",
  "five_hex_words", "four_hex_words", "three_hex_words", "two_hex_words",
  "one_hex_word", "raw_instruction", "hard_examination", "hxs", "jmp",
  "gosub", "nop", "advance_hb_by_wo", "working_register",
  "result_array_range", "immediate_value", "load_bytes_ra_to_wr",
  "store_wr_to_ra", "store_iv_to_ra", "load_sv_to_wo", "add_sv_to_wo",
  "modify_wo_by_wr", "zero_wr", "ones_comp_wr1_to_wr0", "return_sub",
  "set_clr_faf", "bitwise_operator", "operator_set1", "addsub_operator",
  "bitwise_wr_wr_to_wr", "bitwise_wr_iv_to_wr", "addsub_wr_wr_to_wr",
  "addsub_wr_iv_to_wr", "shift_left_wr_by_sv", "shift_right_wr_by_sv",
  "load_bits_iv_to_wr", "load_bytes_pa_to_wr", "load_bits_fw_to_wr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343
};
# endif

#define YYPACT_NINF -96

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-96)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -96,    22,   -96,    11,   143,   204,   -96,    -4,    40,    16,
     -64,   -96,   -48,   -46,   -96,   -96,     7,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,    43,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,    34,    48,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,    -8,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,     3,   248,   -96,   -96,   -96,     5,    37,     3,
     287,    63,    70,   -96,   -96,   -96,   -96,   -96,    44,    44,
     102,    26,   -96,   -96,   -96,   -96,    -1,    24,    90,    90,
      44,   -45,   -96,   119,    66,    74,    45,   -38,   129,    77,
      78,    49,   127,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
      51,   -96,    38,    38,    52,    53,    58,   -96,   136,    56,
      61,   -96,   144,   -96,   -96,   -96,   -96,    60,   -96,     0,
      64,    65,   -96,    60,   -96,     1,    68,    72,   -96,   140,
     133,   -96,   -96,     9,    28,   122,    80,   -96,   -96,   -96,
     -96,   -96,    44,    67,   124,    91,   101,   -96,   -96,   -96,
     -96,   -96,   -96,   141,   185,     3,   -96,   -96,   145,   186,
       3,   -96,   -96,   184,   -96,   -96,   -96,   -96,   -96,   108,
     109,   -96,   -96,   -96,   -96,   110,   111,   -96,   -96,   -96,
       3,   196,   -96,     3,   197,   -96,   183,   188,   190,   191,
     200,    14,   201,    15,   -96,   -96,   -96,   -96,   -96,   205,
       3,   -96,   206,     3,     3,   207,     3,   210,   211,    18,
     212,    25,   -96,   213,     3,   -96,   240,     3,     3,   214,
       3,   215,   245,   -96,   246,   -96,   -96,   -96
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,   109,     0,     0,     0,
       0,   127,     0,     0,   111,   112,     0,   126,    30,    31,
      32,    33,    34,    35,    36,     3,     0,    29,     4,     5,
       6,     7,     9,    10,     0,     0,    11,    12,    13,    14,
      15,    16,    17,    18,     8,    26,    19,    20,    21,    22,
      23,    24,    25,    27,    28,    38,    80,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    75,     0,    91,    92,    93,    76,    98,    75,
       0,    94,    43,    44,    45,    46,    47,    48,     0,     0,
       0,     0,   128,   129,   125,    37,     0,     0,     0,     0,
       0,     0,    74,     0,    82,    78,     0,     0,     0,   100,
      96,     0,    42,   116,   115,   123,   121,   124,   122,   110,
       0,   114,   111,   112,     0,     0,     0,   117,   152,     0,
       0,   118,   154,   149,   150,   119,   120,     0,    81,     0,
       0,     0,    77,     0,    99,     0,     0,     0,    95,    41,
       0,   141,   142,     0,     0,     0,     0,   130,   132,   134,
     133,   131,     0,     0,     0,     0,     0,   135,   136,   138,
     137,   140,   139,     0,     0,    75,    83,    79,     0,     0,
      75,   101,    97,    40,   113,   145,   147,   146,   148,     0,
       0,   156,   143,   144,   151,     0,     0,   158,   153,    84,
      75,     0,   102,    75,     0,    39,     0,     0,     0,     0,
       0,    86,     0,   104,   159,   155,   160,   157,    85,     0,
      75,   103,     0,    75,    75,     0,    75,     0,     0,    88,
       0,   106,    87,     0,    75,   105,     0,    75,    75,     0,
      75,     0,     0,    90,     0,   108,    89,   107
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,    -3,   -89,   -96,   -96,   -96,   -96,   -15,    10,
     -95,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,    99,    83,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    25,    26,    27,    28,    93,    94,    95,    96,
      97,    29,    87,   113,    30,    31,    32,    33,    34,    35,
     126,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,   172,   183,   163,    46,    47,    48,    49,    50,    51,
      52,    53,    54
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     118,   104,    91,   147,   128,    92,   184,   189,   123,   124,
     153,   138,   142,   143,   144,   146,    10,    55,   123,   124,
     229,   232,     2,   101,   243,     3,     4,     5,   100,     6,
       7,   246,   130,   123,   124,     8,     9,   123,   124,    10,
     102,    10,   103,   148,   131,   106,   105,   132,   133,   111,
     154,    98,    99,   123,   124,    14,    15,   134,   195,   110,
     185,   190,   116,   135,    11,   112,    12,    13,   196,   198,
      14,    15,    16,    17,   230,   233,   197,   203,   244,   122,
     115,   107,   139,   125,   127,   247,   200,   120,   140,   108,
     109,   136,    14,    15,   117,   145,   211,   206,   201,   123,
     124,   214,    18,    19,    20,    21,    22,    23,    24,   207,
     167,   168,   169,   161,   162,   129,   137,   141,   170,   171,
     121,   220,   149,   150,   222,   177,   178,   179,   180,   181,
     182,   151,   155,   152,   156,   157,   159,   158,   160,   165,
     166,   235,   173,   174,   237,   238,    56,   240,   175,   193,
     176,   194,   186,   187,   204,   249,   191,   202,   251,   252,
     192,   254,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,   199,    80,   205,   208,    81,
     209,   210,   213,   215,   212,   216,   217,   218,   219,   221,
     223,   224,    82,   228,   231,    83,   225,    88,   226,   227,
     239,   234,   236,   241,   242,   245,   164,   253,   255,   248,
      84,    85,    86,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,   250,    80,   256,   257,
      81,   114,   188,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    89,     0,     0,    90,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
     119,    80,     0,     0,    81,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,     0,
      80,     0,     0,    81
};

static const yytype_int16 yycheck[] =
{
      89,    16,     5,    48,    99,     9,     6,     6,     9,    10,
      48,   106,   107,   108,   109,   110,    17,     6,     9,    10,
       6,     6,     0,    87,     6,     3,     4,     5,    12,     7,
       8,     6,     6,     9,    10,    13,    14,     9,    10,    17,
      88,    17,    88,    88,    18,    11,     3,    48,    49,    57,
      88,    11,    12,     9,    10,    48,    49,    58,    49,    11,
      60,    60,    57,    64,    42,    62,    44,    45,   163,   164,
      48,    49,    50,    51,    60,    60,    48,   172,    60,     9,
      83,    47,    58,    98,    99,    60,     6,    90,    64,    55,
      56,   106,    48,    49,    57,   110,   185,     6,    18,     9,
      10,   190,    80,    81,    82,    83,    84,    85,    86,    18,
      52,    53,    54,    75,    76,    13,   106,   107,    60,    61,
      57,   210,     3,    57,   213,    65,    66,    67,    68,    69,
      70,    57,     3,    88,    57,    57,     9,    88,    87,    87,
      87,   230,     6,    87,   233,   234,     3,   236,    87,     9,
       6,    18,    88,    88,    87,   244,    88,   172,   247,   248,
      88,   250,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    63,    43,    63,    87,    46,
      49,     6,     6,     9,    49,    87,    87,    87,    87,     3,
       3,    18,    59,     3,     3,    62,    18,     3,    18,    18,
       3,     6,     6,     3,     3,     3,   133,     3,     3,     6,
      77,    78,    79,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,     6,    43,     3,     3,
      46,     3,   153,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    -1,    -1,    62,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
       3,    43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      43,    -1,    -1,    46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    90,     0,     3,     4,     5,     7,     8,    13,    14,
      17,    42,    44,    45,    48,    49,    50,    51,    80,    81,
      82,    83,    84,    85,    86,    91,    92,    93,    94,   100,
     103,   104,   105,   106,   107,   108,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   123,   124,   125,   126,
     127,   128,   129,   130,   131,     6,     3,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      43,    46,    59,    62,    77,    78,    79,   101,     3,    59,
      62,   101,     9,    95,    96,    97,    98,    99,    11,    12,
      12,    87,    88,    88,   107,     3,    11,    47,    55,    56,
      11,    57,    62,   102,     3,   101,    57,    57,   102,     3,
     101,    57,     9,     9,    10,   107,   109,   107,   109,    13,
       6,    18,    48,    49,    58,    64,   107,   108,   109,    58,
      64,   108,   109,   109,   109,   107,   109,    48,    88,     3,
      57,    57,    88,    48,    88,     3,    57,    57,    88,     9,
      87,    75,    76,   122,   122,    87,    87,    52,    53,    54,
      60,    61,   120,     6,    87,    87,     6,    65,    66,    67,
      68,    69,    70,   121,     6,    60,    88,    88,   121,     6,
      60,    88,    88,     9,    18,    49,   109,    48,   109,    63,
       6,    18,   107,   109,    87,    63,     6,    18,    87,    49,
       6,   102,    49,     6,   102,     9,    87,    87,    87,    87,
     102,     3,   102,     3,    18,    18,    18,    18,     3,     6,
      60,     3,     6,    60,     6,   102,     6,   102,   102,     3,
     102,     3,     3,     6,    60,     3,     6,    60,     6,   102,
       6,   102,   102,     3,   102,     3,     3,     3
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    89,    90,    90,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      92,    92,    92,    92,    92,    92,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   100,   100,   100,   100,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   102,   102,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   105,
     106,   107,   107,   108,   108,   109,   109,   110,   110,   111,
     112,   113,   114,   115,   115,   116,   117,   118,   119,   119,
     120,   120,   120,   120,   120,   121,   121,   121,   121,   121,
     121,   122,   122,   123,   124,   125,   125,   126,   126,   127,
     128,   129,   129,   129,   129,   130,   130,   130,   130,   131,
     131
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     5,
       4,     3,     2,     1,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     2,     4,     3,     5,
       2,     4,     3,     5,     6,     8,     7,    11,    10,    14,
      13,     2,     2,     2,     2,     4,     3,     5,     2,     4,
       3,     5,     6,     8,     7,    11,    10,    14,    13,     1,
       3,     1,     1,     5,     3,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     5,     5,     5,     5,     5,     3,
       3,     5,     3,     5,     3,     7,     5,     7,     5,     7,
       7
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (_sp_assembler_context_p, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, _sp_assembler_context_p); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, _sp_assembler_parser_context_t *_sp_assembler_context_p)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (_sp_assembler_context_p);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, _sp_assembler_parser_context_t *_sp_assembler_context_p)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, _sp_assembler_context_p);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, _sp_assembler_parser_context_t *_sp_assembler_context_p)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , _sp_assembler_context_p);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, _sp_assembler_context_p); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, _sp_assembler_parser_context_t *_sp_assembler_context_p)
{
  YYUSE (yyvaluep);
  YYUSE (_sp_assembler_context_p);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (_sp_assembler_parser_context_t *_sp_assembler_context_p)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, _sp_assembler_context_p);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 30:
#line 5332 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _sp_uint6_type_e;}
#line 6674 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 5334 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _sp_uint7_type_e;}
#line 6680 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 5336 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _sp_uint8_type_e;}
#line 6686 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 5338 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _sp_uint16_type_e;}
#line 6692 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 5340 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _sp_uint32_type_e;}
#line 6698 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 5342 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _sp_uint48_type_e;}
#line 6704 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 5344 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _sp_uint64_type_e;}
#line 6710 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 5348 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_define_variable_action(_sp_assembler_context_p, (yyvsp[-1].integer), (yyvsp[0].string))) {return (1);}
                                free (yyvsp[0].string);
                               }
#line 6718 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 5354 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P1(_sp_label_action, (yyvsp[-1].string))}
#line 6724 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 5358 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P5(_sp_five_hex_words_action, (yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string))}
#line 6730 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 5362 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P4(_sp_four_hex_words_action, (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string))}
#line 6736 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 5366 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P3(_sp_three_hex_words_action, (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string))}
#line 6742 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 5370 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P2(_sp_two_hex_words_action, (yyvsp[-1].string), (yyvsp[0].string))}
#line 6748 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 5374 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P1(_sp_one_hex_word_action, (yyvsp[0].string))}
#line 6754 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 5378 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P0(_sp_raw_instruction_action)}
#line 6760 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 5380 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P0(_sp_raw_instruction_action)}
#line 6766 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 5382 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P0(_sp_raw_instruction_action)}
#line 6772 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 5384 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P0(_sp_raw_instruction_action)}
#line 6778 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 5386 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P0(_sp_raw_instruction_action)}
#line 6784 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 5390 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_ETH_HXS_LABEL;}
#line 6790 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 5392 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_LLC_SNAP_HXS_LABEL;}
#line 6796 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 5394 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_VLAN_HXS_LABEL;}
#line 6802 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 5396 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_VxLAN_HXS_LABEL;}
#line 6808 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 5398 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_PPPOE_PPP_HXS_LABEL;}
#line 6814 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 5400 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_MPLS_HXS_LABEL;}
#line 6820 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 5402 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_ARP_HXS_LABEL;}
#line 6826 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 5404 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_IP_HXS_LABEL;}
#line 6832 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 5406 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_IPV4_HXS_LABEL;}
#line 6838 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 5408 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_IPV6_HXS_LABEL;}
#line 6844 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 5410 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_GRE_HXS_LABEL;}
#line 6850 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 5412 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_MINENCAP_HXS_LABEL;}
#line 6856 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 5414 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_OTH_L3_HXS_LABEL;}
#line 6862 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 5416 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_TCP_HXS_LABEL;}
#line 6868 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 5418 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_UDP_HXS_LABEL;}
#line 6874 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 5420 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_IPSEC_HXS_LABEL;}
#line 6880 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 5422 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_SCTP_HXS_LABEL;}
#line 6886 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 5424 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_DCCP_HXS_LABEL;}
#line 6892 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 5426 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_OTH_L4_HXS_LABEL;}
#line 6898 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 5428 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_GTP_HXS_LABEL;}
#line 6904 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 5430 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_ESP_HXS_LABEL;}
#line 6910 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 5432 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_OTH_L5_HXS_LABEL;}
#line 6916 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 5434 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_FINAL_SHELL_HXS_LABEL;}
#line 6922 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 5436 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_RETURN_HXS_LABEL;}
#line 6928 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 5438 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = _SP_END_PARSE_LABEL;}
#line 6934 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 5442 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = true;}
#line 6940 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 5444 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = false;}
#line 6946 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 5448 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[0].string), false, false, false, 0)) {return (1);}
                               }
#line 6953 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 5451 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[-2].string), false, false, true, (yyvsp[0].integer))) {return (1);}
                               }
#line 6960 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 5454 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[0].string), true, false, false, 0)) {return (1);}
                               }
#line 6967 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 5457 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[-2].string), true, false, true, (yyvsp[0].integer))) {return (1);}
                               }
#line 6974 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 5460 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[0].string), false, false, false, 0)) {return (1);}
                                free (yyvsp[0].string);
                               }
#line 6982 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 5464 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[-2].string), false, false, true, (yyvsp[0].integer))) {return (1);}
                                free (yyvsp[-2].string);
                               }
#line 6990 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 5468 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[0].string), true, false, false, 0)) {return (1);}
                                free (yyvsp[0].string);
                               }
#line 6998 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 5472 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[-2].string), true, false, true, (yyvsp[0].integer))) {return (1);}
                                free (yyvsp[-2].string);
                               }
#line 7006 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 5476 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_if_wr0_wr1_action(_sp_assembler_context_p, (yyvsp[-4].string), (yyvsp[-1].integer), false)) {return (1);}
                                free (yyvsp[-4].string);
                               }
#line 7014 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 5481 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_case1dj_action(_sp_assembler_context_p, (yyvsp[-4].string), (yyvsp[0].string), (yyvsp[-5].integer), (yyvsp[-1].integer), false)) {return (1);}
                                free (yyvsp[-4].string); free (yyvsp[0].string);
                               }
#line 7022 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 5486 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_case2dc_action(_sp_assembler_context_p, (yyvsp[-3].string), (yyvsp[0].string), (yyvsp[-4].integer), (yyvsp[-1].integer), false)) {return (1);}
                                free (yyvsp[-3].string); free (yyvsp[0].string);
                               }
#line 7030 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 5491 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_case2dj_action(_sp_assembler_context_p, (yyvsp[-7].string), (yyvsp[-4].string), (yyvsp[0].string), (yyvsp[-8].integer), (yyvsp[-5].integer), (yyvsp[-1].integer), false)) {return (1);}
                                free (yyvsp[-7].string); free (yyvsp[-4].string); free (yyvsp[0].string);
                               }
#line 7038 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 5496 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_case3dc_action(_sp_assembler_context_p, (yyvsp[-6].string), (yyvsp[-3].string), (yyvsp[0].string), (yyvsp[-7].integer), (yyvsp[-4].integer), (yyvsp[-1].integer), false)) {return (1);}
                                free (yyvsp[-6].string); free (yyvsp[-3].string); free (yyvsp[0].string);
                               }
#line 7046 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 5501 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_case3dj_action(_sp_assembler_context_p, (yyvsp[-10].string), (yyvsp[-7].string), (yyvsp[-4].string), (yyvsp[0].string), (yyvsp[-11].integer), (yyvsp[-8].integer), (yyvsp[-5].integer), (yyvsp[-1].integer), false)) {return (1);}
                                free (yyvsp[-10].string); free (yyvsp[-7].string); free (yyvsp[-4].string); free (yyvsp[0].string);
                               }
#line 7054 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 5506 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_case4dc_action(_sp_assembler_context_p, (yyvsp[-9].string), (yyvsp[-6].string), (yyvsp[-3].string), (yyvsp[0].string), (yyvsp[-10].integer), (yyvsp[-7].integer), (yyvsp[-4].integer), (yyvsp[-1].integer), false)) {return (1);}
                                free (yyvsp[-9].string); free (yyvsp[-6].string); free (yyvsp[-3].string); free (yyvsp[0].string);
                               }
#line 7062 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 5510 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P0(_sp_jmp_nxt_eth_type_action)}
#line 7068 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 5512 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P0(_sp_jmp_nxt_ip_proto_action)}
#line 7074 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 5514 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P0(_sp_jmp_nxt_tcpudp_ports_action)}
#line 7080 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 5518 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[0].string), false, true, false, 0)) {return (1);}
                               }
#line 7087 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 5521 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[-2].string), false, true, true, (yyvsp[0].integer))) {return (1);}
                               }
#line 7094 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 5524 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[0].string), true, true, false, 0)) {return (1);}
                               }
#line 7101 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 5527 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[-2].string), true, true, true, (yyvsp[0].integer))) {return (1);}
                               }
#line 7108 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 5530 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[0].string), false, true, false, 0)) {return (1);}
                                free (yyvsp[0].string);
                               }
#line 7116 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 5534 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[-2].string), false, true, true, (yyvsp[0].integer))) {return (1);}
                                free (yyvsp[-2].string);
                               }
#line 7124 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 5538 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[0].string), true, true, false, 0)) {return (1);}
                                free (yyvsp[0].string);
                               }
#line 7132 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 5542 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_action(_sp_assembler_context_p, (yyvsp[-2].string), true, true, true, (yyvsp[0].integer))) {return (1);}
                                free (yyvsp[-2].string);
                               }
#line 7140 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 5546 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_if_wr0_wr1_action(_sp_assembler_context_p, (yyvsp[-4].string), (yyvsp[-1].integer), true)) {return (1);}
                                free (yyvsp[-4].string);
                               }
#line 7148 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 5550 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_case1dj_action(_sp_assembler_context_p, (yyvsp[-4].string), (yyvsp[0].string), (yyvsp[-5].integer), (yyvsp[-1].integer), true)) {return (1);}
                                free (yyvsp[-4].string); free (yyvsp[0].string);
                               }
#line 7156 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 5555 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_case2dc_action(_sp_assembler_context_p, (yyvsp[-3].string), (yyvsp[0].string), (yyvsp[-4].integer), (yyvsp[-1].integer), true)) {return (1);}
                                free (yyvsp[-3].string); free (yyvsp[0].string);
                               }
#line 7164 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 5560 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_case2dj_action(_sp_assembler_context_p, (yyvsp[-7].string), (yyvsp[-4].string), (yyvsp[0].string), (yyvsp[-8].integer), (yyvsp[-5].integer), (yyvsp[-1].integer), true)) {return (1);}
                                free (yyvsp[-7].string); free (yyvsp[-4].string); free (yyvsp[0].string);
                               }
#line 7172 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 5565 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_case3dc_action(_sp_assembler_context_p, (yyvsp[-6].string), (yyvsp[-3].string), (yyvsp[0].string), (yyvsp[-7].integer), (yyvsp[-4].integer), (yyvsp[-1].integer), true)) {return (1);}
                                free (yyvsp[-6].string); free (yyvsp[-3].string); free (yyvsp[0].string);
                               }
#line 7180 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 5570 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_case3dj_action(_sp_assembler_context_p, (yyvsp[-10].string), (yyvsp[-7].string), (yyvsp[-4].string), (yyvsp[0].string), (yyvsp[-11].integer), (yyvsp[-8].integer), (yyvsp[-5].integer), (yyvsp[-1].integer), true)) {return (1);}
                                free (yyvsp[-10].string); free (yyvsp[-7].string); free (yyvsp[-4].string); free (yyvsp[0].string);
                               }
#line 7188 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 5575 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_jmp_label_case4dc_action(_sp_assembler_context_p, (yyvsp[-9].string), (yyvsp[-6].string), (yyvsp[-3].string), (yyvsp[0].string), (yyvsp[-10].integer), (yyvsp[-7].integer), (yyvsp[-4].integer), (yyvsp[-1].integer), true)) {return (1);}
                                free (yyvsp[-9].string); free (yyvsp[-6].string); free (yyvsp[-3].string); free (yyvsp[0].string);
                               }
#line 7196 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 5581 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P0(_sp_nop_action)}
#line 7202 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 5585 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P0(_sp_advance_hb_by_wo_action)}
#line 7208 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 5589 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = 0;}
#line 7214 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 5591 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = 1;}
#line 7220 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 5595 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_result_array_range_action(_sp_assembler_context_p, (yyvsp[-3].integer), (yyvsp[-1].integer), false)) {return (1);}}
#line 7226 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 5597 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_result_array_range_action(_sp_assembler_context_p, (yyvsp[-1].integer), (yyvsp[-1].integer), false)) {return (1);}}
#line 7232 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 5601 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = (yyvsp[0].string);}
#line 7238 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 5603 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.string) = (yyvsp[0].string);}
#line 7244 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 5607 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_load_bytes_ra_to_wr_action(_sp_assembler_context_p, (yyvsp[-2].integer), true)) {return (1);}}
#line 7250 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 5609 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_load_bytes_ra_to_wr_action(_sp_assembler_context_p, (yyvsp[-2].integer), false)) {return (1);}}
#line 7256 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 5613 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_store_wr_to_ra_action(_sp_assembler_context_p, (yyvsp[0].integer))) {return (1);}}
#line 7262 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 5617 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P1(_sp_store_iv_to_ra_action, (yyvsp[0].string))}
#line 7268 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 5621 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P1(_sp_load_sv_to_wo_action, (yyvsp[0].string))}
#line 7274 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 5625 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P1(_sp_add_sv_to_wo_action, (yyvsp[0].string))}
#line 7280 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 5629 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_modify_wo_by_wr_action(_sp_assembler_context_p, false, (yyvsp[0].integer))) {return (1);}}
#line 7286 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 5631 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_modify_wo_by_wr_action(_sp_assembler_context_p, true, (yyvsp[0].integer))) {return (1);}}
#line 7292 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 5635 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_zero_wr_action(_sp_assembler_context_p, (yyvsp[0].integer))) {return (1);}}
#line 7298 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 5639 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P0(_sp_ones_comp_wr1_to_wr0_action)}
#line 7304 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 5643 "sp_assembler.y" /* yacc.c:1646  */
    {_SP_PROC_TOK_P0(_sp_return_sub_action)}
#line 7310 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 5647 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_clr_faf_action(_sp_assembler_context_p, (yyvsp[0].integer))) {return (1);}}
#line 7316 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 5649 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_set_faf_action(_sp_assembler_context_p, (yyvsp[0].integer))) {return (1);}}
#line 7322 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 5653 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _SP_OPERATOR_AND;}
#line 7328 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 5655 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _SP_OPERATOR_AND;}
#line 7334 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 5657 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _SP_OPERATOR_OR;}
#line 7340 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 5659 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _SP_OPERATOR_OR;}
#line 7346 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 5661 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _SP_OPERATOR_XOR;}
#line 7352 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 5665 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _SP_OPERATOR_EQUAL;}
#line 7358 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 5667 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _SP_OPERATOR_NOT_EQUAL;}
#line 7364 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 5669 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _SP_OPERATOR_LESS_THAN;}
#line 7370 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 5671 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _SP_OPERATOR_GREATER_THAN;}
#line 7376 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 5673 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _SP_OPERATOR_LESS_THAN_EQUAL;}
#line 7382 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 5675 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _SP_OPERATOR_GREATER_THAN_EQUAL;}
#line 7388 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 5679 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _SP_OPERATOR_PLUS;}
#line 7394 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 5681 "sp_assembler.y" /* yacc.c:1646  */
    {(yyval.integer) = _SP_OPERATOR_MINUS;}
#line 7400 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 5685 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_bitwise_wr_wr_to_wr_action(_sp_assembler_context_p, (yyvsp[-4].integer), (yyvsp[-1].integer))) {return (1);}}
#line 7406 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 5689 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_bitwise_wr_iv_to_wr_action(_sp_assembler_context_p, (yyvsp[-4].integer), (yyvsp[-2].integer), (yyvsp[-1].integer), (yyvsp[0].string))) {return (1);} free (yyvsp[0].string);}
#line 7412 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 5693 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_addsub_wr_wr_to_wr_action(_sp_assembler_context_p, (yyvsp[-4].integer), 0, (yyvsp[-1].integer))) {return (1);}}
#line 7418 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 5695 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_addsub_wr_wr_to_wr_action(_sp_assembler_context_p, (yyvsp[-4].integer), 1, (yyvsp[-1].integer))) {return (1);}}
#line 7424 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 5699 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_addsub_wr_iv_to_wr_action(_sp_assembler_context_p, (yyvsp[-4].integer), 0, (yyvsp[-1].integer), (yyvsp[0].string))) {return (1);}}
#line 7430 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 5701 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_addsub_wr_iv_to_wr_action(_sp_assembler_context_p, (yyvsp[-4].integer), 1, (yyvsp[-1].integer), (yyvsp[0].string))) {return (1);}}
#line 7436 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 5705 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_bitwise_shift_left_wr_by_sv_action(_sp_assembler_context_p, (yyvsp[-2].integer), (yyvsp[0].string))) {return (1);} free (yyvsp[0].string);}
#line 7442 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 5709 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_bitwise_shift_right_wr_by_sv_action(_sp_assembler_context_p, (yyvsp[-2].integer), (yyvsp[0].string))) {return (1);} free (yyvsp[0].string);}
#line 7448 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 5713 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_load_bits_iv_to_wr_action(_sp_assembler_context_p, (yyvsp[-4].integer), (yyvsp[-2].string), (yyvsp[0].integer), true)) {return (1);} free (yyvsp[-2].string);}
#line 7454 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 5715 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_load_bits_iv_to_wr_action(_sp_assembler_context_p, (yyvsp[-2].integer), (yyvsp[0].string), 0, true)) {return (1);} free (yyvsp[0].string);}
#line 7460 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 5717 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_load_bits_iv_to_wr_action(_sp_assembler_context_p, (yyvsp[-4].integer), (yyvsp[-2].string), (yyvsp[0].integer), false)) {return (1);} free (yyvsp[-2].string);}
#line 7466 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 5719 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_load_bits_iv_to_wr_action(_sp_assembler_context_p, (yyvsp[-2].integer), (yyvsp[0].string), 0, false)) {return (1);} free (yyvsp[0].string);}
#line 7472 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 5723 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_load_bytes_pa_to_wr_action(_sp_assembler_context_p, (yyvsp[-6].integer), (yyvsp[-3].integer), (yyvsp[-1].integer), true)) {return (1);}}
#line 7478 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 5725 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_load_bytes_pa_to_wr_action(_sp_assembler_context_p, (yyvsp[-4].integer), (yyvsp[-1].integer), (yyvsp[-1].integer), true)) {return (1);}}
#line 7484 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 5727 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_load_bytes_pa_to_wr_action(_sp_assembler_context_p, (yyvsp[-6].integer), (yyvsp[-3].integer), (yyvsp[-1].integer), false)) {return (1);}}
#line 7490 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 5729 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_load_bytes_pa_to_wr_action(_sp_assembler_context_p, (yyvsp[-4].integer), (yyvsp[-1].integer), (yyvsp[-1].integer), false)) {return (1);}}
#line 7496 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 5733 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_load_bits_fw_to_wr_action(_sp_assembler_context_p, (yyvsp[-6].integer), (yyvsp[-3].integer), (yyvsp[-1].integer), true)) {return (1);}}
#line 7502 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 5735 "sp_assembler.y" /* yacc.c:1646  */
    {if (!_sp_load_bits_fw_to_wr_action(_sp_assembler_context_p, (yyvsp[-6].integer), (yyvsp[-3].integer), (yyvsp[-1].integer), false)) {return (1);}}
#line 7508 "sp_assembler.tab.c" /* yacc.c:1646  */
    break;


#line 7512 "sp_assembler.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (_sp_assembler_context_p, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (_sp_assembler_context_p, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, _sp_assembler_context_p);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, _sp_assembler_context_p);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (_sp_assembler_context_p, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, _sp_assembler_context_p);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, _sp_assembler_context_p);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
