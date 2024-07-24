// 115. 不同的子序列
// labuladong 题解思路
// 困难
// 给你两个字符串 s 和 t ，统计并返回在 s 的 子序列 中 t 出现的个数，结果需要对 10^9 + 7 取模。

// 示例 1：
// 输入：s = "rabbbit", t = "rabbit"
// 输出：3
// 解释：
// 如下所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。
// rabb*it
// rab*bit
// ra*bbit

// 示例 2：
// 输入：s = "babgbag", t = "bag"
// 输出：5
// 解释：
// 如下所示, 有 5 种可以从 s 中得到 "bag" 的方案。 
// ba*g***
// ba****g
// b****ag
// **b**ag
// ****bag

// 提示：
// 1 <= s.length, t.length <= 1000
// s 和 t 由英文字母组成


#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using std::pow;
using std::vector;
using std::string;


class Solution {
public:
    int numDistinct(string s, string t) {

    }
};


// 15:47--15:59(不会)
// 从 s 中得到 t
// dp [i][j]：以 i-1 为结尾的 s 子序列中出现以 j-1 为结尾的 t 的个数为 dp [i][j]。
// 递推公式
// 用 1 初始化第 0 列
// - - b a g
// - 1 0 0 0
// b 1 1 0 0
// a 1 1 1 0
// b 1 2 1 0
// g 1 2 1 1
// b 1 3 1 1
// a 1 3 4 1    // babgb 中出现 b 3次， babgb中出现 ba 1次，那么babgba中出现 ba 的次数为 3 + 1
// g 1 3 4 5
class Solution_D1_M1 {
public:
    int numDistinct(string s, string t) {
        int large = pow(10, 9) + 7;
        int s_size = s.size();
        int t_size = t.size();
        if(s_size < t_size) return 0;
        vector<vector<int>> dp(s_size + 1, vector<int>(t_size + 1, 0));
        for(int i=0; i<=s_size; i++) {
            dp[i][0] = 1;
        }
        for(int i=1; i<=s_size; i++) {
            for(int j=1; j<=t_size; j++) {
                if(s[i-1] == t[j-1]) {
                    dp[i][j] = dp[i-1][j] + dp[i-1][j-1]; // ***
                }
                else {
                    dp[i][j] = dp[i-1][j];
                }
                if(dp[i][j] > large) dp[i][j] %= large;
            }
        }
        return dp.back().back();
    }
};


class Solution_D1_M2 {
public:
    int numDistinct(string s, string t) {
        int large = pow(10, 9) + 7;
        int s_size = s.size();
        int t_size = t.size();
        if(s_size < t_size) return 0;
        vector<int> dp(t_size + 1, 0);
        dp[0] = 1;
        for(int i=1; i<=s_size; i++) {
            int pre = dp[0];
            for(int j=1; j<=t_size; j++) {
                int temp = dp[j];
                if(s[i-1] == t[j-1]) {
                    dp[j] += pre; // ***
                }
                if(dp[j] > large) dp[j] %= large;
                pre = temp;
            }
        }
        return dp.back();
    }
};


// 时间复杂度: O (n * m)
// 空间复杂度: O (n * m)
class Solution_D1_copy {
public:
    int numDistinct(string s, string t) {
        vector<vector<uint64_t>> dp(s.size() + 1, vector<uint64_t>(t.size() + 1));
        for (int i = 0; i < s.size(); i++) dp[i][0] = 1;
        for (int j = 1; j < t.size(); j++) dp[0][j] = 0;
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= t.size(); j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[s.size()][t.size()];
    }
};