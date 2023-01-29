#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// O que falta:
// extenso de numeros com parte fracionaria
// implementar: iterador fracionario e split no "." ou ","
// implementar função de checagem de erros

// sistema decimal
char unidades[10][26] = {"", "um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove"};
char unicos[10][26] = {"", "onze", "doze", "treze", "quatorze", "quinze", "dezesseis", "dezessete", "dezoito", "dezenove"};
char dezenas[10][26] = {"","dez", "vinte", "trinta", "quarenta", "cinquenta", "sessenta", "setenta", "oitenta", "noventa"};
char centenas[10][26] = {"", "cento", "duzentos", "trezentos", "quatrocentos", "quinhentos", "seissentos","setessentos", "oitocentos", "novecentos"};
char conectores[][26] = {"", "mil", "mi", "bi", "tri", "quatri", "quinti", "sexti", "septi", "octi", "noni", "deci"};
char fracionarios[][32] = {"", "dec", "centes", "miles", "miliones", "biliones"};

//  get a substring of a string
char * sub(int ini, int end, char * string){
    size_t len = end - ini;
    char * new = malloc(len);
    int c = 0;
    while(c < len){
        new[c] = string[ini+c];
        c++;
    }
    new[c] = '\0';
    return new;
}

// 1 - lhao, 2 - lhoes
// nomeia as triplas
int nomeador(char * tripla){
    int len = strlen(tripla), ret = (len == 1 && tripla[0] == '1') ? 1 : 2;
    if(strcmp(tripla, "000") == 0) ret = 0;
    if(len == 3){
        if (strcmp(tripla, "100") == 0){
            printf("cem ");
            return ret;
        }
        (tripla[0] == '0') ?
        printf("") :
        printf("%s ", centenas[(tripla[0] - '0')]);
        if(tripla[strlen(tripla) - 2] != '0') printf("e ");
        len--;
    }
    if(len == 2){
        if(tripla[strlen(tripla) - 2] == '1'){
            (tripla[strlen(tripla) - 1] == '0') ?
            printf("%s ", dezenas[tripla[strlen(tripla) - 2] - '0']) :
            printf("%s ", unicos[tripla[strlen(tripla) - 1] - '0']);
            len-=2;
        }
        else{
            (tripla[strlen(tripla) - 2] == '0') ?
            printf("") :
            printf("%s ", dezenas[tripla[strlen(tripla) - 2] - '0']);
            if(tripla[strlen(tripla) - 1] != '0') printf("e ");
            len--;
        }
    }
    if(len == 1){
        (tripla[strlen(tripla) - 1] == '0') ?
        printf("") :
        printf("%s ", unidades[tripla[strlen(tripla) - 1] - '0']);
    }
    return ret;
}

// percorre as triplas
void iterador_inteiro(char * numero, int i, int e, int triplas, int inv){
    if(triplas == 0){   
        return;
    }
    iterador_inteiro(numero, i, e - i, triplas - 1, inv + 1);

    char * tripla = sub(e - i < 0 ? 0 : e - i, e, numero);
    int ret = nomeador(tripla);
    if(inv > 0){
        printf("%s", (ret != 0) ? conectores[inv] : "");
        if(inv > 1) printf("%s ", (ret == 2) ? "lhoes" : (ret == 1) ? "lhao" : "");
        else printf(" ");
    }
}

int main(){
    char numero[100];
    scanf("%s", numero);
    iterador_inteiro(numero, 3, strlen(numero), (int) ceil(strlen(numero)/3.0), 0);
    return 0;
}