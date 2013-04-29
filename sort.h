#ifndef SORT_H
#define SORT_H

typedef int (*cmpfn_t)(const void *, const void *);
typedef void (*sortfn_t)(void *, uint32_t, uint32_t, cmpfn_t);

void bubblesort( void *base, uint32_t len, uint32_t esize, cmpfn_t cmp );
void inssort( void *base, uint32_t len, uint32_t esize, cmpfn_t cmp );
void quicksort( void *base, uint32_t len, uint32_t esize, cmpfn_t cmp );
void mergesort( void *base, uint32_t len, uint32_t esize, cmpfn_t cmp );
void heapsort( void *base, uint32_t len, uint32_t esize, cmpfn_t cmp );


int test_sorts(void);
int benchmark_sorts( uint32_t len, uint32_t esize, uint32_t num_repeat, \
                    cmpfn_t cmp );
void test_cmdline_list(int argc, char *argv[]);

#endif
