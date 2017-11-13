#ifndef ISA_ASM_H
#define ISA_ASM_H


#define MAX_LINE_LEN 500
#define MAX_LABEL_LEN 50

typedef enum opcodes{
    ADD, SUB, AND, OR,
    SLL, SRA, LIMM, BEQ,
    BGT, BLE, BNE, JAL,
    LW, SW, JR, HALT
}OPCODE;

typedef enum registers{
    ZERO, AT, V0, A0,
    A1, T0, T1, T2,
    T3, S0, S1, S2,
    GP, SP, FP, RA
}REGISTER;

int assembler(char* asm_prog_path, char* output_path);

int calc_opcode(char* str);

int calc_register(char* str);

#endif //ISA_ASM_H
