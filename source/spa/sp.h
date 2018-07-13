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

#ifndef __SP_H__
#define __SP_H__

/* --------------------------------------------------------------------------
 *
 * Public header file for soft parse assembler.
 *
 * --------------------------------------------------------------------------*/

#ifndef _MSC_VER
#include <inttypes.h>  /* For standard int types and print format macros */
#include <stdbool.h>   /* For the bool type */
#else
#define uint32_t unsigned int
#define int32_t  signed   int
#define uint16_t unsigned short
#define uint8_t  unsigned char
#endif

/* File type for SP. (uses ASCII for SP) */
#define SP_FILE_TYPE 0x50455350

#define SP_PARSE_PROGRAM_DEFAULT_BASE_ADDRESS 	0x20
#define SP_PARSE_PROGRAM_MIN_BASE_ADDRESS 		0x20
#define SP_PARSE_PROGRAM_MAX_BASE_ADDRESS 		0x7ff

/* --------------------------------------------------------------------------
 * Define error codes.
 *
 * WARNING: Do not remove error codes.
 *          Do not change error code values.
 *          All new error codes must be added to end and enumerated correctly.
 * --------------------------------------------------------------------------*/
typedef enum
{
   /* 0 - Sucess */
   sp_ok_e                                 = 0,

   /* 1 - Memory allocation failure */
   sp_malloc_failure_e                     = 1,

   /* 2 - Failed to open input file */
   sp_input_file_open_failure_e            = 2,

   /* 3 - Failed to open output file */
   sp_output_file_open_failure_e           = 3,

   /* 4 - Unrecognized option */
   sp_unrecognized_option_e                = 4,

   /* 5 - Assemble failed */
   sp_assemble_failed_e                    = 5,

   /* 6 - Warnings */
   sp_warnings_e                           = 6,

   /* 7 - Invalid option */
   sp_invalid_option_e                     = 7,

   /* 8 - Internal error */
   sp_internal_error_e                     = 8,

   /* 9 - Output file write error */
   sp_output_file_write_error_e            = 9,

   /* 10 - Invalid label */
   sp_invalid_label_e                      = 10,

   /* 11 - Max instructions exceeded */
   sp_max_instructions_exceeded_e          = 11,

   /* 12 - Invalid parse program base address */
   sp_invalid_parse_program_base_address_e = 12,

   /* DO NOT MOVE OR REMOVE THIS!                                         */
   /* Used for error detection. Do not number this one and leave it last. */
   sp_last_error_code_e

} sp_error_code_t;


/* --------------------------------------------------------------------------
 * Debug levels
 * --------------------------------------------------------------------------*/
typedef enum
{
   sp_debug_none_e         = 0x00000000,  /* Used to initialize debug level to none */
   sp_debug_summary_e      = 0x00000001,  /* Summary level of info */
   sp_debug_detailed_e     = 0x00000002,  /* Show detailed debug info */
   sp_debug_test_e         = 0x00000004   /* Show test info */

} sp_debug_levels_t;

/* --------------------------------------------------------------------------
 * Assembler options
 * --------------------------------------------------------------------------*/
typedef struct sp_assembler_options
{
   sp_debug_levels_t debug_level;
   int                 warnings_are_errors;
   int                 suppress_warnings;
   uint32_t            program_space_base_address;
   uint32_t            result_code_size;
} sp_assembler_options_t;

/* --------------------------------------------------------------------------
 * Label list which holds the name, size, and position for all labels
 * used in the original assembler code.
 * --------------------------------------------------------------------------*/
typedef struct sp_label_list
{
   char                   *name;
   uint32_t                byte_position;
   uint8_t                 bit_offset;
   uint8_t                 bit_size;
   struct sp_label_list *next_p;
} sp_label_list_t;

/* ==========================================================================
 *                              Public APIs
 * ==========================================================================*/

/* --------------------------------------------------------------------------
 * Assembler API
 *
 * Parameters:
 *   input_string_p     - Input text string.
 *   output_binary_p    - Output binary.
 *   label_list_p       - List of label information objects.
 *   options_p          - Options for the assembler.
 *   assemble_msg_p     - Pointer to pointer to string for assembler
 *                        messages.  The user may choose not to use this
 *                        parameter and supply NULL.
 *
 * Returns:
 *   An error code of type sp_error_code_t.
 * --------------------------------------------------------------------------*/
sp_error_code_t sp_assemble(char                      *input_string_p,
                                uint8_t                   *output_binary_p,
                                sp_label_list_t        **label_list_p,
                                sp_assembler_options_t  *options_p,
                                char                     **assemble_msg_p);

/* --------------------------------------------------------------------------
 * Get error string associated with error code.
 *
 * Parameters:
 *   code - Error code.
 *
 * Returns:
 *   A string representing the code.
 * --------------------------------------------------------------------------*/
const char *sp_get_error_string(sp_error_code_t code);

#endif /* __SP_H__ */
