#include<stdio.h>
#include<math.h>
#define MAX 1000
int main() {
	int i, j, sum;
	for (i = 5; i < MAX; i++) {
		sum = 0;
		for (j = 5; j <= sqrt(i); j++) {
			if (i % j == 0)
				sum += j;
			if ( j != (i / j)) 
				sum += i / j;
		}

		if (sum == i) 
			printf("%d is perfect number\n", i);
		
	}
	return 0;
}