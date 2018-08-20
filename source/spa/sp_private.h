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

#ifndef __SP_PRIVATE_H__
#define __SP_PRIVATE_H__

/* --------------------------------------------------------------------------
 *
 * Private header file for soft parse assembler.
 *
 * --------------------------------------------------------------------------*/
#include "sp.h"
#include "dll.h"
#include "htbl.h"

#ifdef _MSC_VER
#define snprintf _snprintf
#define strtoull _strtoui64
#define strtoll _strtoi64
#endif

#define _SP_LABEL_TABLE_SIZE 100

#define _SP_DISPLAY_LINE_SIZE  92
#define _SP_DISPLAY_DESCR_SIZE 52

#define _SP_PROG_COUNTER_MASK 	0xffff
#define _SP_GOSUB_FLAG 			0x8000
#define _SP_RELATIVE_FLAG 		0x4000
#define _SP_MAX_ABS_PROG_CTR 	SP_PARSE_PROGRAM_MAX_BASE_ADDRESS

/* 
 * Instruction code strings
 */
#define _SP_INSTR_CODE_NOP_STR                     "0x0000"
#define _SP_INSTR_CODE_ADVANCE_HB_BY_WO_STR        "0x0002"
#define _SP_INSTR_CODE_ZERO_WR_STR                 "0x0004"
#define _SP_INSTR_CODE_ONES_COMP_WR1_TO_WR0_STR    "0x0006"
#define _SP_INSTR_CODE_RETURN_SUB_STR              "0x0007"
#define _SP_INSTR_CODE_CASE1_DJ_WR_TO_WR_STR       "0x0008"
#define _SP_INSTR_CODE_CASE2_DC_WR_TO_WR_STR       "0x000c"
#define _SP_INSTR_CODE_CASE2_DJ_WR_TO_WR_STR       "0x0010"
#define _SP_INSTR_CODE_CASE3_DC_WR_TO_WR_STR       "0x0018"
#define _SP_INSTR_CODE_CASE3_DJ_WR_TO_WR_STR       "0x0020"
#define _SP_INSTR_CODE_CASE4_DC_WR_TO_WR_STR       "0x0030"
#define _SP_INSTR_CODE_ADDSUB_WR_WR_TO_WR_STR      "0x0048"
#define _SP_INSTR_CODE_ADDSUB_WR_IV_TO_WR_STR      "0x0050"
#define _SP_INSTR_CODE_BITWISE_WR_WR_TO_WR_STR     "0x0070"
#define _SP_INSTR_CODE_COMPARE_WORKING_REGS_STR    "0x0078"
#define _SP_INSTR_CODE_MODIFY_WO_BY_WR_STR         "0x0080"
#define _SP_INSTR_CODE_BITWISE_WR_IV_TO_WR_STR     "0x00c0"
#define _SP_INSTR_CODE_SHIFT_LEFT_WR_BY_SV_STR     "0x0100"
#define _SP_INSTR_CODE_SHIFT_RIGHT_WR_BY_SV_STR    "0x0180"
#define _SP_INSTR_CODE_LOAD_BITS_IV_TO_WR_STR      "0x0200"
#define _SP_INSTR_CODE_SET_CLR_FAF_STR      	   "0x0300"
#define _SP_INSTR_CODE_LOAD_SV_TO_WO_STR           "0x0600"
#define _SP_INSTR_CODE_ADD_SV_TO_WO_STR            "0x0700"
#define _SP_INSTR_CODE_STORE_IV_TO_RA_STR          "0x0800"
#define _SP_INSTR_CODE_JMP_FAF_STR            	   "0x0c00"
#define _SP_INSTR_CODE_LOAD_BYTES_PA_TO_WR_STR     "0x1000"
#define _SP_INSTR_CODE_JUMP_STR                    "0x1800"
#define _SP_INSTR_CODE_STORE_WR_TO_RA_STR          "0x2800"
#define _SP_INSTR_CODE_LOAD_BYTES_RA_TO_WR_STR     "0x3000"
#define _SP_INSTR_CODE_LOAD_BITS_FW_TO_WR_STR      "0x8000"

