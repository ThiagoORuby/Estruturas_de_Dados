#include <stdio.h>

int main(){
    char str1[10] = {}, str2[10] = {};
    scanf("%s%s", str1, str2);
    for(int i = 0; i < 10; i++) if(str1[i] != str2[i]) return printf("As strings sao diferentes\n");
    return printf("As strings sao iguais\n"); }