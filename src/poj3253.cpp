/*
 * POJ 3617: Fence Repair
 * 题意：农夫要把一个长为l的木板剧成N块，且剧长度为Ni的消耗等于Ni，问剧完木块的最小消耗是多少？
 * 类型：贪心
 * 算法：关键点还是应该能抽象出问题，其实可以想出来用贪心，应该使得长度较小的木块Ni重复计算较多，也就是将木块由小到大排序，
 * 然后就将两个的和加起来；然后将加起来的木板放入原来所有木板，再取最小的木板和次小的木板；直到只剩下一块木板为止；
 * 看看这个过程是不是想到了霍夫曼编码？实际上就是这个过程，可以用优先队列来做
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;

const int MAX_N = 20000;
int woods[MAX_N];

int main() {
    int N;
    ll res = 0;
    priority_queue<ll, vector<ll>, greater<ll> > pq;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> woods[i];
        pq.push(woods[i]);
    }
    while (pq.size() > 1) {
        ll num1 = pq.top();
        pq.pop();
        ll num2 = pq.top();
        pq.pop();
        ll num = num1 + num2;
        res += num;
        pq.push(num);
    }
    cout << res << endl;
    return 0;  
}