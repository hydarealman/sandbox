#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
int main() {
	vector<int> strength = { 1,5,5,5 };
	int num = 16;
	while (num--) {
		next_permutation(strength.begin(), strength.end());
		for (vector<int>::iterator it = strength.begin(); it != strength.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}