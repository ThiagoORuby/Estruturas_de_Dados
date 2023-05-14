// LEFT CHILD & RIGTH SIBLING DYNAMIC TREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct
typedef struct node{
    char value;
    struct node * lchild;
    struct node * rsibling;
} Node;

// create
Node * create_node(char value)
{
    Node * node = malloc(sizeof(Node));
    node->value = value;
    node->lchild = NULL;
    node->rsibling = NULL;
    return node;
}

// find
Node * find(Node * root, char value)
{
    if(root == NULL) return NULL;
    if(root->value == value) return root;

    if(root != NULL)
        return find(root->lchild, value);
    if(root != NULL)
        return find(root->rsibling, value);
    
    return NULL;
}

Node * find_parent(Node * root, char value)
{
    if(root == NULL) return NULL;
    Node * temp = root;

    if(temp->lchild->value == value) return temp;

    temp = temp->lchild; // pego o primeiro filho

    while(temp != NULL) // vou percorrendo todos os filhos
    {
        if(temp->value == value) return root;
        temp = temp->rsibling;
    }

    if(root != NULL)
        return find_parent(root->lchild, value);
    if(root != NULL)
        return find_parent(root->rsibling, value);

    return NULL;
}

// insert
void insert(Node * root, char value, char parent)
{
    Node * finded = find(root, parent);

    if(finded == NULL) return (void) printf("Pai nao encontrado!\n");

    Node * new = create_node(value);

    if(finded->lchild == NULL)
    {
        finded->lchild = new;
        return;
    }
    finded = finded->lchild;

    while(finded->rsibling != NULL)
    {
        finded = finded->rsibling;
    }

    finded->rsibling = new;
    return;
}

void free_tree(Node * root)
{
    if(root == NULL) return;

    if(root != NULL) free_tree(root->lchild);
    if(root != NULL) free_tree(root->rsibling);

    free(root);
}

// remove
void remove_node(Node * root, char value)
{
    Node * temp,* temp2;
    Node * finded = find_parent(root, value);

    if(finded == NULL) return (void) printf("No nao encontrado!\n");

    if(finded->lchild->value == value)
    {
        temp = finded->lchild;
        finded->lchild = temp->rsibling;
        temp->rsibling = NULL;
    }
    else
    {
        temp2 = finded->lchild;
        while(temp2->rsibling->value != value)
        {
            temp2 = temp2->rsibling;
        }

        temp = temp2->rsibling;
        temp2->rsibling = temp->rsibling;
        temp->rsibling = NULL;
    }
    
    return;
    free_tree(temp);
}

// tprint
void tprint(Node * root)
{
    if(root == NULL) return;
    printf("%c", root->value);
    if(root != NULL)
    {
        printf("(");
        tprint(root->lchild);
        printf(")");
    }
    if(root != NULL)
        tprint(root->rsibling);
}

// equal
int isequal(Node * root1, Node * root2)
{
    if(root1 == NULL && root2 == NULL)
        return 1;
    if(root1 == NULL || root2 == NULL)
        return 0;
    if(root1->value != root2->value) return 0;

    Node * child1 = root1->lchild;
    Node * child2 = root2->lchild;
    while(child1 != NULL && child2 != NULL)
    {
        if(!isequal(child1, child2)) return 0;
        child1 = child1->rsibling;
        child2 = child2->rsibling;
    }

    if(child1 != NULL || child2 != NULL) return 0; // deixar comentado se for subset
    return 1;
}

// subset
// root1 is subset of root2
int subset(Node * root1, Node * root2)
{
    if(isequal(root1, root2)) return 0;

    Node * finded = find(root2, root1->value);

    if(finded == NULL) return 0;

    if(isequal(finded, root1)) return 1;

    return 0;
}

// subset equal
int subset_equal(Node * root1, Node * root2)
{
    Node * finded = find(root2, root1->value);

    if(finded == NULL) return 0;

    if(isequal(finded, root1)) return 1;

    return 0;
}

// union
// une a root2 na root1
int union_trees(Node * root1, Node * root2)
{
    if(root1 == NULL || root2 == NULL || find(root1, root2->value) == NULL) return 0;

    Node * finded = find(root1, root2->value);

    finded = finded->lchild;

    while(finded->rsibling != NULL) finded = finded->rsibling;

    finded->rsibling = root2->lchild;

    return 1;
}

// intersect
Node * intersect(Node * root1, Node * root2)
{
    Node * node_int = create_node(root1->value);
    Node * child = root1->lchild;
    while(child != NULL)
    {
        //printf("finded %c: %d\n", child->value, !(find(root2, child->value) == NULL));
        if(find(root2, child->value) != NULL)
        {
            Node * child_int = intersect(child, root2);
            insert(node_int, child_int->value, node_int->value);
        }
        child = intersect(child->lchild, root2);
        child = child->rsibling;
    }

    return  node_int;   
}

// complemento
Node * complement(Node * root1, Node * root2)
{
    Node * node_comp = create_node(root1->value);
    Node * child = root1->lchild;
    while(child != NULL)
    {
        printf("finded %c: %d\n", child->value, !(find(root2, child->value) == NULL));
        if(find(root2, child->value) == NULL)
        {
            Node * child_comp = complement(child, root2);
            insert(node_comp, child_comp->value, node_comp->value);
        }
        child = child->rsibling;
    }

    return  node_comp;
}

int main()
{
    Node * root = create_node('B');
    Node * root2 = create_node('B');

    
    insert(root, 'F', 'B');
    insert(root, 'G', 'B');
    insert(root, 'I', 'B');

    insert(root2, 'F', 'B');
    insert(root2, 'G', 'B');
    

    //printf("parent of C = %c\n", find_parent(root, 'C')->value);

    printf("root1: \n");
    tprint(root);

    printf("\nroot2: \n");
    tprint(root2);

    printf("\nis equal? %d\n", isequal(root, root2));
    printf("is subset? %d\n", subset(root2, root));
    printf("is subset or equal? %d\n", subset_equal(root2, root));

    //printf("join 2 trees...\n");
    //union_trees(root, root2);
    //printf("root1: \n");
    //tprint(root);

    Node * comp = complement(root, root2);
    tprint(comp);
    printf("\n");
    //Node * inter = intersect(root, root2);
    //tprint(inter);

    return 0;
}