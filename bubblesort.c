#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "sort.h"
#include "sortutils.h"

void bubblesort( void *base, uint32_t len, uint32_t esize, cmpfn_t cmp )
{
    uint32_t i,j;
    void *a, *b;
    bool swapped;
    void *temp;

    temp = malloc(esize);
    if (!temp) {
        exit(EXIT_FAILURE);
    }

    if ( len <= 1 ) {
        return;
    }

    for ( i = 1; i < len; i++ )
    {
        swapped = false;
        for ( j = 0; j < len-i; j++ )
        {
            a = base + j*esize;
            b = a + esize;
            if ( (*cmp)(a, b) > 0 ) {
                s_memswap(a, b, temp, esize);
                swapped = true;
            }
            dbgprintl(base, len, esize);
        }
        dbgprintf("\n");

        if (!swapped) {
            return;
        }
    }

    free(temp);
}

