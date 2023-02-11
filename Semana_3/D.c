// nth fibonacci element
#include <stdio.h>

int fibonacci(int n)
{
    if(n <= 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    int n, fib;

    printf("##### SEQUENCIA DE FIBONACCI #####\n");
    printf("Digite a posicao do elemento que deseja ver: ");
    scanf("%d", &n);

    fib = fibonacci(n);

    printf("O %d elemento da sequencia de fibonacci eh: %d\n", n, fib);
    return 0;
}