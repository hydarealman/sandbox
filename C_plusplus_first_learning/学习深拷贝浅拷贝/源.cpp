#include<iostream>
using namespace std;
class person {
public:
	person() {
		cout << "person的默认构造函数" << endl;
	}
	person(int age,int height) {
		int m_age = age;
		m_height = new int(height);
		cout << "person的有参构造函数" << m_age << endl;
		cout << "身高为" << *m_height << endl;

	}
	//浅拷贝带来堆区内存的重复释放//浅拷贝要利用深拷贝来释放
	~person() {
		//析构代码，在堆区开辟数据做释放
		/*if (m_height != NULL) {
			delete m_height;
			m_height = NULL;
		}
		cout << "person的析构构造函数" << endl;*/
		if (m_height != NULL) {
			delete m_height;
			m_height = NULL;
		}
	}
	person(const person& p) {
		cout << "person的拷贝构造函数的调用" << endl;
		m_age = p.m_age;
		m_height = new int(*p.m_height);

	}
	int m_age;
	int* m_height;
};
void test01() {
	person p1(18,160);
	person p2(p1);

}
int main() {
	test01();
}