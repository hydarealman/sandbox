//#include<stdio.h>
//int main() {
//	int a;
//	int b;
//	scanf_s("%d", &a);
//	scanf_s("%d", &b);
//	int* pointer_1 = &a;
//	int* pointer_2 = &b;
//	printf("*pointer_1 = %d ", *pointer_1);
//	printf("*pointer_2 = %d", *pointer_2);
//}
//#include<stdio.h>
//#include<string.h>
//struct student {
//	int No;
//	char name[10];
//	char sex;
//	int age;
//};
//int main() {
//	student students[3] = {
//		{10101,"Li Lin",'M',18},
//		{10102,"Zhang Fun",'M',19},
//		{10104,"Wang Min",'F',20}
//	};
//	for (int i = 0; i < 3; i++) {
//		printf("NO:%d,name:%s,sex:%c,age:%d", students[i].No, students[i].name, students[i].sex, students[i].age);
//		printf("\n");
//	}
//}
//#include<stdio.h>
//#include<string.h>
//struct student {
//	int No;
//	char name[10];
//	float score;
//};
//int main() {
//	struct student students[5] = {
//		{10110 ,"Fun" ,100.00},
//		{10103 ,"Wang", 98.50},
//		{10106 ,"Li" ,86.00},
//		{10101 ,"Zhang", 78.00},
//		{10108 ,"Ling", 73.50}
//	};
//	for (int i = 0; i < 5 - 1; i++) {
//		for (int j = 0; j < 5 - 1 - i; j++) {
//			if (students[i].score < students[i + 1].score ) {
//				student temp = students[i];
//				students[i] = students[i + 1];
//				students[i + 1] = temp;
//			}
//		}
//	}
//	for (int i = 0; i < 5; i++) {
//		printf("No:%d , name: %s, score:%f", students[i].No, students[i].name, students[i].score);
//		printf("\n");
//	}
//
//}
//#include<stdio.h>
//#include<string.h>
//struct student {
//	int No;
//	char name[10];
//	float score[3];
//};
//float average(student students) {
//	float sum = 0.0;
//	for (int i = 0; i < 3; i++) {
//		 sum = students.score[i] + sum;
//	}
//	return sum / 3;
//}
//int main() {
//	student students = { 107151, " Zhang ", {98,88,79} };
//	printf("这门课的平均分为%f", average(students));
//}
//#include<stdio.h>
//#include<stdlib.h>
//#include<memory.h>
//struct student {
//	int No;
//	int score;
//};
//
//int main() {
//	int n;
//	scanf_s("%d", &n);
//	student* const students = (student*)malloc(n * sizeof(int));
//	memset(students, 0, n);
//	for (int i = 0; i < n; i++) {
//		scanf_s("%d", &students[i].No);
//		scanf_s("%d", &students[i].score);
//	}
//	for (int i = 0; i < n; i++) {
//		if (students[0].score < students[i].score) {
//			students[0].score = students[i].score;
//		}
//	}
//	printf("%d", students[0].score);
//	free(students);
//	return 0;
//}
//#include <stdio.h>
//
//int main()
//{
//    int aa[2][5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//    int* ptr1 = (int*)(&aa + 1);
//    int* ptr2 = (int*)(*(aa + 1));
//    printf("%d,%d", *(ptr1 - 1), *(ptr2 - 1));
//    return 0;
//}
#include<stdio.h>

int main()
{
    int a[5] = { 1, 2, 3, 4, 5 };
    int* ptr = (int*)(&a + 1);
    printf("%d,%d", *(a + 1), *(ptr - 1));
    return 0;
}