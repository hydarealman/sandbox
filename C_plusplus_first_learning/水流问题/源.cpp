#include<iostream>
#include<vector>
using namespace std;
int dir[2][4] = { 0,1,1,0,0,-1,-1,0 };
void dfs(vector<vector<int>> &grid, vector<vector<bool>> &visited, int x, int y) {
	if (visited[x][y]) return;
	visited[x][y] = true;
	for (int i = 0; i < 4; i++) {
		int nextx = x + dir[i][0];
		int nexty = y + dir[i][1];
		if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid.size()) continue;
		if (grid[x][y] > grid[nextx][nexty]) continue;
		dfs(grid, visited, nextx, nexty);
	}
}
int main() {
	//ÂÔ
}