#include<stdio.h>

int main()
{
	int x;
	int cnt = 0;
	double sum = 0;
	
	scanf("%d", &x);
	while(x != -1)
	{
		sum += x;
		scanf("%d", &x);
		cnt++;
	}
	if(cnt > 0)
	printf("the sum is %f\n", sum / cnt);
}
