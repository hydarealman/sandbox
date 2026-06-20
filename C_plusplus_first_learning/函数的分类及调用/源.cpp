
#include<iostream>
	using namespace std;
	class person {
	public:
		person() {
			cout << "person的无参构造函数调用" << endl;
		}

		person(int a) {
			age = a;
			cout << "person的有参构造函数的调用" << endl;
		}
		person (const person & p) {
			cout << "person的拷贝构造函数的调用" << endl;
		}
		~person() {
			cout << "person的析构构造函数调用" << endl;
		}
		int age;
};
	void test01() {
		//括号
		/*person p1;*///调用默认构造函数时不要加括号//因为下面这行代码编译器会认为这是一个函数的声明,不会认为在创建对象
		//person p2(10);
		/*person p3(p2);*/
		/*cout << "p2的年龄" << p2.age << endl;
		cout << "p3的年龄" << p3.age << endl;*/
		//person p1;
		//person p2 = person(10);//匿名对象//当前行执行结束后，系统会立即回收掉匿名对象
		//person p3 = person(p2);
		//person(20);
		//不要利用拷贝构造函数，初始化匿名对象
		/*cout << "aaaa" << endl;*/
		person p4 = 10;//相当于person(p4) = person(10);

	}
	int main(){

	test01();
	system("pause");
	return 0;
}