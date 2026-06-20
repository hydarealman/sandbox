#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int cnt1[2]{}, cnt2[2]{};
        int left1 = 0, left2 = 0;
        int ans1 = 0, ans2 = 0;
        for (int right = 0; right < nums.size(); right++) {
            cnt1[nums[right] % 2]++;
            cnt2[nums[right] % 2]++;
            while (left1 <= right && cnt1[1] >= k) {
                cnt1[nums[left1] % 2]--;
                left1++;
            }
            ans1 += left1;
            cout << "ans1: " << ans1 << endl;
            while (left2 <= right && cnt2[1] > k) {
                cnt2[nums[left2] % 2]--;
                left2++;
            }
            ans2 += left2;
            cout << "ans2: " << ans2 << endl;
        }
        return ans1 - ans2;
    }
};
int main() {
    Solution s;
    vector<int> nums{ 1,1,2,1,1 };
    s.numberOfSubarrays(nums,2);

}