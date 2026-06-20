#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;
int main() {
	vector<char> vec;
	long long num;
	cout << "请输入一个数" << endl;
	cin >> num;
	unordered_map<int, char> m;
	m.insert({ 0,'0'});
	m.insert({ 1,'1'});
	m.insert({ 2,'2'});
	m.insert({ 3,'3'});
	m.insert({ 4,'4'});
	m.insert({ 5,'5'});
	m.insert({ 6,'6'});
	m.insert({ 7,'7'});
	m.insert({ 8,'8'});
	m.insert({ 9,'9'});
	m.insert({10,'A'});
	m.insert({11,'B'});
	m.insert({12,'C'});
	m.insert({13,'D'});
	m.insert({14,'E'});
	m.insert({15,'F'});
	while (num) {
		int each = num % 16;
		vec.push_back(m[each]);
		num /= 16;
	}
	vec.push_back('x');
	vec.push_back('0');
	reverse(vec.begin(), vec.end());
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i];
	}
	cout << endl;
}