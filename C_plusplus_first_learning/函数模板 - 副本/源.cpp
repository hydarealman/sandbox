#include<iostream>
using namespace std;

template<typename T>
void mySwap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}
void test01() {
	int a = 10;
	int b = 20;
	mySwap(a, b);
	mySwap<int>(a, b);
	cout << "a = " << a << " b = " << b << endl;
	
}
int main() {

	test01();

	system("pause");
	return 0;
}