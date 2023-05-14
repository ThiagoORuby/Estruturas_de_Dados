// LIST OF CHILDREN IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>

// Linked list node
typedef struct list_node
{
    int value;
    struct list_node * next;
} LNode;

// LCTree node 
typedef struct node
{
    char value;
    int parent;
    LNode * children;
} Node;

int main()
{
    return 0;
}