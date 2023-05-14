#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINES 224
#define MAX_LEN 40

char * names_list[MAX_LINES];

void create_names_list()
{
    int i = 0;
    char line[MAX_LEN];
    FILE * fp = fopen("name_list.txt", "r");

    while(fgets(line, MAX_LEN, fp) && i < 224)
    {
        if(line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';

        names_list[i] = malloc(sizeof(line) + 1);
        strcpy(names_list[i], line);
        i++;
    }
}

void generate_book_input(int n_bc, int * shelves, int max_books)
{

    FILE * fp = fopen("input2.txt", "w");

    fprintf(fp, "%d %d\n", n_bc, max_books);

    for(int i = 0; i < n_bc; i++)
    {
        for(int j = 0; j < shelves[n_bc - 1]; j++)
        {
            int n_books = rand() % max_books;
            char * shelf = malloc(sizeof(char) * (MAX_LEN*n_books + n_books + 1));
            shelf[0] = '\0';
            for(int k = 0; k < n_books; k++)
            {
                const char * name = names_list[rand() % MAX_LINES];
                strcat(shelf, name);
                if(k < n_books - 1) strcat(shelf, ",");
            }

            if (shelf[0] != '\0')
            {
                printf("/%s\\\n", shelf);
                fprintf(fp, "/%s\\\n", shelf);
            }
        }
        printf("_\n");
        fprintf(fp, "_\n");
    }
}


int main()
{
    int num_bc, max_books, * arr;

    printf("Digite o numero de estantes e a quantidade de espaços para livro em cada prateleira: ");
    scanf("%d %d", &num_bc, &max_books);
    
    arr = malloc(sizeof(int)*num_bc);

    printf("\nAgora, para cada estante, digite o numero de prateleiras:\n");
    for(int i = 0; i < num_bc; i++)
    {
        scanf("%d", &arr[i]);
    }
    // initialize random
    srand(time(NULL));

    create_names_list();

    generate_book_input(num_bc, arr, max_books);
    return 0;
}