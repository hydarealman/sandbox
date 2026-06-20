#include<stdio.h>
int main() {
	for (int i = 1; i <= 8; i++) {
		for (int j = i; j <= 9; j++) {
			if (i * (j-i) < 10)
				printf("%d * %d = %d  ", j-i,j,(j-i)*j);
			if (i * (j-i) > 10)
				printf("%d * %d = %d ", j-i,j,(j-i)*j);
		}
		printf("\n");
	}
}