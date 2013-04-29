#ifndef SORT_H
#define SORT_H

typedef void (*sortfn_t)(int *, uint32_t);

void bubblesort( int *base, uint32_t size );
void inssort( int *base, uint32_t size );
void quicksort( int *base, uint32_t size );
void mergesort( int *base, uint32_t size );
void heapsort( int *base, uint32_t size );


int test_sorts(void);
int benchmark_sorts(void);
void test_cmdline_list(int argc, char *argv[]);

#endif
