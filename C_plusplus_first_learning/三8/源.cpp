//写一个银行账户管理系统，这是一个初学者能写出来的吗
//我尽力
#include<stdio.h>
int main() {
	int sum=0, num, x;
	printf("请输入数字选择你接下来的操作\n");
	printf("要存款请输入数字1\n");
	printf("要取款请输入数字2\n");
	printf("要查询余额请输入数字3\n");
	printf("要退出操作请输入数字4\n");

	scanf_s("%d", &x);
	while (1) {
		if (x == 1) {
			printf("请输入你要存储的金额");
			scanf_s("%d", &num);
			sum  += num;
			scanf_s("%d", &x);
		}

		else if (x == 2) {
			printf("请输入你要取出的金额");
			scanf_s("%d", &num);
			sum -= num;
			scanf_s("%d", &x);
		}

		else if (x == 3) {
			printf("您的余额为%d", sum);
			scanf_s("%d", &x);
		}

		else if (x == 4) {
			printf("您已经退出操作");
			break;
		}
	}
	

}
