#ifndef STACKS_H
#define STACKS

#include "stack.h"

typedef struct stacks{
    Stack * stack;
    struct stacks * next;
} Stacks;

Stacks * create_nodes();

int emptys(Stacks ** stacks);

void pushs(Stacks ** stacks, Stack * value);

Stack * pops(Stacks ** stacks);

Stack * tops(Stacks ** stacks);

void print_stacks(Stacks ** stacks);

#endif // STACKS_H