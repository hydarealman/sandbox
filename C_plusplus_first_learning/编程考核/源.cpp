//#include<iostream>
//using namespace std;
//class maker {
//public:
//	maker(int id, int age) {
//		this->m_id = id;
//		this->m_age = age;
//	}
//	int m_id;
//	int m_age;
//	maker operator+ (maker& m2) {
//		this->m_id =  this->m_id + m2.m_id;
//	}
//	maker operator+ (maker& m2) {
//		this->m_age = this->m_age + m2.m_age;
//	}
//};
//int main() {
//	maker m1(2, 3);
//	maker m2(4, 5);
//	maker m3 = m1 + m2;
//	
//	system("pause");
//	return 0;
//}
//

//#include<iostream>
//using namespace std;
//#include<vector>
//void turnFunc(vector<vector<int>>& v,vector<vector<int>>& result) {
//	for (int i = 1; i <= 3; i++) {
//		for (int j = 1; j <= 3; j++) {
//			int num = (v[i - 1][i - 1] + v[i - 1][j] + v[i - 1][j + 1] 
//				       + v[i][j - 1] + v[i][j] + v[i][j+1] 
//				       + v[i + 1][j - 1] + v[i + 1][j] + v[i + 1][j + 1])
//				       / 9;
//			result[i - 1][j - 1] = num;
//		}
//	}
//}
//void inputArry(vector<vector<int>> &v) {
//	for (int i = 0; i < 5; i++) {
//		for (int j = 0; j < 5; j++) {
//			cin >> v[i][j];
//		}
//	}
//}
//void outputArry(vector<vector<int>>& v) {
//	for (int i = 0; i < v.size(); i++) {
//		for (int j = 0; j < v[0].size(); j++) {
//			cout << v[i][j] << " ";
//		}
//		cout << endl;
//	}
//}
//int main() {
//	vector<vector<int>> arry(5, vector<int>(5, 0));
//	vector<vector<int>> result(3, vector<int>(3, 0));
//	cout << "请输入一个5*5数组" << endl;
//	inputArry(arry);
//	turnFunc(arry, result);
//	outputArry(result);
//	system("pause");
//	return 0;
//}



//#include<iostream>
//using namespace std;
//#include<vector>
//vector<int> turnFunc(int n, int k) {
//	vector<int> result;
//	while (n > 0) {
//		result.push_back(n % k);
//		n /= k;
//	}
//	for (int i = 0; i < result.size(); i++) {
//		cout << result[i];
//	}
//	cout << endl;
//	return result;
//}
//bool isvec(vector<int> v) {
//	int left = 0;
//	int right = v.size() - 1;
//	while(left <= right) {
//		if (v[left] != v[right]) {
//			return false;
//		}
//		left++;
//		right--;
//	}
//	return true;
//}
//int main() {
//	int n;
//	cin >> n;
//	int k;
//	cin >> k;
//	if (isvec(turnFunc(n, k))) {
//		cout << "true" << endl;
//	}
//	else {
//		cout << "false" << endl;
//	}
//	system("pause");
//	return 0;
//}


//#include<iostream>
//using namespace std;
//#include<math.h>
//class launchbody {
//public:
//	float calculatetime(float myhigh, float otherhigh) {
//		float temp = 2*(myhigh - otherhigh) / 9.8;
//		float result = pow(temp, 0.5);
//		return result;
//	}
//	float calculatedistance(float speed,float time) {
//		float distance = speed * time;
//		return distance;
//	}
//	float m_speed = 14;
//	float myhigh = 2;
//	float g = 9.8;
//	float m = 0.25;
//	float otherhigh = 1;
//};
//int main() {
//
//	launchbody l1;
//	float time = l1.calculatetime(l1.myhigh, l1.otherhigh);
//	cout << "目标一与发射机构的水平距离为:" << l1.calculatedistance(l1.m_speed,time) << endl;
//
//	system("pause");
//	return 0;
//}
//

//#include<iostream>
//using namespace std;
//#include<string>
//#include<vector>
//class Solution {
//public:
//	bool arrayStringAreEqual(vector<string>& word1, vector<string> word2) {
//		vector<char> result1;
//		vector<char> result2;
//		for (int i = 0; i < word1.size(); i++) {
//			for (int j = 0; j < word1[i].size(); j++) {
//				result1.push_back(word1[i][j]);
//			}
//		}
//		for (int i = 0; i < word2.size(); i++) {
//			for (int j = 0; j < word2[i].size(); j++) {
//				result2.push_back(word2[i][j]);
//			}
//		}
//		int left = 0;
//		int right = 0;
//		for (int i = 0; i < result1.size(); i++) {
//			if (result1[i] != result2[i]) {
//				return false;
//			}
//		}
//		return true;
//	}
//};
//int main() {
//	vector<string> word1 = { "ab","c" };
//	vector<string> word2 = { "a","bc" };
//	Solution s1;
//	if (s1.arrayStringAreEqual(word1, word2)) {
//		cout << "true" << endl;
//	}
//	else {
//		cout << "false" << endl;
//	}
//	system("pause");
//	return 0;
//}

#include<iostream>
using namespace std;
#include<vector>
int index = 0;
void Josephusproblem(vector<int>& arry, int m) {
	while (!arry.empty()) {
		for (int i = 0; i < m; i++) {
			index = index % arry.size();
			index++;
		}
		reverse(arry.begin(), arry.end());
		cout << arry[index] << endl;
		vector<int>::iterator pos = arry.begin();
		arry.erase(pos + index);
	}
}

int main() {
	int n;
	cout << "请输入有几个人" << endl;
	cin >> n;
	int m;
	cout << "请输入每次报数到第几个人" << endl;
	cin >> m;

	vector<int> arry;
	for (int i = 1; i <= n; i++) {
		arry.push_back(i);
	}
	Josephusproblem(arry, m);

	system("pause");
	return 0;
}
