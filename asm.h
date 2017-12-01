#ifndef ISA_ASM_H
#define ISA_ASM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "linked_list.h"

#define MAX_LINE_LEN 500 //The maximum length of a line in the assembly code
#define MEMORY_SIZE 65536 //The size of the memory in words

/**
 * A type to represent all opcodes of the SIMP commands
 */
typedef enum opcodes{
    ADD, SUB, AND, OR,
    SLL, SRA, LIMM, BEQ,
    BGT, BLE, BNE, JAL,
    LW, SW, JR, HALT
}OPCODE;

/**
 * A type to represent all registers in the processor, enumerated from 0 to 15
 */
typedef enum registers{
    ZERO, AT, V0, A0,
    A1, T0, T1, T2,
    T3, S0, S1, S2,
    GP, SP, FP, RA
}REGISTER;

/**
 *
 * @param input_path - The path to the input file (assembly code)
 * @param output_path - The path to the output file to be created
 * @return
 */
int assembler(char* input_path, char* output_path);

/**
 *
 * @param str
 * @return
 */
int calc_opcode(char* str);

/**
 *
 * @param str
 * @return
 */
int calc_register(char* str);

/**
 *
 * @param input_path
 * @return
 */
List* create_label_list(char* input_path);

/**
 *
 * @param imm_str
 * @param label_list
 * @return
 */
int calc_imm(char* imm_str, List* label_list);

/**
 *
 * @param num_string
 * @return
 */
int parse_num(char* num_string);

#endif //ISA_ASM_H
