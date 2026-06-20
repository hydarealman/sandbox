//#include<stdio.h>
//int main() {
//	int i = 1;
//	int sum = 0;
//	while (i < 100) {
//		sum += i;
//		i++;
//	}
//	printf("%d", sum);
//}
//#include<stdio.h>
//int main() {
//	int i = 1;
//	int sum = 0;
//	do {
//		sum += i;
//		i++;
//	} while (i < 100);
//	printf("%d", sum);
//}
//#include<stdio.h>
//int main() {
//	int sum = 0;
//	for (int i = 0; i < 100; i++) {
//		sum += i;
//	}
//	printf("%d", sum);
//}
//#include<stdio.h>
//int func(int n) {
//	if (n == 1) {
//		return 1;
//	}
//	return n * func(n - 1);
//}
//int main() {
//	int n;
//	scanf_s("%d", &n);
//	int sum = 0;
//	for (int i = 1; i <= n; i++) {
//		sum += func(i);
//	}
//	printf("%d", sum);
//}
//#include<stdio.h>
//int main() {
//	int sum = 0;
//	for (int i = 0; i < 5; i++) {
//		int temp;
//		scanf_s("%d", &temp);
//		sum += temp;
//	}
//	float average = sum / 5.0;
//	printf("%.1f", average);
//
//}
//#include<stdio.h>
//int main() {
//    float  grow = 0.008;
//	float n = 1.0;
//	int year = 0;
//	const float threshold = 0.0001;
//	while (n < 2 - threshold) {
//		n *= (1 + grow);
//		year++;
//	}
//	printf("%d", year);
//}
//#include<stdio.h>
//float func(int n) {
//	int num = 1;
//	for (int i = 1; i <= n; i++) {
//		num *= i;
//	}
//	return num;
//}
//int main() {
//	double ans = 1;
//	double each =  1 / func(1);;
//	int i = 2;
//	while (each > 1e-7) {
//		ans += each;
//		each = (1 / func(i));
//		i++;
//	}
//	printf("%lf", ans);
//}
//#include<stdio.h>
//int main() {
//	for (int i = 1; i <= 5; i++) {
//		for (int j = 1; j <= i; j++) {
//			printf("%d ", j);
//		}
//		printf("\n");
//	}
//}
//#include<stdio.h>
//int main() {
//	for (int i = 0; i < 4; i++) {
//
//		for (int j = 3 - i; j > 0; j--) {
//			printf(" ");
//		}
//		for (int j = 0; j < 2 * i + 1; j++) {
//			printf("*");
//
//		}
//		; printf("\n");
//	}
//}
//#include<stdio.h>
//#include<math.h>
//int main() {
//	for (int i = 100; i <= 999; i++) {
//		int sum = 0;
//		int temp = i;
//		while (temp > 0) {
//			int num = temp % 10;
//			sum += pow(num, 3);
//			temp /= 10;
//		}
//		if (sum == i) {
//			printf("%d\n", i);
//		}
//	}
//}
//#include<stdio.h>
//int main() {
//	for (int i = 100; i <= 200; i++) {//遍历
//		int isprime = 1;
//		for (int j = 2; j < i; j++) {
//			int temp = i;
//			if (temp % j == 0) {
//				isprime = 0;
//			}
//		}
//		if (isprime == 1) {
//			printf("素数:%d\n", i);
//		}
//	}
//}
//#include<stdio.h>
//int main() {
//	long dp0 = 1;
//	long dp1 = 1;
//	for (int i = 0; i < 40 - 2; i++) {
//		int temp = dp0 + dp1;
//		dp0 = dp1;
//		dp1 = temp;
//	}
//	printf("%d", dp1);
//}
//#include<stdio.h>
//int main() {
//	long dp0 = 2;
//	long dp1 = 3;
//	long dpa0 = 1;
//	long dpa1 = 2;
//	double sum = 0;
//	for (int i = 0; i < 20; i++) {
//		double up = dp0;
//		double down = dpa0;
//		double num = (up / down);
//		sum += num;
//
//		long temp1 = dp0 + dp1;
//		dp0 = dp1;
//		dp1 = temp1;
//
//		long temp2 = dpa0 + dpa1;
//		dpa0 = dpa1;
//		dpa1 = temp2;
//	}
//	printf("%lf", sum);
//}


#include<stdio.h>
int main() {
	char ch;
	int letters = 0, spaces = 0, digits = 0, others = 0;

	printf("请输入一行字符;\n");

	while ((ch = getchar()) != '\n') {
		if (ch >= 'a' && ch <= 'z') {
			letters++;
		}
		else if (ch == ' ') {
			spaces++;
		}
		else if (ch >= '0' && ch <= '9') {
			digits++;
		}
		else {
			others++;
		}
	}
	printf("字母数%d,空格%d,数字%d,其他字符%d", letters, spaces, digits, others);
}


