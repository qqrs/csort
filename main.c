#include <stdio.h>
#include <stdlib.h>

#include "sort.h"
#include "sortutils.h"

//static int compare_count = 0;

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
int main(int argc, char *argv[])
{
    int data[] = {1,7,2,4,6,7};
    //int data[] = {9,8,7,6,5,4,3,2,1};
    //int data[] = {7,5,4,6,3,2,1};
    int data_len = sizeof(data)/sizeof(data[0]);

    //quicksort(data, data_len);
    //swap(&data[0], &data[1]);
    /*
    print_data(data, data_len);
    printf("===\n\n");

    quicksort(data, data_len);

    printf("===\n\n");
    print_data(data, data_len);

    printf("\ncompare count: %d\n", compare_count);
    */

    return EXIT_SUCCESS;
}
