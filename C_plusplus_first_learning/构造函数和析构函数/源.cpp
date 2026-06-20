#include<iostream>
using namespace std;

class person {
public:
	person() {
		cout << "person构造函数的调用" << endl;
	}
	//对象销毁前会自动调用析构函数
	~person() {
		cout << "person析构函数的调用" << endl;
	}
};

void test01() {
	person p;//在栈上的数据，test01执行完毕后，释放这个对象
}
int main() {
	test01();
	person p;
	system("pause");
	return 0;
}