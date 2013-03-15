#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/resource.h>

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
    SORT_DEF( quicksort         ),
    SORT_DEF( quicksort2        ),
    SORT_DEF( mergesort         ),
    SORT_DEF( heapsort          ),
    SORT_DEF( inssort           ),
    SORT_DEF( inssort2          ),
    SORT_DEF( inssort3          ),
    SORT_DEF( bubblesort        ),
    SORT_DEF( bubblesort2       ),
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
//#define MAX_LIST_SIZE   64*sizeof(int)
//static uint8_t buf_sort[MAX_LIST_SIZE];
//static uint8_t buf_stdsort[MAX_LIST_SIZE];

// run test cases for a single sort function
int test_sort(sortfn_t sortfn)
{
    void *list_sort;
    void *list_stdsort;
    size_t list_sort_size;
    size_t list_stdsort_size;
    uint32_t list_size;
    struct testitem_s *test;

    int failures;

    list_sort = NULL;
    list_stdsort = NULL;
    list_sort_size = 0;
    list_stdsort_size = 0;

    failures = 0;

    for (test = test_cases; test->list != NULL; test++)
    {
        list_size = test->len * test->esize;
        //assert(list_size <= MAX_LIST_SIZE);

        if (list_size > list_sort_size) {
            list_sort = realloc(list_sort, list_size);
            list_sort_size = list_size;
        }
        if (list_size > list_stdsort_size) {
            list_stdsort = realloc(list_stdsort, list_size);
            list_stdsort_size = list_size;
        }
        if ( !list_sort || !list_stdsort ) { 
            free(list_sort);
            free(list_stdsort);
            exit(EXIT_FAILURE);
        }

        memcpy( list_sort, test->list, list_size );
        memcpy( list_stdsort, test->list, list_size );

        dbgprintl(list_sort, test->len );
        (*sortfn)(list_sort, test->len );
        dbgprintl(list_sort, test->len );

        stdsort(list_stdsort, test->len );

        //if ( memcmp(list_sort, list_stdsort, list_size) == 0 ) 
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

    free(list_sort);
    free(list_stdsort);
    return failures;
}

// run tests for all sort functions
int test_sorts( void )
{
    struct sortdef_s *s;

    for ( s = sort_definitions; s->sortfn != NULL; s++ )
    {
        printf("%s: ", s->name);
        test_sort(s->sortfn);
    }

    return 0;
}

// =============================================================================

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

// run benchmark for all sort functions
#define MAX_TEST_DATA 1000000
#define TEST_REPEAT 10
int benchmark_sorts( void )
{
    uint32_t i;
    struct sortdef_s *s;
    uint32_t len, esize;
    int *list_raw, *list_sort, *list_stdsort;
    double start_time, end_time; 
    double min_time, sort_time, stdsort_time;

    // allocate a buffer for test data
    len = MAX_TEST_DATA;
    esize = sizeof(int);
    list_raw = malloc(len*esize);
    list_sort = malloc(len*esize);
    list_stdsort = malloc(len*esize);
    if (!list_raw || !list_sort || !list_stdsort) {
        free(list_raw);
        free(list_sort);
        free(list_stdsort);
        return EXIT_FAILURE;
    }

    // generate test data
    srand(398149);
    for (uint32_t i = 0; i < len; i++)
    {
        list_raw[i] = rand();
    }

    // sort using stdlib qsort
    printf("%16.16s: ", "stdlib qsort");
    memcpy(list_stdsort, list_raw, len*esize);
    start_time = get_time();
    stdsort(list_stdsort, len);
    end_time = get_time();
    stdsort_time = 1000.0*(end_time - start_time);
    printf("%6.2f ms\n", stdsort_time);

    for ( s = sort_definitions; s->sortfn != NULL; s++ )
    {
        printf("%16.16s: ", s->name);

        for ( i = 0; i < TEST_REPEAT; i++ )
        {
            memcpy(list_sort, list_raw, len*esize);

            start_time = get_time();
            (*s->sortfn)(list_sort, len);
            end_time = get_time();

            sort_time = 1000.0*(end_time - start_time);
            if ( cmplist(list_sort, list_stdsort, len, &cmpint) == 0 ) {
                if (i == 0 || sort_time < min_time) {
                    min_time = sort_time;
                }
            } else {
                break;
            }
        }

        if (i != TEST_REPEAT) {
            printf("FAIL\n");
        } else {
            printf("%6.2f ms  %.2f\n", min_time, min_time/stdsort_time);
        }


    }

    return 0;
}

// =============================================================================

void test_cmdline_list(int argc, char *argv[])
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
        free(list);
        free(list_sort);
        free(list_stdsort);
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

    free(list);
    free(list_sort);
    free(list_stdsort);
}
