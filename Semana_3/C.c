// fatorial of a number
#include <stdio.h>

int fatorial(int n)
{
    if(n <= 1) return 1;
    return n * fatorial(n - 1);
}

int main()
{
    int n, fat;
    scanf("%d", &n);
    fat = fatorial(n);
    printf("O fatorial de %d eh %d", n, fat);
    return 0;
}