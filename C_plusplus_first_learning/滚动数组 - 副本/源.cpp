#include<iostream>
#include<vector>
using namespace std;
int main() {
	int M, N;
	cin >> M >> N;

	vector<int> costs(M);
	vector<int> values(M);

	for (int i = 0; i < M; i++) {
		cin >> costs[i];
	}
	for (int j = 0; j < M; j++) {
		cin >> values[j];
	}

	vector<int> dp(N + 1, 0);

	for (int i = 0; i < M; ++i) {
		for (int j = N; j >= costs[i]; --j) {
			dp[j] = max(dp[j], dp[j - costs[i]] + values[i]);
		}
	}

	cout << dp[N] << endl;

	return 0;
}