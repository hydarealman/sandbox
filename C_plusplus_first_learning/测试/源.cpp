#include<stdio.h>
int main() {
	int n, k;
	float cnt1 = 0.0
	float cnt2 = 0.0;
	int sum1 = 0;
	int sum2 = 0;
	scanf_s("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		if (i % k == 0) {
			sum1 += i;
			cnt1++;
		}
		else {
			sum2 += i;
			cnt2++;
		}


		float average1 = sum1 / cnt1;
		float average2 = sum2 / cnt2;

		printf("%f", average1);
		printf("%f", average2);
	}
}