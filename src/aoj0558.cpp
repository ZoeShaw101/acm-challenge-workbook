/*
 * AOJ 0558: Cheese
 * 题意：m*n矩阵内，给出起点、1～N表示N个工厂、障碍、空格。求按顺序遍历1～N的最短路。
 * 类型：BFS＋Queue（／Dijkstra）
 * 算法：从S顺序通过1～N的最短路，可以用BFS求N次相邻序号间最短路的和。
 */

#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

/**
 * 要求顺序遍1~N的最短路径，可以每次用bfs求出相邻两点的最短路，然后加起来
 * 因为bfs每次都是直接遍历所有周围的点，所以搜到终点时,d[x][y]表示的一定是直接走最短的路；
 */ 

typedef pair<int, int> pii;
const int MAX_N = 1002;
char mat[MAX_N][MAX_N];
int d[MAX_N][MAX_N];  //到达某点的耗时
int sx[MAX_N], sy[MAX_N]; //记录对相邻点的坐标位置
int strength; //到达某点时的能量
int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int h, w, n;

int bfs(int sx, int sy, int tx, int ty) {
  queue<pii> q;
  memset(d, -1, sizeof(d));  //初始化d，之后可以防止重复访问
  q.push(make_pair(sx, sy));
  d[sx][sy] = 0;
  int x, y, xx, yy;
  while (!q.empty()) {
    pii cur_point = q.front();
    q.pop();
    x = cur_point.first;
    y = cur_point.second;
    for (int i = 0; i < 4; i++) {
      xx = x + dirs[i][0];
      yy = y + dirs[i][1];
      if (xx >= 0 && xx < h && y >= 0 && y < w 
          && d[xx][yy] == -1 && mat[xx][yy] != 'X') {
            d[xx][yy] = d[x][y] + 1;
            if (xx == tx && yy == ty ) {
              return d[xx][yy];
            }
            q.push(make_pair(xx, yy));
          }
    }
  }
}

int solve() {
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      cin >> mat[i][j];
      if (mat[i][j] == 'S') {
        sx[0] = i;
        sy[0] = j;
      } else if (mat[i][j] >= '1' && mat[i][j] <= '9') {
        int t = mat[i][j] - '0';
        sx[t] = i;
        sy[t] = j;
      }
    }
  }
  int res = 0;
  strength = 1;
  for (int i = 1; i <= n; i++) {
    int tmp = bfs(sx[i - 1], sy[i - 1], sx[i], sy[i]);
    res += tmp;
    strength += 1;
  }
  return res; 
}

int main() {
  cin >> h >> w >> n;
  cout << solve() <<endl;
  return 0;
}




// typedef pair<int, int> pii;

// int m, n, N;
// char mat[1002][1002];
// int d[1002][1002];
// int sx[10], sy[10];
// int dx[4] = {-1, 0, 1, 0};
// int dy[4] = {0, 1, 0, -1};
// int ans;

// int bfs(int sx, int sy, int tx, int ty) {
//   memset(d, -1, sizeof(d));
//   d[sx][sy] = 0;
//   queue<pii> q;
//   q.push(make_pair(sx, sy));
//   int x, y, xx, yy;
//   while (!q.empty()) {
//     pii cur = q.front();
//     q.pop();
//     x = cur.first;
//     y = cur.second;
//     for (int i = 0; i < 4; ++i) {
//       xx = x + dx[i];
//       yy = y + dy[i];
//       if (xx >= 0 && xx < m && yy >= 0 && yy < n && mat[xx][yy] != 'X' && d[xx][yy] == -1) {
//         d[xx][yy] = d[x][y] + 1;
//         if (xx == tx && yy == ty) {
//           return d[xx][yy];
//         }
//         q.push(make_pair(xx, yy));
//       }
//     }
//   }

// }

// void solve() {
//   ans = 0;
//   for (int i = 0; i < m; ++i) {
//     cin >> mat[i];
//     for (int j = 0; j < n; ++j) {
//       if (mat[i][j] == 'S') {
//         sx[0] = i;
//         sy[0] = j;
//       } else if (mat[i][j] >= '1' && mat[i][j] <= '9') {
//         int t = mat[i][j] - '0';
//         sx[t] = i;
//         sy[t] = j;
//       }
//     }
//   }
//   for (int i = 1; i <= N; ++i) {
//     int tmp = bfs(sx[i - 1], sy[i - 1], sx[i], sy[i]);
//     ans += tmp;
//   }
// }

// int main() {
//   cin >> m >> n >> N;
//   solve();
//   cout << ans << endl;
//   return 0;
// }
