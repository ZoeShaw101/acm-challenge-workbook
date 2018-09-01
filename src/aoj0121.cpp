/*
 * AOJ 0121: Seven Puzzle
 * 题意：2行4列的矩阵，标号为0～7，每次可以将0和其相邻格交换，问达到增序局面的最少移动步数。
 * 类型：BFS＋Map
 * 算法：用String表示局面，用Map建立局面与最短路的映射。用最终有序态初始化队列，每次从队列中取出一个局面，搜索可移动且未出现过的局面再加入队列，直到局面为增序或队列空。
 */


#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <string>

using namespace std;

/**
 * 题意：是给定一个8个格子的棋盘，0-7数字，只有0能与周围的数字交换位置，
 * 求能使数字变为有序的局面的最小的交换次数
 * 
 * 算法：使用String表示局面，每次扩展出没有被访问过且可以扩展的局面
 */

#include <vector>
#include <set>
string puzzle;
const string end_status = "01234567";
int chars[7];
set<string> visited;
int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

string str_swap(string str, int x, int y, int xx, int yy) {
  string s = str;
  char t = s[4 * x + y];
  s[x * 4 + y] = s[xx * 4 + yy];
  s[xx * 4 + yy] = t;
  return s;
}

vector<string> get_next(string str) {
  vector<string> next;
  int zero_x, zero_y;
  for (int i = 0; i < 8; i++) {
    if (str[i] == '0') {
      zero_x = i / 4;
      zero_y = i % 4;
    }
  }
  for (int i = 0; i < 4; i++) {
    int xx = zero_x + dirs[i][0];
    int yy = zero_y + dirs[i][1];
    if (xx >= 0 && xx < 2 && yy >= 0 && yy < 4) {
      string n = str_swap(str, zero_x, zero_y, xx, yy);
      next.push_back(n);
    }
  }
  return next;
}

int bfs() {
  int res = 0;
  queue<string> q;
  q.push(puzzle);
  while (!q.empty()) {
    int size = q.size();
    for (int i = 0; i < size; i++) {
      string cur = q.front();
      //cout << cur << endl;
      q.pop();
      if (visited.find(cur) != visited.end()) continue;
      visited.insert(cur);
      if (cur == end_status) return res;
      vector<string> next = get_next(cur);
      for (string n : next) {
        q.push(n);
      }
    }
    res++;
  }
}

int main() {
  while (cin) {
    puzzle.clear();
    visited.clear();
    for (int i = 0; i < 8; i++) {
      cin >> chars[i];
      puzzle += (chars[i] + '0');
    }
    cout << bfs() << endl;
  }
}






// int a[8];
// int d[4] = {-1, 1, -4, 4};

// map<string, int> mymap;

// void bfs() {
//   queue<string> q;
//   q.push("01234567");
//   mymap["01234567"] = 0;
//   while (!q.empty()) {
//     string cur = q.front();
//     string nxt;
//     q.pop();
//     int p = (int) cur.find("0");
//     for (int i = 0; i < 4; ++i) {
//       int np = p + d[i];
//       if (np >= 0 && np < 8 && (p != 3 || d[i] != 1) && (p != 4 || d[i] != -1)) {
//         nxt = cur;
//         nxt[np] = '0';
//         nxt[p] = cur[np];
//         if (mymap.find(nxt) == mymap.end()) {
//           mymap[nxt] = mymap[cur] + 1;
//           q.push(nxt);
//         }
//       }

//     }
//   }
// }

// int main() {
//   bfs();
//   while (cin >> a[0]) {
//     for (int i = 1; i < 8; ++i) {
//       cin >> a[i];
//     }
//     string s = "";
//     for (int i = 0; i < 8; ++i) {
//       s += a[i] + '0';
//     }
//     if (mymap.find(s) == mymap.end())
//       cout << -1 << endl;
//     else
//       cout << mymap[s] << endl;
//   }
//   return 0;
// }
