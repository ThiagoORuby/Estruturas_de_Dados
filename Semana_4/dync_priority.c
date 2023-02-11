// Dynamic priority linked list
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct lnode{
    int priority;
    int position;
    struct lnode * next;
} LNode;

// functions to priority linked list

// create
LNode * create_plist()
{
    LNode * begin = malloc(sizeof(LNode));
    begin->next = NULL;
    return begin;
}

// push_back
void push_back(LNode * plist, int priority, int position)
{
    LNode * temp = plist;
    while(temp->next != NULL) temp = temp->next;
    LNode * lnode = malloc(sizeof(LNode));
    lnode->priority = priority;
    lnode->position = position;
    lnode->next = temp->next;
    temp->next = lnode;
}

// pop
void pop_next(LNode * position)
{
    LNode * temp = position->next;
    position->next = temp->next;
    free(temp);
}

// len
int len(LNode * plist)
{
    int i = 0;
    LNode * temp = plist->next;
    while(temp != NULL)
    {
        i++;
        temp = temp->next;
    }
    return i;
}

// lprint
void lprint(LNode * plist)
{
    LNode * temp = plist->next;
    while(temp != NULL)
    {
        printf("position = %d, priority = %d\n", temp->position, temp->priority);
        temp = temp->next;
    }
}

// find_priority
LNode * find_priority_parent(LNode * plist, int priority)
{
    LNode * temp = plist;
    while(temp != NULL)
    {
        if(temp->next->priority == priority) break;
        temp = temp->next;
    }
    return temp;
}

// lfree
void lfree(LNode * plist)
{
    LNode * temp = plist;
    while(temp != NULL)
    {
        LNode * aux = temp;
        temp = temp->next;
        free(aux);
    }
}

// sort by priority 1 1 2 2 3
LNode * sort_priority(LNode * plist, int count1, int count2, int count3)
{
    LNode * sorted = create_plist();
    while(len(plist) != 0)
    {
        for(int i = 0; i < 2; i++) // priority 1
        {
            if(count1 > 0)
            {
                LNode * temp = find_priority_parent(plist, 1);
                push_back(sorted, temp->next->priority, temp->next->position);
                pop_next(temp);
                count1--;
            }
        }
        for(int i = 0; i < 2; i++) // priority 2
        {
            if(count2 > 0)
            {
                LNode * temp = find_priority_parent(plist, 2);
                push_back(sorted, temp->next->priority, temp->next->position);
                pop_next(temp);
                count2--;
            }
            
        }
        if(count3 > 0)
        {
            LNode * temp = find_priority_parent(plist, 3);
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
    LNode * plist = create_plist();

    while(scanf("%d", &aux) == 1)
    {
        if(aux < 1 || aux > 3)
        {
            printf("The Priority is a number in the range [1,3]! Try again:\n");
            continue;
        }
        push_back(plist, aux, i);
        if(aux == 1) count1++;
        if(aux == 2) count2++;
        if(aux == 3) count3++;
        i++;
    }

    lprint(plist);
    time_t init = time(NULL);
    LNode * sorted = sort_priority(plist, count1, count2, count3);
    printf("\ntime: %f seconds\n", time(NULL) - init);
    printf("\n");
    lprint(sorted);

    lfree(plist);
    lfree(sorted);
    return 0;
}