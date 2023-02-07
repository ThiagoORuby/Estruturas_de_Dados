// fatorial of a number
#include <stdio.h>

int fatorial_sum(int n)
{
    int sum = 1, fat = 1;
    for(int i = 0; i < n; i++)
    {
        fat += i*fat;
        sum += fat;
    }
    return sum;
}

int main()
{
    int n, fat, soma = 0;
    scanf("%d", &n);
    fat = fatorial_sum(n);
    printf("A soma dos fatoriais de 0 ate %d eh %d", n, fat);
    return 0;
}