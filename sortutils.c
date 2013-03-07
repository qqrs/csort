#include <stdio.h>
#include <stdlib.h>

int compare(const int *a, const int *b)
{
    //compare_count++;

    if ( *a < *b ) {
        return -1;
    } 
    if ( *a > *b ) {
        return 1;
    } 
    return 0;
}

int swap(int *a, int *b)
{
    int t;

    t = *a;
    *a = *b;
    *b = t;
}

void print_data( int *base, size_t size )
{
    int i;

    for ( i = 0; i < size; i++ ) {
        printf("%d ", base[i]);
    }
    printf("\n");
}



