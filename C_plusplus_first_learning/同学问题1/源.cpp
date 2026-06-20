//#include<stdio.h>
//int main() {
//	int a;
//	int b = (a += a -= a = 9);
//	printf("%d", b);
//}
#include<stdio.h>
int main() {
	int sum[5], num[5];
	for (int i = 0; i < 5; i++) {
		scanf_s("%d", &sum[i]);
	}
	for (int i = 0; i < 5; i++) {
		num[i] = sum[4 - i];
	}
	for (int i = 0; i < 5; i++) {
		printf("%d ", num[i]);
	}
}