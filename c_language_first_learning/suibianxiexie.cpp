#include<iostream>
using namespace std;
	template<class T>
	T abc(T a, T b, T c)
	{
		return a + b * c;
	}
	int main() {
		int a, b, c;
		cin >> a >> b >> c;
		cout << abc << endl;
	}
