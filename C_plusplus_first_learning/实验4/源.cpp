//#include<stdio.h>
//int main() {
//	int arry[5];
//	for (int i = 0; i < 5; i++) {
//		scanf_s("%d", &arry[i]);
//	}
//	int max = arry[0];
//	for (int i = 1; i < 5; i++) {
//		if (arry[i] > max) {
//			max = arry[i];
//		}
//	}
//	printf("%d", max);
//}
//#include<stdio.h>
//#include<stdlib.h>
//int main() {
//	int n;
//	printf("请输入数组的长度");
//	scanf_s("%d", &n);
//	int* arry = (int*)malloc(n * sizeof(int));
//	for (int i = 0; i < n; i++) {
//		scanf_s("%d", &arry[i]);
//	}
//	int max_num = arry[0];
//	int max_index = 0;
//	for (int i = 0; i < n; i++) {
//		if (arry[i] > max_num) {
//			max_num = arry[i];
//			max_index = i;
//		}
//	}
//	printf("修改前\n");
//	for (int i = 0; i < n; i++) {
//		printf("%d ", arry[i]);
//	}
//	printf("\n");
//	for (int i = max_index; i < n-1; i++) {
//		arry[i] = arry[i + 1];
//	}
//	n--;
//	printf("修改后\n");
//	for (int i = 0; i < n; i++) {
//		printf("%d ", arry[i]);
//	}
//}
//#include<stdio.h>
//#include<stdlib.h>
//int main() {
//	int n;
//	scanf_s("%d", &n);
//	int* arry = (int*)malloc(n * sizeof(int));
//	if (arry == NULL) {
//		printf("memory allocation failed");
//		return 1;
//	}
//	for (int i = 0; i < n - 1; i++) {
//		scanf_s("%d", &arry[i]);
//	}
//	printf("插入前");
//	for (int i = 0; i < n - 1; i++) {
//		printf("%d ", arry[i]);
//	}
//	for (int i = n - 1 - 1; i > 0; i--) {
//		arry[i + 1] = arry[i];
//	}
//	arry[1] = 99;
//	printf("插入后");
//	for (int i = 0; i < n; i++) {
//		printf("%d ", arry[i]);
//	}
//	free(arry);
//	arry = NULL;
//}
//#include<stdio.h>
//int main() {
//	int arry[10] = { 6,3,2,9,8,7,4,5,1,0 };
//	printf("排序前");
//	for (int i = 0; i < 10; i++) {
//		printf("%d", arry[i]);
//	}
//	for (int i = 0; i < 10 - 1; i++) {
//		for (int j = 0; j < 10 - 1 - i; j++) {
//			if (arry[j] > arry[j + 1]) {
//				int temp = arry[j];
//				arry[j] = arry[j + 1];
//				arry[j + 1] = temp;
//			}
//		}
//	}
//	printf("\n");
//	printf("排序后");
//	for (int i = 0; i < 10; i++) {
//		printf("%d", arry[i]);
//	}
//}
//#include<stdio.h>
//int main() {
//	int arry[3][3];
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			scanf_s("%d", &arry[i][j]);
//		}
//	}
//	int sum = arry[0][1] + arry[0][2] + arry[1][2];
//	printf("%d", sum);
//}
//#include<stdio.h>
//int main() {
//	int arry[3][4];
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 4; j++) {
//			scanf_s("%d", &arry[i][j]);
//		}
//	}
//	int indexi = 0;
//	int indexj = 0;
//	int max = arry[0][0];
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 4; j++) {
//			if (arry[i][j] > max) {
//				max = arry[i][j];
//				indexi = i;
//				indexj = j;
//			}
//		}
//	}
//	printf("最大数为%d,行%d,列%d", max, indexi + 1, indexj + 1);
//}
//#include<stdio.h>//有问题晚点看
//#include<string.h>
//#include<stdlib.h>
//int main() {
//	char arry1[] = "hello ";
//	char arry2[] = "world";
//
//	int size1 = strlen(arry1);
//	int size2 = strlen(arry2);
//	char* arry3 = (char*)malloc(size1 + size2 + 1);
//	
//	for (int i = 0; i < size1; i++) {
//		arry3[i] = arry1[i];
//	}
//	for (int i = size1; i < size1 + size2; i++) {
//		arry3[i] = arry2[i - size1];
//	}
//	arry3[size1 + size2] = '\0';
//	printf("%s", arry3);
//	free(arry3);
//	arry3 = NULL;
//}
//#include<stdio.h>
//int main() {
//	char text[26];
//	for (int i = 0; i < 26; i++) {
//		scanf_s("%c", &text[i]);
//	}
//	int bignum = 0;
//	int smallnum = 0;
//	for (int i = 0; i < 26; i++) {
//		if (text[i] >= 'a' && text[i] <= 'z') {
//			smallnum++;
//		}
//		if (text[i] >= 'A' && text[i] <= 'Z') {
//			bignum++;
//		}
//		else continue;
//	}
//	printf("大写字母有%d个，小写字母有%d个", bignum, smallnum);
//}
//#include<stdio.h>
//int main() {
//	int dp[20];
//	dp[0] = 1;
//	dp[1] = 1;
//	for (int i = 2; i < 20; i++) {
//		dp[i] = dp[i - 1] + dp[i - 2];
//	}
//	printf("%d", dp[19]);
//}
//#include<stdio.h>
//int main() {
//	int left = 0;
//	int right = 5 - 1;
//	int arry[5] = { 8,6,5,4,1 };
//	for (int i = 0; i < 5; i++) {
//		printf("%d ", arry[i]);
//	}
//	while(left <= right) {
//		int temp = arry[left];
//		arry[left] = arry[right];
//		arry[right] = temp;
//		left++;
//		right--;
//	}
//	printf("\n");
//	for (int i = 0; i < 5; i++) {
//		printf("%d ", arry[i]);
//	}
//}
//#include<stdio.h>
//int main() {
//	int arry[3][3] = { 1,2,3,4,5,6,7,8,9 };
//	int sum = 0;
//	for (int i = 0; i < 3; i++) {
//		sum += arry[i][i];
//	}
//	for (int i = 2, j = 0; i >=0 &&j < 3; i--,j++) {
//		sum += arry[i][j];
//	}
//	sum -= arry[2][2];
//	printf("%d", sum);
//}
//#include<stdio.h>
//int main() {
//	int arry[10] = { 6,3,8,5,9,2,1,4,7,0 };
//	for (int i = 0; i < 10; i++) {
//		int min = i;
//		for (int j = i + 1; j < 10; j++) {
//			if (arry[j] < arry[min]) {
//				min = j;
//			}
//		}
//		int temp = arry[i];
//		arry[i] = arry[min];
//		arry[min] = temp;
//	}
//	for (int i = 0; i < 10; i++) {
//		printf("%d", arry[i]);
//	}
//}
//#include<stdio.h>
//int main() {
//	int arry[10] = { 0,1,2,3,4,5,6,7,8 };
//	int insertnum = 5;
//	for (int i = 0; i < 9; i++) {
//		if (insertnum <= arry[i]) {
//			for (int j = 8; j >= i; j--) {
//				arry[j + 1] = arry[j];
//			}
//			arry[i] = insertnum;
//			break;
//		}
//	}
//	for (int i = 0; i < 10; i++) {
//		printf("%d", arry[i]);
//	}
//}
//#include<stdio.h>
//int main() {
//	char arry1[100];
//	for (int i = 0; i < 100; i++) {
//		arry1[i] = ' ';
//	}
//	char arry2[100];
//	for (int i = 0; i < 100; i++) {
//		arry2[i] = ' ';
//	}
//	char ch1;
//	int index1 = 0;
//	while ((ch1 = getchar()) != '\n' && index1 < 99) {
//		arry1[index1] = ch1;
//		index1++;
//	}
//	arry1[index1] = '\0';
//	int index2 = 0;
//	char ch2;
//	while ((ch2 = getchar()) != '\n' && index2 < 99) {
//		arry2[index2] = ch2;
//		index2++;
//	}
//	arry2[index2] = '\0';
//	for (int i = 0; i <= index1; i++) {
//		if (arry1[i] > arry2[i]) {
//			printf("1");
//			break;
//		}
//		if (arry1[i] == arry2[i] && arry1[i+1] == ' ' && arry2[i+1] == ' ') {
//			printf("0");
//			break;
//		}
//		if (arry1[i] < arry2[i]) {
//			printf("-1");
//			break;
//		}
//	}
//}
//#include<stdio.h>
//int main() {
//	char ch;
//	int bigletter = 0;
//	int smallletter = 0;
//	int space = 0;
//	int other = 0;
//	int count = 0;
//	while (count != 3) {
//		if ((ch = getchar()) == '\n') {
//			count++;
//			continue;
//		}
//		if (ch >= 'A' && ch <= 'Z') {
//			bigletter++;
//		}
//		else if (ch >= 'a' && ch <= 'z') {
//			smallletter++;
//		}
//		else if (ch == ' ') {
//			space++;
//		}
//		else {
//			other++;
//		}
//	}
//	printf("大写字母数%d,小写字母数%d，空白字符数%d，其他字符数%d", bigletter, smallletter, space, other);
//}
#include<stdio.h>
int main() {
	char arry[26];
	
	for (int i = 0; i < 26; i++) {
		arry[i] = 'a' + i;
	}
	char ch;
	char arry1[100];
	int n = 0;
	while ((ch = getchar()) != '\n') {
		int index = 26 - (ch - 'a' + 1) + 1;
		arry1[n] = arry[index];
		n++;
	}
	for (int i = 0; i < n; i++) {
		printf("%c", arry1[i]);
	}
}