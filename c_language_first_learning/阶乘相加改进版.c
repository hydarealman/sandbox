#include<stdio.h>
int main()
{
	int n,sum=0,num;
	scanf("%d",&n);
	for(int i=0; i<n; i++)
	{
		num = num*(num-1);
		for(int i=0; i<n; i++)
		{
			sum += num;
		}
	}
	printf("%d",sum);
	
	
	
}
