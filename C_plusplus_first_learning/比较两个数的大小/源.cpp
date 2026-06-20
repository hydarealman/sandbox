#include<iostream>
using namespace std;
#define a 10
#define b 20
int main() {
	
	if (a > b) {
		cout << "大的数是a,a是" << a << endl;
	}
	else if (b > a) {
		cout << "大的数是b,b是" << b << endl;
	}
	else
		cout << "a与b相等" << endl;
}