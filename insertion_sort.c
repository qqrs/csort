#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "sortutils.h"

void inssort( void *base, uint32_t len, uint32_t esize, cmpfn_t cmp )
{
    uint32_t i,j;
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
        copy(temp, base + i*esize, esize);
        for ( j = 1; j <= i; j++ )
        {
            if ( (*cmp)( temp, base + (i-j)*esize ) > 0 ) {
                break;
            }
            copy(base + (i-j+1)*esize, base + (i-j)*esize, esize);
        }
        copy(base + (i-j+1)*esize, temp, esize);
        dbgprintl(base, len, esize);
    }

    free(temp);
}


