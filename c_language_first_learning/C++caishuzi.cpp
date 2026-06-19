#include<iostream>
#include<stdlib.h>
using namespace std;

int main(){
	int num = rand()%100 + 1;
	int number;
	cin >> number ;
	while( number != num ){
		if(number > num)
		cout << "你输入的数字太大了" << endl;
		else 
		cout << "你输入的数字太小了" << endl;
		cin >> number ;
	}
	
	cout << "你输入的数字正确" << endl;
	system("pause");
	return 0;
}
 
