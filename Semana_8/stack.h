#ifndef STACK_H
#define STACK

typedef struct stack{
    int value;
    struct stack * next;
} Stack;

Stack * create_node();

int empty(Stack ** stack);

void push(Stack ** stack, int value);

int pop(Stack ** stack);

int top(Stack ** stack);

void print_stack(Stack ** stack);


#endif // STACK_H