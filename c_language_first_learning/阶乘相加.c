#include<stdio.h>
int main()
{
int i,sum=0,m=1,x;
scanf("%d",&x);
do
{
    do 
    {
    	m = m*x;
    	x--;
	}
	while(x>0);
    
    sum = sum+m; 
    x--;
}
while(x>0);

printf("%d",sum);

return 0;
} 
