#include<stdio.h>
int main() {
	int n, num;
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &num);
		if (num == 0 && num == 1)
			printf("1\n");
		if (num >= 2) {
			for (int j = num-1; j > 0; j--) {
				num *= j;
			}
			printf("%d\n ", num);
		}
	}
}