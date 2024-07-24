// 583. 两个字符串的删除操作
// labuladong 题解思路
// 中等
// 给定两个单词 word1 和 word2 ，返回使得 word1 和  word2 相同所需的最小步数。
// 每步 可以删除任意一个字符串中的一个字符。

// 示例 1：
// 输入: word1 = "sea", word2 = "eat"
// 输出: 2
// 解释: 第一步将 "sea" 变为 "ea" ，第二步将 "eat "变为 "ea"

// 示例  2:
// 输入：word1 = "leetcode", word2 = "etco"
// 输出：4

// 提示：
// 1 <= word1.length, word2.length <= 500
// word1 和 word2 只包含小写英文字母


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



// 17:28--17:35
// 最长相同子序列 x
// m + n - 2x
class Solution_M1 {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for(int i=1; i<=m; i++) {
            for(int j=1; j<=n; j++) {
                if(word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                else {
                    dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return m + n - 2 * dp[m][n];
    }
};


// 17:36--17:40
// 滚动数组
// dp[i][j] = dp[i-1][j-1] + 1;
// dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
// dp[j] = pre + 1; pre需要根据 j 变化
// dp[j] = max(dp[j], dp[j-1]);
class Solution_M2 {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        vector<int> dp(n+1, 0);
        for(int i=1; i<=m; i++) {
            int pre = dp[0];
            for(int j=1; j<=n; j++) {
                int temp = dp[j];
                if(word1[i-1] == word2[j-1]) {
                    dp[j] = pre + 1;
                }
                else {
                    dp[j] = std::max(dp[j], dp[j-1]);
                }
                pre = temp;
            }
        }
        return m + n - 2 * dp[n];
    }
};



// 确定 dp 数组（dp table）以及下标的含义
// dp [i][j]：以 i-1 为结尾的字符串 word1，和以 j-1 位结尾的字符串 word2，想要达到相等，所需要删除元素的最少次数。
// 这里 dp 数组的定义有点点绕，大家要撸清思路。
// 确定递推公式
// 当 word1 [i - 1] 与 word2 [j - 1] 相同的时候
// 当 word1 [i - 1] 与 word2 [j - 1] 不相同的时候
// 当 word1 [i - 1] 与 word2 [j - 1] 相同的时候，dp [i][j] = dp [i - 1][j - 1];
// 当 word1 [i - 1] 与 word2 [j - 1] 不相同的时候，有三种情况：
// 情况一：删 word1 [i - 1]，最少操作次数为 dp [i - 1][j] + 1
// 情况二：删 word2 [j - 1]，最少操作次数为 dp [i][j - 1] + 1
// 情况三：同时删 word1 [i - 1] 和 word2 [j - 1]，操作的最少次数为 dp [i - 1][j - 1] + 2
// 那最后当然是取最小值，所以当 word1 [i - 1] 与 word2 [j - 1] 不相同的时候，
// 递推公式：dp [i][j] = min ({dp [i - 1][j - 1] + 2, dp [i - 1][j] + 1, dp [i][j - 1] + 1});
// 因为 dp [i][j - 1] + 1 = dp [i - 1][j - 1] + 2，所以递推公式可简化为：dp [i][j] = min (dp [i - 1][j] + 1, dp [i][j - 1] + 1);
// 这里可能不少录友有点迷糊，从字面上理解 就是 当 同时删 word1 [i - 1] 和 word2 [j - 1]，dp [i][j-1] 本来就不考虑 word2 [j - 1] 了，
// 那么我在删 word1 [i - 1]，是不是就达到两个元素都删除的效果，即 dp [i][j-1] + 1。
// dp 数组如何初始化
// 从递推公式中，可以看出来，dp [i][0] 和 dp [0][j] 是一定要初始化的。
// dp [i][0]：word2 为空字符串，以 i-1 为结尾的字符串 word1 要删除多少个元素，才能和 word2 相同呢，很明显 dp [i][0] = i。

// 时间复杂度: O (n * m)
// 空间复杂度: O (n * m)

class Solution_D1_copy {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1));
        for (int i = 0; i <= word1.size(); i++) dp[i][0] = i;   // ***
        for (int j = 0; j <= word2.size(); j++) dp[0][j] = j;   // ***
        for (int i = 1; i <= word1.size(); i++) {
            for (int j = 1; j <= word2.size(); j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];    // 不用删
                } else {
                    dp[i][j] = std::min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);    // 删除数量的最小值
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};
