#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "sort.h"
#include "sortutils.h"

int main(int argc, char *argv[])
{
    int *list;
    int *list_sort;
    int *list_stdsort;
    uint32_t list_size;

    if ( argc <= 0 ) {
        exit(EXIT_FAILURE);
    } else if ( argc == 1 ) {
        // run tests defined in test.c
        runtests();
    } else {
        // sort list provided on command line
        list_size = argc - 1;

        list = malloc( list_size * sizeof(int) );
        list_sort = malloc( list_size * sizeof(int) );
        list_stdsort = malloc( list_size * sizeof(int) );
        if (!list || !list_sort || !list_stdsort) { 
            exit(EXIT_FAILURE);
        }

        for (uint32_t i = 0; i < list_size; i++) {
            list[i] = atoi(argv[i+1]);
        }
        memcpy(list_sort, list, list_size*sizeof(int));
        memcpy(list_stdsort, list, list_size*sizeof(int));

        sort_under_test(list_sort, list_size);
        stdsort(list_stdsort, list_size);

        dbgprintf("\n\n");
        dbgprintf("unsorted:        ");
        dbgprintl(list, list_size);
        dbgprintf("stdlib qsort:    ");
        dbgprintl(list_stdsort, list_size);
        dbgprintf("sort-under-test: ");
        dbgprintl(list_sort, list_size);

        //if ( memcmp(list_sort, list_stdsort, list_size*sizeof(int)) == 0 ) {
        if ( cmplist(list_sort, list_stdsort, list_size, &cmpint) == 0 ) {
            printf("sort OK\n");
        } else {
            printf("sort FAILED\n");
        }
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
