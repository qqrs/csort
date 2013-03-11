#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "sort.h"
#include "sortutils.h"

// definition for a test case
struct testitem_s {
    void *list;         // list to sort
    char *name;         // name of test case
    uint32_t len;       // number of elements in list
    size_t esize;       // size in bytes of each element in list
    int (*cmp)(const void *,const void *);    // comparison function
};

static int test_even    [] = {6,5,4,3,2,1};
static int test_odd     [] = {7,6,5,4,3,2,1};
static int test_pow2    [] = {8,7,6,5,4,3,2,1};
static int test_sorted  [] = {1,2,3,4,5};
static int test_dup     [] = {2,2,2,2,2};
static int test_ilv     [] = {1,5,2,4,3};

#define TEST_ITEM(x)  { x, #x, (sizeof(x)/sizeof(x[0])), sizeof(x[0]), &cmpint }
static struct testitem_s test_cases[] = {
    TEST_ITEM( test_even     ),
    TEST_ITEM( test_odd      ),
    TEST_ITEM( test_pow2     ),
    TEST_ITEM( test_sorted   ),
    TEST_ITEM( test_dup      ),
    TEST_ITEM( test_ilv      ),
    {NULL, NULL, 0, 0, NULL}
};

// definition for a sort function
struct sortdef_s {
    sortfn_t sortfn;
    char *name;
};

#define SORT_DEF(x) { &(x), #x }
static struct sortdef_s sort_definitions[] = {
    SORT_DEF( bubblesort        ),
    SORT_DEF( bubblesort2       ),
    SORT_DEF( inssort           ),
    SORT_DEF( inssort2          ),
    SORT_DEF( inssort3          ),
    SORT_DEF( quicksort         ),
    { NULL, NULL },
};


// use static buffers rather than allocating on heap for consistent timing
#define MAX_LIST_SIZE   16*sizeof(int)
static uint8_t buf_sort[MAX_LIST_SIZE];
static uint8_t buf_stdsort[MAX_LIST_SIZE];

// run test cases for a single sort function
int runtests(sortfn_t sortfn)
{
    void *list_sort;
    void *list_stdsort;
    uint32_t list_size;
    struct testitem_s *test;

    list_sort = buf_sort;
    list_stdsort = buf_stdsort;

    //test = &test_cases[0];
    for (test = test_cases; test->list != NULL; test++)
    {
        list_size = test->len * test->esize;
        assert(list_size <= MAX_LIST_SIZE);

        /*
        list_sort = malloc(list_size);
        list_stdsort = malloc(list_size);
        if ( !list_sort || !list_stdsort ) { 
            exit(EXIT_FAILURE);
        }
        */

        memcpy( list_sort, test->list, list_size );
        memcpy( list_stdsort, test->list, list_size );

        dbgprintl(list_sort, test->len );
        (*sortfn)(list_sort, test->len );
        dbgprintl(list_sort, test->len );

        stdsort(list_stdsort, test->len );

        /*
        dbgprintf("\n\n");
        dbgprintf("unsorted:        ");
        dbgprintl(test->list, test->len );
        dbgprintf("stdlib qsort:    ");
        dbgprintl(list_stdsort, test->len );
        dbgprintf("sort-under-test: ");
        dbgprintl(list_sort, test->len );
        */

        //if ( memcmp(list_sort, list_stdsort, list_size) == 0 ) {
        if ( cmplist(list_sort, list_stdsort, test->len, test->cmp) == 0 ) {
            printf("OK:   ");
            printl(test->list, test->len);
        } else {
            printf("FAIL: ");
            printl(test->list, test->len);
            printf("   >: ");
            printl(list_sort, test->len);
        }
    }

    return 0;
}

// run tests for all sort functions
int test_sorts( void )
{
    struct sortdef_s *s;

    for ( s = sort_definitions; s->sortfn; s++ )
    {
        printf("\n%s:\n", s->name);
        runtests(s->sortfn);
    }

    return 0;
}
