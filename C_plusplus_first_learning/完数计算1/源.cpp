#include<stdio.h>
#define MAX 1000
int main() {
	int i, j;
	for ( i = 1; i < MAX; i++) {
		int sum = 0;
		for ( j = 1; j < i; j++) {
			if (i % j == 0) 
				sum += j;
		}
		if (sum == i) 
			printf("%d is perfect number\n", i);
	}
}