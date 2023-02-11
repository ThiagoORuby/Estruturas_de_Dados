#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int hasin(char * string, char c)
{
    for(int i = 0; i < strlen(string); i++)
    {
        if(string[i] == c) return 1;
    }
    return 0;
}

char * just_first(char * string)
{
    char * new = malloc(sizeof(char)*strlen(string));
    strcpy(new, "~");
    int k = 0;
    for(int i = 0; i < strlen(string); i++)
    {
        if(!hasin(new, string[i]))
        {
            new[k] = string[i];
            new[k+1] = '\0';
            k++;
        }
    }
    new[k] = '\0';
    return new;
}


int main()
{
    char c, string[999];

    printf("####  APENAS PRIMEIRAS OCORRENCIAS ####\n");
    printf("Digite uma string: ");
    scanf("%[^\n]", string);

    char * att = just_first(string);
    printf("%s\n", att);

    free(att);
    return 0;
}