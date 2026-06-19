#include<stdio.h>
#define num 10
int main() {
	int arry[num];
	int sum = 0;
	float average;
	for (int i = 0; i < num; i++) {
		scanf("%d", arry[i]);
		sum += arry[i];
	}

	for (int i = 0 ; i < num; i++) {
		if (arry[i] < 60)
			printf("不及格的如下%d", arry[i]);
	}

	for (int i = 0; i < num - 1; i++) 
		for (int j = 0; j < num - 1 - i; j++) {
			if(arry[j] < arry[j+1]){
				int temp = 0;
			arry[j] = temp;
			arry[j] = arry[j+1];
			arry[j+1] = temp;
			}
			
		}
	printf("排序后：");
	for (int i = 0; i < num; i++) {
		printf("%d", arry[i]);
	}

	printf("sum =  %d", sum);
	average = sum / num;
	printf("average = %f", average);

}
