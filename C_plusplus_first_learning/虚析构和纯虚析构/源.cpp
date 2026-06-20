#include<iostream>
using namespace std;
#include<string>
class Animal {
public:
	//纯虚函数
	Animal() {
		cout << "Animal构造函数调用" << endl;
	}
	//利用虚析构可以解决 父类指针子类对象时不干净的问题
	/*virtual ~Animal() {
		cout << "Animale析构函数调用" << endl;
	}*/
	//纯虚析构 需要声明也需要实现
	//有了纯虚析构之后普，这个类也属于抽象类
	virtual ~Animal() = 0;
	virtual void speak() = 0;
};
Animal::~Animal() {
	cout << "Animale纯析构函数调用" << endl;
}

class Cat :public Animal {
public:

	Cat(string name) {
		cout << "Cat构造函数调用" << endl;
		m_Name = new string(name);
	}
	virtual void speak() {
		cout << *m_Name <<  " 小猫在说话 " << endl;
	}
	 ~Cat() {
		if (m_Name != NULL) {
			cout << "Cat析构函数调用 " << endl;
			delete m_Name;
			m_Name = NULL;
		}
	}
	string* m_Name; 
};

void test01() {
	Animal* animal = new Cat("Tom");
	animal->speak();
	//父类指针在析构时候，不会调用子类中析构函数，导致子类如果有堆区属性，出现内存泄露
	delete animal;
}
int main() {

	test01();

	system("pause");
	return 0;
}