#include<stdio.h>

int main()
{
	int a[13] = {[1]=2,4,[5]=6};
	printf("%ld\n",sizeof(a));
	int i;
	for(i = 0; i < 13; i++)
	{
		printf("%d\t", a[i]); 
	}
	printf("\n");
}
 
