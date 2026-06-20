//累 要不下次少点题 整难点也无所谓 少点
//就三个数我还写排序。。。。。
#include<stdio.h>
int main() {
	int arry[3];
	for (int i = 0; i < 3; i++)
		scanf_s("%d", &arry[i]);
//刚学排序我写个冒泡吧
	for (int i = 0; i < 3 - 1; i++)
		for (int j = 0; j < 3 - 1 - i; j++) {
			if (arry[j] > arry[j + 1]) {
				arry[j] = arry[j] ^ arry[j + 1];
				arry[j+1] = arry[j] ^ arry[j + 1];
				arry[j] = arry[j] ^ arry[j + 1];
			}
		}
	for (int i = 0; i < 3; i++)
		printf("%d ", arry[i]);
}