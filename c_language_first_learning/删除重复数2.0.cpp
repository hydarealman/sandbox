#include<iostream>
#include<vector>
using namespace std;
int main(){
	vector<int> num = {2,3,2,3,2,3,6,6,6,9,6,8,3,2,4,7,8,9,9,8,2,5,1,8,1};
	int size = num.size();
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (num[i] == num[j]) {
				for (int u = j + 1; u < size; u++) {
					num[u-1] = num[u];
				}
				j--;
				size--;
			}
		}
	}
	for (int i = 0; i < size; i++) {
		cout << num[i] << " ";
	}
}
