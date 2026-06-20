#include<stdio.h>
int main() {
	printf("加法输入1\n减法输入2\n乘法输入3\n除法输入4\n取余输入5\n");
	printf("请选择计算方法:");
	int num;
	int finish;
	scanf_s("%d", &num);
	int x, y;
	scanf_s("%d%d", &x, &y);
	if (num == 1) {
		finish = x + y;
	}
	else if (num == 2) {
		finish = x - y;
	}

	else if (num == 3) {
		finish = x * y;
	}

	else if (num == 4) {
		if (y == 0)
			printf("你输入的数据无效");
		else
			finish = x / y;
	}
	else if (num == 5) {
		if (y == 0)
			printf("你输入的数据无效");
		else
			finish = x % y;
	}
	if(!(y == 0))
	printf("%d", finish);
	return 0;
}