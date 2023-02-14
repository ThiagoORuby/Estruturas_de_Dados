// Check () [] {}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct snode{
    char value;
    struct snode * next;
} SNode;

// create
SNode * create_stack()
{
    SNode * head = malloc(sizeof(SNode));
    head->next = NULL;
    return head;
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

// push
void push(SNode * stack, char value)
{
    SNode * temp = malloc(sizeof(SNode));
    temp->value = value;
    temp->next = stack->next;
    stack->next = temp;
}

// pop
char pop(SNode * stack)
{
    SNode * temp = stack->next;
    stack->next = temp->next;
    char value = temp->value;
    free(temp);
    return value;
}

// empty
int empty(SNode * stack)
{
    if(stack->next == NULL) return 1;
    return 0;
}

// print
void sprint(SNode * stack)
{
    printf("| ");
    SNode * temp = stack->next;
    while(temp != NULL)
    {
        printf("%c", temp->value);
        temp = temp->next;
        if(temp != NULL) printf(" | ");
    }
    printf(" |\n");
}

// top
char top(SNode * stack)
{
    return stack->next->value;
}

// free
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

// check is some char is in '()[]{}'
int is_symbol(char c)
{
    if(c == '(' || c == ')') return 1;
    if(c == '[' || c == ']') return 1;
    if(c == '{' || c == '}') return 1;
    return 0;
}

// check if 2 chars are complements
int is_closer(char c, char c2)
{
    if(c == '(' && c2 == ')') return 1;
    if(c == '[' && c2 == ']') return 1;
    if(c == '{' && c2 == '}') return 1;
    return 0;
}


// check ()[]{}
int checker(char * string, SNode * stack)
{
    for(int i = 0; i < strlen(string); i++)
    {
        char c = string[i];
        if(is_symbol(c))
        {
            if(len(stack) >= 1 && is_closer(top(stack), c))
            {
                pop(stack);
                printf("Find a %c!\n", c);
                sprint(stack);
                continue;
            }
            else
            {
                push(stack, c);
                sprint(stack);
            }
        }
    }

    return empty(stack);
}


int main()
{
    char string[500];
    SNode * stack = create_stack();

    scanf("%[^\n]", string);

    int ret = checker(string, stack);

    printf("%s", (ret) ? "All right!\n" : "Some problem with the closers...\n");

    sfree(stack);
    return 0;
}