//#include<stdio.h>
//int main() {
//	int flizny[10];
//	if (flizny == &flizny[0]) {
//		printf("yes");
//	}
//}
//#include<stdio.h>
//#define SIZE 4
//int main(void) {
//	short dates[SIZE];
//	short* pti;
//	short index;
//	double bills[SIZE];
//	double* ptf;
//	pti = dates;
//	ptf = bills;
//	printf("%23s %15s\n", "short", "double");
//	for (index = 0; index < SIZE; index++) 
//		printf("pointers + %d: %10p %10p\n", index, pti + index, ptf + index);
//		return 0;
//	
//}
//#include<stdio.h>
//int main() {
//	int dates[4];
//	if (dates + 2 == &dates[2]) {
//		printf("666");
//	}
//	if (*(dates + 2) == dates[2]) {
//		printf("999");
//	}
//}
//#include<stdio.h>
//#define MONTHS 12
//int main(void) {
//	int days[MONTHS] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
//	int index;
//
//	for (index = 0; index < MONTHS; index++) {
//		printf("MONTH %2d has %d days.\n", index + 1, *(days + index));
//		
//	}
//}
//#include<stdio.h>
//#define SIZE 10
//int sum(int* ar , int n) {
//	int i;
//	int total = 0;
//
//
//	for (int i = 0; i < 10; i++) {
//		total += ar[i];
//	}
//	printf("the size of ar is %zd bytes.\n", sizeof ar);
//	return total;
//}
//int main() {
//	int marbles[SIZE] = { 20,10,5,39,4,16,19,26,31,20 };
//	long answer;
//
//	answer = sum(marbles, SIZE);
//	printf("the total number of marbles is %ld.\n", answer);
//	printf("the size of marbles is %zd bytes .\n", sizeof marbles);
//
//	return 0;
//}
//#include<stdio.h>
//#define SIZE 10
//int sum(int* start, int* end) {
//	int total = 0;
//
//	while (start < end) {
//		total += *start;
//		start++;
//	}
//	return total;
//}
//int main() {
//	int arry[SIZE] = { 0,1,2,3,4,5,6,7,8,9 };
//	int total = sum(arry, arry + SIZE);
//		printf("%d", total);
//}
//#include<stdio.h>
//int main() {
//	int urn[5] = { 100,200,300,400,500 };
//	int* ptr1, * ptr2, * ptr3;
//
//	ptr1 = urn;
//	ptr2 = &urn[2];
//
//	printf("pointer value ,dereferenced pointer, pointer address");
//	printf("ptr1 = %p, *ptr1 = %d , &ptr1 = %p.\n", ptr1, *ptr1, &ptr1);
//	ptr1++;
//
//
//
//}
//#include<stdio.h>
//int main() {
//	int arry[9] = { 1,2,3,4,5,6,7,8,9, };
//	int* ptr1 = arry;
//	printf("%d\n", *(arry + 9));
//	printf("%d\n", *(arry + 10));
//	printf("%d\n", *(arry + 11));
//	printf("%d\n", *(arry - 100000));
//}
//#include<stdio.h>
//int main() {
//	int a;
//	int* ptr = &a;
//	*ptr = 5;//不要解引用未初始化的指针
//}
//#include<stdio.h>
//int sum(const int ar[],const int n) {
//	int i;
//	n = 100;//const可以用来保护数据
//	int total = 0;
//
//	for (int i = 0; i < n; i++) {
//		total += ar[i];
//		return total;
//	}
//}
//int main() {
//
//}
//int main() {
//	int (*pz)[2];// pz指向一个内含2个int类型值的数组
//	int* ptr[2];// pax是一个内含两个指针元素的数组，每个元素都指向int的指针
//}
//
//#include<stdio.h>
//#define cols 3
//#define rows 4
//void sum_rows(int ar[][cols]) {
//
//}
//void sum_cols(int[][cols]) {
//
//}
//int sum2d(int (*ar)[cols], int) {
//
//}
//变长数组
//#include<stdio.h>
//#define ROWS 3
//#define COLS 4
//int sum2d(int rows, int cols, int ar[rows][cols]);
//int main() {
//	int i, j;
//	int rs = 3;
//	int cs = 10;
//	int junk[ROWS][COLS] = {
//		2,4,6,8,3,5,7,9,12,10,8,6
//	};
//
//	//不想写了差不多得了
//}
//int sum2d(int rows, int cols, int ar[rows][cols]) {
//	int r;
//	int c;
//	int tot = 0;
//	
//	for (r = 0; r < rows; r++)
//		for (c = 0; c < cols; c++)
//			tot += ar[r][c];
//
//	return tot;
//}