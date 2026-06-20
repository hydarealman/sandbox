#include<stdio.h>
int func(int* dp, int i, int j) {
	if (i == 10 && j == 10) {
		return func()
	}

}
int main() {
	int dp[11][11];
	for (int i = 1; i <= 10; i++) {
		dp[i][i] = dp[i][1] = 1;
	}

}