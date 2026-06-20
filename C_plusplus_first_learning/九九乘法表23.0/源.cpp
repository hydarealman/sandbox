#include<stdio.h>
int main() {
	for (int j = 1; j <= 9; j++) {
		for (int i = 1; i <= j; i++) {
			printf("%d * %d = %d\t", i, j, i * j);
		}
		printf("\n");
	}
}