/*
 * POJ 3617: Best Cow Line
 * 题意：给定一个字符串S，和一个空字符串T，每次从s的首部或尾部删除一个字符，加入t的尾部，问能够成的字典序最小的t是多少？
 * 类型：贪心
 * 算法：贪心的思想，从左到右增加t，每次取s的首尾较小的字符即可;具体做的时候用双指针法，每次判断是取头的数加进去还是尾的数
 * 注：字典序比较的问题经常能用得上贪心法
 */

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 2000;
char S[MAX_N];

int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) cin >> S[i];
    string T = "";
    int left = 0, right = N - 1; //双指针
    while (left <= right) {
        bool head = false;
        for (int i = 0; left + i <=  right; i++) {
            if (S[left + i] < S[right - i]) {
                head = true;
                break;
            }
            else if (S[left + i] > S[right - i]) {
                head = false;
                break;
            }
        }
        if (head) T += S[left++];
        else T += S[right--];
    }
    cout << T << endl;
    return 0;
}