#include<iostream>
using namespace std;
int main() {
	int n;
	scanf_s("%d", &n);
	int sum = 0;
	for (int j = 1; j <= n; j++) {
		int number = 1;
	for (int i = 1; i <= j; i++) {
		number = number * i;
	}
	sum += number;
}
	printf("%d", sum);
}