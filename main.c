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

    for ( i = 0; i < size; i++ )
    {
        for ( j = 0; j < size-i; j++ )
        {
            if ( compare( &base[j], &base[j+1] ) > 0 ) {
                swap(&base[j], &base[j+1]);
            }
            print_data(base, size);
        }
        printf("\n");
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
    bubblesort(data, data_len);
    print_data(data, data_len);

    printf("\ncompare count: %d\n", compare_count);

    return EXIT_SUCCESS;
}
