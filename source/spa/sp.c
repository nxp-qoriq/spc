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
 *
 * ===================================================================*/

/* --------------------------------------------------------------------------
 * Public APIs for Packet Engine Soft Parser.
 *
 *
 * --------------------------------------------------------------------------*/

#include <sys/types.h>
#include <sys/stat.h>
#ifndef YY_NO_UNISTD_H
#include <unistd.h>
#endif
#include <stdio.h>

#include "sp.h"
#include "sp_private.h"

#define yyconst const
typedef struct yy_buffer_state *YY_BUFFER_STATE;
YY_BUFFER_STATE _sp_assembler_yy_scan_string (yyconst char * yystr );
int _sp_assembler_yyparse (_sp_assembler_parser_context_t *_sp_assembler_context_p);

const char *_sp_error_code_strings[] =
{
   "SPA: Assemble OK.",                           /* sp_ok_e */
   "SPA: ERROR: Memory allocation failure.",      /* sp_malloc_failure_e */
   "SPA: ERROR: Failed to open input file.",      /* sp_input_file_open_failure_e */
   "SPA: ERROR: Failed to open output file.",     /* sp_output_file_open_failure_e */
   "SPA: ERROR: Unrecognized option.",            /* sp_unrecognized_option_e */
   "SPA: ERROR: Assemble FAILED.",                /* sp_assemble_failed_e */
   "SPA: ERROR: Assemble had warning(s).",        /* sp_warnings_e */
   "SPA: ERROR: Invalid option.",                 /* sp_invalid_option_e */
   "SPA: ERROR: Internal error.",                 /* sp_internal_error_e */
   "SPA: ERROR: Failed to write to output file.", /* sp_output_file_write_error_e */
   "SPA: ERROR: Invalid label.",                  /* sp_invalid_label_e */
   "SPA: ERROR: Max instructions exceeded.",      /* sp_max_instructions_exceeded_e */
   "SPA: ERROR: Invalid base address.",           /* sp_invalid_parse_program_base_address_e */
};

/* --------------------------------------------------------------------------
 * Public Assembler API.
 *
 * Parameters:
 *   input_p            - Input text string.
 *   output_p           - Output binary data.
 *   options_p          - Options for the assembler.
 *   assemble_msg_p     - Pointer to pointer to string for assembler
 *                        messages.  The user may choose not to use this
 *                        parameter and supply NULL.
 *
 * Returns:
 *   An error code of type sp_error_code_t.
 * --------------------------------------------------------------------------*/
