//831. KMP字符串
//
//给定一个字符串 S，以及一个模式串 P，所有字符串中只包含大小写英文字母以及阿拉伯数字。
//模式串 P 在字符串 S 中多次作为子串出现。
//求出模式串 P 在字符串 S 中所有出现的位置的起始下标。
//
//输入格式
//第一行输入整数 N，表示字符串 P 的长度。
//第二行输入字符串 P。
//第三行输入整数 M，表示字符串 S 的长度。
//第四行输入字符串 S。
//
//输出格式
//共一行，输出所有出现位置的起始下标（下标从 0 开始计数），整数之间用空格隔开。
//
//数据范围
//1 ≤ N ≤ 10 ^ 5
//1 ≤ M ≤ 10 ^ 6
//#include<iostream>
//#include<string>
//using namespace std;
//const int N = 100010, M = 1000010;
//int n, m;
//int ne[N];
//string s, p;
//
//void get_Next(string s, int ne[]) {
//	int j = 0;
//	ne[0] = 0;
//	for (int i = 1; i < s.size(); i++) {
//		while (j > 0 && s[i] != s[j]) j = ne[j - 1];
//		if (s[i] == s[j]) j++;
//		ne[i] = j;
//	}
//}
//int main() {
//	cin >> n >> p >> m >> s;
//	get_Next(p, ne);
//	for (int i = 0, j = 0; i < m; i++) {
//		while (j > 0 && s[i] != p[j]) j = ne[j - 1];
//		if (s[i] == p[j])j++;
//		if (j == n) {
//			cout << i - n + 1 << " ";
//			j = ne[j - 1];
//		}
//	}
//	return 0;
//}

void get_Next(string s, int next[]) {
	int j = 0;
	next[0] = 0;
	for (int i = 1; i < s.size(); i++) {
		while (j > 0 && s[i] != s[j]) j = next[j - 1];
		if (s[i] == s[j]) j++;
		next[i] = j;
	}
}
int strStr(string s, string t) {
	if (t.size() == 0) return 0;
	get_Next(t, next);
	int j = 0;
	for (int i = 0; i < s.size(); i++) {
		while (j > 0 && s[i] != t[j]) j = next[j - 1];
		if (s[i] == t[j])j++;
		if (j == t.size()) return i - t.size() + 1;
	}
	return -1;
}