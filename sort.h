#ifndef SORT_H
#define SORT_H

#ifndef sort_under_test
#define sort_under_test bubblesort2
#endif

typedef void (*sortfn_t)(int *, uint32_t);

void bubblesort( int *base, uint32_t size );
void bubblesort2( int *base, uint32_t size );
void inssort( int *base, uint32_t size );
void inssort2( int *base, uint32_t size );
void inssort3( int *base, uint32_t size );
void quicksort( int *base, uint32_t size );
void quicksort2( int *base, uint32_t size );
void quicksort3( int *base, uint32_t size );
void mergesort( int *base, uint32_t size );
void heapsort( int *base, uint32_t size );


int test_sorts(void);
void test_cmdline_list(int argc, char *argv[]);

#endif
