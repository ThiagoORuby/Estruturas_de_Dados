#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct snode{
    char value;
    struct snode * next;
} SNode;

// create
SNode * create_node()
{
    SNode * node = malloc(sizeof(SNode));
    node->next = NULL;
    return node;
}

// empty
int empty(SNode * stack)
{
    if(stack == NULL) return 1;
    return 0;
}

// push
void push(SNode ** stack, char value)
{
    SNode * temp = create_node();
    temp->value = value;
    if(*stack != NULL) temp->next = *stack;
    *stack = temp;
}

// pop
void pop(SNode ** stack)
{
    SNode * temp = *stack;
    *stack = (*stack)->next;
    free(temp);
}

// top
char top(SNode * stack)
{
    return stack->value;
}

int is_symbol(char c)
{
    if(c == '(' || c == ')') return 1;
    if(c == '[' || c == ']') return 1;
    if(c == '{' || c == '}') return 1;
    return 0;
}

char closer(char value)
{
    if(value == '(') return ')';
    if(value == '[') return ']';
    if(value == '{') return '}';
    return '?';
}

// parentesis checker
int checker(char * string)
{
    SNode * stack = NULL;

    for(int i = 0; i < strlen(string); i++)
    {
        char c = string[i];
        if(is_symbol(c))
        {
            if(!empty(stack) && c == closer(top(stack)))
            {
                pop(&stack);
            }
            else push(&stack, c);
        }
    }

    return empty(stack);
}


int main()
{
    int n;
    char aux[256];

    scanf("%d ", &n);

    for(int i = 0; i < n; i++)
    {
        gets(aux);
        if(checker(aux)) printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}