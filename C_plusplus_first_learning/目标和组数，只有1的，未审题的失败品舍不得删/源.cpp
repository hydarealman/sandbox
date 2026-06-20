#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
        }
        if (target > sum) return false;
        if ((sum - target) % 2 == 1) return false;
        int a = (sum - target) / 2;
        int up = 1;
        int down = 1;
        for (int i = n; i >= 1; i--) {
            up *= i;
        }
        for (int i = n - a; i >= 1; i--) {
            down *= i;
        }

        return up / down;
    }
};
int main() {
    Solution p1;
    vector<int> nums = { 1,1,1,1,1,1,1,1,1,1 };
    int target = 6;
    cout << p1.findTargetSumWays(nums,target) << endl;
    return 0;
}