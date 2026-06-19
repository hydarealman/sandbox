#include<iostream>
using namespace std;
int main(){
	int arry[5] {1,2,3,4,5};
	cout << sizeof(arry) << endl;
	cout << &arry << endl;
	cout << &arry[0] << endl;
	cout << &arry[1] << endl;
	cout << arry[0] << endl;
	cout << arry[1] << endl;
	cout << arry[4] << endl;
}
