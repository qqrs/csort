#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

void swap(int *a, int *b)
{
    int t;

    t = *a;
    *a = *b;
    *b = t;
}

void print_data( int *base, uint32_t size )
{
    uint32_t i;

    for ( i = 0; i < size; i++ ) {
        printf("%d ", base[i]);
    }
    printf("\n");
}



