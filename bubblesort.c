#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "sortutils.h"

void bubblesort( int *base, uint32_t size )
{
    uint32_t i,j;
    bool swapped;

    if ( size <= 1 ) {
        return;
    }

    for ( i = 1; i < size; i++ )
    {
        swapped = false;
        for ( j = 0; j < size-i; j++ )
        {
            if ( compare( &base[j], &base[j+1] ) > 0 ) {
                swap(&base[j], &base[j+1]);
                swapped = true;
            }
            dbgprintl(base, size);
        }
        dbgprintf("\n");

        if (!swapped) {
            return;
        }
    }

}

