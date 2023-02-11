#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * remove_first(char * string, char c)
{
    char * new = malloc(sizeof(char)*strlen(string));
    int k = 0, first = 0;
    for(int i = 0; i < strlen(string); i++)
    {
        if(string[i] == c && !first)
        {
            i++;
            first = 1;
        }

        new[k] = string[i];
        k++;
    }
    new[k] = '\0';
    return new;
}

int main()
{
    char c, string[999];

    printf("#### SEM A PRIMEIRA OCORRENCIA ####\n");
    printf("Digite uma string: ");
    scanf("%[^\n]", string);
    printf("Digite uma letra: ");
    scanf(" %c", &c);

    char * att = remove_first(string, c);
    printf("%s\n", att);

    free(att);
    return 0;
}