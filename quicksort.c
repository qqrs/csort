#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "sortutils.h"

// type for pointer to partition function
typedef uint32_t (*partfn_t)(int *, uint32_t, uint32_t, uint32_t, uint32_t);


static uint32_t qs_partition( int *base, uint32_t size, uint32_t left, 
                         uint32_t right, uint32_t pivot )
{
    int pivot_value;

    assert(right <= size);

    pivot_value = base[pivot];
    //dbgprintl(&base[left], right-left+1);

    // move pivot value out of the way
    swap(&base[pivot], &base[right]);
    //dbgprintl(&base[left], right-left+1);

    // walk partition and swap values < pivot to left side
    pivot = left;
    //for ( uint32_t i = 0; i < right; i++ )
    for ( uint32_t i = left; i < right; i++ )
    {
        if (compare(&base[i], &pivot_value) < 0) {
            swap(&base[i], &base[pivot]);
            pivot++;
        }
        //dbgprintl(&base[left], right-left+1);
    }

    // move pivot value to new pivot index
    swap(&base[right], &base[pivot]);
    //dbgprintl(&base[left], right-left+1);

    // return new pivot
    return pivot;
}

static void qs_sort( int *base, uint32_t size, uint32_t left, uint32_t right, 
                     partfn_t partfn )
{
    uint32_t pivot;

    //dbgprintl(&base[left], right-left+1);
    if (left >= right) {
        return;     // only one item in the partition
    }

    // choose a pivot
    // better pivot choice would be one of three elements, selected at random
    pivot = (left+right)/2;     

    // partition around the pivot and get new pivot index
    pivot = (*partfn)(base, size, left, right, pivot);   
    //dbgprintl(&base[left], right-left+1);

    // sort both partitions
    if (pivot > left) {
        qs_sort(base, size, left, pivot-1, partfn);
    }
    if (pivot < right) { 
        qs_sort(base, size, pivot+1, right, partfn);
    }
}

void quicksort( int *base, uint32_t size )
{
    if (size <= 1) {
        return;
    }

    qs_sort(base, size, 0, size-1, qs_partition);
}

// =============================================================================


static void qs_sort2( int *base, uint32_t size, int left, int right)
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
            qs_sort2(base, size, left, j);
        }
        left = i;
    }
}

void quicksort2( int *base, uint32_t size )
{
    if (size <= 1) {
        return;
    }

    qs_sort2(base, size, 0, size-1);
    dbgprintl(base, size);
}
