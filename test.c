#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "sort.h"
#include "sortutils.h"

// =============================================================================

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
    SORT_DEF( quicksort2        ),
    { NULL, NULL },
};

// =============================================================================

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
static int test_rand    [] = {7,9,3,2,6,7,1,4,9,4,1,2,7,2,8,4,
                              6,6,9,3,5,2,5,3,4,8,2,8,3,9,2,7,
                              8,3,3,7,7,2,8,3,4,9,3,7,5,4,4,6,
                              5,9,5,1,3,1,1,4,7,2,1,8,3,1,5,2};

#define TEST_ITEM(x)  { x, #x, (sizeof(x)/sizeof(x[0])), sizeof(x[0]), &cmpint }
static struct testitem_s test_cases[] = {
    TEST_ITEM( test_even     ),
    TEST_ITEM( test_odd      ),
    TEST_ITEM( test_pow2     ),
    TEST_ITEM( test_sorted   ),
    TEST_ITEM( test_dup      ),
    TEST_ITEM( test_ilv      ),
    TEST_ITEM( test_rand     ),
    {NULL, NULL, 0, 0, NULL}
};

// =============================================================================

// TODO: use stack buffers rather than allocating on heap for consistent timing?
//       or build timing into the test framework?
#define MAX_LIST_SIZE   64*sizeof(int)
static uint8_t buf_sort[MAX_LIST_SIZE];
static uint8_t buf_stdsort[MAX_LIST_SIZE];

// run test cases for a single sort function
int runtests(sortfn_t sortfn)
{
    void *list_sort;
    void *list_stdsort;
    uint32_t list_size;
    struct testitem_s *test;

    int failures;

    list_sort = buf_sort;
    list_stdsort = buf_stdsort;

    failures = 0;
    for (test = test_cases; test->list != NULL; test++)
    {
        list_size = test->len * test->esize;
        assert(list_size <= MAX_LIST_SIZE);

        memcpy( list_sort, test->list, list_size );
        memcpy( list_stdsort, test->list, list_size );

        dbgprintl(list_sort, test->len );
        (*sortfn)(list_sort, test->len );
        dbgprintl(list_sort, test->len );

        stdsort(list_stdsort, test->len );

        //if ( memcmp(list_sort, list_stdsort, list_size) == 0 ) {
        if ( cmplist(list_sort, list_stdsort, test->len, test->cmp) == 0 ) {
            // printf("OK:   ");
            // printl(test->list, test->len);
        } else {
            failures++;
            if (failures == 1) {
                printf("\n");
            }
            printf("FAIL: ");
            printl(test->list, test->len);
            printf("   >: ");
            printl(list_sort, test->len);
        }
    }

    if ( failures == 0 ) {
        printf("OK\n");
    }
    return failures;
}

// run tests for all sort functions
int test_sorts( void )
{
    struct sortdef_s *s;

    for ( s = sort_definitions; s->sortfn != NULL; s++ )
    {
        printf("%s: ", s->name);
        runtests(s->sortfn);
    }

    return 0;
}

// =============================================================================

//TODO: free heap memory
void sort_cmdline_list(int argc, char *argv[])
{
    int *list;
    int *list_sort;
    int *list_stdsort;
    uint32_t list_size;
    struct sortdef_s *s;

    for ( s = sort_definitions; s->sortfn != NULL; s++ )
    {
        if ( strcmp(s->name, argv[1]) == 0 ) {
            break;
        }
    }
    if ( s->sortfn == NULL ) {
        printf("sort function not found: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    list_size = argc - 2;

    list = malloc( list_size * sizeof(int) );
    list_sort = malloc( list_size * sizeof(int) );
    list_stdsort = malloc( list_size * sizeof(int) );
    if (!list || !list_sort || !list_stdsort) { 
        exit(EXIT_FAILURE);
    }

    for (uint32_t i = 0; i < list_size; i++) {
        list[i] = atoi(argv[i+2]);
    }
    memcpy(list_sort, list, list_size*sizeof(int));
    memcpy(list_stdsort, list, list_size*sizeof(int));

    //sort_under_test(list_sort, list_size);
    (*s->sortfn)(list_sort, list_size);
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
