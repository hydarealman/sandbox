#include<iostream>
//#include<string>
using namespace std;
class Calculator {
public:
	int getResult(string oper) {
		if (oper == "+") {
			return m_Num1 + m_Num2;
		}
		else if (oper == "-") {
			return m_Num1 - m_Num2;
		}
		else if (oper == "/") {
			return m_Num1 / m_Num2;
		}
		else if (oper == "*") {
			return m_Num1 * m_Num2;
		}
		//在真实开发中 提倡 开闭原则
		//对扩展进行开放，对修改进行关闭
	}

	

	int m_Num1;
	int m_Num2;

};

//利用多态实现计算器
	//实现计算器抽象类
//多态好处
//组织结构清晰
//对于前期和后期的拓展可维护性高 
class AbstractCalculator {
public:
	virtual int getResult() {
		return 0;
	}
	int m_Num1;
	int m_Num2;
};
//加法计算器类
class AddCalculate :public AbstractCalculator {
public:
	int getResult() {
		return m_Num1 + m_Num2;
	}
};

class MulCalculate :public AbstractCalculator {
public:
	int getResult() {
		return m_Num1 * m_Num2;
	}
};

void test01() {
	Calculator c;
	c.m_Num1 = 10;
	c.m_Num2 = 10;
	cout << c.m_Num1 << " + " << c.m_Num2 << " = " << c.getResult("+") << endl;

	cout << c.m_Num1 << " - " << c.m_Num2 << " = " << c.getResult("-") << endl;
	 
	cout << c.m_Num1 << " * " << c.m_Num2 << " = " << c.getResult("*") << endl;

	cout << c.m_Num1 << " / " << c.m_Num2 << " = " << c.getResult("/") << endl;
}
void test02() {
	AbstractCalculator* abs = new AddCalculate;
	abs->m_Num1 = 10;
	abs->m_Num2 = 10;
	cout << abs->m_Num1 << " + " << abs->m_Num2 << " = " << abs->getResult() << endl;
	delete abs;

	abs = new MulCalculate;
	abs->m_Num1 = 10;
	abs->m_Num2 = 10;

	cout << abs->m_Num1 << " * " << abs->m_Num2 << " = " << abs->getResult() << endl;
	delete abs;
}
int main() {

	/*test01();*/
	test02();
	system("pause");
	return 0;
}