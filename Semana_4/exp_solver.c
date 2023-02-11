/*
MATH EXPRESSION SOLVER WITH C USING STACKS
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// STACK FUNCTIONS
typedef struct snode{
    int value;
    struct snode * next;
} SNode;

// create
SNode * create_stack()
{
    SNode * head = malloc(sizeof(SNode));
    head->next = NULL;
    return head;
}

// push
void push(SNode * stack, int value)
{
    SNode * temp = malloc(sizeof(SNode));
    temp->value = value;
    temp->next = stack->next;
    stack->next = temp;
}

// pop
int pop(SNode * stack)
{
    SNode * temp = stack->next; // first element
    stack->next = temp->next; // stack to second element
    //printf("Pop last element: %d\n", temp->value);
    int value = temp->value;
    free(temp);
    return value;
}

// sprint
void sprint(SNode * stack)
{
    SNode * temp = stack->next;
    printf("(");
    while(temp != NULL)
    {
        printf("%d", temp->value);
        temp = temp->next;
        if(temp != NULL) printf(", ");
    }
    printf(")\n");
}

// cprint
void cprint(SNode * stack)
{
    SNode * temp = stack->next;
    printf("(");
    while(temp != NULL)
    {
        printf("%c", temp->value);
        temp = temp->next;
        if(temp != NULL) printf(", ");
    }
    printf(")\n");
}

// len
int len(SNode * stack)
{
    int count = 0;
    SNode * temp = stack->next;
    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

// top
int top(SNode * stack)
{
    return stack->next->value;
}

// empty
int empty(SNode * stack)
{
    if(stack->next == NULL) return 1;
    return 0;
}

// sfree
void sfree(SNode * stack)
{
    SNode * temp = stack;
    while(temp != NULL)
    {
        SNode * aux = temp;
        temp = temp->next;
        free(aux);
    }
}

void inverse_print(SNode * stack1, SNode * stack2)
{
    if(stack1 == NULL) return;

    inverse_print(stack1->next, (stack2 != NULL) ? stack2->next : NULL);

    if(stack2 != NULL) printf("%c ", stack2->value);
    printf("%d ", stack1->value);
}

// remove white spaces in a string
char * strip(char * string)
{
    int k = 0;
    char * striped = malloc(sizeof(char) * strlen(string));
    for(int i = 0; i < strlen(string); i++)
    {
        if(string[i] != ' ')
        {
            striped[k] = string[i];
            k++;
        }
    }
    return striped;
}

void print_string(char * string, int i)
{
    for(i; i < strlen(string); i++)
    {
        printf("%c", string[i]);
    }
}

// SOLVER CODE

// check priority
int check_priority(char old, char new)
{
    if((old == '+' || old == '-') && (new == '*' || new == '/')) return 1;
    return 0;
}

// solve binary operation
int operation(int value1, int value2, char op)
{
    printf("\nSolving: %d %c %d\n\n", value2, op, value1);
    if(op == '+') return value2 + value1;
    if(op == '-') return value2 - value1;
    if(op == '*') return value2*value1;
    if(op == '/') return value2/value1;
}

int get_num(char * exp, int * i)
{
    char aux[10];
    int k = 0;
    while(isdigit(exp[*i]))
    {
        aux[k] = exp[*i];
        k++;
        (*i)++;
    }
    aux[k] = '\0';
    int ret = atoi(aux);
    return ret;
}

// solver function
int solver(SNode * num_stack, SNode * op_stack, char * exp, char * string)
{
    int result = 0, i = 0;
    // iterating in math expression
    while(1)
    {
        if(i >= strlen(exp)) break; // if i >= length of expression, break loop
        int num = get_num(exp, &i); // get nums
        push(num_stack, num); // add number to numstack
        if(len(num_stack) >= 2 && len(op_stack) >= 1) // if has at least 2 nums and 1 op
        {
            if(check_priority(top(op_stack), exp[i])) // check priority operator
            {
                // if has priority, add op to opstack and continue
                push(op_stack, exp[i]);
                i++;
                continue;
            }
            else
            {
                // else, while has 2 nums and 1 op, solve it
                while(len(num_stack) >= 2 && len(op_stack) >= 1)
                {
                    //sprint(num_stack);
                    //cprint(op_stack);
                    int value1 = pop(num_stack);
                    int value2 = pop(num_stack);
                    result = operation(value1, value2, pop(op_stack)); // solve operation
                    push(num_stack, result); // add result to numstack
                    inverse_print(num_stack->next, op_stack->next);
                    print_string(exp, i);
                    printf("\n");
                    //printf("result: %d\n", result);
                    //printf("next op = %c\n", exp[i]);
                    if(!empty(op_stack))
                        if(check_priority(top(op_stack), exp[i])) break; 
                        // if next op has priority, break and get op
                }
            }
        }
        push(op_stack, exp[i]); // add operator to opstack
        i++;
    }
    return result;
}

int main()
{
    char string[100];
    int result;
    SNode * num_stack = create_stack(); // number stack
    SNode * op_stack = create_stack(); // operator stack
    
    scanf("%[^\n]", string);

    char * striped = strip(string);
    result = solver(num_stack, op_stack, striped, string);

    printf("\n%s = %d", string, result);

    sfree(num_stack);
    sfree(op_stack);
    return 0;
}