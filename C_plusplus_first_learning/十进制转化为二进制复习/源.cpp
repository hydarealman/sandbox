//方法一除二取余法
#include<iostream>
#include<vector>
using namespace std;
int main() {
	int n;
	cin >> n;
	vector<int> vec;
	while (n) {
		vec.push_back(n % 2);
		n /= 2;
	}
	for (int i = vec.size()-1; i >= 0; i--) {
		cout << vec[i];
	}
}