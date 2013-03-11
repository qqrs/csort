#ifndef SORT_H
#define SORT_H

#ifndef sort_under_test
#define sort_under_test quicksort
#endif

void quicksort( int *base, size_t size );
void inssort( int *base, size_t size );
void inssort2( int *base, size_t size );
void inssort3( int *base, size_t size );
void bubblesort( int *base, size_t size );
void bubblesort2( int *base, size_t size );

#endif
