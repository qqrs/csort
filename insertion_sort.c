#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "sortutils.h"

void inssort( int *base, uint32_t size )
{
    uint32_t i,j;
    int temp;

    if ( size <= 1 ) {
        return;
    }

    for ( i = 1; i < size; i++ )
    {
        temp = base[i];
        for ( j = 1; j <= i; j++ )
        {
            if ( compare( &temp, &base[i-j] ) > 0 ) {
                break;
            }
            base[i-j+1] = base[i-j];
        }
        base[i-j+1] = temp;
        dbgprintl(base, size);
    }

}


