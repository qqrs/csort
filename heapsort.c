#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "sortutils.h"

static void hs_heapify( void *heap, uint32_t len, int parent, uint32_t esize, 
                        cmpfn_t cmp, void *temp )
{
    int left, right, max;
    right = (parent+1) << 1;
    left = right - 1;

    dbgprintl(heap, len, sizeof(int));

    max = parent;
    if ((uint32_t)left < len && 
            (*cmp)(heap+parent*esize, heap+left*esize) < 0) {
        max = left;
    } 
    if ((uint32_t)right < len && 
            (*cmp)(heap+max*esize, heap+right*esize) < 0) {
        max = right;
    }

    if (max != parent) {
        s_memswap(heap+(size_t)max*esize, heap+(size_t)parent*esize, temp, esize);
        hs_heapify(heap, len, max, esize, cmp, temp);
    }
}

static void hs_buildheap( void *heap, uint32_t len, uint32_t esize, 
                            cmpfn_t cmp, void *temp )
{
    for (int i = len/2 - 1; i >= 0; i--)
    {
        hs_heapify((int *)heap, len, i, esize, cmp, temp);
    }
}

void heapsort( void *base, uint32_t len, uint32_t esize, cmpfn_t cmp )
{
    void *temp;

    temp = malloc(esize);
    if (!temp) {
        exit(EXIT_FAILURE);
    }

    hs_buildheap(base, len, esize, cmp, temp);

    for (int i = len - 1; i >= 2; i--)
    {
        s_memswap(base, base+i*esize, temp, esize);
        hs_heapify((int *)base, i, 0, esize, cmp, temp);
    }

    s_memswap(base, base+esize, temp, esize);
    free(temp);
}
