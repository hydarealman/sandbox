//#include<stdio.h>
//int main() {
//	int num1;
//	int num2;
//	scanf_s("%d", &num1);
//	scanf_s("%d", &num2);
//	int* p1;
//	int* p2;
//	if (num1 > num2) {
//		p1 = &num2;
//		p2 = &num1;
//	}
//	else {
//		p1 = &num1;
//		p2 = &num2;
//	}
//}

//#include<stdio.h>
//void swap(int* num1, int* num2) {
//	int temp = *num1;
//	*num1 = *num2;
//	*num2 = temp;
//}
//int main() {
//	int num1, num2;
//	scanf_s("%d%d", &num1, &num2);
//	printf("%d %d\n", num1, num2);
//	swap(&num1, &num2);
//	printf("%d %d\n", num1, num2);
//}

//#include<stdio.h>
//int getStringLength(char *str) {
//	char* p = str;
//	while (*p != '\0') {
//		p++;
//	}
//	return (int)(p - str);
//}
//int main() {
//	char str[100];
//	fgets(str, sizeof(str), stdin);
//	printf("字符串的长度为:%d", getStringLength(str));
//}

//#include<stdio.h>//为什么多打印了两个空格
//#include<string.h>
//void reverseString(char* str) {
//	int left = 0;
//	int right = strlen(str) - 1;
//	printf("转换前\n");
//	printf("%s", str);
//	printf("\n");
//	while (left <= right) {
//		int temp = str[left];
//		str[left] = str[right];
//		str[right] = temp;
//		left++;
//		right--;
//	}
//	printf("转换后\n");
//	printf("%s", str);
//}
//int main() {
//	char str[100];
//	fgets(str, sizeof(str), stdin);
//	reverseString(str);
//	
//}

//#include<stdio.h>
//int strcmp(char* p1, char* p2) {
//	while (*p1 !=  '\0' && *p1 == *p2) {
//		p1++;
//		p2++;
//	}
//	return *p1 - *p2;
//}
//int main() {
//	char str1[100];
//	fgets(str1, sizeof(str1), stdin);
//	char str2[100];
//	fgets(str2, sizeof(str2), stdin);
//	printf("%d", strcmp(str1, str2));
//}


#include<stdio.h>
#include<math.h>
#define N 1000000
double get_intergal_sin(double a, double b) {
	double x = (b - a) / N;
	double ans = 0;
	for (int i = 0; i <= N; i++) {
		ans += x * sin(a + x * i);
	}
	return ans;
}
double get_intergral_cos(double a, double b) {
	double x = (b - a) / N;
	double ans = 0;
	for (int i = 0; i <= N; i++) {
		ans += x * cos(a + x * i);
	}
	return ans;
}
double get_intergeral_e(double a, double b) {
	double x = (b - a) / N;
	double ans = 0;
	for (int i = 0; i <= N; i++) {
		ans += x * exp(a + x * i);
	}
	return ans;
}

int main() {
	double result = get_intergal_sin(0, 1) * get_intergral_cos(-1, 1) * get_intergeral_e(0, 2);
	printf("计算的结果为%lf", result);
}