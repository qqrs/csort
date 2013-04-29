#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "sortutils.h"

static void qs_sort( int *base, uint32_t size, int left, int right)
{
    int pivot;
    int pivot_value;
    int i, j;

    while (left < right)
    {
        pivot = (left+right)/2; 
        pivot_value = base[pivot]; 

        i = left;
        j = right;
        while (1)
        {
            while (i <= right && base[i] < pivot_value) {
                i++;
            }
            while (j >= left && pivot_value < base[j]) {
                j--;
            }
            if (i > j) break;
            swap(&base[i], &base[j]);
            i++; j--;
        }

        dbgprintf("pivot=%d left=%d i=%d j=%d right=%d | ", 
                                        pivot, left, i, j, right);
        dbgprintl(base, size);

#ifdef DEBUG
        for (int k = left; k <= j; k++) {
            assert(base[k] <= pivot_value);
        }
        for (int k = right; k >= i; k--) {
            assert(base[k] >= pivot_value);
        }
#endif

        if (j > left) {
            qs_sort(base, size, left, j);
        }
        left = i;
    }
}

void quicksort( int *base, uint32_t size )
{
    if (size <= 1) {
        return;
    }

    qs_sort(base, size, 0, size-1);
    dbgprintl(base, size);
}
