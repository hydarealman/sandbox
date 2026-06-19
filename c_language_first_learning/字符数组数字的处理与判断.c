#include<stdio.h>
#include<string.h>
int main()
{
	char str[10];
	scanf("%s",str);
	
	int len = strlen(str);
	printf("%d",len);
	printf("\n");
	for(int i=0; i<len; i++)
	{
		printf("%c",str[i]); 
	}
	printf("\n");
	for(int i=len-1; i>=0; i--)
	{
		printf("%c",str[i]);
	}
	
	
	
	
}
