#include<iostream>
using namespace std;
int factorical(int n) {
	if (n <= 1) {
		return 1;
	}
	else {
		return n * factorical(n - 1);
	}
}
int factoricalsum(int n) {
	if (n == 1) {
		return factorical(1);
	}
	else {
		return factorical(n) + factorical(n - 1);
	}
}
int main() {
	int n;
	cout << " enter a number" << endl;
	cin >> n;
	cout << factoricalsum(n) << endl;
}