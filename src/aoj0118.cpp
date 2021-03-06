/*
 * AOJ 0118: Property Distribution
 * 题意：m＊n矩阵中，共3种植物。相邻的同种植物块可合并，问合并后共多少块区域。
 * 类型：DFS判断连通区域
 * 算法：从某点出发，向上下左右4个方向查询，若为同种植物则继续递归，经过的点需要记忆化。
 */

#include <cstdio>
#include <iostream>

using namespace std;


char mat[102][102];
int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int m, n, res;

void dfs(int x, int y) {
  char t = mat[x][y];
	mat[x][y] = '.';  //标记，标记过的就是一个连通区域了
	int xx, yy;
	for (int i = 0; i < 4; i++) {
		xx = x + dirs[i][0];
		yy = y + dirs[i][1];
		if (xx >= 0 && xx < m && yy >= 0 && yy < n && mat[xx][yy] == t) {
			dfs(xx, yy);
		}
	}
}

void solve() {
	res = 0;
	for (int i = 0; i < m; i++) cin >> mat[i];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
      if (mat[i][j] != '.') {
        res++;
        dfs(i, j);
      }
		}
	}
}

int main() {
	while (cin >> m >> n && m > 0 && n > 0) {
		solve();
		cout << res << endl;
	}
	return 0;
}



