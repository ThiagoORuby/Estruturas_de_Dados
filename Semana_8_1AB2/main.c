#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stacks.h"

#define MAX_BOOKS 10
#define MAX_shelves 6
#define MAX_BOOKCASES 10

// n -> num of bookcases
// m -> num of book per shelves
int n, m;
Stacks * uniques = NULL; // stacks of unique values
Stack * shelves = NULL; // stacks of shelves quantity

// library< bookcase < shelf < book > >

/////// LIBRARY ///////
typedef struct library{
    Stacks ** bookcases;
    int top;
} Library;

// init Library (stack of stacks of stacks)
void init_library(Library ** lib)
{
    Stacks ** bookcases = malloc(sizeof(Stacks)*MAX_BOOKCASES);
    for(int i = 0; i < MAX_BOOKCASES; i++) bookcases[i] = NULL;

    (*lib)->bookcases = bookcases;
    (*lib)->top = -1;
}

// check if library is empty
int empty_lib(Library ** lib)
{
    if((*lib)->top == -1) return 1;
    return 0;
}

// push a bookcase (stack of stacks) to a library
void push_bk(Library ** lib, Stacks * bookcase)
{
    (*lib)->bookcases[(*lib)->top + 1] = bookcase;
    (*lib)->top++;
}

// pop a bookcase (stack of stacks) from a library
Stacks * pop_bk(Library ** lib)
{
    if(empty_lib(lib)) return NULL;

    Stacks * temp = (*lib)->bookcases[(*lib)->top];
    (*lib)->top--;
    return temp; 
}

// print the library
void print_lib(Library ** lib)
{
    for(int i = (*lib)->top; i >= 0; i--)
    {
        print_stacks(&((*lib)->bookcases[i]));
        printf("\n");
    }
}

////// MAIN FUNCTIONS //////

// read the file input formated
// return 0 -> read successfully
// return 1 -> ParamsError: num of bookcases not finded
// return 2 -> EmptyLineError: empty line finded
int read_input(Library ** lib)
{
    char line[MAX_BOOKS*2 + 2];
    int i = 0, j = 0, value;
    Stacks * sts = NULL;

    FILE *fp = fopen("input.txt" , "r");

    fgets(line, sizeof(line), fp);

    if(!isdigit(line[0])) return 1;

    sscanf(line, "%d %d", &n, &m);

    while(fgets(line, sizeof(line), fp))
    {
        if(line[0] == '/')
        {
            Stack * st = NULL;
            char *token = strtok(line, " /\n");
            while (token != NULL) {
                push(&st, atoi(token));
                j++;
                token = strtok(NULL, " /\n");
            }
            i++;
            j = 0;
            pushs(&sts, st);
        }
        else if(line[0] == '_')
        {
            push_bk(lib, sts);
            sts = NULL;
            i = 0; j = 0;
        }
        else return 2;
    }

    print_lib(lib);
    return 0;
}

// sort the stack of unique valuess
void sort_uniques()
{
    Stacks * temp = NULL, * aux = NULL;

    while(!emptys(&uniques))
    {
        if(!emptys(&temp))
        {
            Stack * st1 = pops(&uniques); // uniques top
            Stack * st2 = tops(&temp); // temp top
            while(!emptys(&temp))
            {
                if(top(&st1) <= top(&st2)) break;
                pushs(&aux, pops(&temp));// add aux temp top
                st2 = tops(&temp); // update st2;
            }

            pushs(&temp, st1); // push unique top stack
            while(!emptys(&aux)) pushs(&temp, pops(&aux)); // push other stacks

        }
        else
        {
            pushs(&temp, pops(&uniques));
        }
    }

    uniques = temp;
}

// add height to a unique stack
void add_unique(int height)
{
    Stack * st;
    Stacks * aux = NULL;

    if(emptys(&uniques))
    {
        Stack * temp = NULL;
        push(&temp, height);
        pushs(&uniques, temp);
        return;
    }
    
    // if has an unique stack with this value, push in it
    st = tops(&uniques);
    while(!emptys(&uniques))
    {
        //printf("top: %d, height: %d\n", top(&st), height);
        if(top(&st) == height) break;
        pushs(&aux, pops(&uniques));
        st = tops(&uniques);
    }

    if(!emptys(&uniques))
    {
        push(&st, height);
        pops(&uniques);
        pushs(&uniques, st);
        while(!emptys(&aux)) pushs(&uniques, pops(&aux));
    }
    else
    {
        Stack * temp = NULL;
        push(&temp, height);
        uniques = aux;
        pushs(&uniques, temp);
    }

}

// Generate stack of uniques and save num of shelves per bookcase
void unique_stacks(Library ** lib)
{
    int count = 0;
    Stacks * sts;
    Stack * st;

    while(!empty_lib(lib))
    {
        sts = pop_bk(lib);
        while(!emptys(&sts))
        {
            st = pops(&sts);
            count++;
            while(!empty(&st))
            {
                add_unique(pop(&st));
            }
        }
        push(&shelves, count);
        count = 0;
    }
}

// print the organized library
void print_organized_lib()
{
    int i = 0, j = 0, k = 0;
    int lim = pop(&shelves);
    printf("\n\nBIBLIOTECA ORGANIZADA:\n");
    printf("%d estantes com diferentes qntds de prateleiras, cada uma com %d espacos para livros\n\n", n, m);
    while(!emptys(&uniques))
    {
        Stack * st = pops(&uniques);
        while(!empty(&st))
        {
            if(k > m - 1)
            {
                printf("\n");
                k = 0;
                j++;
            }
            if(j >= lim)
            {
                printf("\n");
                j = 0;
                lim = pop(&shelves);
            }
            printf("%d ", pop(&st));
            k++;
        }
    }

    // print white spaces
    while(!empty(&shelves) || lim != -1)
    {
        if(k > m - 1)
        {
            printf("\n");
            k = 0;
            j++;
        }
        if(j >= lim)
        {
            printf("\n");
            j = 0;
            lim = pop(&shelves);
            if(lim == -1) break;
        }
        printf("0 ");
        k++;
    }
}

// main function
int main()
{
    int out;
    // init library
    Library * lib = malloc(sizeof(Library));
    init_library(&lib);
    
    // read the input file
    out = read_input(&lib);

    if(out == 1) return printf("ParamsError: num of bookcases not finded.");
    else if(out == 2) return printf("EmptyLineError: empty line finded.");

    printf("n = %d, m = %d\n", n, m);

    // generate unique stacks
    unique_stacks(&lib);
    sort_uniques();

    printf("Unique stacks:\n");
    print_stacks(&uniques);

    print_organized_lib();

    free(lib);
    return 0;
}