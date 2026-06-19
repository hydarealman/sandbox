#include<iostream>
#include<vector>
using namespace std;
int main(){
	vector<int> num = {2,2,6,5,2,9,8,7,4,6,9,3,4,8,5,9,};
	int size = num.size();
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (num[i] == num[j]) {
				for (int u = j + 1; u < size; u++) {
					num[u - 1] = num[u];
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
