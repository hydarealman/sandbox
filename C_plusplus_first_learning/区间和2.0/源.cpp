#include<iostream>
#include<vector>
using namespace std;
int main() {
	int n, a, b;
	cin >> n;
	vector<int> vec1(n);
	vector<int> vec2(n);
	for (int i = 0; i < n; i++) {
		cin >> vec1[i];
	}

	for (int i = 0; i < n; i++) {
		int persum = 0;
		persum += vec1[i];
		vec2[i] = persum;
	}
	while (cin >> a >> b) {
		int sum;
		if(a == 0)
			sum = vec2[i]
		else
		sum = vec2[b] - vec2[a - 1];
		cout << sum << endl;
	}
}