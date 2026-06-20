#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
int main() {
    vector<int> nums1 = { 4,2,1,5,3 };
    vector<int> nums2 = { 10, 20, 30, 40, 50 };
    int k = 2;
            vector<long long> result;
            for (int i = 0; i < nums1.size(); i++) {
                vector<int> vec;
                for (int j = 0; j < nums1.size(); j++) {
                    if (nums1[j] < nums1[i]) {
                        vec.push_back(j);
                    }
                }
                vector<long long> num;
                for (int x = 0; x < vec.size(); x++) {
                    num.push_back(nums2[vec[x]]);
                }
                sort(num.begin(), num.end());
                int n = num.size();
                long long sum = 0;
                cout << n << endl;
                for (int i = 0; i < num.size(); i++) {
                    cout << num[i] << " ";
                }
                cout << endl;
                /*for (int i = n - 1; i >= n - k; i--) {
                    sum += num[i];
                }*/
                result.push_back(sum);
            }
}