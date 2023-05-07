#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ITEM char
#define TAM 50

typedef struct pilha {
    ITEM vet[TAM];
    int topo;
} TPilha;

void create(TPilha *p) {
    p->topo = -1;
}

void destroy(TPilha *p) {
    p->topo = -1;
}

int isfull(TPilha *p) {
    return p->topo == TAM;
}

int isempty(TPilha *p) {
    return p->topo == -1;
}

void push(TPilha *p, ITEM x) {
    if( isfull(p) ) {
        puts("overflow");
        abort();
    }
    p->topo++;
    p->vet[p->topo] = x;
}

ITEM pop(TPilha *p) {
    if( isempty(p) ) {
        puts("underflow");
        abort();
    }
    ITEM x = p->vet[p->topo];
    p->topo--;
    return x;
}

ITEM top(TPilha *p) {
    if( isempty(p) ) {
        puts("underflow");
        abort();
    }
    return p->vet[p->topo];
}

int palindromo(char s[]) {
    int n = 0;
    char * temp = s;
    while (*temp != '\0'){
        n++;
        temp++;
    }
    
    TPilha *pilha = malloc(sizeof(TPilha));
    create(pilha);

    for(int i = 0; i < n/2 + (n % 2 != 0); i++)
        push(pilha, s[i]);

    for(int i = n/2; i < n; i++)
    {
        if(!isempty(pilha) && top(pilha) == s[i]) pop(pilha);
    }

    return isempty(pilha);
}

int main(void) {
    char palavra[TAM];

    scanf("%s", palavra);
    printf(palindromo(palavra) ? "sim" : "nao");

    return 0;
}