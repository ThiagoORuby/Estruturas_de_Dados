#include <stdio.h>
#include <stdlib.h>

// PriorityNode
typedef struct {
    int priority;
    int position;
} PriorityNode;

// Static PriorityList functions

// create a priority list
PriorityNode * create_plist(int size)
{
    PriorityNode * plist = malloc(sizeof(PriorityNode) * size);
    PriorityNode end;
    end.position = '~';
    plist[0] = end;
    return plist;
}

// get length of a list
int len(PriorityNode * plist)
{
    int i = 0;
    while(plist[i].position != '~') i++;
    return i;
}

// find position of first occurence from a priority
int find_priority(PriorityNode * plist, int priority)
{
    int i = 0;
    while(plist[i].position != '~')
    {
        if(plist[i].priority == priority) return i;
        i++;
    }
}

// insert in the end of a plist
void insert(PriorityNode * plist, PriorityNode node)
{
    int i = 0;
    while(plist[i].position != '~') i++;
    plist[i + 1] = plist[i];
    plist[i] = node;
}

// drop a element by a position
void pop(PriorityNode * plist, int pos)
{
    while(plist[pos].position != '~')
    {
        plist[pos].position = plist[pos+1].position;
        plist[pos].priority = plist[pos+1].priority;
        pos++;
    }
}

// print priority list
void print_plist(PriorityNode * plist)
{
    int i = 0;
    while(plist[i].position != '~'){
        printf("position: %d priority: %d\n", plist[i].position, plist[i].priority);
        i++;
    }
}

PriorityNode * sort_priority(PriorityNode * plist, int count1, int count2, int count3)
{
    PriorityNode * aux = create_plist(len(plist));
    int l = len(plist);
    while(l > 0)
    {
        for(int j = 0; j < 2; j++) // priority for 1
        {
            if  (count1 > 0)
            {
                int pos = find_priority(plist, 1);
                //printf("pos1 = %d\n", plist[pos].position);
                insert(aux, plist[pos]);
                pop(plist, pos);
                count1--;
            }
        }
        for(int j = 0; j < 2; j++) // priority for 2
        {
            if  (count2 > 0)
            {
                int pos = find_priority(plist, 2);
                //printf("pos2 = %d\n", plist[pos].position);
                insert(aux, plist[pos]);
                pop(plist, pos);
                count2--;
            }
        }
        if  (count3 > 0) // priority for 3
        {
            int pos = find_priority(plist, 3);
            //printf("pos3 = %d\n", plist[pos].position);
            insert(aux, plist[pos]);
            pop(plist, pos);
            count3--;
        }
        l = len(plist);
    }
    return aux;
}

// main
int main()
{
    int n, pr, count1 = 0, count2 = 0, count3 = 0;
    scanf("%d", &n);
    PriorityNode * plist = create_plist(n + 1);
    for(int i = 0; i < n; i++)
    {
        PriorityNode node;
        scanf("%d", &node.priority);
        if (node.priority == 1) count1++;
        if (node.priority == 2) count2++;
        if (node.priority == 3) count3++;
        node.position = i;
        insert(plist, node);
    }

    print_plist(plist);
    printf("\nPriority Sort: \n");
    PriorityNode * new = sort_priority(plist, count1, count2, count3);
    print_plist(new);

    free(plist);
    return 0;
}