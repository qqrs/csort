#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "sortutils.h"

static void hs_heapify( int *heap, uint32_t size, int parent )
{
    int left, right, max;
    right = (parent+1) << 1;
    left = right - 1;

    dbgprintl(heap, size);

    max = parent;
    if ((uint32_t)left < size && heap[parent] < heap[left]) {
        max = left;
    } 
    if ((uint32_t)right < size && heap[max] < heap[right]) {
        max = right;
    }

    if (max != parent) {
        s_memswap(&heap[max], &heap[parent]);
        hs_heapify(heap, size, max);
    }
}

static void hs_buildheap( int *heap, uint32_t size )
{
    for (int i = size/2 - 1; i >= 0; i--)
    {
        hs_heapify(heap, size, i);
    }
}

void heapsort( int *base, uint32_t size )
{
    hs_buildheap(base, size);

    for (int i = size - 1; i >= 2; i--)
    {
        s_memswap(&base[0], &base[i]);
        hs_heapify(base, i, 0);
    }
    s_memswap(&base[0], &base[1]);
}
