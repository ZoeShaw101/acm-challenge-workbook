/*
 * POJ 3669: Meteor Shower
 * 题意：给出M次流星的落点和时间，流星会摧毁该点和上下左右四点，矩阵内每点只在摧毁前才可到达。从左上角出发，求能够到达永不会被摧毁的点最短时间。
 * 类型：BFS（／DFS）
 * 算法：预处理出每点最早被摧毁的时间，使用边界和摧毁时间作入队限制，直到队列空或到达不会被摧毁的点。注意初始状态可能为被摧毁或永不摧毁。
 */

#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

/**
 * 算法思路：
 * 到达安全区，即到达用不可能被摧毁的点，那么需要记录每个点最早被摧毁的时间；求最少用时，用队列宽度搜索；
 * 用一个数组记录到达某点的用时
 * 关键是扩展点的时候的条件：如果到达给点的时间在该点最早被摧毁之前，则可以扩展该点；
 * 且每个扩展出的新的点都应该判断一下该点是不是永远不可能被摧毁，如果是，则已经到到安全区，返回
 */ 


typedef pair<int, int> pii;
const int INF = 1001;
const int MAX_N = 401;
int ms[MAX_N][MAX_N];  //记录每个点最早被摧毁的时间
int d[MAX_N][MAX_N];  //记录到达每个点的时间
int dirs[5][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {0, 0}};
int m;


int bfs() {
	queue<pii> q;
	memset(d, -1, sizeof(d));  //初始化到达每个点的时间
	if (ms[0][0] == INF) return 0;
	d[0][0] = 0;
	q.push(make_pair(0, 0));
	while (!q.empty()) {
		pii point = q.front();
		q.pop();
		int x = point.first;
		int y = point.second;
		for (int i = 0; i < 4; i++) {
			//扩展
			int xx = x + dirs[i][0];
			int yy = y + dirs[i][1];
			if (d[xx][yy] != -1) continue;
			if (xx >= 0 && x <= MAX_N && yy >= 0 && yy <= MAX_N && d[x][y] + 1 < ms[xx][yy]) {
				//d[x][y] + 1 < ms[xx][yy] 如果能够到达该点的时间小于该点最早被摧毁的时间，则可以扩展该点
				d[xx][yy] = d[x][y] + 1;
				if (ms[xx][yy] == INF) return d[xx][yy];
				q.push(make_pair(xx, yy));
			}
		}
	}
	return -1;
}

int solve() {
	cin >> m;
	int x, y, t;
	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_N; j++) {
			ms[i][j] = INF;  //先初始化每个点都是安全的
		}
	}
	while (m--) {
		cin >> x >> y >> t;
		for (int i = 0; i < 5; i++) {
			//得到每个点最早被摧毁的时间
			int xx = x + dirs[i][0];
			int yy = y + dirs[i][1];
			if (xx >= 0 && xx <= MAX_N && yy >= 0 && yy <= MAX_N) {
				ms[xx][yy] = min(ms[xx][yy], t);
			}
		} 
	}
	return bfs();
}

int main() {
	int res = solve();
	cout << res << endl;
	return 0;
}
