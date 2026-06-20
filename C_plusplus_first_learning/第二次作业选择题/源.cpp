//#include<stdio.h>
//int main() {
//	int arry[3][3] = { 1,1,1,2,3,4,5,6,7 };
//	for (int i = 0; i < 3; i++) {
//		printf("%d", arry[i][2 - i]);
//	}
//}
//int main()
//{
//	int aa[4][4] = { {1,2,3,4},{5,6,7,8},{3,9,10,2},{4,2,9,6} };
//	int i, s = 0;
//	for (i = 0; i < 4; i++) s += aa[i][i];
//	printf("%d\n", s);
//	return 0;
//}
//#include<stdio.h>
//int main() {
//	int i = 0, j = 0, sum = 0;
//	int array[][4] = { { 1,2,3,4 }, { 5,6,7,8 }, { 9,10,11,12 }, { 13,14,15,16 } };
//	for(int x = 1; x <= 4; x++)
//		for (int y = 1; y <= 4; y++) {
//			sum = 0;
//			for (i = 0; i < x; i++)
//				for (j = 0; j < y; j++) {
//					sum += array[i][j];
//				}
//			if (sum == 28) {
//				printf("%d %d", x, y);
//			}
//		}
//	
//	
//
//}
//#include<stdio.h>
//int add(int x1,int x2);
//int main() {
//	int i = 0, a = 3, b = 4, sum = 0;
//	int c = b - add(a, b);
//	for (i = a; i > c; i--) {
//		sum += add(a, c);
//		printf("%d\n", sum);
//	}
//}
//int add(int x1, int x2) {
//	return x1 + x2;
//}
//#include<stdio.h>
//int main() {
//	for (int i = 0; i < 100; i++) {
//		if (i % 3 == 0 && i % 10 == 6) {
//			printf("%d\n", i);
//		}
//	}
////}
//#include<stdio.h>
//int main() {
//	int i, j;
//	for (i = 0; i < 10; i++) {
//		j = i * 10 + 6;
//		if (!(j % 3 == 0)) 
//			continue;
//			printf("%d\n", j);
//		
//	}
//	return 0;
//}
//#include<stdio.h>
//int main() {
//	int sum = 0;
//	for (int i = 0; i < 100; i++) {
//		if (!(i % 2 == 0)) {
//			sum += i;
//		}
//	}
//	printf("%d", sum);
//}
//#include<stdio.h>
//int main() {
//	for (int i = 1900; i <= 2023; i++) {
//		if ((i % 4 == 0 && !(i % 100 == 0)) || i % 400 == 0 ) {
//			printf("闰年:%d", i);
//		}
//	}
//}
//#include<stdio.h>
//
//int main() {
//	int arry[10];
//	int sum = 0;
//	float average;
//	for (int i = 0; i < 10; i++) {
//		scanf_s("%d", &arry[i]);
//		sum += arry[i];
//	}
//
//	for (int i = 0; i < 10 - 1; i++) 
//		for (int j = 0; j < 10 - 1 - i; j++) {
//			if (arry[j] < arry[j + 1]) {
//				int temp = arry[j];
//				arry[j] = arry[j + 1];
//				arry[j + 1] = temp;
//			}
//		}
//	printf("排序后：");
//	for (int i = 0; i < 10; i++) {
//		printf("%d ", arry[i]);
//	}
//
//	printf("sum =  %d ", sum);
//	average = sum / 10;
//	printf("average = %f ", average);
//
//}
//#include<stdio.h>
//#define num 10
//int main() {
//	int arry[num];
//	for (int i = 0; i < num; i++) {
//		scanf_s("%d", &arry[i]);
//	}
//	for (int i = 0; i < num - 1; i++)
//		for (int j = 0; j < num - 1 - i; j++) {
//			if (arry[j] > arry[j + 1]) {
//				arry[j] = arry[j] ^ arry[j + 1];
//				arry[j + 1] = arry[j] ^ arry[j + 1];
//				arry[j] = arry[j] ^ arry[j + 1];
//			}
//		}
//	for (int i = 0; i < num; i++) {
//		printf("%d ", arry[i]);
//	}
//	printf("\n");
//	for (int i = num - 1; i >= 0; i--) {
//		printf("%d ", arry[i]);
//	}
//}
//#include<stdio.h>
//void changearry(int arry[][3]);
//
//int main() {
//	int arry[3][3] = { 8,3,4,5,7,1,6,2,9 };
//	changearry(arry);
//	return 0;
//}
//
//void changearry(int arry[][3]) {
//	printf("转换前:\n");
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++)
//			printf("%d ", arry[i][j]);
//		printf("\n");
//	}
//	/*int arry2[3][3];*/
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			int cunt = arry[i][j];
//			arry[i][j] = arry[j][i];
//			arry[j][i] = cunt;
//			/*arry2[i][j] = arry[j][i];*/
// }
//	}
//	printf("转换后:\n");
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++)
//			printf("%d ", arry[i][j]);
//		printf("\n");
//	}
//}
//#include <iostream>
//#include <windows.h>
//using namespace std;
//
//int main()
//{
//	system(" color 0c");
//	float x, y, a;
//	for (y = 1.4f; y > -1; y = y - 0.1f)
//	{
//		for (x = -1.4f; x < 1.4f; x = x + .04f)
//		{
//			a = x * x + y * y - 1;
//			putchar(a * a * a - x * x * y * y * y < 0.0f ? 'x' : ' ');
//		}
//		Sleep(50);
//		printf("\n");
//	}
//	printf("\t王子公主们\n");
//	printf("\t要天天开心\n");
//	return 0;
//}
