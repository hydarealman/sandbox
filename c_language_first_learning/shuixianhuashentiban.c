#include<stdio.h>
int main()
{
	int number,c;
	for(number=0; number<1000; number++)
	    {
	    c = (number%10)*(number%10)*(number%10)+(number/10%10)*(number/10%10)*(number/10%10)+(number/10/10%10)*(number/10/10%10)*(number/10/10%10);
	    if (number == c)
	    printf("%d ",number);
        }
return 0;
} 
