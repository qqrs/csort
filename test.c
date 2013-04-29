#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>

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
    /*SORT_DEF( quicksort         ),*/
    /*SORT_DEF( mergesort         ),*/
    /*SORT_DEF( heapsort          ),*/
    /*SORT_DEF( inssort           ),*/
    SORT_DEF( bubblesort        ),
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

static int64_t test_int64 [] = {6,5,4,3,2,1};
static char *test_str [] = {"the", "quick", "brown", "fox", "jumped"};

#define TEST_ITEM_INT(x)  { x, #x, (sizeof(x)/sizeof(x[0])), sizeof(x[0]), &cmpint }
#define TEST_ITEM(x,cmp)  { x, #x, (sizeof(x)/sizeof(x[0])), sizeof(x[0]), (cmp) }
static struct testitem_s test_cases[] = {
    TEST_ITEM_INT( test_even     ),
    TEST_ITEM_INT( test_odd      ),
    TEST_ITEM_INT( test_pow2     ),
    TEST_ITEM_INT( test_sorted   ),
    TEST_ITEM_INT( test_dup      ),
    TEST_ITEM_INT( test_ilv      ),
    TEST_ITEM_INT( test_rand     ),
    TEST_ITEM( test_int64, &cmpint64 ),
    TEST_ITEM( test_str, &cmpstr ),
    {NULL, NULL, 0, 0, NULL}
};

// =============================================================================

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

        dbgprintl(list_sort, test->len, test->esize);
        (*sortfn)(list_sort, test->len, test->esize, test->cmp);
        dbgprintl(list_sort, test->len, test->esize);

        stdsort(list_stdsort, test->len, test->esize, test->cmp);

        if ( cmplist(list_sort, list_stdsort, test->len, test->esize, 
                                                        test->cmp) != 0 ) {
            failures++;
            if (failures == 1) {
                printf("\n");
            }
            printf("FAIL: ");
            printl(test->list, test->len, test->esize);
            printf("   >: ");
            printl(list_sort, test->len, test->esize);
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


// run benchmark for all sort functions
int benchmark_sorts( uint32_t len, uint32_t esize, uint32_t num_repeat, 
                    cmpfn_t cmp )
{
    uint32_t i;
    size_t size;
    uint32_t buf_len;
    struct sortdef_s *s;
    void *list_raw, *list_sort, *list_stdsort;
    struct timespec start_time, end_time; 
    double min_time, sort_time, stdsort_time;

    // allocate a buffer for test data, multiple of int size
    size = len * esize;
    size += size % sizeof(int);
    buf_len = size / sizeof(int);

    list_raw = malloc(size);
    list_sort = malloc(size);
    list_stdsort = malloc(size);
    if (!list_raw || !list_sort || !list_stdsort) {
        free(list_raw);
        free(list_sort);
        free(list_stdsort);
        return EXIT_FAILURE;
    }

    // generate test data
    srand(398149);
    for (uint32_t i = 0; i < buf_len; i++)
    {
        ((int *)list_raw)[i] = rand();
    }

    // sort using stdlib qsort
    printf("%16.16s: ", "stdlib qsort");
    memcpy(list_stdsort, list_raw, len*esize);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
    stdsort(list_stdsort, len, esize, cmp);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
    stdsort_time = (((double)end_time.tv_sec - start_time.tv_sec)*1e3 \
                    + ((double)end_time.tv_nsec - start_time.tv_nsec)/1e6);
    printf("%6.2f ms\n", stdsort_time);

    // for each defined sort algorithm, sort and show the best time of several
    // repetitions using the same data set
    for ( s = sort_definitions; s->sortfn != NULL; s++ )
    {
        printf("%16.16s: ", s->name);

        for ( i = 0; i < num_repeat; i++ )
        {
            memcpy(list_sort, list_raw, len*esize);

            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
            (*s->sortfn)(list_sort, len, esize, cmp);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);

            sort_time = (((double)end_time.tv_sec - start_time.tv_sec)*1e3 \
                    + ((double)end_time.tv_nsec - start_time.tv_nsec)/1e6);
            if ( cmplist(list_sort, list_stdsort, len, esize, cmp) == 0 ) {
                if (i == 0 || sort_time < min_time) {
                    min_time = sort_time;
                }
            } else {
                break;
            }
        }

        if (i != num_repeat) {
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

    (*s->sortfn)(list_sort, list_size, sizeof(int), &cmpint);
    stdsort(list_stdsort, list_size, sizeof(int), &cmpint);

    dbgprintf("\n\n");
    dbgprintf("unsorted:        ");
    dbgprintl(list, list_size, sizeof(int));
    dbgprintf("stdlib qsort:    ");
    dbgprintl(list_stdsort, list_size, sizeof(int));
    dbgprintf("sort-under-test: ");
    dbgprintl(list_sort, list_size, sizeof(int));

    if (cmplist(list_sort, list_stdsort, list_size, 
                sizeof(int), &cmpint) == 0 ) {
        printf("sort OK\n");
    } else {
        printf("sort FAILED\n");
    }

    free(list);
    free(list_sort);
    free(list_stdsort);
}
