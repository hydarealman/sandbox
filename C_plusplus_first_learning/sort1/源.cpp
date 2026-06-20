#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main() {
	vector<int> nums(10);
	nums = { 5,6,9,8,7,1,3,2,4,0 };
	sort(nums.begin(), nums.end());
	for (int i = 0; i < 10; ++i) {
		cout << nums[i] << " ";
	}
 }