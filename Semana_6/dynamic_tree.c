// ARRAY BASED DYNAMIC TREE
#include <stdio.h>
#include <stdlib.h>

#define MAXN 20

typedef struct node
{
    char value;
    int size;
    struct node ** children; // array[size] of children
} Node;

// create a new node
Node * create_node(char value, int size)
{
    Node * node = malloc(sizeof(Node));
    node->value = value;
    node->size = size;
    node->children = malloc(sizeof(Node *)* size); // n ponteiros para filhos
    node->children[0] = NULL; // sem filhos
    return node;
}

// check if the tree is empty
int empty(Node * root)
{
    if(root == NULL) return 1;
    return 0;
}

// insert an element in a tree
void insert(Node * root, char value, int size, char parent)
{
    if(root->value == parent)
    {
        int i = 0;
        Node * child = create_node(value, size);
        while(root->children[i] != NULL) i++;
        root->children[i] = child;
        root->children[++i] = NULL;
        return;
    }
    
    for(int i = 0; root->children[i] != NULL; i++)
    {
        insert(root->children[i], value, size, parent);
    }

    return;

}

// delete a subtree
void delete(Node * root, char value)
{
    //printf("(root = %c, value = %c)\n", root->value, value);
    if(root->value == value)
    {
        for(int i = 0; root->children[i] != NULL; i++)
        {
            delete(root, root->children[i]->value);
        }
        for(int i = 0; root->children[i] != NULL; i++){
            free(root->children[i]);
            root->children[i] = NULL;
        }
        return;
    }

    for(int i = 0; root->children[i] != NULL; i++)
    {
        delete(root->children[i], value);
    }
    return;
}

void print_tree(Node * root)
{
    //if(root->children[0] == NULL) return;
    printf("%c(", root->value);
    for(int i = 0; root->children[i] != NULL; i++)
        print_tree(root->children[i]);
    printf(")");
}

int main()
{
    Node * root = create_node('C', 5);
    // C children
    insert(root, 'A', 5, 'C');
    insert(root, 'B', 5, 'C');
    insert(root, 'D', 5, 'C');
    // A children
    insert(root, 'S', 5, 'A');
    insert(root, 'E', 5, 'A');

    printf("is empty? %d\n", empty(root));

    print_tree(root);
    printf("\n");
    delete(root, 'A');
    print_tree(root);

    printf("\n");

    return 0;
}