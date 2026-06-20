//#include<iostream>
//#include<string>
//using namespace std;
//int main() {
//	int x = 566;
//	string str = to_string(x);
//	cout << str << endl;
//	cout << str[0] << endl;
//	return 0;
//}

#include<iostream>
#include<string>
using namespace std;
int main() {
	string str = "32";
	int x = stoi(str,0,2);
	cout << x << endl;
	return 0;
}