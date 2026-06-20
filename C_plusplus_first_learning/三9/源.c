#include<stdio.h>
int main() {
	int year, month, day;
	int s = 0;
	scanf_s("%d%d%d", &year, &month, &day);
	printf("请输入年份：");
	printf("请输入月份：");
	printf("请输入日期：");
	switch (month)
	{
	case 12:s += 30;
	case 11:s += 31;
	case 10:s += 30;
	case 9:s += 31;
	case 8:s += 31;
	case 7:s += 30;
	case 6:s += 31;
	case 5:s += 30;
	case 3:s += 28;
	case 2:s += 31;
	case 1:s += day;
	}
	if ((year % 4 == 0 && year % 100 != 0 || year % 400 == 0) && year > 2)
		s++;
	printf("%d", s);
	return 0;
}