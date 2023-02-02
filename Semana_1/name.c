/*
- check if the string has only letters
- check if the string is no null
- check if the string dont begins with uppercase or space
*/

#include<stdio.h>
#include <string.h>

#define MAX 1000

int checkValidate(char name[]){
    printf("checking: %s with length %d\n", name, strlen(name));
    // check name length
    if (strlen(name) == 0) return 0;
    // check first letter
    if (name[0] < 65 || name[0] > 90) return 0;
    for(int i = 1; i < strlen(name); i++)
    {
        // check each char
        if(name[i] < 97 || name[i] > 122) return 0;
    }
    return 1;
}

int split(char name[], char splited[][MAX]){
   int i = 0;
   char * token = strtok(name, " ");
   while (token != NULL){
       //printf("%s \n", token);
       strcpy(splited[i], token);
       token = strtok(NULL, " ");
       i++;
   }
   return i;
}

int nameValidate(char name[]){
    int validate = 1;
    char splited[10][MAX], copy_name[MAX];
    strcpy(copy_name, name);
    int k = split(copy_name, splited);
    // for each name in the complete name check if it valid
    for(int i = 0; i < k; i++){
        if (!checkValidate(splited[i])) return 0;
    }
    return 1;
}

int main(){
    // a-z 97 - 122
    // A-Z 65 - 90
    char name[1000];
    scanf("%[^\n]", name);
    if (nameValidate(name)){
        printf("\n%s is a valid name\n", name);
    }else
    {
        printf("\n%s is a invalid name\n", name);
    }
    return 1;
}