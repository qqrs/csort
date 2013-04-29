#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "sort.h"
#include "sortutils.h"

int main(int argc, char *argv[])
{
    if ( argc <= 0 ) {
        exit(EXIT_FAILURE);
    } else if ( argc == 1 ) {
        // run tests defined in test.c
        test_sorts();
    } else if ( argc == 2 ) {
        if ( strcmp(argv[1], "benchmark") != 0 ) {
            exit(EXIT_FAILURE);
        }
        benchmark_sorts();
    } else {
        // csort <sort_function> <list...>
        test_cmdline_list(argc, argv);
    }

    exit(EXIT_SUCCESS);
}

