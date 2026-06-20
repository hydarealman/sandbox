#include <iostream>
using namespace std;
int main() {
	int arry[] = { 8,8,9,9,0,0,1,1,2 };
	int eor = 0;
	for (int i = 0; i < sizeof(arry) / 4; i++) {
		eor ^= arry[i];
		}
	cout << eor << endl;
	system("pause");
	return 0;
}