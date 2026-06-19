#include<stdio.h>

int main()
{
	int x;
	int cnt = 0;
	double sum = 0;
	int number[100]; 
	
	scanf("%d", &x);
	while(x != -1)
	{
		number[cnt] = x;
		sum += x;
		scanf("%d", &x);
		cnt++;
	}
	if(cnt > 0)
	{
		int i;
		double average = sum / cnt;
		for(i = 0; i<cnt; i++)
		{
			if(number[i] > average)
			{
				printf("%d ", number[i]);
			}
		}
	}

}
