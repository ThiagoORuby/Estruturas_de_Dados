#include <stdio.h>
#include <string.h>

int hasin(char * string, char c)
{
    for(int i = 0; i < strlen(string); i++)
    {
        if(string[i] == c) return 1;
    }
    return 0;
}

int main()
{
    char c, string[999];

    printf("#### ESTA NA STRING? ####\n");
    printf("Digite uma string: ");
    scanf("%[^\n]", string);
    printf("Digite uma letra: ");
    scanf(" %c", &c);

    printf("%s\n",hasin(string, c) ? "Yes" : "No");

    return 0;
}