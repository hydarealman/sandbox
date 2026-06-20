#include<stdio.h>
int main() {
	int dp[10][10]{};
	for (int i = 1; i < 10; i++) {
		dp[i][i] = 1;
		dp[i][1] = 1;
	}
	for (int i = 1; i < 10; i++) {
		for (int j = 2; j < i; j++) {
			dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
		}
	}
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j <= i; j++) {
			printf("%d ", dp[i][j]);
		}
		printf("\n");
	}
}