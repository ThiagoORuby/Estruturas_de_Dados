#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int print_arr(int * arr, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d%s", arr[i], (i < n - 1) ? " " : "\n");
}


int main()
{
    int n = 8;
    int arr[] = {6, 5, 2, 8, 9, 1, 0, 7};

    print_arr(arr, n);
    insertion_sort(arr, n);
    print_arr(arr, n);
    return 0;
}