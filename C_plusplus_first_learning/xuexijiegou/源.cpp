#include<stdio.h>
struct date {
	int year;
	int month;
	int day;
};
int main() {
	struct date today{07,31,2014};
	struct date thismonth{.year=2014, .month=31};
	printf("Today's date is %d %d %d", today.year, today.month, today.day);
	printf("Today's date is %d %d %d", thismonth.year, thismonth.month, thismonth.day);
		return 0;
}