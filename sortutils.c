#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "sortutils.h"

#ifdef SORT_STATS
static int sortutils_compare_count = 0;
static int sortutils_copy_count = 0;
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
#ifdef SORT_STATS
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
#ifdef SORT_STATS
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
#ifdef SORT_STATS
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
#ifdef SORT_STATS
    sortutils_compare_count++;
#endif
    return strcmp(*(char **)a, *(char **)b);
}

void s_memswap(void *a, void *b, void *temp, uint32_t esize)
{
#ifdef SORT_STATS
    sortutils_copy_count += 3;
#endif

    memcpy(temp, a, esize);
    memcpy(a, b, esize);
    memcpy(b, temp, esize);
}

void s_memcpy(void *dest, void *src, uint32_t esize)
{
#ifdef SORT_STATS
    sortutils_copy_count++;
#endif

    memcpy(dest, src, esize);
}

#ifdef SORT_STATS
void s_reset_stats()
{
    sortutils_compare_count = 0;
    sortutils_copy_count = 0;
}

void s_get_stats(int *compare_count, int *copy_count)
{
    *compare_count = sortutils_compare_count;
    *copy_count = sortutils_copy_count;
}
#endif

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



