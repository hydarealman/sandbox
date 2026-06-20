#include<iostream>
#include<string>
using namespace std;
int main() {
	int arry[] = { 2,2,3,3,4,4,5,6 };
	int eor = 0;
	for (int i = 0; i < strlen(arry[]); i++) {
		eor ^= arry[i];
	}
	int rightone = eor & (~eor + 1);
	int onlyone = 0;
	for (int cur = 0; cur < strlen(arry[]); cur++) {
		if ((arry[cur] & rightone) == 0)
			onlyone ^= arry[cur];
	}
	cout << onlyone <<endl;
	cout << eor ^ onlyone << endl;
	system("pause");
	return 0;



}