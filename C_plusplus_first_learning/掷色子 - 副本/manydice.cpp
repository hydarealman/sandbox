#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"diceroll.h"

int main() {
	int dice, roll;
	int sides;
	int status;
	
	srand((unsigned int)time(0));
	printf("Ente the number of sides per die ,0 to stop");
	while (scanf_s("%d", &sides) == 1 && sides > 0) {
		printf("How many dice?");
		if ((status = scanf_s("%d", &dice)) != 1) {
			if (status == EOF)
				break;
			else {
				printf("You should have enter an integer");
				printf("let's enter again");
				while (getchar() != '\n')
					continue;
				printf("How many sides? Enter 0 to stop.\n");
			}
			printf("The rollem() function was called %d times.\n", roll_count);
			printf("Good FORTUNE TO YOU!\n");

			return 0;
		}
	}
}
