#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node * left;
    struct node * right;
} Node;


Node * create_node()
{
    Node * root = malloc(sizeof(Node));
    root->value = -1;
    root->left = NULL;
    root->right = NULL; 
    return root;
}

void add_sorted(Node * root, int value)
{
    if(root->value == -1)
    {
        root->value = value;
        printf("add %d\n", value);
        return;
    }
    if(value <= root->value)
    {
        printf("entrei esqd\n");
        if(root->left == NULL)
        {
            Node * new = malloc(sizeof(Node));
            new->left = NULL; new->right = NULL;
            new->value = value;
            root->left = new;
            printf("add %d\n", value);
            return;
        }
        add_sorted(root->left, value);
    }
    if(value > root->value)
    {
        printf("entrei dir\n");
        if(root->right == NULL)
        {
            Node * new = malloc(sizeof(Node));
            new->left = NULL; new->right = NULL;
            new->value = value;
            root->right = new;
            printf("add %d\n", value);
            return;
        }
        add_sorted(root->right, value);
    }
}

void inorder(Node * root)
{
    if(root == NULL) return;
    inorder(root->left);
    printf("%d ", root->value);
    inorder(root->right);
}


int main()
{
    int aux;
    Node * root = create_node();

    while(scanf("%d", &aux) == 1)
    {
        add_sorted(root, aux);
    }

    inorder(root);
    //printf("%d\n", root->right->right->value);

    return 0;
}