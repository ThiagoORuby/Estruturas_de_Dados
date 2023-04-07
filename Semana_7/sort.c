#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

void swap(int * pos1, int * pos2)
{
    int aux = *pos1;
    *pos1 = *pos2;
    *pos2 = aux;
}

void bubble_sort(int * arr, int n)
{
    if(n <= 0) return;

    for(int j = 0; j < n - 1; j++)
    {
        if(arr[j] > arr[j+1])
            swap(&arr[j], &arr[j+1]);
    }

    bubble_sort(arr, n - 1);
}

void selection_sort(int * arr, int n)
{
    int mid; // minor id 

    for(int i = 0; i < n; i++)
    {
        mid = i;

        for(int j = i; j < n; j++)
        {
            if(arr[j] < arr[mid]) mid = j;
        }

        if(i != mid)
            swap(&arr[i], &arr[mid]);
    }
}

void insertion_sort(int * arr, int n)
{
    int j, value;

    for(int i = 1; i < n; i++)
    {
        j = i - 1;
        value = arr[i];
        while(arr[j] > value && j >= 0)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j+1] = value;
    }
}