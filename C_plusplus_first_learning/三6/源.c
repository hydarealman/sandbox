//忘记截图就把程序删了有重写一遍。。。。
#include<stdio.h>
#include<math.h>
int main() {
	int x;
	scanf_s("%d", &x);
	if (x < 0)
		printf("%d", (int)pow(x, 2) + 1);
	else if(0 <= x && x < 10)
		printf("%d", 2*x + 3);
	else if(x >= 10)
		printf("%d", (int)pow(x,2)-1);


}