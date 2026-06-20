#include<iostream>
using namespace std;
#include<vector>
int main() {
	for (int right = 0; right < 10; right++) {
		right = right % 10;
		cout << right << " ";
	}
}