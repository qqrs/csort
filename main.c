#include <stdio.h>
#include <stdlib.h>

static int compare_count = 0;

/*
int compare(const void *a, const void *b)
{
    if ( *(int *)a < *(int *)b ) {
        return -1;
    } 
    if ( *(int *)a > *(int *)b ) {
        return 1;
    } 
    return 0;
}
*/
int compare(const int *a, const int *b)
{
    compare_count++;

    if ( *a < *b ) {
        return -1;
    } 
    if ( *a > *b ) {
        return 1;
    } 
    return 0;
}

int swap(int *a, int *b)
{
    int t;

    t = *a;
    *a = *b;
    *b = t;
}

void print_data( int *base, size_t size )
{
    int i;

    for ( i = 0; i < size; i++ ) {
        printf("%d ", base[i]);
    }
    printf("\n");
}

void bubblesort( int *base, size_t size )
{
    int i,j,n;

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

void bubblesort2( int *base, size_t size )
{
    int i;
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

void inssort( int *base, size_t size )
{
    int i,j,n;
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
    int i,j,n;
    int temp;

    if ( size < 2 ) {
        return;
    }

    for ( i = 1; i < size; i++ )
    {
        temp = base[i];
        j = i-1;
        while ( compare( &temp, &base[j] ) < 0  && j >= 0) 
        {
            base[j+1] = base[j];
            j--;
        }

        base[j+1] = temp;
        print_data(base, size);
    }

}


void quicksort( void *base, size_t num )
{
    //qsort(base, num, sizeof(int), compare);
}

int main(int argc, char *argv[])
{
    //int data[] = {1,7,2,4,6,7};
    int data[] = {9,8,7,6,5,4,3,2,1};
    int data_len = sizeof(data)/sizeof(data[0]);

    //quicksort(data, data_len);
    //swap(&data[0], &data[1]);
    print_data(data, data_len);
    printf("===\n\n");

    inssort2(data, data_len);

    printf("===\n\n");
    print_data(data, data_len);

    printf("\ncompare count: %d\n", compare_count);

    return EXIT_SUCCESS;
}
