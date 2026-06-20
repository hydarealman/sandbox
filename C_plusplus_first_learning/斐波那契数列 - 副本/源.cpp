#include<stdio.h>
int main() {
    int dp1 = 1;
    int dp2 = 1;
    for (int i = 1; i <= 8; i++) {
        int sum = dp1 + dp2;
        dp1 = dp2;
        dp2 = sum;
    }
    printf("%d", dp2);
}
//#include<stdio.h>
//int fib(int n) {
//	if (n == 1 || n == 2) {
//		return 1;
//	}
//	return fib(n - 1) + fib(n - 2);
//}
//int main() {
//	int n = 10;
//	printf("%d", fib(n));
//}