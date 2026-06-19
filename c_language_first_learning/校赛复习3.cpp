#include<iostream>
#include<vector>
using namespace std;
int main(){
	int buycnt;
	cin >> buycnt;
	vector<int> result(7,0);
	vector<int> answer(7,0);
	for (int i = 0; i < 7; i++) {
		cin >> answer[i];
	}
	int testnumber = buycnt;
	vector<vector<int>> buynum(buycnt,vector<int> (7,0));
	while (buycnt > 0) {
		for (int i = 0; i < 7; i++) {
			cin >> buynum[buycnt][i];
		}
		buycnt--;
	}
	while (testnumber > 0) {
		int resultcnt = 0;
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				if (buynum[testnumber][i] == answer[j]) {
					resultcnt++;
					break;
				}
			}
		}
		result[resultcnt]++;
		testnumber--;
	}	
	for (int i = 7; i > 0; i--) {
		cout << result[i] << " ";
	}
	return 0; 
}
