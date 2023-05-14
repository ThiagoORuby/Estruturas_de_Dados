#ifndef LIST_H
#define LIST_H

#define TRUE 1
#define FALSE 0
#define BOOL int 

typedef struct list
{
    int value;
    struct list * next;
} List;


List * create_node();
int isempty(List ** list);
void append(List ** list, int value);
void pop(List ** list);
void remove_first(List ** list, int value);
void lfree(List ** list);
void lprint(List ** list);
int len(List ** list);


#endif //LIST_H