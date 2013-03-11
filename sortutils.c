#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "sortutils.h"

//static int compare_count = 0;

// compare two lists of same size
int cmplist(const int *a, const int *b, size_t size,
                int (*cmp)(const void*,const void*) )
{
    int result;
    for (uint32_t i = 0; i < size; i++)
    {
        result = (*cmp)(&a[i], &b[i]);
        if (result != 0) {
            return result;
        }
    }

    return 0;
}

void stdsort( int *base, uint32_t size )
{
    qsort(base, size, sizeof(int), cmpint);
}

int cmpint(const void *a, const void *b)
{
    if ( *(int *)a < *(int *)b ) {
        return -1;
    } 
    if ( *(int *)a > *(int *)b ) {
        return 1;
    } 
    return 0;
}

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

// print list
void printl( int *base, uint32_t size )
{
    uint32_t i;

    for ( i = 0; i < size; i++ ) {
        printf("%d ", base[i]);
    }
    printf("\n");
}



