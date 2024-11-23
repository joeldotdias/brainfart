#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

// more stupidity
const char* ASM_START = "_asm/x86_64_start.s";
const char* ASM_END = "_asm/x86_64_end.s";

// helpers
static char* read_file(const char* path);
static char* extract_filename(const char* filepath);

void write_inst_asm(FILE* out_file, const Inst* inst) {
    switch(inst->kind) {
    case INST_INCR_PTR:
        EMIT("\n\taddq $%zu, %%r12", inst->times);
        break;
    case INST_DECR_PTR:
        EMIT("\n\tsubq $%zu, %%r12", inst->times);
        break;
    case INST_INCR_BYTE:
        EMIT("\n\taddb $%zu, (%%r12)", inst->times);
        break;
    case INST_DECR_BYTE:
        EMIT("\n\tsubb $%zu, (%%r12)", inst->times);
        break;
    case INST_WRITE_BYTE:
        for(size_t i = 0; i < inst->times; i++) {
            EMIT("\n\tmovq $SYS_WRITE, %%rax\n"
                 "\tmovq $STDOUT, %%rdi\n"
                 "\tmovq %%r12, %%rsi\n"
                 "\tmov $1, %%rdx\n"
                 "\tsyscall\n");
        }
        break;
    case INST_READ_BYTE:
        for(size_t i = 0; i < inst->times; i++) {
            EMIT("\n\tmovq $SYS_READ, %%rax\n"
                 "\tmovq $STDIN, %%rdi\n"
                 "\tmovq %%r12, %%rsi\n"
                 "\tmov $1, %%rdx\n"
                 "\tsyscall\n");
        }
        break;
    case INST_LOOP_START:
        EMIT("\n\tcmpb $0, (%%r12)\n"
             "\tje LOOP_END_%zu\n"
             "\nLOOP_START_%zu:\n",
             inst->end_idx - 1, inst->idx);
        break;
    case INST_LOOP_END:
        EMIT("\n\tcmpb $0, (%%r12)\n"
             "\tjne LOOP_START_%zu\n"
             "\nLOOP_END_%zu:\n",
             inst->end_idx - 1, inst->idx);
        break;
    }
}

void parse_and_compile(const char* filepath) {
    FILE* source = fopen(filepath, "r");
    if(source == NULL) {
        LOG_FATAL("Couldn't open file %s", filepath);
    }

    Program* prog = init_program();

    ParseErr result = parse(source, prog);
    if(result != Parse_OK) {
        LOG_FATAL("%s", err_to_str(result));
    }

    char out_filepath[256];
    char* filename = extract_filename(filepath);
    strcpy(out_filepath, "./");
    strcat(out_filepath, filename);
    strcat(out_filepath, ".s");
    free(filename);

    FILE* out_file = fopen(out_filepath, "w");
    if(!out_file) {
        LOG_FATAL("Couldn't open output file\n");
    }

    char* asm_start = read_file(ASM_START);
    char* asm_end = read_file(ASM_END);

    EMIT("%s", asm_start);
    for(size_t i = 0; i < prog->size; i++) {
        write_inst_asm(out_file, &prog->instructions[i]);
    }

    EMIT("%s", asm_end);

    free(asm_start);
    free(asm_end);
    fclose(out_file);
};

static char* read_file(const char* path) {
    FILE* file = fopen(path, "r");
    if(!file) {
        LOG_FATAL("Couldn't open %s'\n", path);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(size + 1);
    size_t bytes_read = fread(buffer, 1, size, file);
    buffer[bytes_read] = '\0';

    fclose(file);
    return buffer;
}

static char* extract_filename(const char* filepath) {
    if(!filepath) {
        return NULL;
    }

    const char* filename_start = filepath;
    const char* last_slash = strrchr(filepath, '/');
    const char* last_backslash = strrchr(filepath, '\\');

    if(last_slash && (!last_backslash || last_slash > last_backslash)) {
        filename_start = last_slash + 1;
    } else if(last_backslash) {
        filename_start = last_backslash + 1;
    }

    const char* dot = strrchr(filename_start, '.');

    size_t length;
    if(dot) {
        length = dot - filename_start;
    } else {
        length = strlen(filename_start);
    }

    char* result = (char*)malloc(length + 1);
    if(!result)
        return NULL;

    strncpy(result, filename_start, length);
    result[length] = '\0';

    return result;
}
