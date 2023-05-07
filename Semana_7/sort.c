#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

// print an array
void print_arr(int * arr, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d%s", arr[i], (i < n - 1) ? " " : "\n");
}

// print interval of an array
void print_intv(int * arr, int bg, int n)
{
    for(int i = bg; i < n; i++)
        printf("%d%s", arr[i], (i < n - 1) ? " " : "\n");
}

// swap two values in an array
void swap(int * pos1, int * pos2)
{
    int aux = *pos1;
    *pos1 = *pos2;
    *pos2 = aux;
}

// Bubble Sort -> send the max to the end
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

// Bubble Sort -> send the min to the begin
void bubble_sort2(int * arr, int i, int n)
{
    if(i >= n) return;

    for(int j = n; j > 0; j--)
    {
        if(arr[j] < arr[j-1])
            swap(&arr[j], &arr[j-1]);
    }

    bubble_sort2(arr, i + 1, n);
}

// Selection Sort
// best case O(N²), average case O(N²), worst case O(N²)
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

        print_arr(arr, n);
    }
}

// Selection Sort with 2 pointers and check order
// best case O(N), average case O(N²/4), worst case O(N²/2)
void selection_sort2(int * arr, int n)
{
    int mid, min, max, count;
    int i = 0, j = n - 1; 

    mid = n/2;

    while(mid-- > 0)
    {
        min = i; max = j; count = 0;
        for(int k = i; k <= j; k++)
        {
            if(arr[k] < arr[min]) min = k;
            if(arr[k] > arr[max]) max = k;
            // melhorar complexidade no melhor caso:
            if(k < j && arr[k] < arr[k+1]) count++; 
        }

        if(count == j - i ) break;

        if(i != min)
        {
            if(i == max) max = min;
            swap(&arr[i], &arr[min]);
        }
        if(j != max) swap(&arr[j], &arr[max]);

        print_arr(arr, n);

        i++; j--;
    }
}

// Insertion Sort
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

// insertion sort with binary search
void insertion_sort2(int * arr, int n)
{
}

// Bin sort
void bin_sort(int * arr, int n)
{
    int i = 0;
    while(i < n)
    {
        if(i != arr[i])
        {
            int aux = arr[i];
            arr[i] = arr[aux];
            arr[aux] = aux;
        }
        else i++;
    }
}

// Quick Sort - static 
void quick_sort(int * arr, int bg, int n)
{
    // stop recursion codition
    if(abs(bg - n) <= 1) return;

    int pos = (n - bg)/3 + bg;
    int pivot = arr[pos];
    int i = bg;

    printf("bg = %d, n = %d\n", bg, n);
    printf("pos = %d, pivot = %d\n", pos, pivot);

    for(int j = bg; j < n; j++)
    {
        if(arr[j] < pivot)
        {
            if(j != i) swap(&arr[i], &arr[j]);
            i++;
            if(i == pos) i++;
        }
    }

    while(arr[pos+1] < arr[pos])
    {
        swap(&arr[pos+1], &arr[pos]);
        pos++;
    }

    while(arr[pos-1] > arr[pos] && (pos - 1) >= 0)
    {
        swap(&arr[pos-1], &arr[pos]);
        pos--;
    }



    print_intv(arr, bg, n);

    quick_sort(arr, bg, pos);
    quick_sort(arr, pos + 1, n);

}

// Merge Sort - dynamic
List * merge(List ** left, List ** right)
{
    List * joined = NULL;

    while(!isempty(left) && !isempty(right))
    {
        if(!isempty(left) && (*left)->value <= (*right)->value)
        {
            append(&joined, (*left)->value);
            pop(left);
        }
        else
        {
            append(&joined, (*right)->value);
            pop(right);
        }
    }
    
    while(!isempty(left))
    {
        append(&joined, (*left)->value);
        pop(left);
    }

    while(!isempty(right))
    {
        append(&joined, (*right)->value);
        pop(right);
    }

    printf("merged left right: ");
    lprint(&joined);

    return joined;
}

List * merge_sort(List ** list)
{
    if(len(list) <= 1) return *list;

    List * left = NULL;
    List * right = NULL;

    int middle = len(list)/2, i = 0;
    List * temp = *list;

    while(temp != NULL)
    {
        if(i < middle) append(&left, temp->value);
        else append(&right, temp->value);

        temp = temp->next;
        i++;
    }

    printf("left: ");
    lprint(&left);
    printf("right: ");
    lprint(&right);

    left = merge_sort(&left);
    right = merge_sort(&right);

    return merge(&left, &right);
}

// Shell Sort / Comb Sort
void shell_sort(int * arr, int n)
{
    int gap = n/2;

    while(gap >= 1)
    {
        printf("gap = %d\n", gap);
        for(int i = 0; i + gap < n; i++)
        {
            if(arr[i] > arr[i + gap])
            {
                swap(&arr[i], &arr[i+gap]);
            }
        }

        print_arr(arr, n);

        gap--;
    }
}

// Radix Sort
void radix_sort(int * arr, int n)
{
    int max = -1;
    int output[n];

    for(int i = 0; i < n; i++) 
        if(arr[i] > max) max = arr[i];

    printf("max = %d\n", max);

    int base = 1;

    while(base <= max)
    {
        int count[10] = {0};

        for(int i = 0; i < n; i++) count[(arr[i]/base) % 10]++;

        for(int i = 0; i < 9; i++) count[i+1] += count[i];

        for(int i = n - 1; i >= 0; i--) output[--count[(arr[i]/base) % 10]] = arr[i];

        for(int i = 0; i < n; i++) arr[i] = output[i];

        print_arr(arr, n);

        base *= 10;
    }
}

// Counting Sort
void counting_sort(int * arr, int n)
{
    int max = -1;
    int output[n];

    for(int i = 0; i < n; i++)
        if(arr[i] > max) max = arr[i];
    max++;

    int * count = calloc(max, sizeof(int));

    for(int i = 0; i < n; i++) count[arr[i]]++;

    print_arr(count, max);

    for(int i = 0; i < max - 1; i++) count[i+1] += count[i];

    print_arr(count, max);

    for(int i = 0; i < n; i++) output[--count[arr[i]]] = arr[i]; 

    print_arr(output, n);
}

