// 392. 判断子序列
// labuladong 题解思路
// 简单
// 给定字符串 s 和 t ，判断 s 是否为 t 的子序列。
// 字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace" 是 "abcde" 的一个子序列，而 "aec" 不是）。

// 进阶：
// 如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >= 10 亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？

// 致谢：
// 特别感谢 @pbrother 添加此问题并且创建所有测试用例。

// 示例 1：
// 输入：s = "abc", t = "ahbgdc"
// 输出：true

// 示例 2：
// 输入：s = "axc", t = "ahbgdc"
// 输出：false

// 提示：
// 0 <= s.length <= 100
// 0 <= t.length <= 10^4
// 两个字符串都只由小写字符组成。


#include<iostream>
#include<string>
#include<vector>
using std::vector;
using std::string;

class Solution {
public:
    bool isSubsequence(string s, string t) {

    }
};



// 14:38--14:47
// 动态规划
// dp[i] 最长重合子序列长度
// s 是否是 t 的子序列
class Solution_M1 {
public:
    bool isSubsequence(string s, string t) {
        int s_size = s.size();
        int t_size = t.size();
        if(s_size > t_size) return false;
        vector<int> dp(s_size + 1, 0);
        for(int i=1; i<=t_size; i++) {
            int pre = dp[0];
            for(int j=1; j<=s_size; j++) {
                int temp = dp[j];
                if(t[i-1] == s[j-1]) {
                    dp[j] = pre + 1;
                }
                else {
                    dp[j] = std::max(dp[j], dp[j-1]);
                }
                pre = temp;
            }
        }
        if(dp.back() == s_size) return true;
        return false;
    }
};

// 递推方式
// dp[i][j] = dp[i - 1][j - 1] + 1;
// dp[i][j] = dp[i][j - 1];
// s = "abc", t = "ahgdc"
// - 0 a h g d c
// - 0 0 0 0 0 0
// a 0 1 1 1 1 1
// b 0 0 0 0 0 0
// c 0 0 0 0 0 1
// 匹配的是 "c"，因为匹配 "b" 的时候没匹配上，从 "c" 重新开始匹配
// 
// dp[i][j] = dp[i-1][j-1] + 1;
// dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
// s = "abc", t = "ahgdc"
// - - a h g d c
// - 0 0 0 0 0 0
// a 0 1 1 1 1 1
// b 0 1 1 1 1 1
// c 0 0 0 0 0 2
// 匹配的是 "ac"
// 时间复杂度：O (n × m)
// 空间复杂度：O (n × m)
class Solution_D1 {
public:
    bool isSubsequence(string s, string t) {
        vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= t.size(); j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else {
                    dp[i][j] = dp[i][j - 1];    // 只要中间有一个没有匹配上，前面匹配上的个数都作废
                    // dp[i][j] = max(dp[i-1][j], dp[i][j-1])
                }
            }
        }
        if (dp[s.size()][t.size()] == s.size()) return true;
        return false;
    }
};

// 由此对于上面的 D1 可以优化
class Solution_D1 {
public:
    bool isSubsequence(string s, string t) {
        vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= t.size(); j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
            if(dp[i].back() == 0) return false; // s[i] 没有在 t中找到  ***
        }
        if (dp[s.size()][t.size()] == s.size()) return true;
        return false;
    }
};


// 14:52
// 双指针
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int s_size = s.size();
        int t_size = t.size();
        if(s_size > t_size) return false;
        int num = 0;
        for(int i=0, j=0; i<t_size; i++) {
            if(t[i] == s[j]) {
                num++;  // 匹配上一个
                j++;    // 准备匹配下一个
            }
        }
        if(num == s_size) return true;
        return false;
    }
};



// 注意：cpp 代码由 chatGPT根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution_L1 {
public:
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0;
        while (i < s.length() && j < t.length()) {
            if (s[i] == t[j]) {
                i++;
            }
            j++;
        }
        return i == s.length();
    }
};