//#include<stdio.h>
//#include"calculate.h"
//int main() {
//	float up = 3.5;
//	float down = 6.2;
//	float high = 5.0;
//	printf("梯形的面积为%.2f", calculate(up, down, high));
//}
//#include<stdio.h>
//bool isprime(int num) {
//	if (num == 0) {
//		return false;
//	}
//	for (int i = 2; i < num; i++) {
//		if (num % i == 0) {
//			return false;
//		}
//	}
//	return true;
//}
//int main() {
//	int num;
//	scanf_s("%d", &num);
//	if (isprime(num)) {
//		printf("yes");
//	}
//	else {
//		printf("no");
//	}
//}
//#include<stdio.h>
//#include<stdlib.h>
//#define MAX_COLS 100
//#define MAX_ROWS 100
//void inputArray(int rows, int cols, int arry[][MAX_COLS]) {
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < cols; j++) {
//			scanf_s("%d", &arry[i][j]);
//		}
//	}
//}
//void outputArray(int rows, int cols, int arry[][MAX_COLS]) {
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < cols; j++) {
//			printf("%d ", arry[i][j]);
//		}
//	}
//}
//int maxabsValue(int rows, int cols, int arry[][MAX_COLS]) {
//	int max = -1;
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < cols; j++) {
//			max = max < abs(arry[i][j]) ? abs(arry[i][j]) : max;
//		}
//	}
//	return max;
//}
//int main() {
//	int rows = 0;
//	int cols = 0;
//	printf("请输入数组的行数和列数");
//	scanf_s("%d", &rows);
//	scanf_s("%d", &cols);
//	int arry[MAX_COLS][MAX_ROWS];
//	inputArray(rows,cols,arry);
//	outputArray(rows,cols,arry);
//	printf("绝对值的最大值为%d", maxabsValue(rows,cols,arry));
//}
//#include<stdio.h>
//void inputArry(int arry[3][3]) {
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			scanf_s("%d", &arry[i][j]);
//		}
//	}
//}
//void outputArry(int arry[3][3]) {
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			printf("%d", arry[i][j]);
//		}
//		printf("\n");
//	}
//}
//void shiftArry(int arry[3][3]) {
//	int result[3][3];
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			result[j][i] = arry[i][j];
//		}
//	}
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			arry[i][j] = result[i][j];
//		}
//	}
//}
//int main() {
//	int arry[3][3];
//	inputArry(arry);
//
//	printf("转制前\n");
//	outputArry(arry);
//
//	shiftArry(arry);
//
//	printf("转制后\n");
//	outputArry(arry);
//}
//#include<stdio.h>
//int stringLength(const char* arr) {
//	int length = 0;
//	while (arr[length] != '\0') {
//		length++;
//	}
//	if (arr[length - 1] == '\n') {
//		return length - 1;
//	}
//	return length;
//}
//int main() {
//	char arr[100];
//	fgets(arr, sizeof(arr), stdin);
//	printf("字符串的长度为%d", stringLength(arr));
//	return 0;
//}
//#include<stdio.h>
//#include<string.h>
//int main() {
//	printf("请输入一个十六进制数");
//	char arr[100];
//	fgets(arr, sizeof(arr), stdin);
//	int multinum = 1;
//	int sum = 0;
//	for (int i = strlen(arr) - 1 - 1; i >= 0; i--) {
//		if (arr[i] >= '0' && arr[i] <= '9') {
//			sum += (arr[i] - '0') * multinum;
//		}
//		if (arr[i] >= 'a' && arr[i] <= 'f') {
//			sum += (arr[i] - 'a' + 10) * multinum;
//		}
//		if (arr[i] >= 'A' && arr[i] <= 'F') {
//			sum += (arr[i] - 'A' + 10) * multinum;
//		}
//		multinum *= 16;
//	}
//	printf("对应的十进制数为%d", sum);
//}



//#include<stdio.h>
//#include<string.h>
//void outputLongestArry(char str[]) {
//	char tempstr[100][100];//暂时存放所有单词
//	int count[100];//记录各个单词长度
//	//初始化
//	for (int i = 0; i < 100; i++) {
//		count[i] = 0;
//	}
//	int index2 = 0;//记录单词个数
//	for (int i = 0; i < strlen(str); i++) {
//		int index1 = 0;//记录单词长度
//		if (str[i] != ' ') {
//			tempstr[index2][index1] = str[i];
//			index1++;
//			continue;
//		}
//		count[index2] = index1;
//		index2++;
//	}
//	int maxlenindex = 1;
//	int maxlen = 0;
//	for (int i = 0; i < index2; i++) {
//		if (count[i] > maxlen) {
//			maxlenindex = i;
//			maxlen = count[i];
//		}
//	}
//	for (int i = 0; i < maxlen; i++) {
//		printf("%c", tempstr[i][maxlenindex]);
//	}
//}
//int main() {
//	char str[100];
//	fgets(str, sizeof(str), stdin);
//	outputLongestArry(str);
//}
//



//#include<stdio.h>
//int GCD(int num1,int num2) {
//	if (num1 < num2) {
//		int temp = num1;
//		num1 = num2;
//		num2 = temp;
//	}
//	int r = 0;
//	while (r = num1 % num2) {
//		num1 = num2;
//		num2 = r;
//	}
//	return num2;
//}
//int LCM(int num1, int num2, int gcd) {
//	return (num1 * num2) / gcd;
//}
//int main() {
//	int num1, num2;
//	printf("请输入两个整数\n");
//	scanf_s("%d", &num1);
//	scanf_s("%d", &num2);
//	printf("最大公约数为%d\n", GCD(num1,num2));
//	printf("最小公倍数为%d\n", LCM(num1, num2, GCD(num1, num2)));
//}

#include<stdio.h>
void int_to_string(int n) {
	if (n == 0)  return;
	int_to_string(n / 10);
	printf("%c", 48 + n % 10);
}
int main() {
	int n;
	scanf_s("%d", &n);
	int_to_string(n);
}
