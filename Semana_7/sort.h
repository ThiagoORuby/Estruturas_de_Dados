#ifndef SORT_H
#define SORT_H
#include "list.h"

// print an array
void print_arr(int * arr, int n);

// Swap two array values
void swap(int * pos1, int * pos2);

// O(N²) sort algorithms
void bubble_sort(int * arr, int n);
void bubble_sort2(int * arr, int i, int n);
void insertion_sort(int * arr, int n);
void selection_sort(int * arr, int n);
void selection_sort2(int * arr, int n);


// O(N LOG(N)) sort algorithms
void bin_sort(int * arr, int n);
void counting_sort(int * arr, int n);
void quick_sort(int * arr, int bg, int n);
List * merge_sort(List ** list);
void heap_sort(int * arr, int n);

// another efficient sort algorithms
void radix_sort(int * arr, int n);
void shell_sort(int * arr, int n); // combsort sao praticamente iguais

// algoritmos otimizados
// insertion sort -> busca binaria e evitar conferencias desnecessárias
// bubble_sort -> ordenar as duas metades ao mesmo tempo com 2 ponteiros


#endif // SORT_H