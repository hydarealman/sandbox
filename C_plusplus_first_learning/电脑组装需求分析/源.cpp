#include<iostream>
using namespace std;
class CPU {
public:
	virtual void calculate() = 0;
};
class videoCard {
public:
	virtual void display() = 0;
};
class Memory {
public:
	virtual void storge() = 0;
};

class Computer {
public:
	Computer(CPU* cpu, videoCard* vc, Memory* mem) {
		m_cpu = cpu;
		m_vc = vc;
		m_mem = mem;
	}
	//提供工作函数
	void work() {
		//让零件工作起来，调用接口
		m_cpu->calculate();

		m_vc->display();

		m_mem->storge();
	}
	//提供析构函数释放3个电脑的零件
	~Computer() {
		//释放cpu
		if (m_cpu != NULL) {
			delete m_cpu;
			m_cpu = NULL;
		}
		//释放显卡
		if (m_vc != NULL) {
			delete m_vc;
			m_vc = NULL;
		}
		//释放内存
		if (m_mem != NULL) {
			delete m_mem;
			m_mem = NULL;
		}
	}
private:
	CPU* m_cpu;
	videoCard* m_vc;
	Memory* m_mem;
};
//具体厂商
//Intel厂商
class IntelCPU :public CPU {
public:
	void calculate() {
		cout << "Intel的CPU开始计算了!" << endl;
	}
};

class IntelvideoCard :public videoCard {
public:
	void display() {
		cout << "Intel的显卡开始显示了!" << endl;
	}
};

class IntelMemory :public Memory {
public:
	void storge() {
		cout << "Intel的内存开始存储了!" << endl;
	}
};
//Lenovo
class LenovoCPU :public CPU {
public:
	void calculate() {
		cout << "Lenovo的CPU开始计算了!" << endl;
	}
};

class LenovovideoCard :public videoCard {
public:
	void display() {
		cout << "Lenovo的显卡开始显示了!" << endl;
	}
};

class LenovoMemory :public Memory {
public:
	void storge() {
		cout << "Lenovo的内存开始存储了!" << endl;
	}
};

void test01() {
	//第一台电脑的零件
	CPU* intelCpu = new IntelCPU;
	videoCard* intelCard = new IntelvideoCard;
	Memory* intelmory = new IntelMemory;
	cout << "第一台电脑开始工作" << endl;
	//创建第一台电脑
	Computer* computer1 = new Computer(intelCpu, intelCard, intelmory);
	computer1->work();
	delete computer1;
	cout << "-------------------" << endl;
	cout << "第二胎电脑开始工作" << endl;
	//第二台电脑组装
	Computer* computer2 = new Computer(new LenovoCPU, new LenovovideoCard, new LenovoMemory);
	computer2->work();
	delete computer2;
	//第三台电脑组装
	cout << "-------------------" << endl;
	cout << "第三台电脑开始工作" << endl;
	Computer* computer3 = new Computer(new IntelCPU, new LenovovideoCard, new LenovoMemory);
	computer3->work();
	delete computer3;
}
int main() {
	
	test01();

	system("pause");
	return 0;
}