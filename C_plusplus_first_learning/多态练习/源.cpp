#include<iostream>
using namespace std;
class father {
public:
	virtual void dospeak(){
		cout << "666" << endl;
}
};
class son1:public father {
public:
	void dospeak() {
		cout << "1" << endl;
	}
};
class son2 : public father{
public:
	void dospeak() {
		cout << "2" << endl;
	}
};
void speak(father &far) {
	far.dospeak();
}
void test01() {
	son1 s1;
	speak(s1);
	son2 s2;
	speak(s2);
}
int main() {

	test01();

	system("pause");
	return 0;
}