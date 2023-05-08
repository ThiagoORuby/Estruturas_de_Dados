#ifndef STACK_H
#define STACK

typedef struct stack{
    int value;
    char string[40];
    struct stack * next;
} Stack;

Stack * create_node();

int empty(Stack ** stack);

void push(Stack ** stack, int value);
void push_str(Stack ** stack, char * value);

int pop(Stack ** stack);
char * pop_str(Stack ** stack);

int top(Stack ** stack);
char * top_str(Stack ** stack);

void print_stack(Stack ** stack);
void print_stack_str(Stack ** stack);


#endif // STACK_H