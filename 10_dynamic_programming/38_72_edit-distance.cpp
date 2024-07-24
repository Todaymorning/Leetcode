// 72. 编辑距离
// labuladong 题解思路
// 中等
// 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。
// 你可以对一个单词进行如下三种操作：
// 插入一个字符
// 删除一个字符
// 替换一个字符
 

// 示例 1：
// 输入：word1 = "horse", word2 = "ros"
// 输出：3
// 解释：
// horse -> rorse (将 'h' 替换为 'r')
// rorse -> rose (删除 'r')
// rose -> ros (删除 'e')

// 示例 2：
// 输入：word1 = "intention", word2 = "execution"
// 输出：5
// 解释：
// intention -> inention (删除 't')
// inention -> enention (将 'i' 替换为 'e')
// enention -> exention (将 'n' 替换为 'x')
// exention -> exection (将 'n' 替换为 'c')
// exection -> execution (插入 'u')

// 提示：
// 0 <= word1.length, word2.length <= 500
// word1 和 word2 由小写英文字母组成


#include<iostream>
#include<string>
#include<vector>
using std::vector;
using std::string;

class Solution {
public:
    int minDistance(string word1, string word2) {

    }
};


// 21:45--21:52(错误)--22:21(添加 idx，也错误)
// 1 变成 2
// 求 1 2 的最长子序列 n
// result = n1 - n;
// 
#if 0
class Solution {
public:
    int minDistance(string word1, string word2) {
        int size1 = word1.size();
        int size2 = word2.size();
        vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, 0));
        int idx = 0;
        for(int i=1; i<=size1; i++) {
            for(int j=1; j<=size2; j++) {
                if(word1[i-1] == word2[j-1]) {
                    idx = j-1;
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                else {
                    dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return size1 - dp[size1][size2] + size2 - idx;
    }
};
#endif


// 22:21--22:43(看 D1 思路)
// 1. 确定 dp 数组（dp table）以及下标的含义
// dp [i][j] 表示以下标 i-1 为结尾的字符串 word1，和以下标 j-1 为结尾的字符串 word2，最近编辑距离为 dp [i][j]。
// if (word1[i - 1] == word2[j - 1])
//     不操作
// if (word1[i - 1] != word2[j - 1])
//     增
//     删
//     换
// if (word1[i - 1] == word2[j - 1]) 那么说明不用任何编辑，
//      dp[i][j] = dp[i - 1][j - 1];
// if (word1[i - 1] != word2[j - 1])，此时就需要编辑了，如何编辑呢？
//      操作一：word1 删除一个元素，那么就是以下标 i - 2 为结尾的 word1 与 j-1 为结尾的 word2 的最近编辑距离 再加上一个操作。
//          即 dp[i][j] = dp[i - 1][j] + 1;
//      操作二：word2 删除一个元素，那么就是以下标 i - 1 为结尾的 word1 与 j-2 为结尾的 word2 的最近编辑距离 再加上一个操作。
//          即 dp[i][j] = dp[i][j - 1] + 1;
//          word2 添加一个元素，相当于 word1 删除一个元素，例如 word1 = "ad" ，word2 = "a"，word1 删除元素'd' 和 word2 添加一个元素'd'，
//          变成 word1="a", word2="ad"， 最终的操作数是一样！
//                  a                         a     d
//         +-----+-----+             +-----+-----+-----+
//         |  0  |  1  |             |  0  |  1  |  2  |
//         +-----+-----+   ===>      +-----+-----+-----+
//       a |  1  |  0  |           a |  1  |  0  |  1  |
//         +-----+-----+             +-----+-----+-----+
//       d |  2  |  1  |
//         +-----+-----+
//      操作三：替换元素，word1 替换 word1[i - 1]，使其与 word2[j - 1] 相同，此时不用增删加元素。
//          即 dp[i][j] = dp[i - 1][j - 1] + 1;
//                  a     b     e
//         +-----+-----+-----+-----+
//         |  0  |  1  |  2  |  3  |
//         +-----+-----+-----+-----+
//       a |  1  |  0  |  1  |  2  |
//         +-----+-----+-----+-----+
//       b |  2  |  1  |  0  |  1  |
//         +-----+-----+-----+-----+
//       c |  3  |  2  |  1  |  0  |

// 22:43--23:00
// 时间复杂度: O (n * m)
// 空间复杂度: O (n * m)
class Solution_D1_M1 {
public:
    int minDistance(string word1, string word2) {
        int size1 = word1.size();
        int size2 = word2.size();
        vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, 0));
        for(int i=0; i<=size1; i++) dp[i][0] = i;
        for(int j=0; j<=size2; j++) dp[0][j] = j;
        for(int i=1; i<=size1; i++) {
            for(int j=1; j<=size2; j++) {
                if(word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    // 替换 word1[i-1]：dp[i-1][j-1] + 1
                    // 经过 dp[i-1][j-1] 步操作后，word1[0,i-2] == word2[0, j-2]
                    // 在此基础上增加一步操作：将 word1[i-1] 替换为 word2[j-1]，可以使得 word1[0, i-1] == word2[0, j-1]
                    //
                    // 删除 word1[i-1] (w2增加字符)：dp[i-1][j] + 1
                    // 经过 dp[i-1][j] 步操作后，word[0, i-2] == word2[0, j-1]
                    // 在此基础上增加一步操作：将 word1[i-1] 删除，可以使得 word1[0, i-1] == word1[0, i-2] == word2[0, j-1]
                    // 
                    // 增加 word2[j-1](w1删除字符): dp[i][j-1] + 1
                    dp[i][j] = std::min(dp[i-1][j-1] + 1, std::min(dp[i-1][j] + 1, dp[i][j-1] + 1));
                }
            }
        }
        return dp.back().back();
    }
};


