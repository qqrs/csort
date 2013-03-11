#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "sort.h"
#include "sortutils.h"

int main(int argc, char *argv[])
{
    int *list;
    uint32_t list_size;

    if ( argc <= 0 ) {
        exit(EXIT_FAILURE);
    } else if ( argc == 1 ) {
        // run tests
    } else {
        list_size = argc - 1;
        list = malloc( list_size * sizeof(int) );
        if (!list) { 
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < list_size; i++) {
            list[i] = atoi(argv[i+1]);
        }
        dbgprintl(list, list_size);
        stdsort(list, list_size);
        dbgprintl(list, list_size);
    }

    exit(EXIT_SUCCESS);
}

    /*
{
    int data[] = {1,7,2,4,6,7};
    //int data[] = {9,8,7,6,5,4,3,2,1};
    //int data[] = {7,5,4,6,3,2,1};
    int data_len = sizeof(data)/sizeof(data[0]);
    //quicksort(data, data_len);
    //swap(&data[0], &data[1]);
    print_data(data, data_len);
    printf("===\n\n");

    quicksort(data, data_len);

    printf("===\n\n");
    print_data(data, data_len);

    printf("\ncompare count: %d\n", compare_count);

    return EXIT_SUCCESS;
}
    */
