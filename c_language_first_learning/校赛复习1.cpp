#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class solution{
public:
	int search(vector<int>& nums, int target) {
		int left = 0;
		int right = nums.size() - 1;
		while (left <= right) {
			int middle = left + ((right - left) / 2);
			if (nums[middle] > target) {
				right = middle - 1;
			} else if (nums[middle] < target) {
				left = middle - 1;
			} else {
				return middle;
			}
		}
		return -1;
	}
		
};
int main(){
	vector<int> nums = {1,2,3,4,5,6,7,8,9};
	int target = 2;
	solution p1;
	solution p2;
	int result1 = p1.search(nums,target); 
	int result2 = p2.search(nums,10); 
	cout << result1 << endl;
	cout << result2 << endl;
	cout << target << endl;
	return 0;
} 
