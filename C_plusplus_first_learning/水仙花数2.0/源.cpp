#include<stdio.h>
int main() {
	int select;
	scanf_s("%d", &select);
	while (select > 0) {
		int n;
		int k = 0;
		int N = 1;
		int number = 1;
		int j;
		int cnt = 0;
		int sum = 0;
		int arry[3000];
		scanf_s("%d", &n);
		for (int i = 0; i < n; i++) {
			N *= 10;
		}
		for (j = 100; j < N; j++) {
			int num = j;
			while (num > 0) {
				arry[j] = num % 10;
				num /= 10;
				cnt++;
			}
			k += n;
			for (int i = k; i < cnt + k; i++) {
				sum += arry[i] * arry[i];
			}
			if (sum == j) {
				printf("%d", j);
			}
		}
	}
	return 0;
}