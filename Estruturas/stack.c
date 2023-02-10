// Stack in c
#include <stdio.h>
#include <stdlib.h>

typedef struct snode{
    int value;
    struct snode * next;
} SNode;

// create
SNode * create_stack()
{
    SNode * head = malloc(sizeof(SNode));
    head->next = NULL;
    return head;
}

// push
void push(SNode * stack, int value)
{
    SNode * temp = malloc(sizeof(SNode));
    temp->value = value;
    temp->next = stack->next;
    stack->next = temp;
}

// pop
void pop(SNode * stack)
{
    SNode * temp = stack->next; // first element
    stack->next = temp->next; // stack to second element
    printf("Pop last element: %d\n", temp->value);
    free(temp);
}

// print
void sprint(SNode * stack)
{
    SNode * temp = stack->next;
    printf("(");
    while(temp != NULL)
    {
        printf("%d", temp->value);
        temp = temp->next;
        if(temp != NULL) printf(", ");
    }
    printf(")\n");
}

// len
int len(SNode * stack)
{
    int count = 0;
    SNode * temp = stack->next;
    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

// top
int top(SNode * stack)
{
    return stack->next->value;
}

// empty
int empty(SNode * stack)
{
    if(stack->next == NULL) return 1;
    return 0;
}

// sfree
void sfree(SNode * stack)
{
    SNode * temp = stack;
    while(temp != NULL)
    {
        SNode * aux = temp;
        temp = temp->next;
        free(aux);
    }
}


int main()
{
    SNode * stack = create_stack();
    int aux;

    while(scanf("%d", &aux) == 1)
    {
        push(stack, aux);
    }

    printf("\nLen = %d\n", len(stack));
    sprint(stack);
    pop(stack);
    pop(stack);
    sprint(stack);
    printf("top = %d\n", top(stack));
    printf("Is empty? %s", empty(stack) ? "Yes" : "No");

    sfree(stack);
    return 0;
}