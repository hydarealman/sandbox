#include<iostream>
#include<vector>
using namespace std;
int main(){
	vector<int> num = {2,2,2,3,6,2,4,8,9,8,7,5,2,3,6,7,4,8,9,5,1,5,2,6,4};
	int size = num.size();
	int cnt = size;
	for (int i = 0; i < size; i++) {
		int slow = i+1;
		for (int fast = i+1; fast < num.size(); fast++) {
			if (num[i] != num[fast]) {
				num[slow++] = num[fast];
			} 
		}
	}
	for (int i = 0; i < num.size(); i++) {
		cout << num[i] << " ";
	}
} 
