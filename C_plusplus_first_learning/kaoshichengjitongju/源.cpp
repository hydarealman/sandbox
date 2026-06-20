#include<iostream>
#include<string>
using namespace std;
int main() {
	int arry[3][3] = {
		{65,59,78},
		{48,62,74},
		{91,73,66}
	};
	string names[3] = { "张三","李四","王五" };
	for (int i = 0; i < 3; i++) {
		int sum = 0;
		for (int j = 0; j < 3; j++)
			sum += arry[i][j];
		cout << names[i] << "";
		cout << sum << endl;
	}




	system("pause");
}