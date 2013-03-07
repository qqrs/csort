#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "sortutils.h"

void bubblesort( int *base, uint32_t size )
{
    uint32_t i,j;

    if ( size < 2 ) {
        return;
    }

    for ( i = 0; i < size-1; i++ )
    {
        for ( j = 0; j < size-i-1; j++ )
        {
            if ( compare( &base[j], &base[j+1] ) > 0 ) {
                swap(&base[j], &base[j+1]);
            }
            print_data(base, size);
        }
        // if no swaps on this sweep, break loop
        printf("\n");
    }

}


void bubblesort2( int *base, uint32_t size )
{
    int *a, *b, *end;

    if ( size < 2 ) {
        return;
    }
    end = base + size - 1;

    while (end != base)
    {
        for ( a = base, b = base+1; b <= end; a++, b++ )
        {
            if ( compare( a, b ) > 0 ) {
                swap( a, b );
            }
            print_data(base, size);
        }
        // if no swaps on this sweep, break loop
        printf("\n");
        end--;
    }

}
