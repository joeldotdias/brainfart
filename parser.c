#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

const char INSTS[] = {'>', '<', '+', '-', '.', ',', '[', ']'};

static void push_inst(Program* prog, Inst inst);

Program* init_program() {
    size_t len = sizeof(Program);
    Program* prog = malloc(len);
    memset(prog, 0, len);
    prog->instructions = malloc(sizeof(Inst) * INITIAL_PROG_CAPACITY);
    prog->size = 0;
    prog->capacity = INITIAL_PROG_CAPACITY;

    return prog;
}

ParseErr parse(FILE* source, Program* prog) {
    int curr_ch;
    size_t loop_depth = 0;

    while((curr_ch = fgetc(source)) != EOF) {
        if(strchr(INSTS, curr_ch) == NULL) {
            continue;
        }

        if(curr_ch == ']') {
            if(loop_depth == 0) {
                annihilate_program(&prog);
                return ParseErr_UnbalancedBrackets;
            }
            loop_depth--;
        } else if(curr_ch == '[') {
            loop_depth++;
        }

        InstKind kind;
        switch(curr_ch) {
        case '>':
            kind = INST_INCR_PTR;
            break;
        case '<':
            kind = INST_DECR_PTR;
            break;
        case '+':
            kind = INST_INCR_BYTE;
            break;
        case '-':
            kind = INST_DECR_BYTE;
            break;
        case '.':
            kind = INST_WRITE_BYTE;
            break;
        case ',':
            kind = INST_READ_BYTE;
            break;
        case '[':
            kind = INST_LOOP_START;
            break;
        case ']':
            kind = INST_LOOP_END;
            break;
        default:
            continue;
        }

        // if the previous instruction is the same
        // we consider incr times on the previous instruction
        // instead of adding it to the program
        Inst curr_inst = {.kind = kind, .idx = prog->size, .times = 1};
        Inst* prev_inst = prog->size > 0 ? &prog->instructions[prog->size - 1] : NULL;

        if(prev_inst != NULL && prev_inst->kind == kind) {
            prev_inst->times++;
        } else {
            push_inst(prog, curr_inst);
        }
    }

    if(loop_depth > 0) {
        annihilate_program(&prog);
        return ParseErr_UnbalancedBrackets;
    }

    // TODO: change these stupid nested loops
    for(size_t i = 0; i < prog->size; i++) {
        Inst* curr_inst = &prog->instructions[i];
        if(curr_inst->kind == INST_LOOP_START) {
            size_t loop_starts = curr_inst->times;
            for(size_t j = i + 1; j < prog->size; j++) {
                Inst* scan_inst = &prog->instructions[j];
                if(scan_inst->kind == INST_LOOP_END) {
                    size_t loop_ends = scan_inst->times;
                    if(loop_starts <= loop_ends) {
                        loop_starts = 0;
                    } else {
                        loop_starts -= loop_ends;
                    }
                    if(loop_starts == 0) {
                        curr_inst->end_idx = j + 1;
                        scan_inst->start_idx = i + 1;
                        if(i == j - 1) {
                            annihilate_program(&prog);
                            return ParseErr_InfiniteLoop;
                        }
                        break;
                    }
                } else if(scan_inst->kind == INST_LOOP_START) {
                    loop_starts += scan_inst->times;
                }
            }
        }
    }

    return Parse_OK;
}

static void push_inst(Program* prog, Inst inst) {
    if(prog->size >= prog->capacity) {
        prog->capacity *= 2;
        prog->instructions = realloc(prog->instructions, sizeof(Inst) * prog->capacity);
    }

    prog->instructions[prog->size++] = inst;
}

void annihilate_program(Program** prog) {
    free((*prog)->instructions);
    free(*prog);
}

void print_instruction(const Inst* inst) {
    char* kind_str;
    switch(inst->kind) {
    case INST_INCR_PTR:
        kind_str = "IncrPtr";
        break;
    case INST_DECR_PTR:
        kind_str = "DecrPtr";
        break;
    case INST_INCR_BYTE:
        kind_str = "IncrByte";
        break;
    case INST_DECR_BYTE:
        kind_str = "DecrByte";
        break;
    case INST_WRITE_BYTE:
        kind_str = "WriteByte";
        break;
    case INST_READ_BYTE:
        kind_str = "ReadByte";
        break;
    case INST_LOOP_START:
        kind_str = "LoopStart";
        break;
    case INST_LOOP_END:
        kind_str = "LoopEnd";
        break;
    }

    printf("{Type: %s, Times: %zu", kind_str, inst->times);

    // jump targets for loops
    if(inst->kind == INST_LOOP_START) {
        printf(", JumpEnd: %zu", inst->end_idx);
    } else if(inst->kind == INST_LOOP_END) {
        printf(", JumpStart: %zu", inst->start_idx);
    }
    printf("}\n");
}

char* err_to_str(ParseErr err) {
    switch(err) {
    case ParseErr_UnbalancedBrackets:
        return "ERROR: unbalanced brackets in bf source";
        break;
    case ParseErr_InfiniteLoop:
        return "ERROR: potential infinite loop in bf source";
        break;
    default:
        return NULL;
    }
}
