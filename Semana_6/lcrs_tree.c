// LEFT-CHILD, RIGHT-SIBLING IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>

#define MAXT 100

typedef struct ntree
{
    char value;
    int parent;
    int left; // left child
    int right; // right sibling
} NTree;

// CREATE
void create_ntree(NTree tree[])
{
    tree[0].value = ' ';
    tree[0].parent = -1;
    tree[0].left = -1;
    tree[0].right = -1;
}

// FIND
char find_value(NTree tree[], char value)
{
    for(int i = 0; i < MAXT; i++)
    {
        if(tree[i].value == ' ') return -1; // se chegar ao final e nao tem nada, retorne -1
        if(tree[i].value == value) return i; // se encontrar, retorne a posição
    }
}

int find_parent(NTree tree[], int parent)
{
    for(int i = 0; i < MAXT; i++)
    {
        if(tree[i].parent == -1) return -1; // se chegar ao final e nao tem nada, retorne -1
        if(tree[i].parent == parent) return i; // se encontrar, retorne a posição
    }
}

int empty(NTree tree[])
{
    if (tree[0].value == ' ') return 1;
    return 0;
}

// INSERT -> PAI, ELEMENTO
void insert(NTree tree[], char value, char parent)
{
    if(empty(tree))
    {
        tree[0].value = value;
        tree[1].value = ' ';
        tree[1].parent = parent;
        return;
    }

    int pos_p = find_value(tree, parent);
    if(pos_p != -1)
    {
        int i = 0;
        for(i = 0; i < MAXT; i++) if(tree[i].value == ' ') break;
        if(i == MAXT - 1)
        {
            printf("NTree is full!!\n");
            return;
        }
        // add node at end of table
        tree[i].value = value;
        tree[i].parent = pos_p;
        tree[i].left = -1;
        tree[i].right = -1;
        // change the end of table
        if(i < MAXT - 1)
        {
            tree[i+1].value = ' ';
            tree[i+1].parent = -1;
        }
        // put the node as the first child of its parent 
        int aux = tree[pos_p].left;
        tree[pos_p].left = i;
        tree[i].right = aux;
    }
    else{
        printf("This fucking parent doesnt exists!!!!!\n");
    }
    
}

// PRINT
void print_tree(NTree tree[])
{
    printf("ID | VALUE | PARENT | LEFT | RIGHT\n");
    for(int i = 0; i < MAXT; i++)
    {
        if(tree[i].value == ' ') break;
        printf("%d | %c | %d | %d | %d\n", i, tree[i].value, tree[i].parent, tree[i].left, tree[i].right);
    }
}

// DELETE
void remove_row(NTree tree[], int index)
{
    while(tree[index].value != ' ')
    {
        tree[index] = tree[index+1];
        index++;
        for(int i = 0; tree[i].value != ' '; i++)
        {
            if(tree[i].left == index) tree[i].left--;
            if(tree[i].right == index) tree[i].right--;
            if(tree[i].parent == index) tree[i].parent--;
        }
    }
}

void recursive_remove(NTree tree[], int index)
{
    for(int i = 0; tree[i].value != ' '; i++)
    {
        if(tree[i].parent == index)
        {
            //printf("Find the child %c\n", tree[i].value);
            remove_row(tree, i);
            //print_tree(tree);
            recursive_remove(tree, i);
            i = i-1;
        }
        if(tree[i].left == index) tree[i].left = tree[index].right;
        if(tree[i].right == index) tree[i].right = tree[index].right;
    }
    return;
}

void delete(NTree tree[], char value)
{
    // find the value index
    int i;
    for(i = 0; tree[i].value != value; i++);

    // remove its descendents
    recursive_remove(tree, i);
    // remove it
    remove_row(tree, i);
    return;
}

// NB TREE EXAMPLE
/*
        A
    B   C   D
   G   E  F
*/

// PERCORRER
int tprint(NTree tree[], int root)
{
    if(tree[root].value == ' ') return printf("This structure is empty!\n");
    printf("%c(", tree[root].value);
    // checa os filhos
    (tree[root].left != -1 ) ? tprint(tree, tree[root].left) : printf(")");
    // checa os irmãos
    if (tree[root].parent != -1) 
    (tree[root].right != -1) ? tprint(tree, tree[root].right) : printf(")");
}

// EMPTY
// PERTENCE
// contido ou contido propriamente+
// UNIAO
// acrescenta os filhos de uma arvore a outra pelo pai em comum
// mensagem de erro ou acerto
// INTERSEÇÃO
// será o conjunto das subarvores que pertence as duas arvores de entrada

int main()
{
    NTree tree[MAXT];
    create_ntree(tree);
    insert(tree, 'A', -1);
    insert(tree, 'D', 'A');
    insert(tree, 'C', 'A');
    insert(tree, 'B', 'A');
    insert(tree, 'F', 'C');
    insert(tree, 'E', 'C');
    insert(tree, 'G', 'F');
    print_tree(tree);
    tprint(tree, 0);
    printf("\n\n");
    //delete(tree, 'D');
    delete(tree, 'B');
    //delete(tree, 'A');
    print_tree(tree);
    tprint(tree, 0);
    printf("\n");
    return 0;
}