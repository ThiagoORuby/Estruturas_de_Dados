#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * remove_all(char * string, char c)
{
    char * new = malloc(sizeof(char)*strlen(string));
    int k = 0;
    for(int i = 0; i < strlen(string); i++)
    {
        if(string[i] != c)
        {
            new[k] = string[i];
            k++;
        }
    }
    new[k] = '\0';
    return new;
}

int main()
{
    char c, string[999];

    printf("#### SEM TODAS AS OCORRENCIAS ####\n");
    printf("Digite uma string: ");
    scanf("%[^\n]", string);
    printf("Digite uma letra: ");
    scanf(" %c", &c);

    char * att = remove_all(string, c);
    printf("%s\n", att);

    free(att);
    return 0;
}