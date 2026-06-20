#include<stdio.h>
int main() {
	int year;
	int month;
	int day;
	scanf_s("%d %d %d", &year, &month, &day);
	if (!(year % 100 == 0) && year % 4 == 0) {
		if (month == 2) {
			if (month >= 0 && month <= 28)
				printf("有效");
			else
				printf("无效");

		}

		else if (month == 1 && month == 3 && month == 5 && month == 7 && month == 8 && month == 10 && month == 12) {
			if (day >= 0 && day <= 31)
				printf("有效");
			else
				printf("无效");
		}

		else if (month == 4 && month == 6 && month == 9 && month == 11) {
			if (day >= 0 && day <= 30)
				printf("有效");
			else
				printf("无效");

		}
	}
	else {
		if (month == 2) {
			if (month >= 0 && month <= 29)
				printf("有效");
			else
				printf("无效");
		}

		else if (month == 1 && month == 3 && month == 5 && month == 7 && month == 8 && month == 10 && month == 12) {
			if (day >= 0 && day <= 31)
				printf("有效");
			else
				printf("无效");
		}

	

		else if (month == 4 && month == 6 && month == 9 && month == 11) {
			if (day >= 0 && day <= 30)
				printf("有效");
			else
				printf("无效");

		}
}
}