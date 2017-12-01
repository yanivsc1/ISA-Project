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


List* create_label_list(char* input_path){
    List* label_list;
    FILE* input_file;
    char line[MAX_LINE_LEN];
    char* str = NULL;
    char* label = NULL;
    unsigned int line_num = 0;
    input_file = fopen(input_path, "r");
    if (input_file == NULL){
        perror("open() error");
        return NULL;
    }
    label_list = create_list();
    while (fgets(line, MAX_LINE_LEN, input_file) != NULL) {
        if (line[0] == '\n' || line[0] == '#'){
            continue;
        }
        line_num++;
        str = strtok(line, " \t\r\n");
        if (str == NULL){
            printf("strtok() error\n");
            fclose(input_file);
            free_list(label_list);
            return NULL;
        }
        if (strcmp(str, ".word") == 0){
            line_num--;
            continue;
        }
        if (strstr(str, ":") != NULL){ //LABEL FOUND
            label = str;
            if (strtok(NULL, " \t\r\n") == NULL) {
                line_num--;
            }
            insert_node(label_list, label, line_num);
        }
    }
    fclose(input_file);
    return label_list;
}

int calc_imm(char* imm_str, List* label_list){
    if ((imm_str[0] >= 'a' && imm_str[0] <= 'z') || (imm_str[0] >= 'A' && imm_str[0] <= 'Z')){ //If the first character of imm is a letter
        return find_node(label_list, imm_str);
    }
    return parse_num(imm_str);
}

int parse_num(char* num_string){
    if (strstr(num_string, "0x") != NULL){ // Num is in hexadecimal
        return (int)strtol(num_string, NULL, 0);
    }
    return strtol(num_string, NULL, 10);
}



int assembler(char* input_path, char* output_path){
    FILE* input_file;
    FILE* output_file;
    char line[MAX_LINE_LEN];
    char* str;
    int op_code = 0;
    int rd = 0;
    int rs = 0;
    int rt = 0;
    int imm = 0;
    int instruction = 0;
    unsigned int mask = 0;
    List* label_list = create_label_list(input_path);
    int memory[MEMORY_SIZE] = {0};
    int memory_index = 0;
    int address = 0, data = 0;
    int memin_length = 0;

    input_file = fopen(input_path, "r");
    if (input_file == NULL){
        perror("open() error");
        free_list(label_list);
        return -1;
    }
    output_file = fopen(output_path, "w");
    if (output_file == NULL){
        perror("open() error");
        fclose(input_file);
        free_list(label_list);
        return -1;
    }

    while (fgets(line, MAX_LINE_LEN, input_file) != NULL) {
        if (line[0] == '\n' || line[0] == '#'){
            continue;
        }
        str = strtok(line, " \t\r\n,");
        if (str == NULL) {
            printf("strtok() error\n");
            fclose(input_file);
            fclose(output_file);
            free_list(label_list);
            return -1;
        }
        if (strstr(str, ":") != NULL) { // We found a label
            str = strtok(NULL, " \t\r\n:,");
            if (str == NULL) {
                continue;
            }
        }
        if (strcmp(str, ".word") == 0) { // If command is "word"
            str = strtok(NULL, " \t\r\n");
            if (str == NULL) {
                printf("strtok() error");
                fclose(input_file);
                fclose(output_file);
                free_list(label_list);
                return -1;
            }
            address = parse_num(str);
            str = strtok(NULL, " \t\r\n");
            if (str == NULL) {
                printf("strtok() error");
                fclose(input_file);
                fclose(output_file);
                free_list(label_list);
                return -1;
            }
            data = parse_num(str);
            memory[address] = data;
        } else {
            op_code = calc_opcode(str);

            str = strtok(NULL, " \t\r\n,");
            if (str == NULL) {
                printf("strtok() error");
                fclose(input_file);
                fclose(output_file);
                free_list(label_list);
                return -1;
            }
            rd = calc_register(str);
            str = strtok(NULL, " \t\r\n,");
            if (str == NULL) {
                printf("strtok() error");
                fclose(input_file);
                fclose(output_file);
                free_list(label_list);
                return -1;
            }
            rs = calc_register(str);
            str = strtok(NULL, " \t\r\n,");
            if (str == NULL) {
                printf("strtok() error");
                fclose(input_file);
                fclose(output_file);
                free_list(label_list);
                return -1;
            }
            rt = calc_register(str);
            str = strtok(NULL, " \t\r\n,");
            if (str == NULL) {
                printf("strtok() error");
                fclose(input_file);
                fclose(output_file);
                free_list(label_list);
                return -1;
            }

            imm = calc_imm(str, label_list);

            mask = 1;
            for (int i = 0; i < 15; ++i) {
                mask <<= 1;
                mask++;
            }

            imm &= mask;

            op_code <<= 28;
            rd <<= 24;
            rs <<= 20;
            rt <<= 16;
            instruction = op_code | rd | rs | rt | imm;
            memory[memory_index] = instruction;
            memory_index++;
        }
    }

    for (memin_length = MEMORY_SIZE-1; memin_length > 0; --memin_length){
        if (memory[memin_length] != 0){
            break;
        }
    }
    for (int i = 0; i <= memin_length; ++i){
        fprintf(output_file, "%.8X\n", memory[i]);
    }

    fclose(input_file);
    fclose(output_file);
    free_list(label_list);
    return 0;
}