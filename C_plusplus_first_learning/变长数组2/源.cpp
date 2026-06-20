#include<iostream>
#include<vector>
using namespace std;
int main() {
	vector<int> arry;
	int num;
	while (scanf_s("%d", &num)) {
		arry.push_back(num);
	}
	int n = arry.size();
	for (int i = 0; i < n; i++) {
		printf("%d", arry[i]);
	}
}