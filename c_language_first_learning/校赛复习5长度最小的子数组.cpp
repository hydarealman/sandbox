#include<iostream>
#include<vector>
#include<algorithm>
#include<stdint.h>
using namespace std;
int main(){
	vector<int> num = {5,6,9,8,2,8,4,1,5,1,1,1,1,5,10};
	int s = 10;
	int result = INT32_MAX;
	for (int i = 0; i < num.size(); i++) {
		int sum = 0;
		int sublength = 0;
		for (int j = i; j < num.size(); j++) {
			sum += num[j];
			sublength++;
			if (sum >= s) {
				result = result > sublength ? sublength : result;
			}
		}
	}
	int n =  result == INT32_MAX ? 0 : result ;
	cout << n;
} 
