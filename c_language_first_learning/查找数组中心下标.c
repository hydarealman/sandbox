#include <stdio.h>
#include <stdlib.h>

 int get_array_flag(int arr[],int n,int t)
 {
 	int i,xiabiao;
 	for(i=0;i<n;i++)
 	if(arr[i]==t)
 	xiabiao=i;
 	return xiabiao;
 }
 int main()
 {
 	int xiabiao;
 	int a[5]={10,52,63,1,5};
 	xiabiao=get_array_flag(a,5,63);
 	printf("ÏÂ±êÎª£º%d\\n",xiabiao);
 	system("pause");
 }
