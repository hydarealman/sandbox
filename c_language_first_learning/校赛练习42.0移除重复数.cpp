#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
	int val;
	cin >> val;
	vector<int> num(9,0);
	int size = num.size();
	for (int i = 0; i < size; i++) {
		cin >> num[i];
	}
	for (int i = 0; i < size; i++) {
		if (val == num[i]) {
			for (int j = i + 1; j < size; j++) {
				num[j-1] = num[j];
			}
			size--;
			i--;
		}
	}
	for (int i = 0; i < size; i++) {
		cout << num[i] << " ";
	}
}
