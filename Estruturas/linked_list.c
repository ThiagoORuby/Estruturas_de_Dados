#include <stdio.h>
#include <stdlib.h>

// list node
typedef struct qnode{
    int value;
    struct qnode * next;
} QNode;

// create
QNode * create_list()
{
    QNode * begin = malloc(sizeof(QNode));
    begin->next = NULL;
    return begin;
}

// insert
void push_back(QNode * list, int value)
{
    QNode * temp = list;
    while(temp->next != NULL) temp = temp->next;
    QNode * new = malloc(sizeof(QNode));
    new->value = value;
    new->next = NULL;
    temp->next = new;
}

// len
int len(QNode * list)
{
    int i = 0;
    QNode * temp = list->next;
    while(temp != NULL)
    {
        i++;
        temp = temp->next;
    }
    return i;
}

// remove
void pop_front(QNode * list)
{
    QNode * temp = list->next; // temp = list[1];
    list->next = temp->next; // list[0].next = list[1].next -> list[2];
    free(temp);
}

// print
void qprint(QNode * list)
{
    QNode * temp = list->next;
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
void qfree(QNode * list)
{
    QNode * temp = list;
    while(temp != NULL)
    {
        QNode * aux = temp;
        temp = temp->next;
        free(aux);
    }
}

int main()
{
    int aux;
    QNode * list = create_list();
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