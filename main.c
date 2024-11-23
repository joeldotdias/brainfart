#include <stdio.h>
#include <stdlib.h>

#include "compiler.h"

int main(int argc, char** argv) {
    if(argc < 2) {
        fprintf(stderr, "Wrong usage");
        return 1;
    }

    const char* filepath = argv[1];
    parse_and_compile(filepath);

    return EXIT_SUCCESS;
}