#define _SP_INSTR_CODE_JMP_PROTOCOL_STR            "0x0044"
/* For convenience further define the only two possible types of "JMP PROTOCOL" */
#define _SP_INSTR_CODE_JMP_NXT_ETH_TYPE_STR        "0x0044"
#define _SP_INSTR_CODE_JMP_NXT_IP_PROTO_STR        "0x0045"
#define _SP_INSTR_CODE_JMP_NXT_TCPUDP_PORTS_STR    "0x0046"
#define _SP_INSTR_CODE_JMP_NXT_INVALID_STR	   	   "0x0047"

/* 
 * Instruction codes
 */
#define _SP_INSTR_CODE_NOP                  0x0000
#define _SP_INSTR_CODE_ADVANCE_HB_BY_WO     0x0002
#define _SP_INSTR_CODE_ZERO_WR              0x0004
#define _SP_INSTR_CODE_ONES_COMP_WR1_TO_WR0 0x0006
#define _SP_INSTR_CODE_RETURN_SUB           0x0007
#define _SP_INSTR_CODE_CASE1_DJ_WR_TO_WR    0x0008
#define _SP_INSTR_CODE_CASE2_DC_WR_TO_WR    0x000c
#define _SP_INSTR_CODE_CASE2_DJ_WR_TO_WR    0x0010
#define _SP_INSTR_CODE_CASE3_DC_WR_TO_WR    0x0018
#define _SP_INSTR_CODE_CASE3_DJ_WR_TO_WR    0x0020
#define _SP_INSTR_CODE_CASE4_DC_WR_TO_WR    0x0030
#define _SP_INSTR_CODE_ADDSUB_WR_WR_TO_WR   0x0048
#define _SP_INSTR_CODE_ADDSUB_WR_IV_TO_WR   0x0050
#define _SP_INSTR_CODE_BITWISE_WR_WR_TO_WR  0x0070
#define _SP_INSTR_CODE_COMPARE_WORKING_REGS 0x0078
#define _SP_INSTR_CODE_MODIFY_WO_BY_WR      0x0080
#define _SP_INSTR_CODE_BITWISE_WR_IV_TO_WR  0x00c0
#define _SP_INSTR_CODE_SHIFT_LEFT_WR_BY_SV  0x0100
#define _SP_INSTR_CODE_SHIFT_RIGHT_WR_BY_SV 0x0180
#define _SP_INSTR_CODE_LOAD_BITS_IV_TO_WR   0x0200
#define _SP_INSTR_CODE_SET_CLR_FAF        	0x0300
#define _SP_INSTR_CODE_LOAD_SV_TO_WO        0x0600
#define _SP_INSTR_CODE_ADD_SV_TO_WO         0x0700
#define _SP_INSTR_CODE_STORE_IV_TO_RA       0x0800
#define _SP_INSTR_CODE_JMP_FAF            	0x0c00
#define _SP_INSTR_CODE_LOAD_BYTES_PA_TO_WR  0x1000
#define _SP_INSTR_CODE_JUMP                 0x1800
#define _SP_INSTR_CODE_STORE_WR_TO_RA       0x2800
#define _SP_INSTR_CODE_LOAD_BYTES_RA_TO_WR  0x3000
#define _SP_INSTR_CODE_LOAD_BITS_FW_TO_WR   0x8000

#define _SP_INSTR_CODE_JMP_PROTOCOL         0x0044
/* For convenience further define the only two possible types of "JMP PROTOCOL" */
#define _SP_INSTR_CODE_JMP_NXT_ETH_TYPE     0x0044
#define _SP_INSTR_CODE_JMP_NXT_IP_PROTO     0x0045
#define _SP_INSTR_CODE_JMP_NXT_TCPUDP_PORTS 0x0046
#define _SP_INSTR_CODE_JMP_NXT_INVALID		0x0047

/*
 * Instruction modification values
 */
#define _SP_INSTR_MOD_JMP_HXS               0x0400
#define _SP_INSTR_MOD_JMP_FAF_HXS           0x0080

/*
 * Operator values
 */
#define _SP_OPERATOR_OR  0
#define _SP_OPERATOR_AND 1
#define _SP_OPERATOR_XOR 2

