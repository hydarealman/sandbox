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
