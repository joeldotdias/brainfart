#ifndef COMPILER_H
#define COMPILER_H

#include "parser.h"

#define EMIT(fmt, ...) fprintf(out_file, fmt, ##__VA_ARGS__)

// more stupidity
#define ASM_START "_asm/x86_64_start.s"
#define ASM_END "_asm/x86_64_end.s"

void parse_and_compile(const char* filepath);

#endif
