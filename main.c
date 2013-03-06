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

int qs_partition( int *base, size_t size, int left, int right, int pivot )
{
    int pivot_value;
    int i;

    pivot_value = base[pivot];
    print_data(&base[left], right-left+1);

    // move pivot value out of the way
    swap(&base[pivot], &base[right]);
    print_data(&base[left], right-left+1);

    // walk partition and swap values < pivot to left side
    pivot = 0;
    for ( i = 0; i < right; i++ )
    {
        if (compare(&base[i], &pivot_value) < 0) {
            swap(&base[i], &base[pivot]);
            pivot++;
        }
        print_data(&base[left], right-left+1);
    }

    // move pivot value to new pivot index
    swap(&base[right], &base[pivot]);
    print_data(&base[left], right-left+1);

    // return new pivot
    return pivot;
}

void qs_sort( int *base, size_t size, int left, int right )
{
    int pivot;

    if (left >= right) {
        return;     // only one item in the partition
    }

    pivot = (left+right)/2;     // choose a pivot

    // partition around the pivot and get new index of pivot value
    pivot = qs_partition(base, size, left, right, pivot);   

    // sort both partitions
    qs_sort(base, size, left, pivot-1);
    qs_sort(base, size, pivot+1, right);
}

void quicksort( int *base, size_t size )
{
    //qsort(base, num, sizeof(int), compare);
    qs_sort(base, size, 0, size-1);
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

    quicksort(data, data_len);

    printf("===\n\n");
    print_data(data, data_len);

    printf("\ncompare count: %d\n", compare_count);

    return EXIT_SUCCESS;
}
