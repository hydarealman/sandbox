#include<stdio.h>

int main()
{
	do
	{
		printf("请输入一个数\n");
		
		int n = 0;
		scanf("%d", &n);
		
	}
	while(n < 1);
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("#"); 
		}
		
		printf("\n");
	}	
	
	
}
