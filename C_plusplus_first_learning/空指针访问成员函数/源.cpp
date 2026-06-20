#include<iostream>
using namespace std;

class person {
public:

	void showClassName() {
		cout << "this is person class" << endl;
	}
	void showPersonAge() {
		//报错的原因传入的指针为空
		if (this == NULL) {
			return;
		}
		cout << "age = " << this->m_age << endl;
	}
	int m_age;
};

void test01() {
	person* p = NULL;
	p->showClassName();
	p->showPersonAge();
}
int main() {
	test01();
	system("pause");
	return 0;
}