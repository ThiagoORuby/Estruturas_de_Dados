#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "list.h"
#include <time.h>


int main()
{
    int n = 6;
    int arr[] = {3, 2, 1, 5, 6, 7};

    
    List * list = NULL;
    for(int i = 0; i < n; i++) append(&list, arr[i]);

    print_arr(arr, n);
    //lprint(&list);

    selection_sort2(arr, n);
    //List * sorted = merge_sort(&list);
    print_arr(arr, n);
    //lprint(&sorted);
    lfree(&list);
    return 0;
}