#include<iostream>
using namespace std;
class Base {
public:
	int m_A = 10;
protected:
	int m_B = 10;
private:
	int m_C = 10;
};
//利用开发人员命令提示工具查看对象模型
class Son :public Base {
public:
	int m_D = 10;
};
void test01() {
	cout << "sizeof Son = " << sizeof(Son) << endl;
	//父类中所有非静态成员属性都会被子类继承下去
	//父类中私有成员属性 是被编译器给隐藏了，因此是访问不到的，但是确实被继承下去了
}
int main() {

	test01();

	system("pause");
	return 0;
}