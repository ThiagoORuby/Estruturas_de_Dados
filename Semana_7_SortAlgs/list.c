#include "list.h"
#include <stdio.h>
#include <stdlib.h>


List * create_node()
{
    List * node = malloc(sizeof(List));
    node->next = NULL;
    return node;
}

BOOL isempty(List ** list)
{
    if(*list == NULL) return TRUE;
    return FALSE;
}

void append(List ** list, int value)
{
    List * temp = create_node();
    temp->value = value;

    if(isempty(list))
    {
        *list = temp;
        return;
    }

    List * aux = *list;
    while(aux->next != NULL)
    {
        aux = aux->next;
    }

    aux->next = temp;
}

void pop(List ** list)
{
    List * temp = *list;
    *list = temp->next;
    free(temp);
}

void remove_first(List ** list, int value)
{
    if(isempty(list)) return;

    if((*list)->value == value)
    {
        *list = (*list)->next;
        return;
    }

    List * aux = *list;

    // remove at the middle of list
    while(aux->next != NULL)
    {
        if(aux->next->value == value) break;
        aux = aux->next;
    }

    // remove at the end of list
    if(aux->next == NULL)
    {
        if(aux->value == value) *list = NULL;
        return;
    }

    List * temp = aux->next;
    aux->next = temp->next;
    free(temp);
}

void lfree(List ** list)
{
    if(isempty(list)) return;

    List * temp = *list;
    while(temp != NULL)
    {
        List * aux = temp;
        temp = temp->next;
        free(aux);
    }
}

void lprint(List ** list)
{
    List * temp = *list;
    while(temp->next != NULL)
    {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("%d\n", temp->value);
}

int len(List ** list)
{
    int counter = 0;
    List * temp = *list;

    while(temp != NULL)
    {
        counter++;
        temp = temp->next;
    }

    return counter;
}