#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "sortutils.h"


int ms_sort( int *list, uint32_t size )
{
    int rc;
    int *a, *b, *dest;
    uint32_t sa, sb;
    uint32_t ai, bi;

    // base case
    if ( size <= 1 ) {
        return EXIT_SUCCESS;
    }

    // divide
    sa = size/2;
    sb = size - size/2;
    assert(sa+sb == size);
    a = malloc( sa * sizeof(int) );
    b = malloc( sb * sizeof(int) );
    
    if ( !a || !b ) {
        free(a);
        free(b);
        return EXIT_FAILURE;
    }

    memcpy(a, list, sa*sizeof(int) );
    memcpy(b, &list[sa], sb*sizeof(int) );

    // conquer
    rc = ms_sort(a, sa);
    if ( rc == EXIT_FAILURE ) {
        free(a);
        free(b);
        return EXIT_FAILURE;
    }
    rc = ms_sort(b, sb);
    if ( rc == EXIT_FAILURE ) {
        free(a);
        free(b);
        return EXIT_FAILURE;
    }

    // combine
    ai = 0;
    bi = 0;
    dest = list;
    while (ai+bi < size)
    {
        if ( ai >= sa ) {
            // copy rest of b
            while ( bi < sb ) {
                *dest = b[bi];
                dest++;
                bi++;
            }
        } else if ( bi >= sb ) {
            // copy rest of a
            while ( ai < sa ) {
                *dest = a[ai];
                dest++;
                ai++;
            }
        } else {
            if ( a[ai] < b[bi] ) {
                *dest = a[ai];
                dest++;
                ai++;
            } else {
                *dest = b[bi];
                dest++;
                bi++;
            }
        }
    }

    // cleanup
    free(a);
    free(b);
    return EXIT_SUCCESS;
}


void mergesort( int *base, uint32_t size )
{
    ms_sort(base, size);
}
