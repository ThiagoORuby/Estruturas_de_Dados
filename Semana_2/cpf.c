#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 20

// remove todos os caracteres que nao sejam numeros
char * get_nums(char * string)
{
    char * new_string = malloc(MAXN * sizeof(char));
    int k = 0;

    for(int i = 0; i < strlen(string); i++){
        if(string[i] >= '0' && string[i] <= '9'){
            new_string[k] = string[i];
            k++;
        }
    }
    new_string[k] = '\0';

    return new_string;
}

// valida o CPF
int validate(char * cpf){
    
    // checa o tamanho
    int len = strlen(cpf);
    if (len < 11 || len > 11) return 0;
    
    // se todos forem iguais, invalido
    int count = 0;
    for(int i = 0; i < len - 1; i++){
        if(cpf[i] == cpf[i+1]) count++;
    }

    if(count + 1 == len){
        return -1;
    }

    // checa validade com digitos diferentes
    int dv1 = 0, dv2 = 0;
    
    // primeiro digito do DV
    for(int i = 0; i < len - 2; i++){
        dv1 += (cpf[i] - '0') * (int) (len - 1 - i);
    }
    dv1 = (11 - (dv1 % 11));
    dv1 = dv1 >= 10 ? 0 : dv1;
    // segundo digito do DV
    for(int i = 0; i < len - 1; i++){
        dv2 += (cpf[i] - '0') * (int) (len - i);
    }
    dv2 = (11 - (dv2 % 11));
    dv2 = dv2 >= 10 ? 0 : dv2;

    printf("valor de DV encontrado: %d%d\n", dv1, dv2);

    return (dv1 + '0' == cpf[len - 2] && dv2 + '0' == cpf[len - 1]);
}

int main()
{
    // array char
    char cpf[20];

    printf("Digite o numero do CPF: ");
    scanf("%s", cpf);

    char * nums = get_nums(cpf);
    int ret = validate(nums);

    if (ret == 1)
        printf("O cpf %s eh valido!\n", cpf);
    else if (ret == -1)
        printf("O cpf %s eh invalido! Nao existem cpfs com todos os numeros iguais\n", cpf);
    else
        printf("O cpf %s eh invalido!\n", cpf);

    return 0;
}