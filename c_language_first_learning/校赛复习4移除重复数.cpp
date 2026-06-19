#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
	int val;
	cin >> val;
	vector<int> result(9,0);
	int size = result.size();
	for (int i = 0; i < size; i++) {
		cin >> result[i];
	}
	for (int i = 0; i < size; i++) {
		if (result[i] == val) {
			for (int j = i + 1; j < size; j++) {
				result[j - 1] = result[j];
			}
			i--;
			size--;
		}
	}
	for (int  i = 0; i < size; i++) {
		cout << result[i] << " ";
	}
}
