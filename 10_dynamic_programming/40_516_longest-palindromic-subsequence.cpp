// 516. 最长回文子序列
// labuladong 题解思路
// 中等
// 给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。
// 子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。

// 示例 1：
// 输入：s = "bbbab"
// 输出：4
// 解释：一个可能的最长回文子序列为 "bbbb" 。

// 示例 2：
// 输入：s = "cbbd"
// 输出：2
// 解释：一个可能的最长回文子序列为 "bb" 。

// 提示：
// 1 <= s.length <= 1000
// s 仅由小写英文字母组成


#include<iostream>
#include<string>
#include<vector>
using std::vector;
using std::string;
using std::max;

class Solution {
public:
    int longestPalindromeSubseq(string s) {

    }
};



// 11:58--12:12(读题找思路，不会，看 D1 中 dp 的定义)
// dp [i][j]：字符串 s 在 [i, j] 范围内最长的回文子序列的长度为 dp [i][j]。
// 15：05--15:09(尝试自己分析)--15:21(有错)
// s[i] != s[j] 时，dp[i][j] = dp[i][j-1]; 错
// s[i] == s[j] 时，dp[i][j] = max(dp[i][j-1], dp[i+1][j-1] + 2)
// 求 i 需要知道 i+1, 因此 i 倒序
// 求 j 需要知道 j-1, 因此 j 正序
// i在左，j在右，j >= i
// s =
// "euazbipzncptldueeuechubrcourfpftcebikrxhybkymimgvldiwqvkszfycvqyvtiwfckexmowcxztkfyzqovbtmzpxojfofbvwnncajvrvdbvjhcrameamcfmcoxryjukhpljwszknhiypvyskmsujkuggpztltpgoczafmfelahqwjbhxtjmebnymdyxoeodqmvkxittxjnlltmoobsgzdfhismogqfpfhvqnxeuosjqqalvwhsidgiavcatjjgeztrjuoixxxoznklcxolgpuktirmduxdywwlbikaqkqajzbsjvdgjcnbtfksqhquiwnwflkldgdrqrnwmshdpykicozfowmumzeuznolmgjlltypyufpzjpuvucmesnnrwppheizkapovoloneaxpfinaontwtdqsdvzmqlgkdxlbeguackbdkftzbnynmcejtwudocemcfnuzbttcoew"
// 输出
// 49
// 预期结果
// 159
#if 0
class Solution_M1 {
public:
    int longestPalindromeSubseq(string s) {
        int size = s.size();
        vector<vector<int>> dp(size, vector<int>(size, 0));
        int result = 0;
        for(int i=size-1; i>=0; i--) {
            for(int j=i; j<size; j++) {
                if(i == j) {
                    dp[i][j] = 1;   // i == j, 0, size-1
                }
                else if(s[i] != s[j]) {
                    dp[i][j] = dp[i][j-1];  // j>i=0, j-1>=0
                }
                else {
                    dp[i][j] = std::max(dp[i][j-1], dp[i+1][j-1] + 2);  // j-1>=0, i+1<=size-1
                }

                if(dp[i][j] > result) result = dp[i][j];
            }
        }
        return result;
    }
};
#endif


class Solution_M2 {
public:
    int longestPalindromeSubseq(string s) {
        int size = s.size();
        vector<vector<int>> dp(size, vector<int>(size, 0));
        for(int i=size-1; i>=0; i--) {
            for(int j=i; j<size; j++) {
                if(i == j) {
                    dp[i][j] = 1;   // i == j, 0, size-1                                        // ***
                }
                else if(s[i] != s[j]) {
                    // 不相等时掐头去尾看哪个大
                    dp[i][j] = std::max(dp[i][j-1], dp[i+1][j]);  // j>i=0, j-1>=0              // ***
                }
                else {
                    // 相等时掐尾和中间看哪个大
                    dp[i][j] = std::max(dp[i][j-1], dp[i+1][j-1] + 2);  // j-1>=0, i+1<=size-1  // ***
                }
            }
        }
        return dp[0][size-1];   // dp[i][j]的定义   ***
    }
};


// 1. 确定 dp 数组（dp table）以及下标的含义
// dp [i][j]：字符串 s 在 [i, j] 范围内最长的回文子序列的长度为 dp [i][j]。
// 2. 确定递推公式
// 在判断回文子串的题目中，关键逻辑就是看 s [i] 与 s [j] 是否相同。
// 如果 s [i] 与 s [j] 相同，那么 dp [i][j] = dp [i + 1][j - 1] + 2;
// 如果 s [i] 与 s [j] 不相同，说明 s [i] 和 s [j] 的同时加入 并不能增加 [i,j] 区间回文子序列的长度，那么分别加入 s [i]、s [j] 看看哪一个可以组成最长的回文子序列。
// 加入 s [j] 的回文子序列长度为 dp [i + 1][j]。
// 加入 s [i] 的回文子序列长度为 dp [i][j - 1]。
// 那么 dp [i][j] 一定是取最大的，即：dp [i][j] = max (dp [i + 1][j], dp [i][j - 1]);
// 3. dp 数组如何初始化
// 首先要考虑当 i 和 j 相同的情况，从递推公式：dp [i][j] = dp [i + 1][j - 1] + 2; 可以看出 递推公式是计算不到 i 和 j 相同时候的情况。
// 所以需要手动初始化一下，当 i 与 j 相同，那么 dp [i][j] 一定是等于 1 的，即：一个字符的回文子序列长度就是 1。
// 其他情况 dp [i][j] 初始为 0 就行，这样递推公式：dp [i][j] = max (dp [i + 1][j], dp [i][j - 1]); 中 dp [i][j] 才不会被初始值覆盖。
// 4. 确定遍历顺序
// 从递归公式中，可以看出，dp [i][j] 依赖于 dp [i + 1][j - 1] ，dp [i + 1][j] 和 dp [i][j - 1]
// 5. 举例推导 dp 数组
// - c b b d
// c 1 1 2 2
// b 0 1 2 2
// b 0 0 1 1
// d 0 0 0 1
// 时间复杂度: O (n^2)
// 空间复杂度: O (n^2)
class Solution_D1 {
public:
    int longestPalindromeSubseq(string s) {
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        for (int i = 0; i < s.size(); i++) dp[i][i] = 1;    // 初始化 i == j
        for (int i = s.size() - 1; i >= 0; i--) {           // i 倒序
            for (int j = i + 1; j < s.size(); j++) {        // j 正序 j在 i右边 即 j>i
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][s.size() - 1];
    }
};


// 16:38
// 滚动数组
// s[i] == s[j]:dp[i][j] = dp[i+1][j-1] + 2;
//              dp[j] = pre + 2;
// s[i] != s[j]:dp[i][j] = std::max(dp[i+1][j], dp[i][j-1]);
//              dp[j] = std::max(dp[j], dp[j-1]);
class Solution_D2 {
public:
    int longestPalindromeSubseq(string s) {
        int size = s.size();
        vector<int> dp(size, 0);
        for(int i=size-1; i>=0; i--) {
            int pre = 0; // 
            for(int j=i; j<size; j++) {
                int temp = dp[j];
                if(i == j) {
                    dp[j] = 1;
                }
                else if(s[i] == s[j]) {
                    dp[j] = pre + 2;
                }
                else {
                    dp[j] = std::max(dp[j], dp[j-1]);
                }
                pre = temp;
            }
        }
        return dp[size-1];
    }
};
