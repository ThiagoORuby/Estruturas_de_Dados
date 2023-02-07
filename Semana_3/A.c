// Sum of elements
#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

typedef struct node{
    int value;
    struct node * next;
} Node;

Node * create_vector()
{
    Node * head = (Node *) malloc(sizeof(Node));
    head->next = NULL;
    return head;
}

void insert_end(Node * head, int ele)
{
    Node * temp = (Node *) malloc(sizeof(Node));
    temp->value = ele;
    if((* head)->next == NULL)
    {
        temp->next = NULL;
        (* head)->next = temp;
    }
    while((* head)->next )
}



int main()
{
    int valor = 10;
    int * ponteiro = &valor;
    int ** pp = &ponteiro;

    printf("%p\n", &valor);
    printf("%p\n", &ponteiro);
    printf("%p\n", &(**pp));
    return 0;
}