#define _SP_OPERATOR_EQUAL              0
#define _SP_OPERATOR_NOT_EQUAL          1
#define _SP_OPERATOR_GREATER_THAN       2
#define _SP_OPERATOR_LESS_THAN          3
#define _SP_OPERATOR_GREATER_THAN_EQUAL 4
#define _SP_OPERATOR_LESS_THAN_EQUAL    5

#define _SP_OPERATOR_PLUS  0
#define _SP_OPERATOR_MINUS 1

#define _SP_ETH_HXS_LABEL           "ETH_HXS"
#define _SP_LLC_SNAP_HXS_LABEL      "LLC_SNAP_HXS"
#define _SP_VLAN_HXS_LABEL          "VLAN_HXS"
#define _SP_PPPOE_PPP_HXS_LABEL     "PPPOE_PPP_HXS"
#define _SP_MPLS_HXS_LABEL          "MPLS_HXS"
#define _SP_ARP_HXS_LABEL           "ARP_HXS"
#define _SP_IP_HXS_LABEL            "IP_HXS"
#define _SP_IPV4_HXS_LABEL          "IPV4_HXS"
#define _SP_IPV6_HXS_LABEL          "IPV6_HXS"
#define _SP_GRE_HXS_LABEL           "GRE_HXS"
#define _SP_MINENCAP_HXS_LABEL      "MINENCAP_HXS"
#define _SP_OTH_L3_HXS_LABEL        "OTH_L3_HXS"
#define _SP_TCP_HXS_LABEL           "TCP_HXS"
#define _SP_UDP_HXS_LABEL           "UDP_HXS"
#define _SP_IPSEC_HXS_LABEL         "IPSEC_HXS"
#define _SP_SCTP_HXS_LABEL          "SCTP_HXS"
#define _SP_DCCP_HXS_LABEL          "DCCP_HXS"
#define _SP_OTH_L4_HXS_LABEL        "OTH_L4_HXS"
#define _SP_GTP_HXS_LABEL           "GTP_HXS"
#define _SP_ESP_HXS_LABEL           "ESP_HXS"
#define _SP_VxLAN_HXS_LABEL         "VxLAN_HXS"
#define _SP_OTH_L5_HXS_LABEL		"OTH_L5_HXS"
#define _SP_FINAL_SHELL_HXS_LABEL	"FINAL_SHELL"
#define _SP_RETURN_HXS_LABEL        "RETURN_HXS"
#define _SP_END_PARSE_LABEL         "END_PARSE"

#define _SP_ETH_HXS           0x000
#define _SP_LLC_SNAP_HXS      0x001
#define _SP_VLAN_HXS          0x002
#define _SP_PPPOE_PPP_HXS     0x003
#define _SP_MPLS_HXS          0x004
#define _SP_ARP_HXS			  0x005
#define _SP_IP_HXS			  0x006
#define _SP_IPV4_HXS          0x007
#define _SP_IPV6_HXS          0x008
#define _SP_GRE_HXS           0x009
#define _SP_MINENCAP_HXS      0x00a
#define _SP_OTH_L3_HXS        0x00b
#define _SP_TCP_HXS           0x00c
#define _SP_UDP_HXS           0x00d
#define _SP_IPSEC_HXS         0x00e
#define _SP_SCTP_HXS          0x00f
#define _SP_DCCP_HXS          0x010
#define _SP_OTH_L4_HXS        0x011
#define _SP_GTP_HXS			  0x012
#define _SP_ESP_HXS			  0x013
#define _SP_VxLAN_HXS		  0x014
#define _SP_OTH_L5_HXS		  0x01e
#define _SP_FINAL_SHELL_HXS	  0x01f
#define _SP_RETURN_HXS        0x7fe
#define _SP_END_PARSE         0x7ff

#define _SP_MAX_INSTR_WORDS 	992


// Frame Attribute Flag (FAF) codes:

