//#include<stdio.h>
//int main() {
//	int a, b;
//	scanf_s("%d%d", &a, &b);
//	if (a > b) {
//		printf("%d", a);
//	}
//	else {
//		printf("%d", b);
//	}
//}
//#include<stdio.h>
//int main() {
//	char letter;
//	scanf_s("%c", &letter);
//	if (letter >= 'A' && letter <= 'Z') {
//		printf("%c", letter + 32);
//	}
//	else {
//		printf("%c", letter);
//	}
//}
//#include<stdio.h>
//int main() {
//	int x;
//	scanf_s("%d", &x);
//	if (x < 1) {
//		printf("%d", x);
//	}
//	if (1 <= x && x < 10) {
//		printf("%d", 2 * x - 1);
//	}
//	if (x >= 10) {
//		printf("%d", 3 * x - 11);
//	}
//}
//#include<stdio.h>
//int main() {
//	int age;
//	float nowwages;
//	scanf_s("%f%d", &nowwages, &age);
//	if (age >= 20) {
//		if (nowwages > 2000) {
//			nowwages += 200;
//		}
//		else {
//			nowwages += 180;
//		}
//	}
//	else {
//		if (nowwages > 1500) {
//			nowwages += 150;
//		}
//		else {
//			nowwages += 120;
//		}
//	}
//	printf("%.2f", nowwages);
//}
//
//#include<stdio.h>
//int main() {
//	int score;
//	scanf_s("%d", &score);
//	if (score < 0 || score > 100) {
//		printf("什么鬼");
//		return 0;
//	}
//	int n = score / 10;
//	if (n == 10) {
//		n = 9;
//	}
//	switch (n) {
//	case 9: printf("A"); break;
//	case 8: printf("B"); break;
//	case 7: printf("C"); break;
//	case 6: printf("D"); break;
//	default: printf("E"); break;
//	}
//}
//#include<stdio.h>
//int main() {
//	int wage;
//	scanf_s("%d", &wage);
//	if (wage >= 5000) {
//		wage = wage * (1 - 0.15);
//	}
//	else if (4000 <= wage && wage < 5000) {
//		wage = wage * (1 - 0.1);
//	}
//	else if (2000 <= wage && wage < 4000) {
//		wage = wage * (1 - 0.05);
//	}
//	else {
//		wage = wage;
//	}
//	printf("%d", wage);
//}
//#include<stdio.h>
//int main() {
//	int wage;
//	scanf_s("%d", &wage);
//	int n = wage / 1000;
//	if (n >= 5) {
//		n = 5;
//	}
//	if (n <= 1) {
//		n = 1;
//	}
//	switch (n) {
//	case 5: 
//		printf("%.1f", wage * (1 - 0.15));
//		break;
//	case 4:
//		printf("%.1f", wage * (1 - 0.1));
//		break;
//	case 3:
//		printf("%.1f", wage * (1 - 0.05));
//		break;
//	case 2:
//		printf("%.1f", wage * (1 - 0.05));
//		break;
//	case 1:
//		printf("%.1f",wage);
//	default:
//		printf("什么鬼");
//	}
//}
#include<stdio.h>
#define PI 3
int main() {
	printf("选择圆形请输入1\n");
	printf("选择长方形请输入2\n");
	printf("选择正方形请输入3\n");
	int n;
	scanf_s("%d", &n);
	int area = 0;
	switch (n) {
	case 1:
		printf("请输入半径值");
		int r;
		scanf_s("%d", &r);
		area = PI * r * r;
		printf("圆的面积为%d", area);
		break;
	case 2:
		printf("请输入长和宽");
		int m, n;
		scanf_s("%d%d", &m, &n);
		area = m * n;
		printf("%d", area);
		break;
	case 3:
		printf("请输入边长");
		int a;
		scanf_s("%d", &a);
		area = a * a;
		printf("正方形的面积为%d", area);
		break;
	default:
		printf("什么鬼");
	}
}
