#include<stdio.h>

int main()
{
	const int number = 10;
	int x;
	int i;
	int count[number];
	
	
	for( i = 0; i < number; i++)
	{
		count[i] = 0;
	}
	
	scanf("%d", &x);
	while(x != -1)
	{
		if(x <= 9 && x >= 0)
		{
			count[number]++;
		}
		scanf("%d", &x);
	}
	for( i = 0; i < 10; i++)
	{
		printf("%d:%d\n", i,count[i]);
	}

}
 
