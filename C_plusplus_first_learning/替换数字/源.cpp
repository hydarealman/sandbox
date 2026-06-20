#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
int main() {
	string s;
	while (cin >> s) {
		int s0 = s.size() - 1;
		int count = 0;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] >= '0' && s[i] <= '9') {
				count++;
			}
		}
		s.reserve(s.size() + count * 5);
		int snew = s.size() - 1;

		while (s0 >= 0) {
			if (s[s0] >= '0' && s[s0] <= '9') {
				s[snew--] = 'r';
				s[snew--] = 'e';
				s[snew--] = 'b';
				s[snew--] = 'm';
				s[snew--] = 'u';
				s[snew--] = 'n';
			}
			else {
				s[snew--] = s[s0];
			}
			s0--;
		}
		cout << s << endl;
	}
}