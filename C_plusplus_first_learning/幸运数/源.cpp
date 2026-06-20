//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//int main()
//{
//  int cnt = 0;
//  for (int i = 1; i <= 100000000; i++ ) {
//    int num = i;
//    vector<int> result;
//    while(num){
//      result.push_back(num%10);
//      num /= 10;
//    }
//    int size = result.size();
//    if (size%2 != 0) continue;
//    int leftsum = 0;
//    int rightsum = 0;
//    int middlesize = size / 2;
//    for (int j = 0; j < middlesize; j++) {
//      leftsum += result[j];
//    }
//    for (int j = middlesize; j < size; j++) {
//      rightsum += result[j];
//    }
//    if (leftsum == rightsum) cnt++;
//  }
//  cout << cnt << endl;
//  // 请在此输入您的代码
//  return 0;
//}
//#include<iostream>
//using namespace std;
//int main() {
//	int n, a, b;
//	cin >> n;
//	int mn = 0, mx = 1e9;
//	while (n--) {
//		cin >> a >> b;
//		mn = max(mn, (a / (b + 1)) + 1);
//		mx = min(mx, a / b);
//		cout << mn << " " << mx;
//	}
//}
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
int main() {
	int ans = 0;
	for (int i = 1; i <= 100000000; ++i) {
		string s = to_string(i);
		int n = (int)s.size();
		if (n % 2) continue;
		int l = 0, r = 0;
		for (int j = 0; j < n; ++j) {
			if (j < n / 2) l += s[j] - '0';
			else r += s[j] - '0';
		}
		if (l == r) ans++;
	}
	cout << ans << "\n";
	return 0;
}