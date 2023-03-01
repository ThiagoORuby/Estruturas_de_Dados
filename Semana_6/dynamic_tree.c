// ARRAY BASED DYNAMIC TREE
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char value;
    int size;
    struct node ** children; // array[size] of children
} Node;

int main()
{
    return 0;
}