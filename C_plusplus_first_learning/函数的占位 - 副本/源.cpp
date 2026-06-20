#include<iostream>
using namespace std;
void func(int a = 10, int = 10) {
	cout << a << endl;
}
int main() {
	func(20);
}