#include<iostream>
#include<vector>
#include<climits>

using namespace std;
int main() {
	int n, m;
	cin >> n >> m;
	int sum = 0;


	vector<vector<int>> vec(n, vector(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> vec[i][j];
			sum += vec[i][j];
		}
	}

	//统计横向
	vector<int> horizontal(n, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			horizontal += vec[i][j];
		}
	}


	//统计纵向
	vector<int> vertical(m, 0);
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++)
			vertical[j] += vec[i][j];
	}


	int result = INT_MAX;
	int horizontalcut = 0;
	for (int j = 0; j < m; j++) {
		horizontalcut += horizontal[i];
		result = min(result, abs(sum - hotrizontalcut - horizontalcut));
	}



	int veticalcut = 0;
	for (int j = 0; j < m; j++) {
		verticalcut += vertical[j];
		result = min(result, abs(sum - veticalcut - verticalcut))
	}
	cout << result << endl;
}