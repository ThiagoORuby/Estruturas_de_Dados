#include <stdio.h>
#include <stdlib.h>
#include "stacks.h"

Stacks * create_nodes()
{
    Stacks * node = malloc(sizeof(Stacks));
    node->next = NULL;
    return node;
}

int emptys(Stacks ** stacks)
{
    if(*stacks == NULL) return 1;
    return 0;
}

void pushs(Stacks ** stacks, Stack * st)
{
    Stacks * new = create_nodes();
    new->stack = st;

    if(!emptys(stacks)) new->next = *stacks;

    *stacks = new;
}

Stack * pops(Stacks ** stacks)
{
    if(emptys(stacks)) return NULL;

    Stacks * temp = (*stacks);
    *stacks = (*stacks)->next;

    Stack * st = temp->stack;
    free(temp);

    return st;
}

Stack * tops(Stacks ** stacks)
{
    if(emptys(stacks)) return NULL;

    return (*stacks)->stack;
}

void print_stacks(Stacks ** stacks)
{
    Stacks * temp = *stacks;

    while(temp != NULL)
    {
        print_stack(&(temp->stack));
        temp = temp->next;
    }
}

void print_stacks_str(Stacks ** stacks)
{
    Stacks * temp = *stacks;

    while(temp != NULL)
    {
        print_stack_str(&(temp->stack));
        temp = temp->next;
    }
}