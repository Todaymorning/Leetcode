// 1143. 最长公共子序列
// labuladong 题解思路
// 中等
// 给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。
// 一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
// 例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
// 两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。

// 示例 1：
// 输入：text1 = "abcde", text2 = "ace" 
// 输出：3  
// 解释：最长公共子序列是 "ace" ，它的长度为 3 。

// 示例 2：
// 输入：text1 = "abc", text2 = "abc"
// 输出：3
// 解释：最长公共子序列是 "abc" ，它的长度为 3 。

// 示例 3：
// 输入：text1 = "abc", text2 = "def"
// 输出：0
// 解释：两个字符串没有公共子序列，返回 0 。

// 提示：
// 1 <= text1.length, text2.length <= 1000
// text1 和 text2 仅由小写英文字符组成。


#include<iostream>
#include<vector>
#include<string>
using std::vector;
using std::string;
using std::max;


class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {

    }
};

// 17:35--17:56(不会，理不清递推公式)
// dp[i][j]：以 text1[0, i-1] 和 text2[0, j-1] 字符串的最大公共子序列
// 确定递推公式
// 主要就是两大情况： text1 [i - 1] 与 text2 [j - 1] 相同，text1 [i - 1] 与 text2 [j - 1] 不相同
// 如果 text1 [i - 1] 与 text2 [j - 1] 相同，那么找到了一个公共元素，所以 dp [i][j] = dp [i - 1][j - 1] + 1;
// 如果 text1 [i - 1] 与 text2 [j - 1] 不相同，那就看看 text1 [0, i - 2] 与 text2 [0, j - 1] 的最长公共子序列 
// 和 text1 [0, i - 1] 与 text2 [0, j - 2] 的最长公共子序列，取最大的。
// 即：dp [i][j] = max (dp [i - 1][j], dp [i][j - 1]);
// 时间复杂度: O (n * m)，其中 n 和 m 分别为 text1 和 text2 的长度
// 空间复杂度: O (n * m)
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int size1 = text1.size();
        int size2 = text2.size();
        if(size1 == 0 || size2 == 0) return 0;
        vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, 0));
        for(int i=1; i<=size1; i++) {
            for(int j=1; j<=size2; j++) {
                if(text1[i-1] == text2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp.back().back();
    }
};


// 滚动数组，由于相等时会使用 dp[i-1][j-1] 的数据，因此需要注意
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int size1 = text1.size();
        int size2 = text2.size();
        if(size1 == 0 || size2 == 0) return 0;
        vector<int> dp(size2 + 1, 0);
        for(int i=1; i<=size1; i++) {
            int dp_i_1_j_1 = dp[0];
            for(int j=1; j<=size2; j++) {
                int temp = dp[j];
                if(text1[i-1] == text2[j-1]) {
                    dp[j] = dp_i_1_j_1 + 1;            // dp[i][j] = dp[i-1][j-1] + 1， 需要保存 dp[i-1][j-1];
                }
                else {
                    dp[j] = max(dp[j], dp[j-1]);    // dp[i][j] = max(dp[i-1][j], dp[i][j-1])
                }
                dp_i_1_j_1 = temp;                  // j++,更新 dp_i_1_j_1
            }
        }
        return dp.back();
    }
};