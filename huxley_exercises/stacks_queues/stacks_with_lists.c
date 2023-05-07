#include <stdio.h>
#include <stdlib.h>


typedef struct lnode{
    int value;
    struct lnode * next;
} LNode;

typedef struct snode{
    LNode * list;
    struct snode * next;
} SNode;

// create nodes
LNode * create_lnode()
{
    LNode * node = malloc(sizeof(LNode));
    node->next = NULL;
    return node;
}

SNode * create_snode()
{
    SNode * node = malloc(sizeof(SNode));
    node->next = NULL;
    return node;
}


// append (list)
void append(LNode ** list, int value)
{
    LNode * temp, *aux;
    temp = create_lnode();
    temp->value = value;

    if(*list == NULL) *list = temp;
    else{
        aux = *list;
        while(aux->next != NULL) aux = aux->next;
        aux->next = temp;
    }
}

// print (list)
void lprint(LNode * list)
{
    LNode * temp = list;

    while(temp->next != NULL) 
    {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("%d\n", temp->value);
}

// free (list)
void lfree(LNode * stack)
{
    LNode * temp = stack;
    while(temp != NULL)
    {
        LNode * aux = temp;
        temp = temp->next;
        free(aux);
    }
}


// push and pop (stack)
void push(SNode ** stack, LNode * list)
{
    SNode * temp;
    temp = create_snode();
    temp->list = list;

    if(*stack != NULL) temp->next = *stack;
    *stack = temp;
}

// pop (stack)
void pop(SNode ** stack)
{
    if(*stack == NULL) return (void) printf("EMPTY STACK\n");
    SNode * temp = *stack;
    *stack = temp->next;
    lprint(temp->list);
    lfree(temp->list);
    free(temp);
}


// main
int main()
{
    int aux;
    char command[5];
    SNode * stack = NULL;

    while(scanf("%s", command) == 1)
    {
        if(command[1] == 'U') // PUSH
        {
            LNode * list = NULL;
            while(scanf("%d", &aux) == 1) append(&list, aux);
            push(&stack, list);
        }
        else // POP
        {
            pop(&stack);
        }
    }
}