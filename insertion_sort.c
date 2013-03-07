#include <stdlib.h>
#include <stdio.h>

#include "sortutils.h"

void inssort( int *base, size_t size )
{
    int i,j;
    int temp;

    if ( size < 2 ) {
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
        print_data(base, size);
    }

}


void inssort2( int *base, size_t size )
{
    int i,j;
    int temp;

    if ( size < 2 ) {
        return;
    }

    for ( i = 1; i < size; i++ )
    {
        temp = base[i];
        j = i-1;
        while ( j >= 0 && compare( &temp, &base[j] ) < 0 ) 
        {
            base[j+1] = base[j];
            j--;
        }

        base[j+1] = temp;
        print_data(base, size);
    }

}

void inssort3( int *base, size_t size )
{
    int temp;
    int *a, *end, *hole;
    end = base + size - 1;

    if ( size < 2 ) {
        return;
    }

    for ( a = base + 1; a <= end; a++ )
    {
        temp = *a;
        hole = a-1;
        while ( hole >= base && compare( &temp, hole ) < 0 ) 
        {
            *(hole+1) = *hole;
            hole--;
        }

        *(hole+1) = temp;
        print_data(base, size);
    }

}

