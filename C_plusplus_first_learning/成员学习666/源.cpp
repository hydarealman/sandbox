#include<iostream>
using namespace std;
class person
{
	int m_A;
	static int p;
	void func() {

	}
	static void func2() {

	}
};
int person::p;
void test01() {
	person p;
	//空对象占用内存的空间为
	cout << " size of p" << sizeof(p) << endl;


}
int main() {
	test01();


	system("pause");
}