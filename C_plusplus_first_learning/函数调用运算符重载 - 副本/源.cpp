#include<iostream>
#include<string>
using namespace std;
//打印输出类
class MyPrint {
public:
	void operator()(string str) {
		cout << str << endl;
	}
};
void MyPrint02(string str) {
	cout << str << endl;
}

void test01() {
	MyPrint myPrint;
	myPrint("hello world");
	MyPrint02("hello world");
}
//打印加法类
class MyAdd {
public:
	int operator()(int num1, int num2) {
		return num1 + num2;
	}
};
void test02() {
	MyAdd myadd;
	int ret = myadd(10, 20);
	cout << "ret = " << ret << endl;
	//匿名函数对象
	cout << MyAdd()(100, 100) << endl;

}
int main() {
	test01();
	test02();
}