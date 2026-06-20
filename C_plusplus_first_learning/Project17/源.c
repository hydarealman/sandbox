#include<stdio.h>
struct date {
	int year;
	int month;
	int day;
};
int main() {
	struct date today;
	scanf_s("%d%d%d",today.year,today.month,today.day)
}