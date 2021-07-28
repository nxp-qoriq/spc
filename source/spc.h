/* ============================================================================
 *
 * The MIT License (MIT)
 * Copyright 2018-2019,2021 NXP
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
 * File Name : spc.h
 *
 * ========================================================================= */

#ifndef LIBSPC_H
#define LIBSPC_H

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdio.h>
#include <std_ext.h>
//include mc net header: /linux/drivers/staging/fsl-mc/include/net.h
#include <net.h>

#define SP_ASSEMBLER_BASE_COUNT 			0x20				/**< Soft Parser base in instruction words (1 word = 2 bytes): must be larger than 0x20 */
#define SP_ASSEMBLER_BASE_ADDRESS 			(2 * SP_ASSEMBLER_BASE_COUNT)	/**< Soft Parser base address in bytes: must be larger than 0x40 */
#define MAX_SP_CODE_SIZE      				0xFBC 				 /**< 4028 bytes */

#define PRS_NUM_OF_HDRS                      16                  /**< Number of headers supported by HW parser */
#define PRS_PARAM_SIZE                       64                  /**< Size in bytes of parameters area */
#define PRS_NUM_OF_LABELS                    32                  /**< Maximum number of SW parser labels */


int spc_compile(const char*  nameCfg, const char*  namePDL, const char*  nameSP, bool genIntermCode);

const char* spc_get_error( void );


#define LOG_NONE 0
#define LOG_ERR  1
#define LOG_WARN 2
#define LOG_INFO 3
#define LOG_DBG1 4
#define LOG_DBG2 5
#define LOG_DBG3 6

int32_t spc_log( int32_t level );

void spc_log_write( int32_t level, const char* format, ... );


#ifdef __cplusplus
}  // extern "C"
#endif

#endif // LIBSPC_H
