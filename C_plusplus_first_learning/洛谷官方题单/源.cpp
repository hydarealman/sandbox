#include<stdio.h>
int main() {
	int m, n;
	int cnt = 0;
	scanf_s("%d%d", &m, &n);
	for (int i = 0; i < m * n; i++) {
		for (int j = i; j < m * n; j++) {
			cnt++;
		}
	}
	printf("%d", cnt);
}