#include<iostream>
using namespace std;
int main() {
	int arr[] = { 0,1,2,3,4,5,6 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
		cout << arr[i] << "";
	cout << endl;
	for (auto i : arr)
		cout << i << " ";
	cout << endl;
}