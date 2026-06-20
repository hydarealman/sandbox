#include"speechManager.h"
#include<iostream>
#include<ctime>
using namespace std;

int main() {
	//随机数种子
	srand((unsigned int) time(NULL));
	//创建管理类对象
	SpeechManager sm;

	//测试代码    creatManager能正常运行
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		cout << "选手编号: " << it->first
			<< " 姓名： " << it->second.m_name
			<< " 成绩：" << it->second.m_score[0] << endl;
	}*/

	sm.show_menu();

	
	int choice = 0;
	cout << "请输入你的选择" << endl;
	cin >> choice;

	while (true) {
		switch (choice) {
		case 1: //开始比赛
			sm.startSpeech();
			break;
		case 2://查看记录
			sm.showRecord();
			break;
		case 3://清空记录
			sm.clearRecord();
			break;
		case 0://退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
		sm.show_menu();
		cout << "请输入您的选择" << endl;
		cin >> choice;
	}

	system("pause");
	return 0;
}