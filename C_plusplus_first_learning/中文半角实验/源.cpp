#include<stdio.h>
int max(int a, int b) {
	if (b > a)
		a = b;
	return b;
}
int main() {
	int a, b;
	scanf_s("%d,%d", &a,&b);
	int c = max( a,  b);
	printf("%d", c);
}
//还是不理解什么原因