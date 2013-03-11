#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "sort.h"
#include "sortutils.h"

struct testitem_s {
    char *name;         // name of test case
    void *list;         // list to sort
    uint32_t len;       // number of elements in list
    size_t esize;       // size in bytes of each element in list
    int (*cmp)(const void*,const void*);    // comparison function
};


int test1[] = {9,8,7,6,5,4,3,2,1};
int test2[] = {9,8,7,6,5,4,3,2,1};
int test3[] = {9,8,7,6,5,4,3,2,1};
int test4[] = {9,8,7,6,5,4,3,2,1};

#define TESTITEM(x)  { #x, x, (sizeof(x)/sizeof(x[0])), sizeof(x[0]), &cmpint }
struct testitem_s test_cases[] = {
    TESTITEM(test1),
    TESTITEM(test2),
    TESTITEM(test3),
    TESTITEM(test4)
};



int runtests(void)
{
    int *list;
    int *list_sort;
    int *list_stdsort;
    uint32_t list_size;

    struct testitem_s *test;

    test = &test_cases[0];

    list = test->list;
    list_size = test->len * test->esize;

    list_sort = malloc(list_size);
    list_stdsort = malloc(list_size);
    if ( !list_sort || !list_stdsort ) { 
        exit(EXIT_FAILURE);
    }

    memcpy( list_sort, list, list_size );
    memcpy( list_stdsort, list, list_size );

    sort_under_test(list_sort, test->len );
    stdsort(list_stdsort, test->len );

    dbgprintf("\n\n");
    dbgprintf("unsorted:        ");
    dbgprintl(list, test->len );
    dbgprintf("stdlib qsort:    ");
    dbgprintl(list_stdsort, test->len );
    dbgprintf("sort-under-test: ");
    dbgprintl(list_sort, test->len );

    //if ( memcmp(list_sort, list_stdsort, list_size) == 0 ) {
    if ( cmplist(list_sort, list_stdsort, test->len, test->cmp) == 0 ) {
        printf("sort OK\n");
    } else {
        printf("sort FAILED\n");
    }

    return 0;
}

