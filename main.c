#include <stdio.h>

#include "parser.h"

int main(int argc, char** argv) {
    if(argc < 2) {
        fprintf(stderr, "Wrong usage");
        return 1;
    }

    const char* filepath = argv[1];
    FILE* source = fopen(filepath, "r");
    if(source == NULL) {
        fprintf(stderr, "Couldn't open file %s", filepath);
    }

    Program* prog = init_program();
    parse(source, prog);

    for(size_t i = 0; i < prog->size; i++) {
        print_instruction(&prog->instructions[i]);
    }
}
