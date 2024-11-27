#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "parser.h"

#define ANSI_CLEAR "\033[2J\033[H"
#define ANSI_RESET "\033[0m"
#define ANSI_BLUE "\033[34m"
#define ANSI_BOLD_GREEN "\033[1;32m"

#define MEM_CAPACITY 30000
#define DELAY 200000

typedef struct {
    unsigned char* mem_tape;
    size_t tape_size;
    size_t mem_ptr;
    size_t width;
    size_t offset;
} Visualizer;

typedef enum {
    EvalErr_IOError,
    EvalErr_PtrBelowZero,
    EvalErr_PtrAboveLimit,
    Eval_OK,
} EvalErr;

void parse_and_visualize(const char* filepath);

#endif
