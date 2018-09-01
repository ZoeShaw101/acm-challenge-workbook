/*
 * POJ 3009: Curling 2.0
 * 题意：m＊n矩阵中，给出起点、终点、空格、障碍，从每个点可向4方前进，直到遇到障碍，打碎并停在障碍格的前面。求到达终点的最少前进次数。
 * 类型：DFS＋记忆化搜索
 * 算法：从某点出发，向4个方向投掷，遇到障碍格，标记其为空格状态，继续递归障碍前一点，回退恢复障碍状态。每次递归直至到达终点或全部出界失败。
 */

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

/**
 * 题意：要学会对问题建模：其实就是一个m*n的矩阵，给定起点、终点、障碍、空格，需要从某一点起，开始运球，
 * 直到球撞到障碍则障碍被打碎，球停在原来障碍旁边的一格；问球能到达终点最少的扔球次数
 * 
 * 算法：从某一点开始，向四个方向扔球，递归下一点，空格继续前进，如果碰到障碍，则障碍置为空格，返回置递归前一点；否则出界或到达终点，本次递归结束；
 */



// const int INF = 1000;
// const int MAX_THROW = 10;
// const int TYPE_END = 3;
// const int TYPE_VACANT = 0;
// const int TYPE_BLOCK = 1;
// const int TYPE_START = 2;

// int m, n, res;
// int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
// int mat[21][21];

// void dfs(int x, int y, int step) {
//     if (step > MAX_THROW) return;
//     //每次递归进来都是重新扔球
//     for (int i = 0; i < 4; i++) {
//         int xx = x, yy = y;
//         while (true) {
//             //如果是空格则一直向前走
//             xx += dirs[i][0];
//             yy += dirs[i][1];
//             if (xx < 0 || xx >= m || yy < 0 || yy >= n) break;
//             if (mat[xx][yy] == TYPE_END) {
//                 res = min(res, step + 1);
//                 break;
//             } 
//             if (mat[xx][yy] == TYPE_BLOCK) {
//                 mat[xx][yy] = TYPE_VACANT;
//                 int prex = xx - dirs[i][0];
//                 int prey = yy - dirs[i][1];
//                 if (prex != x || prey != y) {
//                     dfs(prex, prey, step + 1);
//                 }
//                 mat[xx][yy] = TYPE_BLOCK;  //回退至上一状态时(xx, yy)这一点 应该还是block
//                 break;
//             }
//         }
//     }    
// }

// void solve() {
//     res = INF;
//     int sx, sy;
//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j < n; j++) {
//             cin >> mat[i][j];
//             if (mat[i][j] == TYPE_START) {
//                 sx = i;
//                 sy = j;
//             }
//         }
//     }
//     dfs(sx, sy, 0);
//     if (res == INF) res = -1;
// }

// int main() {
//     while (cin >> n >> m && m > 0 && n > 0) {
//         solve();
//         cout << res << endl;
//     }
//     return 0;
// }






const int INF = 1000;
const int TYPE_VACANT = 0;
const int TYPE_BLOCK = 1;
const int TYPE_START = 2;
const int TYPE_GOAL = 3;
const int MAX_THROW = 10;

int m, n;
int mat[22][22];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int ans;

void dfs(int x, int y, int step) {
    if(step >= MAX_THROW) {
        return;
    }
    for(int i = 0; i < 4; ++i) {  //每次递归进来都是需要重新向四个方向扔球
        int xx = x;
        int yy = y;
        /**
         * 为什么这里需要个循环？因为是空格的话就继续前进，直到遇到终点或者障碍或者出界；
         * 因为要找到能到终点的最少扔球次数，所以需要遍历所有的可行方案找到最小的，即res = min(res, step + 1)
         * 如果遇到了block，则将障碍标记为空格，继续递归障碍前一点；
         * 递归结束的条件是从该点出发已经遍历过了（不能到达终点或已能到达终点）则将该点设为block
         */ 
        while(true) { 
            xx += dx[i];
            yy += dy[i];
            if(xx < 0 || xx >= m || yy < 0 || yy >= n) {
                break;
            }
            if(mat[xx][yy] == TYPE_GOAL) {
                ans = min(ans, step + 1);
                break;
            }
            if(mat[xx][yy] == TYPE_BLOCK) {
                mat[xx][yy] = TYPE_VACANT;
                int prex = xx - dx[i];
                int prey = yy - dy[i];
                if(prex != x || prey != y) {
                    dfs(prex, prey, step + 1);
                }
                mat[xx][yy] = TYPE_BLOCK;
                break;
            }
        }
    }
}

void solve() {
    ans = INF;
    int sx, sy;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> mat[i][j];
            if(mat[i][j] == TYPE_START){
                sx = i;
                sy = j;
            }
        }
    }
    dfs(sx, sy, 0);
    if(ans == INF){
        ans = -1;
    }
}

int main() {
    while(cin >> n >> m && n > 0 && m > 0) {
        solve();
        cout << ans << endl;
    }
    return 0;
}