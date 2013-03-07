#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "sortutils.h"

int qs_partition( int *base, uint32_t size, uint32_t left, uint32_t right, 
                    uint32_t pivot )
{
    int pivot_value;

    pivot_value = base[pivot];
    print_data(&base[left], right-left+1);

    // move pivot value out of the way
    swap(&base[pivot], &base[right]);
    print_data(&base[left], right-left+1);

    // walk partition and swap values < pivot to left side
    pivot = 0;
    for ( uint32_t i = 0; i < right; i++ )
    {
        if (compare(&base[i], &pivot_value) < 0) {
            swap(&base[i], &base[pivot]);
            pivot++;
        }
        print_data(&base[left], right-left+1);
    }

    // move pivot value to new pivot index
    swap(&base[right], &base[pivot]);
    print_data(&base[left], right-left+1);

    // return new pivot
    return pivot;
}

int qs_partition2( int *base, uint32_t size, int left, int right, int pivot )
{
    int pivot_value;
    uint32_t i,j;

    pivot_value = base[pivot];
    print_data(&base[left], right-left+1);

    // walk partition from both ends and swap if on wrong side of pivot
    i = left-1;
    j = right+1;
    while (1)
    {
        do {
            i++;
        } while (compare(&base[i], &pivot_value) < 0);
        do {
            j--;
        } while (compare(&base[j], &pivot_value) > 0);

        if (i >= j) {
            break;
        }

        swap(&base[i], &base[j]);
        print_data(&base[left], right-left+1);
    }

    printf("new pivot: %d\n", j);
    // return new pivot
    return j;
}

void qs_sort( int *base, uint32_t size, int left, int right )
{
    int pivot;

    if (left >= right) {
        return;     // only one item in the partition
    }

    pivot = (left+right)/2;     // choose a pivot

    // partition around the pivot and get new pivot index
    pivot = qs_partition2(base, size, left, right, pivot);   

    // sort both partitions
    qs_sort(base, size, left, pivot-1);
    qs_sort(base, size, pivot+1, right);
}

void quicksort( int *base, uint32_t size )
{
    //qsort(base, num, sizeof(int), compare);
    qs_sort(base, size, 0, size-1);
}
