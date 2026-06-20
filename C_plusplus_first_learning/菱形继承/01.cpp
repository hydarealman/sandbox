#include<iostream>
using namespace std;
class Animal {
public:
	int m_Age;
};
//利用虚继承 解决菱形继承的问题
//继承之前 加上关键字virtual 变为虚继承
//Animal类称为虚基类
class sheep :virtual public Animal{

};
class Tuo :virtual public Animal{

};
class SheepTuo :public sheep, public Tuo {

};
void test01() {

	SheepTuo st;
	st.sheep::m_Age = 18;
	st.Tuo::m_Age = 28;
	//当菱形继承，两个父类拥有相同数据，需要加以作用域区分
	cout << "st.sheep::m_Age = " << st.sheep::m_Age << endl;
	cout << "st.Tuo::m_Age = " << st.Tuo::m_Age << endl;
	cout << "st.m_age = " << st.m_Age << endl;
	//这份数据我们知道只有一份就可以，菱形继承导致数据有两份，资源浪费
}
int main() {
	test01();

	system("pause");
	return 0;
}
