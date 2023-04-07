#ifndef SORT_H
#define SORT_H

// Swap two array values
void swap(int * pos1, int * pos2);

// O(N²) sort algorithms
void bubble_sort(int * arr, int n);
void insertion_sort(int * arr, int n);
void selection_sort(int * arr, int n);

// O(N LOG(N)) sort algorithms
void quick_sort(int * arr, int n);
void merge_sort(int * arr, int n);
void heap_sort(int * arr, int n);

// another efficient sort algorithms
void radix_sort(int * arr, int n);
void shell_sort(int * arr, int n);

#endif // SORT_H