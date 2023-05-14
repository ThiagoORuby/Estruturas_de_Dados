#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stacks.h"

#define MAX_BOOKS 10
#define MAX_SIZE 40
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
        print_stacks_str(&((*lib)->bookcases[i]));
        printf("\n");
    }
}

////// MAIN FUNCTIONS //////

// read the file input formated
// return 0 -> read successfully
// return 1 -> ParamsError: num of bookcases not found
// return 2 -> EmptyLineError: empty line found
int read_input(Library ** lib)
{
    char line[MAX_BOOKS*MAX_SIZE + MAX_BOOKS + 2];
    int i = 0, j = 0, value;
    Stacks * sts = NULL;

    FILE *fp = fopen("input2.txt" , "r");

    fgets(line, sizeof(line), fp);

    // check error in line 0
    if(!isdigit(line[0])) return 1;

    // get num of bookcases and num of book spaces
    sscanf(line, "%d %d", &n, &m);

    // get the bookcases
    while(fgets(line, sizeof(line), fp))
    {
        if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
        if(line[0] == '/')
        {
            Stack * st = NULL;
            char *token = strtok(line, ",/\\");
            while (token != NULL) {
                push_str(&st, token);
                j++;
                token = strtok(NULL, ",/\\");
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

// sort the stack of unique values
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
                if(tolower(top_str(&st1)[0]) <= tolower(top_str(&st2)[0])) break;
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

// book1 < book2 ?
int order_check(char * book1, char * book2, int i)
{
    if(i > strlen(book1)) return 1;
    if(i > strlen(book2)) return 0;
    if(tolower(book1[i]) < tolower(book2[i])) return 1;
    if(tolower(book1[i]) > tolower(book2[i])) return 0;
    if(tolower(book1[i]) == tolower(book2[i]))
        return order_check(book1, book2, i + 1); 
}

void push_sorted(Stack ** st, char * name)
{
    Stack * aux = NULL;

    while(*st && order_check(top_str(st), name, 0))
    {
        push_str(&aux, pop_str(st));
    }

    push_str(st, name);

    while(aux)
    {
        push_str(st, pop_str(&aux));
    }
}

// add height to a unique stack
void add_unique(char * name)
{
    Stack * st;
    Stacks * aux = NULL;

    if(emptys(&uniques))
    {
        Stack * temp = NULL;
        push_str(&temp, name);
        pushs(&uniques, temp);
        return;
    }
    
    // if has an unique stack with the same first char, push in it
    st = tops(&uniques);
    while(!emptys(&uniques))
    {
        if(tolower(top_str(&st)[0]) == tolower(name[0])) break;
        pushs(&aux, pops(&uniques));
        st = tops(&uniques);
    }

    if(!emptys(&uniques))
    {
        push_sorted(&st, name);
        pops(&uniques);
        pushs(&uniques, st);
        while(!emptys(&aux)) pushs(&uniques, pops(&aux));
    }
    else
    {
        Stack * temp = NULL;
        push_str(&temp, name);
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

    while(!empty_lib(lib)) // percorre biblioteca
    {
        sts = pop_bk(lib);
        while(!emptys(&sts)) // percorre estante
        {
            st = pops(&sts);
            count++;
            while(!empty(&st)) // percorre prateleira
            {
                add_unique(pop_str(&st));
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
    printf("%d estantes com diferentes qntds de prateleiras, cada uma com %d espacos para livros\n\n| ", n, m);
    while(!emptys(&uniques))
    {
        Stack * st = pops(&uniques);
        while(!empty(&st))
        {
            if(k > m - 1)
            {
                k = 0;
                j++;
                printf("\n%s", (j < lim) ? "| " : "");
            }
            if(j >= lim)
            {
                j = 0;
                lim = pop(&shelves);
                printf("\n%s", (lim != -1) ? "| " : "");
            }
            printf("%s | ", pop_str(&st));
            k++;
        }
    }

    // print white spaces
    while(!empty(&shelves) || lim != -1)
    {
        if(k > m - 1)
        {
            k = 0;
            j++;
            printf("\n%s", (j < lim) ? "| " : "");
        }
        if(j >= lim)
        {
            j = 0;
            lim = pop(&shelves);
            printf("\n%s", (lim != -1) ? "| " : "");
            if(lim == -1) break;
        }
        printf("%svazio | ", "");
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
    print_stacks_str(&uniques);

    print_organized_lib();

    free(lib);
    return 0;
}