#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char value;
    struct node * right;
    struct node * left;
} Node;

Node * create_node(char value)
{
    Node * root = malloc(sizeof(Node));
    root->value = value;
    root->left = NULL;
    root->right = NULL;
    return root;  
}

void preorder(Node * root)
{
    if(root == NULL) return;
    printf("%c", root->value);
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node * root)
{
    if(root == NULL) return;
    inorder(root->left);
    printf("%c", root->value);
    inorder(root->right);
}

void postorder(Node * root)
{
    if(root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c", root->value);
}

/*
TREE EXAMPLE
        A
    B       C
  K   D   E   F
         G   H I
*/

int main()
{
    // tree example 1
    // A B C D E F G H I
    Node * root = create_node('A');
    root->left = create_node('B');
    root->right = create_node('C');
    root->left->left = create_node('K');
    root->left->right = create_node('D');
    root->right->left = create_node('E');
    root->right->right = create_node('F');
    (root->right->left)->left = create_node('G');
    (root->right->right)->left = create_node('H');
    (root->right->right)->right = create_node('I');

    // tree exemple 2
    // 2 * 3 + 5 - 4
    Node * root2 = create_node('+');
    root2->left = create_node('*');
    root2->right = create_node('-');
    root2->left->left = create_node('2');
    root2->left->right = create_node('3');
    root2->right->left = create_node('5');
    root2->right->right = create_node('4');

    Node * trees[2] = {root, root2};

    // Printing tree
    for(int i = 0; i < 2; i++)
    {
        printf("TREE %d: \n", i+1);
        printf("Preorder: ");
        preorder(trees[i]);
        printf("\n");
        printf("Inorder: ");
        inorder(trees[i]);
        printf("\n");
        printf("Postorder: ");
        postorder(trees[i]);
        printf("\n\n");
    }


    return 0;
}