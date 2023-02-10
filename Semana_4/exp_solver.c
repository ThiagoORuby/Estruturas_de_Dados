/*
MATH EXPRESSION SOLVER WITH C USING STACKS
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

// solver function


int main()
{
    char string[20];
    scanf("%[^\n]", string);

    printf("%s", strip(string));

    return 0;
}