#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "sortutils.h"

static void qs_sort( void *base, uint32_t len, int left, int right, 
                    uint32_t esize, cmpfn_t cmp )
{
    int pivot;
    int i, j;
    void *temp, *pivot_value;

    temp = malloc(esize);
    pivot_value = malloc(esize);
    if (!temp || !pivot_value) {
        exit(EXIT_FAILURE);
    }

    while (left < right)
    {
        pivot = (left+right)/2; 
        copy(pivot_value, base + pivot*esize, esize);

        i = left;
        j = right;
        while (1)
        {
            while (i <= right && (*cmp)(base+i*esize, pivot_value) < 0) {
                i++;
            }
            while (j >= left && (*cmp)(pivot_value, base+j*esize) < 0 ) {
                j--;
            }
            if (i > j) break;
            swap(base + i*esize, base + j*esize, temp, esize);
            i++; j--;
        }

        dbgprintf("pivot=%d left=%d i=%d j=%d right=%d | ", 
                                        pivot, left, i, j, right);
        dbgprintl(base, len, esize);

#ifdef DEBUG
        for (int k = left; k <= j; k++) {
            assert( (*cmp)(base+k*esize, pivot_value) <= 0 );
        }
        for (int k = right; k >= i; k--) {
            assert( (*cmp)(base+k*esize, pivot_value) >= 0 );
        }
#endif

        if (j > left) {
            qs_sort(base, len, left, j, esize, cmp );
        }
        left = i;
    }

    free(temp);
    free(pivot_value);
}

void quicksort( void *base, uint32_t len, uint32_t esize, cmpfn_t cmp )
{
    if (len <= 1) {
        return;
    }

    qs_sort(base, len, 0, len-1, esize, cmp);
    dbgprintl(base, len, esize);
}