//Frame Attribute Flags 0-95
#define _FAF_IPv6_Route_Hdr2_Present                0
#define _FAF_GTP_Primed_Detected					1
#define _FAF_VLAN_Prio_Detected						2
#define _FAF_PTP_Detected							3
#define _FAF_VXLAN_Present							4
#define _FAF_VXLAN_Parsing_error					5
#define _FAF_Ethernet_slow_protocol					6
#define _FAF_IKE_Present							7
#define _FAF_Shim_Shell_Soft_Parsing_Error          8
#define _FAF_Parsing_Error                          9
#define _FAF_Ethernet_MAC_Present                   10
#define _FAF_Ethernet_Unicast                       11
#define _FAF_Ethernet_Multicast                     12
#define _FAF_Ethernet_Broadcast                     13
#define _FAF_BPDU_Frame                             14
#define _FAF_FCoE_Detected                          15
#define _FAF_FIP_Detected                           16
#define _FAF_Ethernet_Parsing_Error                 17
#define _FAF_LLC_SNAP_Present                       18
#define _FAF_Unknown_LLC_OUI                        19
#define _FAF_LLC_SNAP_Error                         20
#define _FAF_VLAN_1_Present                         21
#define _FAF_VLAN_n_Present                         22
#define _FAF_GRE_Ethernet                           23
#define _FAF_VLAN_Parsing_Error                     24
#define _FAF_PPPoE_PPP_Present                      25
#define _FAF_PPPoE_PPP_Parsing_Error                26
#define _FAF_MPLS_1_Present                         27
#define _FAF_MPLS_n_Present                         28
#define _FAF_MPLS_Parsing_Error                     29
#define _FAF_ARP_Frame_Present                      30
#define _FAF_ARP_Parsing_Error                      31
#define _FAF_L2_Unknown_Protocol                    32
#define _FAF_L2_Soft_Parsing_Error                  33
#define _FAF_IPv4_1_Present                         34
#define _FAF_IPv4_1_Unicast                         35
#define _FAF_IPv4_1_Multicast                       36
#define _FAF_IPv4_1_Broadcast                       37
#define _FAF_IPv4_n_Present                         38
#define _FAF_IPv4_n_Unicast                         39
#define _FAF_IPv4_n_Multicast                       40
#define _FAF_IPv4_n_Broadcast                       41
#define _FAF_IPv6_1_Present                         42
#define _FAF_IPv6_1_Unicast                         43
#define _FAF_IPv6_1_Multicast                       44
#define _FAF_IPv6_n_Present                         45
#define _FAF_IPv6_n_Unicast                         46
#define _FAF_IPv6_n_Multicast                       47
#define _FAF_IP_1_Option_Present                    48
#define _FAF_IP_1_Unknown_Protocol                  49
#define _FAF_IP_1_Packet_Is_A_Fragment              50
#define _FAF_IP_1_Packet_Is_An_Initial_Fragment     51
#define _FAF_IP_1_Parsing_Error                     52
#define _FAF_IP_n_Option_Present                    53
#define _FAF_IP_n_Unknown_Protocol                  54
#define _FAF_IP_n_Packet_Is_A_Fragment              55
#define _FAF_IP_n_Packet_Is_An_Initial_Fragment     56
#define _FAF_ICMP_Detected                          57
#define _FAF_IGMP_Detected                          58
#define _FAF_ICMPv6_Detected                        59
#define _FAF_UDP_Light_Detected                     60
#define _FAF_IP_n_Parsing_Error                     61
#define _FAF_Min_Encap_Present                      62
#define _FAF_Min_Encap_S_flag_Set                   63
#define _FAF_Min_Encap_Parsing_Error                64
#define _FAF_GRE_Present                            65
#define _FAF_GRE_R_Bit_Set                          66
#define _FAF_GRE_Parsing_Error                      67
#define _FAF_L3_Unknown_Protocol                    68
#define _FAF_L3_Soft_Parsing_Error                  69
#define _FAF_UDP_Present                            70
#define _FAF_UDP_Parsing_Error                      71
#define _FAF_TCP_Present                            72
#define _FAF_TCP_Options_Present                    73
#define _FAF_TCP_Control_Bits_6_11_Set              74
#define _FAF_TCP_Control_Bits_3_5_Set               75
#define _FAF_TCP_Parsing_Error                      76
#define _FAF_IPSec_Present                          77
#define _FAF_IPSec_ESP_Found                        78
#define _FAF_IPSec_AH_Found                         79
#define _FAF_IPSec_Parsing_Error                    80
#define _FAF_SCTP_Present                           81
#define _FAF_SCTP_Parsing_Error                     82
#define _FAF_DCCP_Present                           83
#define _FAF_DCCP_Parsing_Error                     84
#define _FAF_L4_Unknown_Protocol                    85
#define _FAF_L4_Soft_Parsing_Error                  86
#define _FAF_GTP_Present                            87
#define _FAF_GTP_Parsing_Error                      88
#define _FAF_ESP_Present                            89
#define _FAF_ESP_Parsing_Error                      90
#define _FAF_iSCSI_Detected                         91
#define _FAF_Capwap_Control_Detected                92
#define _FAF_Capwap_Data_Detected                   93
#define _FAF_L5_Soft_Parsing_Error                  94
#define _FAF_IPv6_Route_Hdr1_Present                95

