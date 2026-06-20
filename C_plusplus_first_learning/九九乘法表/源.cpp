#include<stdio.h>
int main() {
	for (int i = 1; i <= 9; i++) {
		for (int j = i; j <= 9; j++) {
			if ((j-i+1) * j < 10)
			printf("%d * %d = %d  ", j-i+1, j, (j-i+1) * j);
			else
			printf("%d * %d = %d ", j-i+1, j, (j-i+1) * j);
		}
		printf("\n");
	}
}