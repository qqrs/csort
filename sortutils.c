#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "sortutils.h"

#ifdef DEBUG
int sortutils_compare_count = 0;
int sortutils_copy_count = 0;
#endif

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

// TODO: esize, cmp
void stdsort( int *base, uint32_t size )
{
    qsort(base, size, sizeof(int), cmpint);
}

// TODO: compare_count
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
#ifdef DEBUG
    sortutils_compare_count++;
#endif

    if ( *a < *b ) {
        return -1;
    } 
    if ( *a > *b ) {
        return 1;
    } 
    return 0;
}

// TODO: esize, cmp
void swap(int *a, int *b)
{
    int t;

#ifdef DEBUG
    sortutils_copy_count++;
#endif

    t = *a;
    *a = *b;
    *b = t;
}

// TODO: copy

// print list
// TODO: return if not int type?
void printl( int *base, uint32_t size )
{
    uint32_t i;

    for ( i = 0; i < size; i++ ) {
        printf("%d ", base[i]);
    }
    printf("\n");
}



