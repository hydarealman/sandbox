//≤Â»Î≈≈–Ú
//#include<stdio.h>
//void insertsort(int* arr, int n) {
//	for (int i = 0; i < n - 1; ++i) {
//		int end = i;
//		int tem = arr[end + 1];
//		while (end >= 0) {
//			if (tem < arr[end]) {
//				arr[end] = arr[end + 1];
//				end--;
//			}
//			else break;
//		}
//		arr[end + 1] = tem;
//	}
//}
//int main() {
//
//}
//œ£∂˚≈≈–Ú
//#include<stdio.h>
//int main() {
//	int arry[10] = { 9,8,7,6,5,4,3,2,1 };
//	printf("≈≈–Ú«∞");
//	for (int i = 0; i < 10; i++) {
//		printf("%d", arry[i]);
//	}
//	int n = 10;
//	int gap = n;
//	while (gap > 1) {
//		gap = gap / 2;
//		for (int i = 0; i < n - gap; i++) {
//			int end = i;
//			int tem = arry[end + gap];
//			while (end >= 0) {
//				if (arry[end] > arry[end + gap]) {
//					arry[end + gap] = arry[end];
//				}
//				else {
//					break;
//				}
//			}
//			arry[end + gap] = tem;
//		}
//	}
//	printf("≈≈–Ú∫Û");
//	for (int i = 0; i < n; i++) {
//		printf("%d", arry[i]);
//	}
//}