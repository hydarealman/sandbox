//#include<iostream>
//using namespace std;
//int main() {
//	int dp0 = 1;
//	int dp1 = 1;
//	for (int i = 0; i < 10; i++) {
//		int temp = dp0 + dp1;
//		dp0 = dp1;
//		dp1 = temp;
//	}
//	cout << dp1 << endl;
//}
#include<stdio.h>
int main() {
	int a[10] = { 2,3,1,6,9,5,8,7,4,0 };
	printf("≈≈–Ú«∞\n");
	for (int i = 0; i < 10; i++) {
		printf("%d", a[i]);
	}
	printf("\n");
	for (int i = 0; i < 10-1; i++) {
		for (int j = 0; j < 10-1 - i; j++) {
			if (a[j] > a[j + 1]) {
				int temp = a[j ];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	printf("≈≈–Ú∫Û\n");
	for (int i = 0; i < 10; i++) {
		printf("%d", a[i]);
	}
}