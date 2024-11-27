#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "parser.h"
#include "visualizer.h"

static char* eval_err_to_str(EvalErr err);

Visualizer* init_visualizer(size_t width) {
    size_t v_len = sizeof(Visualizer);
    Visualizer* v = malloc(v_len);
    memset(v, 0, v_len);

    v->tape_size = MEM_CAPACITY;
    v->mem_tape = malloc(v->tape_size);
    memset(v->mem_tape, 0, v->tape_size);
    v->mem_ptr = 0;

    v->width = width;

    return v;
}

void update_offset(Visualizer* v) {
    // adjusting the offset to keep pointer visible on the screen
    if(v->mem_ptr < v->offset) {
        v->offset = v->mem_ptr;
    } else if(v->mem_ptr >= v->offset + v->width) {
        v->offset = v->mem_ptr - v->width + 1;
    }
}

static void draw_visualizer(Visualizer* v, char* out_buf) {
    update_offset(v);

    printf(ANSI_CLEAR);

    // top border
    printf("┌");
    for(size_t i = 0; i < v->width; i++) {
        printf("───");
        if(i < v->width - 1)
            printf("┬");
    }
    printf("┐\n");

    // cells
    printf("│");
    // cell indices
    for(size_t i = 0; i < v->width && (i + v->offset) < v->tape_size; i++) {
        printf("%3zu", i + v->offset);
        if(i < v->width - 1)
            printf("│");
    }
    printf("│\n");

    // cell values --> '·' if it is empty
    // bold green makes the . jump up when cell is highlighted
    // great success
    printf("│");
    for(size_t i = 0; i < v->width && (i + v->offset) < v->tape_size; i++) {
        if(i + v->offset == v->mem_ptr) {
            printf(ANSI_BOLD_GREEN);
        }

        char c = v->mem_tape[i + v->offset];
        if(c >= 32 && c <= 126) {
            printf(" %c ", c);
        } else {
            printf(" · ");
        }

        printf(ANSI_RESET);
        if(i < v->width - 1)
            printf("│");
    }
    printf("│\n");

    // bottom border
    printf("└");
    for(size_t i = 0; i < v->width; i++) {
        printf("───");
        if(i < v->width - 1)
            printf("┴");
    }
    printf("┘\n");

    // pointer triangle
    size_t rel_pos = v->mem_ptr - v->offset;
    for(size_t i = 0; i < rel_pos; i++) {
        printf("    ");
    }
    printf(ANSI_BLUE "  ▲" ANSI_RESET "\n");

    printf("\nPointer: %zu  Value: %d  ASCII: ", v->mem_ptr, v->mem_tape[v->mem_ptr]);
    if(v->mem_tape[v->mem_ptr] >= 32 && v->mem_tape[v->mem_ptr] <= 126) {
        printf("'%c'", v->mem_tape[v->mem_ptr]);
    } else {
        printf("n/a");
    }

    // buffer contents
    printf("\nBuffer: %s", out_buf);
    fflush(stdout);
    printf("\n");
}

EvalErr eval(Program* prog) {
    size_t inst_ptr = 0;
    char out_buffer[1024];
    size_t out_idx = 0;

    Visualizer* v = init_visualizer(16);

    while(inst_ptr < prog->size) {
        Inst* curr_inst = &prog->instructions[inst_ptr];

        draw_visualizer(v, out_buffer);
        usleep(DELAY);

        switch(curr_inst->kind) {
        case INST_INCR_PTR:
            if(v->mem_ptr + curr_inst->times >= MEM_CAPACITY) {
                return EvalErr_PtrAboveLimit;
            }
            v->mem_ptr += curr_inst->times;
            inst_ptr++;
            break;

        case INST_DECR_PTR:
            if(curr_inst->times > v->mem_ptr) {
                return EvalErr_PtrBelowZero;
            }
            v->mem_ptr -= curr_inst->times;
            inst_ptr++;
            break;

        case INST_INCR_BYTE:
            v->mem_tape[v->mem_ptr] += curr_inst->times;
            inst_ptr++;
            break;

        case INST_DECR_BYTE:
            v->mem_tape[v->mem_ptr] -= curr_inst->times;
            inst_ptr++;
            break;

        case INST_WRITE_BYTE:
            for(size_t i = 0; i < curr_inst->times; i++) {
                out_buffer[out_idx++] = v->mem_tape[v->mem_ptr];
            }

            inst_ptr++;
            break;

        case INST_READ_BYTE:
            fflush(stdout);
            // probably might have to move to bottom of screen for input
            // also might not be a good idea
            printf("\033[%zu;0H", v->width + 10);

            for(size_t i = 0; i < curr_inst->times; i++) {
                int ch = fgetc(stdin);
                v->mem_tape[v->mem_ptr] = (ch == EOF) ? '\0' : (unsigned char)ch;
            }
            inst_ptr++;
            break;

        case INST_LOOP_START:
            if(v->mem_tape[v->mem_ptr] == 0) {
                inst_ptr = curr_inst->end_idx;
            } else {
                inst_ptr++;
            }
            break;

        case INST_LOOP_END:
            if(v->mem_tape[v->mem_ptr] != 0) {
                inst_ptr = curr_inst->start_idx;
            } else {
                inst_ptr++;
            }
            break;
        }
    }

    return Eval_OK;
}

void parse_and_visualize(const char* filepath) {
    FILE* source = fopen(filepath, "r");
    if(source == NULL) {
        LOG_FATAL("Couldn't open file %s", filepath);
    }

    Program* prog = init_program();

    ParseErr result = parse(source, prog);
    if(result != Parse_OK) {
        LOG_FATAL("%s", err_to_str(result));
    }

    EvalErr eval_res = eval(prog);
    if(eval_res != Eval_OK) {
        LOG_FATAL("%s\n", eval_err_to_str(eval_res));
    }
}

static char* eval_err_to_str(EvalErr err) {
    char* msg = NULL;

    switch(err) {
    case EvalErr_PtrBelowZero:
        msg = "Memory pointer reached below zero";
        break;
    case EvalErr_PtrAboveLimit:
        msg = "Memory pointer went above limit";
        break;
    case EvalErr_IOError:
        msg = "IO operation failed";
        break;
    case Eval_OK:
        break;
    }

    return msg;
}
