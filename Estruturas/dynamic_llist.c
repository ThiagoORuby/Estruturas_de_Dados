#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union data{
    int i;
    double d;
    char c;
    char s[20];
} Data;

typedef struct list{
    Data value;
    struct list * next;
} List;

List * create_node()
{
    List * node = malloc(sizeof(List));
    node->next = NULL;
    return node;
}

int empty(List ** list)
{
    if((*list) == NULL) return 1;
    return 0;
}

void append(List ** list, void * value, char type)
{
    List * aux;
    List * new = create_node();

    switch (type)
    {
        case 'i':
            new->value.i = *(int *) value;
            break;
        case 'd':
            new->value.d = *(double *) value;
            break;
        case 'c':
            new->value.c = *(char *) value;
            break;
        case 's':
            strcpy(new->value.s, (char *) value);
            break;
        default:
            return (void) printf("TypeError: type not finded.\n");
    }

    if(empty(list))
    {

    }
    
}