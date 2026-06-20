#include<stdio.h>

int main()
{
    int a, b, c, e;

    scanf_s("%d%d", &a, &b);
    printf("Õ∑=%d,Ω≈=%d", a, b);

    e = (b - 2 * a) / 2;
    c = a - e;
    printf("º¶=%d,Õ√=%d\n", c, e);
    return 0;
}