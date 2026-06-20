#include"speechManager.h"
#include"speaker.h"
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;

SpeechManager::SpeechManager() {
	//初始化属性
	this->initSpeech();
	//创建12名选手
	this->creatSpeaker();
	//加载往届记录
	this->loadRecord();
	//初始化比赛轮数
	this->m_Index = 1;
	//将记录的容器 也清空
	this->m_Record.clear();
}
void SpeechManager::clearRecord() {
	cout << "确认清空?" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
	}
	//初始化属性
	this->initSpeech();

	//创建选手
	this->creatSpeaker();

	//获取往届记录
	this->loadRecord();

	cout << "清空成功" << endl;
	system("pause");
	system("cls");
}
void SpeechManager::showRecord() {
	if (this->filesEmpty) {
		cout << "文件为空,或记录为空!" << endl;
	}
	else {
		for (int i = 0; i < m_Record.size(); i++) {
			cout << "第" << i + 1 << "届" <<
				"冠军编号" << this->m_Record[i][0] << "得分" << this->m_Record[i][1] << " "
				"亚军编号" << this->m_Record[i][2] << "得分" << this->m_Record[i][3] << " "
				"季军编号" << this->m_Record[i][4] << "得分" << this->m_Record[i][5] <<endl;
		}
	}
	system("pause");
	system("cls");
}
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);//输入流对象 读取文件
	if (!ifs.is_open()) {
		this->filesEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "文件为空" << endl;
		this->filesEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->filesEmpty = false;
	
	ifs.putback(ch);//将上面读取的单个字符再放回来
	string data;
	int index = 0;
	while (ifs >> data) {
		//cout << data << endl;
		vector<string>v;//存放6个string字符串
		int pos = -1;//查到逗号的位置的变量
		int start = 0;
		
		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				//没有找到的情况
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

	/*for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != m_Record.end(); it++) {
		cout << it->first << "冠军编号" << it->second[0] << "分数:" << it->second[1] << endl;
	}*/
}
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv",ios::out | ios::app);//用输出方式打开文件 --写文件

	//将每个人数据写入文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << ","
			<< m_Speaker[*it].m_score[1] << ",";
	}
	ofs << endl;

	//关闭文件
	ofs.close();

	cout << "记录已经保存" << endl;
	//有记录了,文件不为空
	this->filesEmpty = false;
}
void SpeechManager::show_Score() {
	cout << "-----------------------第" << this->m_Index << "轮晋级的选手的信息如下-----------------------" << endl;
	vector<int> v;
	if (this->m_Index == 1) {
		v = v1;
	}
	else {
		v = v2;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "选手编号" << *it << "姓名" << m_Speaker[*it].m_name << "得分" << m_Speaker[*it].m_score[m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	cout << endl;
}
void SpeechManager::speechContest() {
	cout << "第" << this->m_Index << "轮比赛正式开始------------------" << endl;

	//准备临时容器 存放小组成绩
	multimap<double, int, greater<double>> groupScore;//因为有可能两人分数相同

	int num = 0;//记录人员个数，六人一组

	vector<int> v_src;//比赛选手容器
	if (this->m_Index) {
		v_src = v1;
	}
	else {
		v_src = v2;
	}
	//遍历所有选手进行比赛
	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++) {
		//评委打分
		num++;
		deque<double>d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600)/10.f; //600-1000
			/*cout << score << " ";*/
			d.push_back(score);
		}
		/*cout << endl;*/
		sort(d.begin(), d.end(),greater<double>());
		d.pop_front();//去掉最高分
		d.pop_back();//去掉最低分
		double sum = accumulate(d.begin(), d.end(),0.0f);
		double avg = sum / (double)d.size();//平均分

		//打印平均分
		/*cout << "编号 " << *it << "姓名： " << this->m_Speaker[*it].m_name << "获取平均分" << avg << endl;*/
		
		//将平均分放入map容器里
		this->m_Speaker[*it].m_score[this->m_Index - 1] = avg;

		//将打分数据都放到临时容器中
		groupScore.insert(make_pair(avg, *it));//key得分,value是具体选手编号
		//每六人取出前三名
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛的名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "编号" << it->second << "姓名：" << this->m_Speaker[it->second].m_name << "比赛成绩:" <<
					this->m_Speaker[it->second].m_score[this->m_Index - 1] << endl;
			}
			//取走前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++,count++) {
				if (this->m_Index == 1) {
					v2.push_back((*it).second);
				}
				else {
					vVictory.push_back((*it).second);
				}
				cout << endl;
			}
			groupScore.clear();//小组容器清空
		}

	}
	cout << "第" << this->m_Index << "轮比赛完毕--------------------------------" << endl;
	system("pause");
	system("cls");
	cout << endl;
}
void SpeechManager::speechDraw() {
	cout << "第" << this->m_Index << "第几轮比赛选手正在抽签" << endl;
	cout << "------------------------" << endl;
	if (this->m_Index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "------------------------" << endl;
	system("pause");
	cout << endl;
}
void SpeechManager::startSpeech() {
	//第一轮比赛
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->show_menu();
	//第二轮比赛
	this->m_Index++;
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->show_Score();
	//4.保存分数
	this->saveRecord();
	//重制比赛,获取记录
	//初始化属性
	this->initSpeech();
	//创建12名选手
	this->creatSpeaker();
	//加载往届记录
	this->loadRecord();
}
void SpeechManager::initSpeech() {
	//确保容器为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	//初始化比赛轮数
	this->m_Index = 1;
}
void SpeechManager::creatSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_name = name;
		for (int i = 0; i < 2; i++) {
			sp.m_score[i] = 0;
		}

		//12名选手编号
		this->v1.push_back(i + 10001);

		//选手编号 以及对应选手 存放到nap容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}
void SpeechManager::show_menu() {
	cout << "**************************************" << endl;
	cout << "**********欢迎参加比赛****************" << endl;
	cout << "**********1.开始演讲比赛**************" << endl;
	cout << "**********2.查看往届记录**************" << endl;
	cout << "**********3.清空比赛记录**************" << endl;
	cout << "**********0.退出比赛程序**************" << endl;
	cout << "**************************************" << endl;
	cout << endl;
}
void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
SpeechManager::~SpeechManager() {

}