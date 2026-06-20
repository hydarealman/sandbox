//#include<stdio.h>
//int main() {
//	int m, n;
//	int sum = 0;
//	scanf_s("%d%d", &m, &n);
//	if (m == 1) m = 2;
//	for (int i = m; i < n; ++i) {
//		int isprime = 1;
//		for (int j = 1; j < i; ++j) {
//			if (i % j == 0) {
//				isprime = 0;
//				break;
//			}
//		}
//		if (isprime == 1) {
//			sum += i;
//		}
//	}
//	printf("%d", sum);
//}
//#include<stdio.h>
//#include<stdlib.h>
//int main() {
//	int n;
//	int i;
//	scanf_s("%d", &n);
//	int* a;
//	a = (int*)malloc(n * sizeof(int));
//	for (int i = 0; i < n; i++) {
//		scanf("%d", &a[i]);
//	}
//	free(a);
//}
//#include<stdio.h>
//int main() {
//	for (int i = 1; i < 10; i++) {
//		for (int j = i; j < 10; j++) {
//			printf("%d*%d = %d ", i,j, i * j);
//		}
//		printf("\n");
//	}
//}
//#include<stdio.h>
//int main() {
//	for (int i = 1; i < 10; i++) {
//		for (int j = 1; j <= i; j++) {
//			printf("%d*%d=%d", j, i, i * j);
//			if (i * j < 10) {
//				printf("    ");
//			}
//			else
//				printf("   ");
//		}
//		printf("\n");
//	}
//}
//#include<stdio.h>
//int main() {
//	int m, n;
//	int sum = 0;
//	scanf_s("%d", &m);
//	scanf_s("%d", &n);
//	if (m == 1) m = 2;
//	for (int i = m; i <= n; ++i) {
//		int isprime = 1;
//		for (int j = 2; j < m-1; ++i) {
//			if (i % j == 0) {
//				isprime = 0;
//				break;
//			}
//		}
//		if (isprime) {
//			sum += i;
//		}
//	}
//	printf("%d", sum);
//}
//#include<stdio.h>
//int main() {
//	int m;
//	scanf_s("%d", &m);
//	for (int i = 1; i < m; i++) {
//		int isprime = 1;
//		for (int j = 2; j < i; j++) {
//			if (i % j == 0) {
//				isprime = 0;
//			}
//		}
//		if (isprime) {
//			printf("%d\n", i);
//		}
//	}
//}
//	#include<stdio.h>
//int main() {
//	int m, n;
//	int sum = 0;
//	scanf_s("%d%d", &m, &n);
//	if (m == 1) m = 2;
//	//遍历m到n的数
//	for (int i = m; i < n; i++) {
//		int isprime = 1;
//		for (int j = 2; j < i; j++)//判断数是不是素数
//		{
//			if (i % j == 0) {
//				isprime = 0;
//				break;
//			}
//		} 
//		if (isprime) {
//			sum += i;
//			printf("%d ", i);
//		}
//	}
//	printf("\n");
//	printf("the sum is %d", sum);
//}
#include<stdio.h>
int main() {
	int m, n;
	int sum = 0;
	scanf_s("%d%d", &m, &n);
	if (m == 1) m = 2;
	for (int i = m; i <= n; i++) {
		int isprime = 1;
		for (int j = 2; j < i; j++) {
			if (i % j == 0) {
				isprime = 0;
				break;
			}
		}
		if (isprime) {
			sum += i;
			printf("%d ", i);
		}
	}
	printf("\n");
	printf("%d", sum);
}