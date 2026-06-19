#include<stdio.h>
int isprime(int a, int count);

int main()
{
   int a;
   int count;
    scanf("%d", &a);
    isprime(a,count);
    return 0;
}

int isprime(int a, int count)
{
 for(count = 2; count < a; count++)
 {
    if(a%count == 0)
     break;
 }
  if(a<count)
 printf("不是素数");
 else
 printf("是素数");
 
} 