//FAF Extension
#define _FAF_User_Defined_0                         96
#define _FAF_User_Defined_1                         97
#define _FAF_User_Defined_2                         98
#define _FAF_User_Defined_3                         99
#define _FAF_User_Defined_4                         100
#define _FAF_User_Defined_5                         101
#define _FAF_User_Defined_6                         102
#define _FAF_User_Defined_7                         103
#define _FAF_Reserved                               104

/* ------------------------------------------------------------------------
 * Assembler parser context object.
 * ------------------------------------------------------------------------ */
typedef struct _sp_assembler_parser_context
{
   bool                       assemble_failed;
   sp_assembler_options_t   options;
   sp_error_code_t          assemble_msg_composition_error;
   char                     **assemble_msg_p;
   char                      *current_file_name_p;
   char                      *output_file_name_p;
   uint32_t                   line_number;
   dll_list_t                 instruction_list;
   uint32_t                   next_program_counter;
   htbl_table_t              *label_table_p;
   char                      *raw_str_p[5];
   uint16_t                   immediate_value[4];
   uint8_t                    num_immediate_values;
   uint32_t                   total_data_bytes;
   uint8_t                    range_start;
   uint8_t                    range_end;
   uint32_t                   ethernet_hxs;
   uint32_t                   ipv4_hxs;
   uint32_t                   ipv6_hxs;
   uint32_t                   other_l3_hxs;
   uint32_t                   tcp_hxs;
   uint32_t                   udp_hxs;
   uint32_t                   ipsec_hxs;
   uint32_t                   other_l4_hxs;
   uint32_t                   l5_hxs;
   char                      *current_source_line_p;
} _sp_assembler_parser_context_t;

/* ------------------------------------------------------------------------
 * Instruction type
 * ------------------------------------------------------------------------ */
typedef enum
{
   _sp_assembler_raw_e = 0,
   _sp_assembler_label_e,
   _sp_assembler_nop_e,
   _sp_assembler_advance_hb_by_wo_e,
   _sp_assembler_zero_wr_e,
   _sp_assembler_ones_comp_wr1_to_wr0_e,
   _sp_assembler_return_sub_e,
   _sp_assembler_case1_dj_wr_to_wr_e,
   _sp_assembler_case2_dc_wr_to_wr_e,
   _sp_assembler_case2_dj_wr_to_wr_e,
   _sp_assembler_case3_dc_wr_to_wr_e,
   _sp_assembler_case3_dj_wr_to_wr_e,
   _sp_assembler_case4_dc_wr_to_wr_e,
   _sp_assembler_bitwise_wr_wr_to_wr_e,
   _sp_assembler_compare_working_regs_e,
   _sp_assembler_bitwise_wr_iv_to_wr_e,
   _sp_assembler_shift_left_wr_by_sv_e,
   _sp_assembler_shift_right_wr_by_sv_e,
   _sp_assembler_load_bits_iv_to_wr_e,
   _sp_assembler_set_clr_faf_e,
   _sp_assembler_load_sv_to_wo_e,
   _sp_assembler_add_sv_to_wo_e,
   _sp_assembler_store_iv_to_ra_e,
   _sp_assembler_jmp_faf_e,
   _sp_assembler_load_bytes_pa_to_wr_e,
   _sp_assembler_jump_e,
   _sp_assembler_store_wr_to_ra_e,
   _sp_assembler_load_bytes_ra_to_wr_e,
   _sp_assembler_load_bits_fw_to_wr_e,
   _sp_assembler_modify_wo_by_wr_e,
   _sp_assembler_addsub_wr_wr_to_wr_e,
   _sp_assembler_addsub_wr_iv_to_wr_e,
   _sp_assembler_jmp_nxt_eth_type_e,
   _sp_assembler_jmp_nxt_ip_proto_e,
   _sp_assembler_jmp_nxt_tcpudp_ports_e

} _sp_assembler_instruction_type_t;

