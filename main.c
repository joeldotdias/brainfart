#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"
#include "visualizer.h"

int main(int argc, char** argv) {
    if(argc < 2) {
        fprintf(stderr, "Wrong usage");
        return 1;
    }

    const char* filepath = argv[1];

    if(argc >= 3 && strcmp(argv[2], "-v") == 0) {
        parse_and_visualize(filepath);
    } else {
        parse_and_compile(filepath);
    }

    return EXIT_SUCCESS;
}
