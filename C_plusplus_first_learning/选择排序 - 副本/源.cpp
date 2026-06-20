#include<stdio.h>
#include<stdlib.h>
int main() {
	int n;
	scanf_s("%d", &n);
	int* arry = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &arry[i]);
	}
	printf("≈≈–Ú«∞\n");
	for (int i = 0; i < n; i++) {
		printf("%d", arry[i]);
	}
	printf("\n");
	for (int i = 0; i < n; i++) {
		int min_num = arry[i];
		int min_num_index = i;
		for (int j = i; j < n; j++) {
			if (min_num > arry[j]) {
				min_num = arry[j];
				min_num_index = j;
			}
		}
		int temp = arry[i];
		arry[i] = arry[min_num_index];
		arry[min_num_index] = temp;
	}
	printf("≈≈–Ú∫Û\n");
	for (int i = 0; i < n; i++) {
		printf("%d", arry[i]);
	}
}