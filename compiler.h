#ifndef COMPILER_H
#define COMPILER_H

#define EMIT(fmt, ...) fprintf(out_file, fmt, ##__VA_ARGS__)

#define LOG_FATAL(fmt, ...) (fprintf(stderr, fmt "\n", ##__VA_ARGS__), exit(EXIT_FAILURE))

void parse_and_compile(const char* filepath);

#endif
