// Queue
#include <stdio.h>
#include <stdlib.h>

typedef struct qnode{
    int value;
    struct qnode * next;
    struct qnode * prev;
} QNode;

// create
QNode ** create_queue()
{
    QNode ** queue = malloc(sizeof(QNode *)*2);

    for(int i = 0; i < 2; i++) queue[i] = malloc(sizeof(QNode));

    queue[0]->next = queue[1];
    queue[1]->prev = queue[0];
    return queue;
}

// empty
int empty(QNode ** queue)
{
    if(queue[0]->next == queue[1]) return 1;
    return 0;
}

// push
void push(QNode ** queue, int value)
{
    QNode * new = malloc(sizeof(QNode));
    new->value = value;
    if(empty(queue))
    {
        printf("valor add = %d\n", value);
        queue[0]->next = new;
        queue[1]->prev = new;
        new->next = queue[1];
    }
    else
    {
        QNode * temp = queue[1]->prev;
        temp->next = new;
        new->next = queue[1];
        queue[1]->prev = new;
    }
}

// pop
void pop(QNode ** queue)
{
    QNode * temp = queue[0]->next;
    queue[0]->next = temp->next;
    printf("Pop first element: %d\n",  temp->value);
    free(temp);
}


// len
int len(QNode ** queue)
{
    int count = 0;
    QNode * temp = queue[0]->next;
    while(temp != queue[1])
    {
        count++;
        temp = temp->next;
    }
    return count;
}

// print
void qprint(QNode ** queue)
{
    QNode * temp = queue[0]->next;
    printf("[");
    while(temp != queue[1])
    {
        printf("%d", temp->value);
        temp = temp->next;
        if(temp != queue[1]) printf(", ");
    }
    printf("]\n");
}

// front
int front(QNode ** queue)
{
    return queue[0]->next->value;
}

// back
int back(QNode ** queue)
{
    return queue[1]->prev->value;
}

// qfree
void qfree(QNode ** queue)
{
    int count = 0;
    QNode * temp = queue[0];
    while(temp != queue[1])
    {
        QNode * aux = temp;
        temp = temp->next;
        free(temp);
    }
    free(queue[1]);
}

int main()
{
    QNode ** queue = create_queue();
    int aux;

    while(scanf("%d", &aux) == 1)
    {
        push(queue, aux);
    }

    printf("\nLen = %d\n", len(queue));
    qprint(queue);
    pop(queue);
    pop(queue);
    qprint(queue);
    printf("Front = %d\n", front(queue));
    printf("Back = %d\n", back(queue));
    printf("Is empty? %s\n", empty(queue) ? "Yes" : "No");

    return 0;
}