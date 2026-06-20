#include<iostream>
#include<vector>
using namespace std;
int dir[2][4] = { 0,1,1,0,0,-1,-1,0 };
void dfs(vector<vector<int>> grid, vector<vector<bool>> visited, int x, int y) {
	grid[x][y] = 2;
	for (int i = 0; i < 4; i++) {
		int nextx = x + dir[i][0];
		int nexty = y + dir[i][1];
		if (x < 0 || x > grid.size() || y < 0 || grid[0].size()) continue;
		if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) {
			visited[nextx][nexty] = true;
			dfs(grid, visited, nextx, nexty);
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
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	for (int i = 0; i < n; i++) {
		if (!visited[i][0] && grid[i][0] == 1) dfs(grid, visited, i, 0);
		if (!visited[i][m - 1] && grid[i][m - 1] == 1) dfs(grid, visited, i, m - 1);
	}
	for (int i = 0; i < m; i++) {
		if (!visited[0][i] && grid[0][i] == 1) dfs(grid, visited, 0, i);
		if (!visited[n - 1][i] && grid[n - 1][i] == 1) dfs(grid, visited, n - 1, i);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 1) grid[i][j] = 0;
			if (grid[i][j] == 2) grid[i][j] = 1;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << grid[i][j] << endl;
		}
	}
}