// 23:01--10:44
// 滚动数组
class Solution_M2 {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        if(m == 0) return n;
        if(n == 0) return m;
        vector<int> dp(n + 1, 0);
        for(int j=0; j<=n; j++) dp[j] = j;  // 初始化
        for(int i=1; i<=m; i++) {
            dp[0] = i;              // ***
            int pre = dp[0] - 1;    // dp[i-1][0]   // ***
            for(int j=1; j<=n; j++) {
                int temp = dp[j];   // dp[i-1][j-1]
                if(word1[i-1] == word2[j-1]) {
                    dp[j] = pre;
                }
                else {
                    // dp[i][j] = std::min(dp[i-1][j-1] + 1, std::min(dp[i-1][j] + 1, dp[i][j-1] + 1));
                    dp[j] = std::min(pre + 1, std::min(dp[j] + 1, dp[j-1] + 1));
                }
                pre = temp;
            }
        }
        return dp.back();
    }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码不保证正确性，仅供参考。如有疑惑，可以参照我写的 java 代码对比查看。

// 暴力解法
class Solution {
public:
    int minDistance(string s1, string s2) {
        int m = s1.length(), n = s2.length();
        // i，j 初始化指向最后一个索引
        return dp(s1, m - 1, s2, n - 1);
    }

    // 定义：返回 s1[0..i] 和 s2[0..j] 的最小编辑距离
    int dp(string s1, int i, string s2, int j) {
        // base case
        if (i == -1) return j + 1;
        if (j == -1) return i + 1;

        if (s1[i] == s2[j]) {
            return dp(s1, i - 1, s2, j - 1); // 啥都不做
        }
        return min(
            dp(s1, i,     s2, j - 1) + 1,    // 插入
            dp(s1, i - 1, s2, j    ) + 1,    // 删除
            dp(s1, i - 1, s2, j - 1) + 1     // 替换
        );
    }

    int min(int a, int b, int c) {
        return std::min(std::min(a, b), c);
    }
};

// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码不保证正确性，仅供参考。如有疑惑，可以参照我写的 java 代码对比查看。
// 记忆优化
class Solution {
private:
    // 备忘录
    vector<vector<int>> memo;
    int dp(string s1, int i, string s2, int j) {
        if (i == -1) return j + 1;
        if (j == -1) return i + 1;
        // 查备忘录，避免重叠子问题
        if (memo[i][j] != -1) {
            return memo[i][j];
        }
        // 状态转移，结果存入备忘录
        if (s1[i] == s2[j]) {
            memo[i][j] = dp(s1, i - 1, s2, j - 1);
        } else {
            memo[i][j] = min(
                dp(s1, i, s2, j - 1) + 1,
                dp(s1, i - 1, s2, j) + 1,
                dp(s1, i - 1, s2, j - 1) + 1
            );
        }
        return memo[i][j];
    }
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        // 备忘录初始化为特殊值，代表还未计算
        memo = vector<vector<int>>(m, vector<int>(n, -1));
        return dp(word1, m - 1, word2, n - 1);
    }
    int min(int a, int b, int c) {
        return std::min(a, std::min(b, c));
    }
};



