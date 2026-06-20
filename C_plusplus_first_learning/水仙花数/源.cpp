#include<stdio.h>
int main() {
	int n;
	int i = 0;//计算数组索引
	int arry[1000];
	int number = 1;
	int sum = 0;
	scanf_s("%d", &n);
	while (n > 0) {
		number = n % 10;
		n /= 10;
		arry[i] = number;
		i++;
	}
	for (int j = 0; j < i; j++) {
		sum += arry[j] * arry[j];
	}
}