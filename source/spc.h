/* ============================================================================
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

#define MAX_SP_CODE_SIZE      		0xFBC //4028 bytes

#define PRS_NUM_OF_HDRS                      16                  /**< Number of headers supported by HW parser */
#define PRS_NUM_OF_LABELS                    32                  /**< Maximum number of SW parser labels */

/**************************************************************************//**
 @Description   A structure for SW parser labels
 *//***************************************************************************/
typedef struct t_PrsLabelParams {
    uint32_t                instructionOffset;              /**< SW parser label instruction offset (2 bytes
                                                                 resolution), relative to Parser RAM. */
    enum net_prot         	hdr;                            /**< The existence of this header will invoke
                                                                 the SW parser code; Use  NET_PROT_NONE
                                                                 to indicate that sw parser is to run
                                                                 independent of the existence of any protocol
                                                                 (run before HW parser). */
    uint8_t                 indexPerHdr;                    /**< Normally 0, if more than one SW parser
                                                                 attachments for the same header, use this
                                                                 index to distinguish between them. */
} t_PrsLabelParams;


/**************************************************************************//**
 @Description   A structure for SW parser
 *//***************************************************************************/
typedef struct t_PrsSwParams {
    bool                    override;                   /**< FALSE to invoke a check that nothing else
                                                             was loaded to this address, including
                                                             internal patches.
                                                             TRUE to override any existing code.*/
    uint32_t                size;                       /**< SW parser code size */
    uint16_t                base;                       /**< SW parser base (in instruction counts!
                                                             must be larger than 0x20)*/
    uint8_t                 *p_Code;                    /**< SW parser code */
    uint32_t                swPrsDataParams[PRS_NUM_OF_HDRS];
                                                        /**< SW parser data (parameters) */
    uint8_t                 numOfLabels;                /**< Number of labels for SW parser. */
    t_PrsLabelParams   		labelsTable[PRS_NUM_OF_LABELS];
                                                        /**< SW parser labels table, containing
                                                             numOfLabels entries */
} t_PrsSwParams;

typedef struct spc_model_t {

    unsigned int             format_version;
    t_PrsSwParams		     sp;                  ///< Soft parser configuration
    uint8_t                  spCode[MAX_SP_CODE_SIZE];

} spc_model;


int spc_compile(
		spc_model*   model,
        const char*  namePDL,
        const char*  nameSP,
        unsigned int swOffset,
        bool genIntermCode
);

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
