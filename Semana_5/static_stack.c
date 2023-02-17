// Static stack
#include <stdio.h>
#include <stdlib.h>

#define MAXN 500

typedef struct snode{
    int value;
} SNode;

// create
SNode * create_stack(int * top)
{
    SNode * stack = malloc(sizeof(SNode) * MAXN);
    *top = -1;
    return stack;
}

// push
void push(SNode * stack, int * top, int value)
{
    if(*top == MAXN - 1) 
    {
        printf("Stack is full\n");
        return;
    }
    stack[*top+1].value = value;
    *top += 1; 
}

// pop
int pop(SNode * stack, int * top)
{
    if(*top == -1)
    {
        printf("Stack empty\n");
        return 0;
    }
    int value = stack[*top].value;
    *top -= 1;
    return value;
}

// len
int len(SNode * stack, int * top)
{
    return *top + 1;
}

// sprint
void sprint(SNode * stack, int * top)
{
    printf("[");
    for(int i = 0; i <= *top; i++)
    {
        printf("%d", stack[i].value);
        if(i < *top) printf(", ");
    }
    printf("]\n");
}

// top
// empty

// sort
// union
// invert

int main()
{
    // initialize stack
    int top, aux;
    SNode * stack = create_stack(&top);

    while(scanf("%d", &aux) == 1)
    {
        push(stack, &top, aux);
    } 

    printf("len = %d\n\n", len(stack, &top));

    sprint(stack, &top);
    pop(stack, &top);
    sprint(stack, &top);
    
    return 0;
}