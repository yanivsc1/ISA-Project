#include "asm.h"

//Returns -1 if failed
int calc_opcode(char* str){
    if (strcmp(str, "add") == 0){
        return ADD;
    }
    if (strcmp(str, "sub") == 0){
        return SUB;
    }
    if (strcmp(str, "and") == 0){
        return AND;
    }
    if (strcmp(str, "or") == 0){
        return OR;
    }
    if (strcmp(str, "sll") == 0){
        return SLL;
    }
    if (strcmp(str, "sra") == 0){
        return SRA;
    }
    if (strcmp(str, "limm") == 0){
        return LIMM;
    }
    if (strcmp(str, "beq") == 0){
        return BEQ;
    }
    if (strcmp(str, "beq") == 0){
        return BEQ;
    }
    if (strcmp(str, "bgt") == 0){
        return BGT;
    }
    if (strcmp(str, "ble") == 0){
        return BLE;
    }
    if (strcmp(str, "bne") == 0){
        return BNE;
    }
    if (strcmp(str, "jal") == 0){
        return JAL;
    }
    if (strcmp(str, "lw") == 0){
        return LW;
    }
    if (strcmp(str, "sw") == 0){
        return SW;
    }
    if (strcmp(str, "jr") == 0){
        return JR;
    }
    if (strcmp(str, "halt") == 0){
        return HALT;
    }
    return -1;
}

int calc_register(char* str){
    if (strcmp(str, "$zero") == 0){
        return ZERO;
    }
    if (strcmp(str, "$at") == 0){
        return AT;
    }
    if (strcmp(str, "$v0") == 0){
        return V0;
    }
    if (strcmp(str, "$a0") == 0){
        return A0;
    }
    if (strcmp(str, "$a1") == 0){
        return A1;
    }
    if (strcmp(str, "$t0") == 0){
        return T0;
    }
    if (strcmp(str, "$t1") == 0){
        return T1;
    }
    if (strcmp(str, "$t2") == 0){
        return T2;
    }
    if (strcmp(str, "$t3") == 0){
        return T3;
    }
    if (strcmp(str, "$s0") == 0){
        return S0;
    }
    if (strcmp(str, "$s1") == 0){
        return S1;
    }
    if (strcmp(str, "$s2") == 0){
        return S2;
    }
    if (strcmp(str, "$gp") == 0){
        return GP;
    }
    if (strcmp(str, "$sp") == 0){
        return SP;
    }
    if (strcmp(str, "$fp") == 0){
        return FP;
    }
    if (strcmp(str, "$ra") == 0){
        return RA;
    }
    return -1;
}


int assembler(char* asm_prog_path, char* output_path){
    FILE* asm_prog;
    FILE* output_file;
    char line[MAX_LINE_LEN];
    char* str;
    int op_code = 0;
    int rd = 0;
    int rs = 0;
    int rt = 0;
    int imm = 0;
    int instruction;
    asm_prog = fopen(asm_prog_path, "r");
    if (asm_prog == NULL){
        //TODO: HANDLE ERROR !!!!!!!!!!!!!!!!!!!!!
    }
    output_file = fopen(output_path, "w");
    if (output_file == NULL){
        //TODO: HANDLE ERROR !!!!!!!!!!!!!!!!!!!!!!!
    }

    // TODO: LABELS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    while (fgets(line, MAX_LINE_LEN, asm_prog) != NULL){
        str = strtok(line, " \t\r\n,");
        if (str == NULL){
            // TODO: HANDLE ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
        //TODO: CHECK IF IT'S A LABEL BEFORE CONTINUING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        op_code = calc_opcode(str);
        str = strtok(NULL, " \t\r\n,");
        if (str == NULL){
            // TODO: HANDLE ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
        rd = calc_register(str);
        str = strtok(NULL, " \t\r\n,");
        if (str == NULL){
            // TODO: HANDLE ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
        rs = calc_register(str);
        str = strtok(NULL, " \t\r\n,");
        if (str == NULL){
            // TODO: HANDLE ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
        rt = calc_register(str);
        str = strtok(NULL, " \t\r\n,");
        if (str == NULL){
            // TODO: HANDLE ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
        imm = atoi(str);

        op_code = op_code << 28;
        rd = rd << 24;
        rs = rs << 20;
        rt = rt << 16;
        instruction = op_code + rd + rs + rt + imm;
        //TODO: DELETE THIS PRINTF!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        printf("%.8x\n", instruction);
    }

}