//#include<stdio.h>
//void up_and_down(int);
//
//int main() {
//	up_and_down(1);
//	return 0;
//}
//
//void up_and_down(int n) {
//	printf("Level %d: n location %p\n", n, &n);
//	if (n < 4)
//		up_and_down(n + 1);
//	printf("LEVEL %d: n location %p\n", n, &n);
//}

//#include<stdio.h>
//long fact(int n);
//long rfact(int n);
//int main() {
//	int num;
//
//	printf("This program calculates factorials.\n");
//	printf("Enter a value in the programe 0-12 (q to quit)\n");
//	while (scanf_s("%d", &num) == 1) {
//		if (num < 0) {
//			printf("No negative numbers,please.\n");
//		}
//		else if (num > 12) {
//			printf("keep input under 13\n");
//		}
//		else {
//			printf("loop: %d factorical = %ld\n",
//				num, fact(num));
//			printf("recursion: %d factorical = %ld\n",
//				num, rfact(num));
//		}
//		printf("Enter a value in the range 0-12 (q to quit):\n");
//	}
//	printf("Bye.\n");
//
//	return 0;
//}
//
//long fact(int n) {
//	long ans;
//
//	for (ans = 1; n > 1; n--) {
//		ans *= n;
//	}
//
//	return ans;
//}
//
//long rfact(int n) {
//	long ans;
//
//	if (n > 0)
//		ans = n * rfact(n - 1);
//	else
//		ans = 1;
//
//	return ans;
//}

  //以二进制形式打印整数
#include<stdio.h>
void to_binary(unsigned long n);

int main() {
	unsigned long number;
	printf("Enter an integer (q to quit)：\n");
	while (scanf_s("lu", &number) == 1) {
		printf("Binary equivalent: ");
		to_binary(number);
		putchar('n');
		printf("Enter an integer(q to quit) : \n");
	}
	printf("Done.\n");

	return 0;
}

void to_binary(unsigned long n) {
	int r;

	r = n % 2;
	if (n >= 2)
		to_binary(n / 2);
	putchar(r == 0 ? '0' : '1');

	return;
}