#include<iostream>
using namespace std;
int main() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << i << " " << j << "    ";
		}
		cout << endl;
	}
	for (int i = 10; i >= 0; i--) {
		for (int j = i; j < 10; j++) {
			cout << i << " " << j << "    ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}