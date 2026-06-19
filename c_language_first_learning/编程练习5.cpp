#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
	vector<int> num(9,0);
	for (int i = 0; i < 9; i++) {
		cin >> num[i];
		num[i] = num[i]*num[i];
	}
	sort(num.begin(),num.end());
	for (int i = 0; i < 9; i++) {
		cout << num[i] << " ";
	}
	return 0;
}
