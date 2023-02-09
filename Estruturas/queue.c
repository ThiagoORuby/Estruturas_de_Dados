#include <stdio.h>
#include <stdlib.h>

// queue node
typedef struct qnode{
    int value;
    struct qnode * next;
} QNode;

// create
QNode * create_queue()
{
    QNode * begin = malloc(sizeof(QNode));
    begin->next = NULL;
    return begin;
}

// insert
void push_back(QNode * queue, int value)
{
    QNode * temp = queue;
    while(temp->next != NULL) temp = temp->next;
    QNode * new = malloc(sizeof(QNode));
    new->value = value;
    new->next = NULL;
    temp->next = new;
}

// len
int len(QNode * queue)
{
    int i = 0;
    QNode * temp = queue->next;
    while(temp != NULL)
    {
        i++;
        temp = temp->next;
    }
    return i;
}

// remove
void pop_front(QNode * queue)
{
    QNode * temp = queue->next; // temp = queue[1];
    queue->next = temp->next; // queue[0].next = queue[1].next -> queue[2];
    free(temp);
}

// print
void qprint(QNode * queue)
{
    QNode * temp = queue->next;
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
void qfree(QNode * queue)
{
    QNode * temp = queue;
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
    QNode * queue = create_queue();
    while(scanf("%d", &aux) == 1){
        push_back(queue, aux);
    }

    int l = len(queue);

    printf("len = %d\n", l);
    qprint(queue);
    pop_front(queue);
    qprint(queue);
    pop_front(queue);
    qprint(queue);
    qfree(queue);
    return 0;
}