sp_error_code_t sp_assemble(char                      *input_p,
                                uint8_t                   *output_buffer_p,
                                sp_label_list_t        **output_label_list_p,
                                sp_assembler_options_t  *options_p,
                                char                     **assemble_msg_p)
{
   extern FILE                      *_sp_assembler_yyin;
   sp_error_code_t                 result;
   _sp_assembler_parser_context_t *_sp_context_p;

   /* If user passed in pointer to string for assemble msg, init to NULL
    * before any errors can happen.
    */
   if (assemble_msg_p != NULL)
   {
      *assemble_msg_p = NULL;
   }

   /* Create a parse context */
   _sp_context_p = _sp_new_parse_context();

   if (_sp_context_p == NULL)
   {
      return (sp_malloc_failure_e);
   }

   /* Check input string */
   if (input_p == NULL)
   {
// TODO Change error code 
      return (sp_input_file_open_failure_e);
   }

   _sp_context_p->current_file_name_p = NULL;

   /* Flush the lexical analyzer's buffer. */
   //_sp_assembler_yyrestart(_sp_assembler_yyin);

   if (output_buffer_p == NULL)
   {
// TODO Change error code 
      return (sp_output_file_open_failure_e);
   }

   _sp_context_p->output_file_name_p = NULL;

   /* Set Flex to read from input string */
   _sp_assembler_yy_scan_string(input_p);

   /* Set options */
   if (options_p == NULL)
   {
      (_sp_context_p->options).debug_level                = sp_debug_none_e;
      (_sp_context_p->options).warnings_are_errors        = false;
      (_sp_context_p->options).suppress_warnings          = false;
      (_sp_context_p->options).program_space_base_address = SP_PARSE_PROGRAM_DEFAULT_BASE_ADDRESS;
   }
   else
   {
      options_p->result_code_size = 0;

      /* Validate options */

      if (options_p->debug_level > 0)
      {
#ifdef SP_DEBUG
         if ((options_p->debug_level & (sp_debug_none_e    |
                                        sp_debug_summary_e |
                                        sp_debug_test_e    |
                                        sp_debug_detailed_e)) == 0)
         {
            _sp_cleanup(_sp_context_p);
            return (sp_invalid_option_e);
         }
#else
         _sp_cleanup(_sp_context_p);
         return (sp_invalid_option_e);
#endif /* SP_DEBUG */
      }

      if (options_p->warnings_are_errors != true &&
          options_p->warnings_are_errors != false)
      {
         _sp_cleanup(_sp_context_p);
         return (sp_invalid_option_e);
      }

      if (options_p->suppress_warnings != true &&
          options_p->suppress_warnings != false)
      {
         _sp_cleanup(_sp_context_p);
         return (sp_invalid_option_e);
      }

      /* If warnings are errors, then display warnings regardless of user
       * setting suppress_warnings. If we don't do this, the assembler will
       * fail on a warning and give no indication of what happened. */
      if (options_p->warnings_are_errors == true)
      {
         options_p->suppress_warnings = false;
      }

      (_sp_context_p->options).debug_level            = options_p->debug_level;
      (_sp_context_p->options).warnings_are_errors    = options_p->warnings_are_errors;
      (_sp_context_p->options).suppress_warnings      = options_p->suppress_warnings;

      if (options_p->program_space_base_address < SP_PARSE_PROGRAM_MIN_BASE_ADDRESS ||
          options_p->program_space_base_address > SP_PARSE_PROGRAM_MAX_BASE_ADDRESS)
      {
         return (sp_invalid_parse_program_base_address_e);
      }

      (_sp_context_p->options).program_space_base_address = options_p->program_space_base_address;
      _sp_context_p->next_program_counter = options_p->program_space_base_address;
      
   }

   /* User passed in a string pointer to use for assembler message? */
   if (assemble_msg_p != NULL)
   {
      _sp_context_p->assemble_msg_p = assemble_msg_p;
   }
   else
   {
      _sp_context_p->assemble_msg_p = NULL;
   }

   /* Initialize linked list for instructions within context object */
   dll_list_init(&(_sp_context_p->instruction_list));
   
   /* ------------------------------------------------------------------------
    * Parse code
    * ------------------------------------------------------------------------*/

   /* Uncomment to turn on parser debugging. */
//     extern int _sp_assembler_yydebug;
//     _sp_assembler_yydebug = 1;

   if (_sp_assembler_yyparse(_sp_context_p))
   {
      _sp_context_p->assemble_failed = true;
   }

   _sp_assembler_lexical_analyzer_cleanup();

   /* ------------------------------------------------------------------------
    * Process instruction list
    * ------------------------------------------------------------------------*/
   result = _sp_assembler_process_instructions(_sp_context_p);

   if (result != sp_ok_e)
   {
      _sp_cleanup(_sp_context_p);
      return(result);
   }

   /* ------------------------------------------------------------------------
    * Debug display of the instruction list.
    * ------------------------------------------------------------------------*/
   if ((_sp_context_p->options).debug_level & sp_debug_summary_e)
   {
      //_sp_assembler_display_instruction_list(_sp_context_p);
   }

   /* ------------------------------------------------------------------------
    * Check number of instructions.
    * ------------------------------------------------------------------------*/

   options_p->result_code_size = _sp_context_p->total_data_bytes;

   if (_sp_context_p->total_data_bytes > (
                                            (SP_PARSE_PROGRAM_MAX_BASE_ADDRESS                   -
                                             (_sp_context_p->options).program_space_base_address +
                                             1
                                            ) * 2
                                           ))
   {
      _sp_cleanup(_sp_context_p);
      return (sp_max_instructions_exceeded_e);
   }

   /* ------------------------------------------------------------------------
    * Output hardware instructions to a file or buffer.
    * ------------------------------------------------------------------------*/
   result = _sp_assembler_save_instructions(_sp_context_p,
                                              output_buffer_p,
                                              output_label_list_p);

   if (_sp_context_p->assemble_failed == true)
   {
      _sp_cleanup(_sp_context_p);
      return (sp_assemble_failed_e);
   }
   else
   {
      _sp_cleanup(_sp_context_p);
      return (sp_ok_e);
   }   
}

/* --------------------------------------------------------------------------
 * Get error string associated with error code.
 *
 * Parameters:
 *   code - Error code.
 *
 * Returns:
 *   A string representing the code.
 * --------------------------------------------------------------------------*/
const char *sp_get_error_string(sp_error_code_t code)
{
   if (code >= sp_last_error_code_e)
   {
      return("SPA: Internal error: Invalid error code passed to sp_get_error_string!");
   }

   return(_sp_error_code_strings[code]);
}
