#include <stdio.h>
#include <assert.h>

#include "asm.h"

int main(int argc, char* argv[]) {
    char* asm_prog_path;
    char* output_path;


    assert(argc == 3);
    asm_prog_path = argv[1];
    output_path = argv[2];

    assembler(asm_prog_path, output_path);
    return 0;
}