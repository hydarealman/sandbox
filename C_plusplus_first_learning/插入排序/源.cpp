#include<iostream>
using namespace std;
int swap(int *arr, int i, int j);
int main() {
	int arr[10] = { 5,6,9,4,7,1,0,8,2,3 };

	for (int i = 0; i < 10; i++)
		cout << arr[i] << "";
	cout << endl;

	for (int i = 1; i < 10; i++)
		for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--)
			swap(arr, j, j+1);
	
	for (int i = 0; i < 10; i++)
		cout << arr[i] << "";
	
	system("pause");
}
    int swap(int *arr, int i, int j) {
	arr[i] = arr[i] ^ arr[j];
	arr[j] = arr[i] ^ arr[j];
	arr[i] = arr[i] ^ arr[j];
	return 0;
}