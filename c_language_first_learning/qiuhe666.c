#include<stdio.h>
#include<math.h>
int main()
{
int n,sum=0,number=0,c;
float num=0.0;
float i=0.0;
scanf("%d",&n);
for(i=1; i<=n; i++)
{
sum = sum + i;
num = num + 1/i;
c = pow(i,2);
number = number + c;
	
}	
printf("%d %d %lf ",sum,number,num);	
	
} 
