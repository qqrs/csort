#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "sortutils.h"

#ifdef DEBUG
int sortutils_compare_count = 0;
int sortutils_copy_count = 0;
#endif

// compare two lists of same length
int cmplist(const void *a, const void *b, uint32_t len, uint32_t esize, 
            cmpfn_t cmp)
{
    int result;
    for (uint32_t i = 0; i < len; i++)
    {
        result = (*cmp)((a+i*esize), (b+i*esize));
        if (result != 0) {
            return result;
        }
    }

    return 0;
}

void stdsort( int *base, uint32_t len, uint32_t esize, cmpfn_t cmp )
{
    qsort(base, len, esize, cmp);
}

int cmpint(const void *a, const void *b)
{
#ifdef DEBUG
    sortutils_compare_count++;
#endif
    if ( *(int *)a < *(int *)b ) {
        return -1;
    } 
    if ( *(int *)a > *(int *)b ) {
        return 1;
    } 
    return 0;
}

int cmpint64(const void *a, const void *b)
{
#ifdef DEBUG
    sortutils_compare_count++;
#endif
    if ( *(int64_t *)a < *(int64_t *)b ) {
        return -1;
    } 
    if ( *(int64_t *)a > *(int64_t *)b ) {
        return 1;
    } 
    return 0;
}

int cmp10ints(const void *a, const void *b)
{
#ifdef DEBUG
    sortutils_compare_count++;
#endif
    for ( uint32_t i = 0; i < 10; i++ )
    {
        if ( *(int *)a < *(int *)b ) {
            return -1;
        } 
        if ( *(int *)a > *(int *)b ) {
            return 1;
        } 
        a++;
        b++;
    }
    return 0;
}

int cmpstr(const void *a, const void *b)
{
#ifdef DEBUG
    sortutils_compare_count++;
#endif
    return strcmp(*(char **)a, *(char **)b);
}

/*
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
*/

void swap(int *a, int *b, uint32_t esize)
{
    void *t;

#ifdef DEBUG
    sortutils_copy_count += 3;
#endif

    t = malloc(esize);
    if (!t) {
        exit(EXIT_FAILURE);
    }
    memcpy(t, a, esize);
    memcpy(a, b, esize);
    memcpy(b, t, esize);
    free(t);
}

/*void swapint(int *a, int *b)
{
    int t;

#ifdef DEBUG
    sortutils_copy_count++;
#endif

    t = *a;
    *a = *b;
    *b = t;
}
*/

void copy(int *dest, int *src, uint32_t esize)
{
#ifdef DEBUG
    sortutils_copy_count++;
#endif

    memcpy(dest, src, esize);
}


// print list
void printl( int *base, uint32_t len, uint32_t esize )
{
    uint32_t i;

    if (esize != sizeof(int)) {
        return;
    }

    for ( i = 0; i < len; i++ ) {
        printf("%d ", base[i]);
    }
    printf("\n");
}



