#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<unordered_map>
#include<queue>
using namespace std;
int main() {
	int n;
	cin >> n;
	string beginStr, endStr;
	cin >> beginStr >> endStr;
	string str;
	unordered_set<string> strSet;
	for (int i = 0; i < n; i++) {
		cin >> str;
		strSet.insert(str);
	}
	unordered_map<string, int> visitMap;

	queue<string> que;
	que.push(beginStr);

	visitMap.insert(pair<string, int>(beginStr, 1));

	while (!que.empty()) {
		string word = que.front();
		que.pop();
		int path = visitMap[word];
		for (int i = 0; i < word.size(); i++) {
			string newWord = word;
			for (int j = 0; j < 26; j++) {
				newWord[i] = j + 'a';
				if (newWord == endStr) {
					cout << path + 1 << endl;
					return 0;
				}
				if (strSet.find(newWord) != strSet.end() && visitMap.find(newWord) == visitMap.end()) {
					visitMap.insert(pair<string, int>(newWord, path + 1));
					que.push(newWord);
				}
			}
		}
	}
	cout << 0 << endl;
}