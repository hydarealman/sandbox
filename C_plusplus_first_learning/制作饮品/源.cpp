#include<iostream>
using namespace std;

class AbstractDringking {
public:
	//煮水
	virtual void Boil() = 0;
	//冲泡
	virtual void Brew() = 0;
	//倒入杯中
	virtual void PourInCup() = 0;
	//加入辅料
	virtual void PutSomething() = 0;
	//制作饮品
	virtual void makeDrink() {
		Boil();
		Brew();
		PourInCup();
		PutSomething();
	}
};
//制作咖啡
class Coffee:public AbstractDringking {
public:
	//煮水
	virtual void Boil() {
		cout << " 煮开水 " << endl;
	}
	//冲泡
	virtual void Brew() {
		cout << " 冲泡咖啡 " << endl;
	}
	//倒入杯中
	virtual void PourInCup() {
		cout << " 倒入咖啡杯中 " << endl;
	}
	//加入辅料
	virtual void PutSomething() {
		cout << " 加入牛奶和糖 " << endl;
	}
	//制作饮品
	virtual void makeDrink() {
		Boil();
		Brew();
		PourInCup();
		PutSomething();
	}
};
//制作茶叶
class Tea :public AbstractDringking {
public:
	//煮水
	virtual void Boil() {
		cout << " 煮开水 " << endl;
	}
	//冲泡
	virtual void Brew() {
		cout << " 冲泡茶叶 " << endl;
	}
	//倒入杯中
	virtual void PourInCup() {
		cout << " 倒入茶杯中 " << endl;
	}
	//加入辅料
	virtual void PutSomething() {
		cout << " 加入枸杞 " << endl;
	}
	//制作饮品
	virtual void makeDrink() {
		Boil();
		Brew();
		PourInCup();
		PutSomething();
	}
};
void doWork(AbstractDringking* abs) {
	abs->makeDrink();
	delete abs;
}
void test01() {
	//制作咖啡
	doWork(new Coffee);
	cout << "-------------------------" << endl;
	doWork(new Tea);
}
int main() {

	test01();

	system("pause");
	return 0;
}