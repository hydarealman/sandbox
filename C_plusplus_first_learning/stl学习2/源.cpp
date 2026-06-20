//#include<iostream>
//using namespace std;
//#include<deque>
//
//void printDeque(const deque<int>& d) {
//	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
//		cout << *it << " ";
//	}
//}
//int main() {
//
//	deque<int> d1;
//	for (int i = 0; i < 10; i++) {
//		d1.push_back(i);
//	}
//	printDeque(d1);
//
//	system("pause");
//	return 0;
//}

//deque没有容量的限制而vector有容量

//deque容器的插入和删除

//#include<iostream>
//using namespace std;
//#include<deque>
//int main() {
//	deque<int> d1;
//	d1.push_back(100);
//	d1.push_back(200);
//	d1.push_front(100);
//	d1.push_front(100);
//	/*for (int i = 0; i < d1.size(); i++) {
//		cout << d1[i] << endl;
//	}*/
//	cout << d1.back() << endl;
//	cout << d1.front() << endl;
//	system("pause");
//	return 0;
//}

//deque排序操作
//#include<iostream>
//using namespace std;
//#include<deque>
//#include<algorithm>
//void printDeque(const deque<int>&d) {
//	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
//		cout << *it << " ";
//	}
//}
//void test01() {
//	deque<int>d;
//	d.push_back(100);
//	d.push_back(80);
//	d.push_back(155);
//	d.push_back(88);
//	printDeque(d);
//	sort(d.begin(), d.end());
//	//对于支持随机访问的迭代器的容器,都可以利用sort算法直接对其进行排序
//	cout << endl;
//	printDeque(d);
//}
//
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}

//评委打分
#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<deque>
#include<algorithm>
//选手类
class person {
public:
	person(string name, int score) {
		this->m_Name = name;
		this->m_Score = score;
	}
	string m_Name;
	int m_Score;
};
void creatperson(vector<person>&v) {
	string nameSeed = "ABCDE";
	for (int i = 0; i < 5; i++) {
		string name = "选手";
		name += nameSeed[i];

		int score = 0;
		person p(name, score);
		v.push_back(p);
	}
}

void setScore(vector<person>&v) {
	for (vector<person>::iterator it = v.begin(); it != v.end(); it++) {
		//将评委的分数 放入deque容器中
		deque<int>d;
		for (int i = 0; i < 10; i++) {
			int score = rand() % 41 + 60;
			d.push_back(score);
		}
		//排序
		sort(d.begin(), d.end());
		//去除最高分和最低分
		d.pop_back();
		d.pop_front();
		//取平均分
		int sum = 0;
		for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++) {
			sum += *dit;
		}
		int avg = sum / d.size();
		it->m_Score = avg;
	}
}
void showScore(vector<person>&v) {
	for (vector<person>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "姓名 " << (*it).m_Name << "平均分" << (*it).m_Score << endl;
	}
}

int main() {

	//创建5名选手
	vector<person>v;
	creatperson(v);

	//测试
	/*for (vector<person>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "姓名 " << (*it).m_Name << " 分数 " << (*it).m_Score << endl;
	}*/
	//给5名选手打分
	setScore(v);
	//显示最后得分
	showScore(v);

	system("pause");
	return 0;
}