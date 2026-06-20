#include<stdio.h>
#include<stdlib.h>
int a[4];
bool Fun(int n)
{
    if (n == 1)
        return a[0] == 24;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j) continue;
            int a1 = a[i], a2 = a[j];
            a[i] = a1 + a2;
            a[j] = a[n - 1];
            if (Fun(n - 1)) return true;
            a[i] = a1 - a2;
            a[j] = a[n - 1];
            if (Fun(n - 1)) return true;
            a[i] = a1 * a2;
            a[j] = a[n - 1];
            if (Fun(n - 1)) return true;
            if (a2 != 0 && a1 % a2 == 0)
            {
                a[i] = a1 / a2;
                a[j] = a[n - 1];
                if (Fun(n - 1)) return true;
            }
            a[i] = a1;
            a[j] = a2;
        }
    }
    return false;
}
int main()
{
    int n;
    scanf_s("%d", &n);
    int* result = (int*)malloc(n * sizeof(int));
    int index = 0;
    while (index != n)
    {
        for (int i = 0; i < 4; i++) {
            scanf_s("%d", &a[i]);
        }
        if (Fun(4))
            result[index] = 1;
        else
            result[index] = 0;
        index++;
    }
    for (int i = 0; i < index; i++) {
        if (result[i] == 1) {
            printf("true ");
        }
        else {
            printf("false ");
        }
    }
}