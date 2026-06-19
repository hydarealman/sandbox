#include<stdio.h>
#define PI 3
int main() {
	printf("选择圆形请输入1\n");
	printf("选择长方形请输入2\n");
	printf("选择正方形请输入3\n");
	int n;
	scanf("%d", &n);
	int area = 0; 
	switch (n) {
	case 1:
		printf("请输入半径值");
		int r;
		scanf("%d", &r);
		area = PI * r * r;
		printf("圆的面积为%d", area);
		break;
	case 2:
		printf("请输入长和宽");
		int m, n;
		scanf("%d%d", &m, &n);
		area = m * n;
		printf("%d", area);
		break;
	case 3:
		printf("请输入边长");
		int a;
		scanf("%d", &a);
		area = a * a;
		printf("正方形的面积为%d", area);
		break;
	default:
		printf("什么鬼");
	}
}

