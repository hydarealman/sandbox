//1207独一无二的出现次数
#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        vector<int> vec(1001, 0);
        if (arr.size() == 1) {
            return true;
        }
        for (int i = 0; i < arr.size(); i++) {
            vec[arr[i]]++;
        }
        for (int i = 0; i < arr.size(); i++) {
            if (vec[arr[i]] > 1) {
                return false;
            }
        }
        return true;
    }
};
int main() {
    vector<int> arr;
    arr.push_back(-3)
    Solution s;
    s.uniqueOccurrences(arr);
}