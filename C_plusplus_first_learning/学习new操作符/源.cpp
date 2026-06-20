#include<iostream>
using namespace std;
int func() {
	int* p = new int(10);
	return p;
}
void test01() {
	int* a = func();
	cout << *a << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}