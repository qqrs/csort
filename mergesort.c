#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "sortutils.h"

int ms_sort( void *list, uint32_t len, uint32_t esize, cmpfn_t cmp )
{
    int rc;
    void *a, *b, *dest;
    uint32_t sa, sb;
    uint32_t ai, bi, i;

    // base case
    if ( len <= 1 ) {
        return EXIT_SUCCESS;
    }

    // divide
    sa = len/2;
    sb = len - len/2;
    assert(sa+sb == len);
    a = malloc( sa * esize );
    b = malloc( sb * esize );
    
    if ( !a || !b ) {
        free(a);
        free(b);
        return EXIT_FAILURE;
    }

    // use s_memcpy() and copy element-by-element for accurate copy count stats
    for (i = 0; i < sa; i++)
    {
        s_memcpy(a + i*esize, list + i*esize, esize);
    }
    for (i = 0; i < sb; i++)
    {
        s_memcpy(b + i*esize, list + (sa+i)*esize, esize);
    }

    // conquer
    rc = ms_sort(a, sa, esize, cmp);
    if ( rc == EXIT_FAILURE ) {
        free(a);
        free(b);
        return EXIT_FAILURE;
    }
    rc = ms_sort(b, sb, esize, cmp);
    if ( rc == EXIT_FAILURE ) {
        free(a);
        free(b);
        return EXIT_FAILURE;
    }

    // combine
    ai = 0;
    bi = 0;
    dest = list;
    while (ai+bi < len)
    {
        if ( ai >= sa ) {
            // copy rest of b
            while ( bi < sb ) {
                s_memcpy(dest, b+bi*esize, esize);
                dest += esize;
                bi++;
            }
        } else if ( bi >= sb ) {
            // copy rest of a
            while ( ai < sa ) {
                s_memcpy(dest, a+ai*esize, esize);
                dest += esize;
                ai++;
            }
        } else {
            if ( (*cmp)(a+ai*esize, b+bi*esize) < 0 ) {
                s_memcpy(dest, a+ai*esize, esize);
                dest += esize;
                ai++;
            } else {
                s_memcpy(dest, b+bi*esize, esize);
                dest += esize;
                bi++;
            }
        }
    }

    // cleanup
    free(a);
    free(b);
    return EXIT_SUCCESS;
}


void mergesort( void *base, uint32_t len, uint32_t esize, cmpfn_t cmp )
{
    ms_sort(base, len, esize, cmp);
}
