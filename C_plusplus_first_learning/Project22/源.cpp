#include<iostream>
using namespace std;
int* func() {
	 int *p = new int(10);
	return p;
}
void test01() {
	int* p = func();
	
	cout << *p << endl;
	cout << *p << endl;

}

void test02() {
	int* arr = new int[10];
	for (int i = 0; i < 10; i++) {
		arr[i] = i + 100;
	}
	for (int j = 0; j < 10; j++) {
		cout << arr[j] << endl;
	}
	delete[] arr;
}
int main() {

	//test01();
	test02();

	system("pause");

	return 0;
}