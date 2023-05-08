// Queue
#include <stdio.h>
#include <stdlib.h>

typedef struct qnode{
    int value;
    struct qnode * next;
} QNode;

typedef struct queue{
    QNode * front;
    QNode * back;
} Queue;

QNode * create_node()
{
    QNode * node = malloc(sizeof(QNode));
    node->next = NULL;
    return node;
}

int empty(Queue ** queue)
{
    if((*queue) == NULL) return 1;
    return 0;
}

void push(Queue ** queue, int value)
{
    QNode * new = create_node();
    new->value = value;

    if(empty(queue))
    {
        *queue = malloc(sizeof(Queue));
        (*queue)->front = new;
        (*queue)->back = new;
    }
    else
    {
        (*queue)->back->next = new;
        (*queue)->back = new;
    }
}

int pop(Queue ** queue)
{
    if(empty(queue)) return -1;

    QNode * temp = (*queue)->front;
    (*queue)->front = temp->next;
    int value = temp->value;
    free(temp);
    return value;
}

int front(Queue ** queue)
{
    return (*queue)->front->value;
}

int back(Queue ** queue)
{
    return (*queue)->back->value;
}

void print_queue(Queue ** queue)
{
    QNode * temp = (*queue)->front;

    printf("| ");
    while(temp != NULL)
    {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("|\n");
}

int main()
{
    int arr[6] = {3, 4, 2, 5, 1, 5};
    Queue * queue = NULL;

    for(int i = 0; i < 6; i++)
    {
        push(&queue, arr[i]);
    }

    print_queue(&queue);
    printf("front: %d\n", front(&queue));
    printf("back: %d\n", back(&queue));
    printf("pop: %d\n", pop(&queue));
    printf("pop: %d\n", pop(&queue));
    push(&queue, 8);
    push(&queue, 11);
    printf("front: %d\n", front(&queue));
    printf("back: %d\n", back(&queue));
    print_queue(&queue);

    return 0;
}