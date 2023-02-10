// Dynamic priority queue
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct qnode{
    int priority;
    int position;
    struct qnode * next;
} QNode;

// functions to priority queue

// create
QNode * create_pqueue()
{
    QNode * begin = malloc(sizeof(QNode));
    begin->next = NULL;
    return begin;
}

// push_back
void push_back(QNode * pqueue, int priority, int position)
{
    QNode * temp = pqueue;
    while(temp->next != NULL) temp = temp->next;
    QNode * qnode = malloc(sizeof(QNode));
    qnode->priority = priority;
    qnode->position = position;
    qnode->next = temp->next;
    temp->next = qnode;
}

// pop
void pop_next(QNode * position)
{
    QNode * temp = position->next;
    position->next = temp->next;
    free(temp);
}

// len
int len(QNode * pqueue)
{
    int i = 0;
    QNode * temp = pqueue->next;
    while(temp != NULL)
    {
        i++;
        temp = temp->next;
    }
    return i;
}

// qprint
void qprint(QNode * pqueue)
{
    QNode * temp = pqueue->next;
    while(temp != NULL)
    {
        printf("position = %d, priority = %d\n", temp->position, temp->priority);
        temp = temp->next;
    }
}

// find_priority
QNode * find_priority_parent(QNode * pqueue, int priority)
{
    QNode * temp = pqueue;
    while(temp != NULL)
    {
        if(temp->next->priority == priority) break;
        temp = temp->next;
    }
    return temp;
}

// qfree
void qfree(QNode * pqueue)
{
    QNode * temp = pqueue;
    while(temp != NULL)
    {
        QNode * aux = temp;
        temp = temp->next;
        free(aux);
    }
}

// sort by priority 1 1 2 2 3
QNode * sort_priority(QNode * pqueue, int count1, int count2, int count3)
{
    QNode * sorted = create_pqueue();
    while(len(pqueue) != 0)
    {
        for(int i = 0; i < 2; i++) // priority 1
        {
            if(count1 > 0)
            {
                QNode * temp = find_priority_parent(pqueue, 1);
                push_back(sorted, temp->next->priority, temp->next->position);
                pop_next(temp);
                count1--;
            }
        }
        for(int i = 0; i < 2; i++) // priority 2
        {
            if(count2 > 0)
            {
                QNode * temp = find_priority_parent(pqueue, 2);
                push_back(sorted, temp->next->priority, temp->next->position);
                pop_next(temp);
                count2--;
            }
            
        }
        if(count3 > 0)
        {
            QNode * temp = find_priority_parent(pqueue, 3);
            push_back(sorted, temp->next->priority, temp->next->position);
            pop_next(temp);
            count3--;
        }
    }
    return sorted;
}

int main()
{
    int aux, i = 0, count1 = 0, count2 = 0, count3 = 0;
    QNode * pqueue = create_pqueue();

    while(scanf("%d", &aux) == 1)
    {
        push_back(pqueue, aux, i);
        if(aux == 1) count1++;
        if(aux == 2) count2++;
        if(aux == 3) count3++;
        i++;
    }

    qprint(pqueue);
    time_t init = time(NULL);
    QNode * sorted = sort_priority(pqueue, count1, count2, count3);
    printf("\ntime: %f seconds\n", time(NULL) - init);
    printf("\n");
    qprint(sorted);

    qfree(pqueue);
    qfree(sorted);
    return 0;
}