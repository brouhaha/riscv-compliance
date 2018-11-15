// RISC-V Compliance Test Header File
// Copyright (c) 2017, Codasip Ltd. All Rights Reserved.
// See LICENSE for license details.
//
// Description: Common header file for RV32I tests

// Added UART output code for Glacial based on work by Charles Papon:
//    https://github.com/SpinalHDL/riscv-compliance/blob/vexriscv_contest/riscv-target/vexriscv_contest/compliance_test.h

#ifndef _COMPLIANCE_TEST_H
#define _COMPLIANCE_TEST_H

#include "riscv_test.h"

//-----------------------------------------------------------------------
// RV Compliance Macros
//-----------------------------------------------------------------------



#define UART_OUT(s1)  .word (0x0000000b + (s1 << 15))



// RV_COMPLIANCE_HALT register usage:
//   a0 - start of line pointer
//   a1 - end pointer (one past last byte)
//   a2 - constant 10 (decimal)
//   a3 - pointer to byte being processed
//   a4 - byte being processed
//   a5 - digit/character being processed

#define RV_COMPLIANCE_HALT                                                    \
	la a0, codasip_signature_start;					      \
	la a1, codasip_signature_end;					      \
	li a2, 10;							      \
compliance_halt_loop: ;							      \
	bge a0, a1, compliance_halt_break;				      \
	addi a3, a0, 16;						      \
compliance_halt_loop2: ;						      \
	addi a3, a3, -1;						      \
	lb a4, 0 (a3);							      \
	srai a5, a4, 4;							      \
	andi a5, a5, 0xf;						      \
	bltu a5, a2, compliance_halt_digit1;				      \
	addi a5, a5, 39;						      \
compliance_halt_digit1: ;						      \
	addi a5, a5, 0x30;						      \
	UART_OUT(15); /* a5 == x15 */					      \
	andi a5, a4, 0xf;						      \
	bltu a5, a2, compliance_halt_digit2;				      \
	addi a5, a5, 39;						      \
compliance_halt_digit2: ;						      \
	addi a5, a5, 0x30;						      \
	UART_OUT(15); /* a5 == x15 */					      \
	bne a3, a0, compliance_halt_loop2;				      \
	addi a0, a0, 16;						      \
	li a5, 0x0a;							      \
	UART_OUT(15); /* a5 == x15 */					      \
	j compliance_halt_loop;						      \
compliance_halt_break: ;						      \
	li a5, 0x04;							      \
	UART_OUT(15); /* a5 == x15 */					      \
	j compliance_halt_break;					      \


#define RV_COMPLIANCE_RV32M                                                   \


#define RV_COMPLIANCE_CODE_BEGIN                                              \
	.section .text.init;						      \
	.align 4;							      \
	.global _start;							      \
	_start: j _start2;						      \
	.align 5;							      \
	_start2: ;							      \


#define RV_COMPLIANCE_CODE_END                                                \


#define RV_COMPLIANCE_DATA_BEGIN                                              \
	.align 4;							      \
	.global codasip_signature_start;				      \
	codasip_signature_start:					      \


#define RV_COMPLIANCE_DATA_END                                                \
	.align 4;							      \
	.global codasip_signature_end;					      \
	codasip_signature_end:						      \


#endif
