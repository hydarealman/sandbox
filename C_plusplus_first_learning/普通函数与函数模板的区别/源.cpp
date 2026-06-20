#include<iostream>
using namespace std;
int test001(int a, int b) {
	return a + b;
}
template<typename T>
int test002(T a, T b) {
	return a + b;
}
void test01() {
	int a = 10;
	int b = 20;
	int c = 'c';
	cout << test001(a,b) << endl;
	cout << test002<int>(a, b) << endl;
}
int main() {
	test01();
	system("pause");
	return 0;
}