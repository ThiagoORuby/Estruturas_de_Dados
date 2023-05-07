#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack * create_node()
{
    Stack * node = malloc(sizeof(Stack));
    node->next = NULL;
    return node;
}

int empty(Stack ** stack)
{
    if(*(stack) == NULL) return 1;
    return 0;
}

void push(Stack ** stack, int value)
{
    Stack * new = create_node();
    new->value = value;

    if(!empty(stack)) new->next = *stack;
    *stack = new;
}

int pop(Stack ** stack)
{
    if(empty(stack)) return -1;

    Stack * temp = *stack;
    *stack = (*stack)->next;

    int value = temp->value;
    free(temp);

    return value;
}

int top(Stack ** stack)
{
    if(empty(stack)) return printf("Empty stack!");

    return (*stack)->value;
}

void print_stack(Stack ** stack)
{
    Stack * temp = *stack;

    printf("| ");
    while(temp != NULL)
    {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("|\n");
}