/* ------------------------------------------------------------------------
 * Variable type
 * ------------------------------------------------------------------------ */
typedef enum _sp_variable
{
   _sp_uint6_type_e,
   _sp_uint7_type_e,
   _sp_uint8_type_e,
   _sp_uint16_type_e,
   _sp_uint32_type_e,
   _sp_uint48_type_e,
   _sp_uint64_type_e

} _sp_assembler_variable_type_t;

/* ------------------------------------------------------------------------
 * Label type
 * ------------------------------------------------------------------------ */
typedef struct _sp_label
{
   htbl_entry_t htbl_entry;
   int32_t      program_counter;
} _sp_label_t;

/* ------------------------------------------------------------------------
 * Assembler instruction object
 * ------------------------------------------------------------------------ */
typedef struct _sp_assembler_instruction
{
   /* Double linked list node */
   dll_node_t                         dll_node;

   /* Instruction type */
   _sp_assembler_instruction_type_t type;

   /* Souce file line number for this instruction */
   uint32_t                           line_number;

   /* Hardware program counter for this instruction */
   uint32_t                           program_counter;

   /* Operands, if any */
   uint16_t                           operand[4];
   uint32_t                           operand_size; /* 0, 1, 2, 3, or 4 */

   /* Jump labels */
   char                              *jump_label1_p;
   char                              *jump_label2_p;
   char                              *jump_label3_p;
   char                              *jump_label4_p;

   /* Working register */
   uint8_t                            working_register;

   /* Target working register */
   uint8_t                            target_working_register;

   /* Source working register */
   uint8_t                            source_working_register;

   /* Function */
   uint8_t                            function;

   /* Range start */
   uint8_t                            range_start;

   /* Range end */
   uint8_t                            range_end;

   /* Assign or Concat */
   bool                               is_assign;

   /* HXS */
   bool                               hxs;
   bool                               hxs_1;
   bool                               hxs_2;
   bool                               hxs_3;
   bool                               hxs_4;

   /* Increment Window Offset */
   bool                               increment_window_offset;

   /* Hardware instruction words */
   char                              *hw_words_str_p[5];
   uint16_t                           hw_words_p[5];
   uint8_t                            num_valid_hw_words;

   /* Number of bits */
   uint8_t                            num_bits;

   /* Gosub instead of a normal jump */
   bool                               gosub;

} _sp_assembler_instruction_t;

/* ------------------------------------------------------------------------
 * Cleanup the lexical analyzer.
 * ------------------------------------------------------------------------ */
void _sp_assembler_lexical_analyzer_cleanup(void);

/* ------------------------------------------------------------------------
 * Deal with parse error.
 * ------------------------------------------------------------------------ */
void _sp_assembler_yyerror (_sp_assembler_parser_context_t *context_p,
                              char const                       *str_p);

/* ------------------------------------------------------------------------
 * New assembler parser context object.
 *
 * Parameters:
 *   None.
 *
 * Returns:
 *   Pointer to new context object.
 * ------------------------------------------------------------------------ */
_sp_assembler_parser_context_t *_sp_new_parse_context(void);

/* ------------------------------------------------------------------------
 * Destroy assembler parser context object.
 *
 * Parameters:
 *   Pointer to context object.
 *
 * Returns:
 *   Nothing.
 * ------------------------------------------------------------------------ */
void _sp_destroy_parse_context(_sp_assembler_parser_context_t *object_p);

/* ------------------------------------------------------------------------
 * New assembler instruction object.
 *
 * Parameters:
 *   type - Instruction type.
 *
 * Returns:
 *   Pointer to new instruction object.
 * ------------------------------------------------------------------------ */
