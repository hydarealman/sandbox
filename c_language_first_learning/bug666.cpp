#include<stdio.h>
int main()
{
	int a, b;
	float x, y;
	char c1, c2;
	scanf("%d%d", &a, &b);
	scanf("%f%f", &x, &y);
	scanf(" %c %c", &c1,&c2);
	printf("a:%d\tb:%d\tx:%f\ty:%e\tc1:%c\tc2:%c", a, b, x, y, c1, c2);
}
