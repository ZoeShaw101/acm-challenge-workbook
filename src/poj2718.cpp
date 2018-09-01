/*
 * POJ 2718: Smallest Difference
 * 题意：给出不重复升序单数字，将其分为两组打乱顺序后组成整数，求两个整数的最小差值。
 * 类型：穷竭搜索＋全排列
 * 算法：将序列全排列，按长度均分成两组，计算每个排列下的差值。
 */


#include <cstdio>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

/**
 * 题意：0-9数字分成两部分，随意组合，求能使得这两个数绝对值差最小的情况的差
 * 算法：肯定是将数组对半分，然后求所有的全排列的差的最小值
 * c++中全排列用到:next_permutation
 */

int n, res;
int nums[10];
int d[2];
const int INF = 10000000;

int array2num(int s, int t) {
    int num = 0;
    if (nums[s] == 0 && s + 1 < t) return -1;
    for (int i = s; i < t; i++) {
        num = num * 10 + nums[i];
    }
    return num;
}

void helper(int index) {
    int x = array2num(0, index);
    int y = array2num(index, n);
    if (x != -1 && y != -1) {
        res = min(res, abs(x - y));
    }
}

void solve() {
    int x, y;
    do {
        //n可能为偶数也可能为奇数，需要分开考虑
        if (n % 2 == 0) {
            helper(n / 2);
        } else {
            //n为奇数，则分给左边多和右边多的结果不一样，要分开考虑
            int s1 = n / 2;
            int s2 = (n + 1) / 2;
            helper(s1);
            helper(s2);
        }
    } while (next_permutation(nums, nums + n));
}

int main() {
    int case_n;
    cin >> case_n;
    cin.get();
    while (case_n--) {
        n = 0;
        res = INF;
        string str;
        getline(cin, str);
        stringstream ss(str);
        while (ss >> nums[n]) n++;
        solve();
        cout << res << endl;
    }
}