_sp_assembler_instruction_t *_sp_new_instruction(_sp_assembler_instruction_type_t  type,
                                                     _sp_assembler_parser_context_t   *ctx_p);

/* ------------------------------------------------------------------------
 * Destroy assembler instruction object.
 *
 * Parameters:
 *   Pointer to instruction object.
 *
 * Returns:
 *   Nothing.
 * ------------------------------------------------------------------------ */
void _sp_destroy_instruction(_sp_assembler_instruction_t *object_p);

/* ------------------------------------------------------------------------
 * New label object.
 *
 * Parameters:
 *   label_string - Pointer to label string.
 *
 * Returns:
 *   Pointer to new label object.
 * ------------------------------------------------------------------------ */
_sp_label_t *_sp_new_label(char     *label_string,
                               uint32_t  program_counter);

/* ------------------------------------------------------------------------
 * Destroy label object.
 *
 * Parameters:
 *   Pointer to label object.
 *
 * Returns:
 *   Nothing.
 * ------------------------------------------------------------------------ */
void _sp_destroy_label(_sp_label_t *object_p);

/* ------------------------------------------------------------------------
 * Cleanup
 *
 * Parameters:
 *   Pointer to context object.
 *
 * Returns:
 *   Nothing.
 * ------------------------------------------------------------------------ */
void _sp_cleanup(_sp_assembler_parser_context_t *object_p);

/* ---------------------------------------------------------------------------
 * Compose assembler messages
 *
 * Parameters:
 *   context_p - Pointer to context object.
 *   string_p  - Pointer to string to add to message.
 *
 * Returns:
 *   Error code of type sp_error_code_t.
 * ---------------------------------------------------------------------------*/
sp_error_code_t _sp_compose_user_msg (_sp_assembler_parser_context_t *context_p,
                                          char                             *string_p);

/* ---------------------------------------------------------------------------
 * Process instruction list
 *
 * Parameters:
 *   context_p - Pointer to context object.
 *
 * Returns:
 *   Error code of type sp_error_code_t.
 * ---------------------------------------------------------------------------*/
sp_error_code_t _sp_assembler_process_instructions (_sp_assembler_parser_context_t *context_p);

/* ---------------------------------------------------------------------------
 * Write out hardware instructions
 *
 * Parameters:
 *   context_p - Pointer to context object.
 *
 * Returns:
 *   Error code of type sp_error_code_t.
 * ---------------------------------------------------------------------------*/
sp_error_code_t _sp_assembler_write_output (_sp_assembler_parser_context_t *context_p);

/* ---------------------------------------------------------------------------
 * Save hardware instructions
 *
 * Parameters:
 *   ctx_p        - Pointer to context object.
 *   buffer_p     - Buffer to store assembled opcodes.
 *   label_list_p - List to store labels.
 *
 * Returns:
 *   Error code of type sp_error_code_t.
 * ---------------------------------------------------------------------------*/
sp_error_code_t _sp_assembler_save_instructions (_sp_assembler_parser_context_t  *ctx_p,
                                                     uint8_t                           *buffer_p,
                                                     sp_label_list_t                **label_list_p);

/* ---------------------------------------------------------------------------
 * Clear context instruction values for next instruction.
 *
 * Parameters:
 *   ctx_p - Pointer to context object.
 *
 * Returns:
 *   Nothing.
 * ---------------------------------------------------------------------------*/
void _sp_clear_ctx_instruction_values (_sp_assembler_parser_context_t *ctx_p);

/* ---------------------------------------------------------------------------
 * Convert range string to start and end integer values.
 *
 * Parameters:
 *   range_string_p - Range string of form xxx:yyy
 *   start_index_p  - Pointer to start index that function will fill in.
 *   end_index_p    - Pointer to end index that function will fill in.
 *
 * Returns:
 *   Boolean - True if successful, false if not.
 * ---------------------------------------------------------------------------*/
bool _sp_convert_range_string (char    *range_string_p,
                                 uint8_t *start_index_p,
                                 uint8_t *end_index_p);

#endif /* __SP_PRIVATE_H__ */
