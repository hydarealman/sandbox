#include<iostream>
#include<string>
using namespace std;
void swap(string str,int left,int right);
int main() {
	string str = "abcdefg";
	int num;
	int size = str.length();
	cin >> num;
	int left = 0;
	int right = size - num;
	cout << "修改前" << endl;
	for (int i = 0; i < size; i++) {
		cout << str[i] << " ";
	}
	for (int i = left; i < num; left++,right++) {
		swap(str,left,right);
	}
	cout << endl;
	cout << " 修改后 " << endl;
	for (int i = 0; i < size; i++) {
		cout << str[i] << " ";
	}

}
void swap(string str,int left,int right) {
	char temp;
	temp = str[left];
	str[left] = str[right];
	str[right] = temp;
}