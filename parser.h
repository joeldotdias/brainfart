#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <stdio.h>

#define LOG_FATAL(fmt, ...) (fprintf(stderr, fmt "\n", ##__VA_ARGS__), exit(EXIT_FAILURE))

#define INITIAL_PROG_CAPACITY 1024
#define MAX_PROG_LEN 4096

typedef enum {
    INST_INCR_PTR,
    INST_DECR_PTR,
    INST_INCR_BYTE,
    INST_DECR_BYTE,
    INST_WRITE_BYTE,
    INST_READ_BYTE,
    INST_LOOP_START,
    INST_LOOP_END,
} InstKind;

typedef struct {
    size_t idx;
    size_t times;
    InstKind kind;

    // for the loop start and end instruction kinds
    union {
        // used along with loop start
        // represents the index of inst after matching loop end
        size_t end_idx;

        // used along with loop end
        // represents the index of inst after matching loop start
        size_t start_idx;
    };
} Inst;

typedef enum {
    ParseErr_UnbalancedBrackets,
    ParseErr_InfiniteLoop,
    // if everything works. probably not a good way to do this
    Parse_OK,
} ParseErr;

typedef struct {
    Inst* instructions;
    size_t size;
    size_t capacity;
} Program;

Program* init_program();
ParseErr parse(FILE* source, Program* prog);
void annihilate_program(Program** prog);
void print_instruction(const Inst* inst);
char* err_to_str(ParseErr);

#endif
