// sum of fibonacci
#include <stdio.h>

int fib_sum(int n)
{
    int sum = 0, fib0 = 1, fib1 = 1, fib = 0;
    if(n == 0) return fib0;
    if(n == 1) return fib1 + fib0;
    sum = fib0 + fib1;
    for(int i = 0; i < n - 2; i++)
    {
        fib = fib0 + fib1;
        fib0 = fib1; fib1 = fib;
        sum += fib;
    }
    return sum;
}

int main()
{
    int n, fib, soma = 0;

    printf("##### SOMA DE FIBONACCI #####\n");
    printf("Digite um numero: ");
    scanf("%d", &n);

    fib = fib_sum(n);
    printf("A soma dos %d primeiros termos de fibonacci eh %d\n", n, fib);
    return 0;
}