//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//int main() {
//    int n;
//    cin >> n;
//    vector<int> num(n, 0);
//    for (int i = 0; i < n; i++) {
//        cin >> num[i];
//    }
//    vector<int> dp(n,0);
//    for (int i = 2; i < n; i++) {
//        dp[i] = max(dp[i - 1], dp[i - 2] + num[i]);
//    }
//    cout << dp[n];
//}
//#include<iostream>
//using namespace std;
//int main() {
//    int n;
//    int cnt = 0;
//    cin >> n;
//    cnt =  n / 15;
//    cout << cnt * 2 << endl;
//}
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main() {
    vector<int> num;
    int n;
    cin >> n;
    while (n) {
        num.push_back(n % 10);
        n /= 10;
    }
    int size = num.size();
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += num[i];
    }
    cout << sum;
}