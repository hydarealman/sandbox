#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int dir[2][4] = { 0,1,1,0,0,-1,-1,0 };
void bfs(vector<vector<int>> grid, vector<vector<bool>> visited, int x, int y) {
	queue<int, int> que;
	que.push(make_pair(x, y));
	while (!que.empty()) {
		pair<int, int> cur = que.front(); que.pop();
		int curx = cur.first;
		int cury = cur.second;
		for (int i = 0; i < 4; i++) {
			int nextx = curx + grid[i][0];
			int nexty = cury + grid[i][1];
			if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;
			if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) {
				que.push(make_pair(nextx, nexty));
				visited[nextx][nexty] = false;
			}
		}
	}
}
int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> grid(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
		}
	}
	vector<vector<bool>> visited(n, vector<bool>(m, 0));
	int result = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!visited[i][j] && grid[i][j] == 1) {
				result++;
				bfs(grid, visited, i, j);
			}
		}
	}
	cout << result << endl;
}