#include<iostream>
#include<vector>
using namespace std;
int grid[4][2] = { 0,1,1,0,0,-1,-1,0 };
void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
	for (int i = 0; i < 4; i++) {
		int nextx = x + grid[i][0];
		int nexty = y + grid[i][1];
		if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;
		if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) {
			visited[nextx][nexty] = true;
			dfs(grid, visited, nextx, nexty);
		}
	}
}
int main() {
	int n, m;
	vector<vector<int>> grid(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
		}
	}
	vector<vector<bool>> visited(m, vector<bool>(n, false));
	int result = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!visited[i][j] && grid[i][j] == 1) {
				visited[i][j] = true;
				result++;
				dfs(grid, visited, i, j);
			}
		}
	}
	cout << result << endl;
}