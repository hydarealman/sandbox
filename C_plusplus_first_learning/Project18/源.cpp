#include <iostream>
using namespace std;
int main()
{
    long long sum = 0;
    long long n;
    long long m;
    long long num;
    long l = 1;
    scanf_s("%lld", n);
    scanf_s("%lld", m);
    sum = 4 * n + m;
    while (num > sum) {
        num = l * l;
    }
    printf("%ld", l - 1);
    // 请在此输入您的代码
    return 0;
}