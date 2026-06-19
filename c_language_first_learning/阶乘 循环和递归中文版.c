#include<stdio.h>
long fact(int n);
long rfact(int n);
int main(void)
{
	int num;
	printf("这个程序计算阶乘:\n");
	 printf("输入一个1到12的数字:\n");
	while(scanf("%d", &num) == 1)
	{
		if (num < 0)
		printf("负数不行\n");
		else if (num > 12)
		printf("请输入一个小于13的数字.\n");
		else{
			printf("循环数:%d 阶乘 = %ld\n",num, fact (num));
	        printf("递归数: %d 阶乘 = %ld\n",num, rfact (num));
		    }
		    printf("输入一个1到12的数:\n)");
	}
	printf("结束. \n");
	
	return 0;
}
long fact(int n)
{
	long ans;
		
	for(ans = 1; n > 1; n--)
	ans *= n;
	return ans;
}
long rfact(int n)
{
	long ans;
	
	if(n > 0)
        ans = n *rfact(n - 1);
        else
            ans = 1;
            
        return ans;
}
