#include <stdio.h>
#include <stdlib.h>

// list node
typedef struct lnode{
    int value;
    struct lnode * next;
} LNode;

// create
LNode * create_list()
{
    LNode * begin = malloc(sizeof(LNode));
    begin->next = NULL;
    return begin;
}

// insert
void push_back(LNode * list, int value)
{
    LNode * temp = list;
    while(temp->next != NULL) temp = temp->next;
    LNode * new = malloc(sizeof(LNode));
    new->value = value;
    new->next = NULL;
    temp->next = new;
}

// len
int len(LNode * list)
{
    int i = 0;
    LNode * temp = list->next;
    while(temp != NULL)
    {
        i++;
        temp = temp->next;
    }
    return i;
}

// remove
void pop_front(LNode * list)
{
    LNode * temp = list->next; // temp = list[1];
    list->next = temp->next; // list[0].next = list[1].next -> list[2];
    free(temp);
}

// print
void qprint(LNode * list)
{
    LNode * temp = list->next;
    printf("(");
    while(temp != NULL)
    {
        printf("%d", (*temp).value);
        temp = temp->next;
        if(temp != NULL) printf(", ");
    }
    printf(")\n");
}

//free
void qfree(LNode * list)
{
    LNode * temp = list;
    while(temp != NULL)
    {
        LNode * aux = temp;
        temp = temp->next;
        free(aux);
    }
}

int main()
{
    int aux;
    LNode * list = create_list();
    while(scanf("%d", &aux) == 1){
        push_back(list, aux);
    }

    int l = len(list);

    printf("len = %d\n", l);
    qprint(list);
    pop_front(list);
    qprint(list);
    pop_front(list);
    qprint(list);
    qfree(list);
    return 0;
}