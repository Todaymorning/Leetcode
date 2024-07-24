// https://leetcode.cn/problems/longest-palindromic-substring
// 5. 最长回文子串
// labuladong 题解
// 思路
// 已解答
// 中等
// 相关标签
// 相关企业
// 提示
// 给你一个字符串 s，找到 s 中最长的回文
// 子串
// 。
// 如果字符串的反序与原始字符串相同，则该字符串称为回文字符串。

// 示例 1：
// 输入：s = "babad"
// 输出："bab"
// 解释："aba" 同样是符合题意的答案。

// 示例 2：
// 输入：s = "cbbd"
// 输出："bb"

// 提示：
// 1 <= s.length <= 1000
// s 仅由数字和英文字母组成

#include<iostream>
#include<string>
#include<vector>
using std::vector;
using std::string;
using std::pair;

class Solution {
public:
    string longestPalindrome(string s) {

    }
};


// 10:43--11:10
// 中心扩展算法
// 暴力， 分奇偶
class Solution_L1_M1 {
    struct range {
        int size;
        int left;
        int right;
        range(int s, int l, int r) : size(s), left(l), right(r) {}
        range() : size(0), left(0), right(0) {}
    };
public:
    string longestPalindrome(string s) {
        int n = s.size();
        range max;
        for(int i=0; i<n; i++) {
            range r1 = palindrome(s, i, i); // 以 s[i] 为中心
            range r2 = palindrome(s, i, i+1);   // 以 s[i][i+1] 为中心
            if(r1.size > max.size) {
                max = r1;
            }
            if(r2.size > max.size) {
                max = r2;
            }
        }
        return string(s.begin() + max.left, s.begin() + max.right + 1);
    }
    // 中心向两边扩展
    range palindrome(const string& s, int l, int r) {
        if(l<0 || r>=s.size() || s[l] != s[r]) return range(0, 0, 0);
        while(l>=0 && r<s.size() && s[l] == s[r]) {
            l--;    // 可能过界
            r++;
        }
        l++;
        r--;
        return range(r - l + 1, l, r);  // [l, r]
    }
};



// 作者：力扣官方题解
// 链接：https://leetcode.cn/problems/longest-palindromic-substring/solutions/255195/zui-chang-hui-wen-zi-chuan-by-leetcode-solution/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
class Solution_G2_copy {
public:
    // 参数 left 和 right 最多差 1
    // [left+1, right-1]
    pair<int, int> expandAroundCenter (const string& s, int left, int right) {
        while (left >= 0 && right < s.size () && s [left] == s [right]) {
            --left;
            ++right;
        }
        return {left + 1, right - 1};
        // {i, i} --> {i, i}
        // {i, i+1} --> {i+1, i}    // 可能 返回的第二个数比第一个数小，但不影响 len 的计算
    }

    string longestPalindrome (string s) {
        int start = 0, end = 0;
        for (int i = 0; i < s.size (); ++i) {
            auto [left1, right1] = expandAroundCenter (s, i, i);
            auto [left2, right2] = expandAroundCenter (s, i, i + 1);
            if (right1 - left1 > end - start) {
                start = left1;
                end = right1;
            }
            if (right2 - left2 > end - start) {
                start = left2;
                end = right2;
            }
        }
        return s.substr (start, end - start + 1);
    }
};




// 11:17--11:39(超时)
// 动态规划
// dp[i][j] = {size, left, right} [left, right];
// s[i] == s[j]: dp[i][j][0] = dp[i+1][j-1][0] == j - i - 1 ? dp[i+1][j-1][0] : 1;
// i >= j
// i 倒序，j 正序
#if 0
class Solution_M2 {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(3, 0)));
        for(int i=0; i<n; i++) {
            dp[i][i] = {1, i, i};
        }
        vector<int> res = {1, 0, 0};
        for(int i=n-1; i>=0; i--) {
            for(int j=i+1; j<n; j++) {
                if(s[i] == s[j]) {
                    if(j == i+1) {  // 相邻
                        dp[i][j] = {2, i, j};
                    }
                    else {  // 不相邻
                        dp[i][j][0] = dp[i+1][j-1][0] == j - i - 1 ? dp[i+1][j-1][0] + 2 : 1;
                        dp[i][j][1] = i;
                        dp[i][j][2] = j;
                    }
                    if(dp[i][j][0] > res[0]) {
                        res = dp[i][j];
                    }
                }
            }
        }
        return string(s.begin() + res[1], s.begin() + res[2] + 1);
    }
};
#endif




// 11:40--11:54(有错)--解决
// dp[i][j]记录s[i]~s[j]是否是回文
// s[i] == s[j] : dp[i][j] = dp[i+1][j-1] == 1 ? 1 : 0;
// s[i] != s[j] : dp[i][j] = 0;
// i < j, i 倒序 ， j 正序
        // s[i] == s[j]
        // i == j    dp[i][j] = 1;
        // j = i + 1 dp[i][j] = 1;
        // j > i + 1 dp[i][j] = dp[i+1][j-1];
// 输入
// s =
// "aacabdkacaa"
// 输出
// "aacabdkacaa"
// 预期结果
// "aca"
class Solution_G1_M1 {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for(int i=0; i<n; i++) {
            dp[i][i] = 1;   // 初始化对角线
        }
        int max = 1;    // ***
        int idx = 0;    // 起始索引
        for(int i=n-1; i>=0; i--) {         // i 倒序
            for(int j=i+1; j<n; j++) {      // j 正序
                if(s[i] == s[j]) {
                    if(j == i+1)    // i j相邻          ***
                        dp[i][j] = 1;
                    else            // i j不相邻
                        dp[i][j] = dp[i+1][j-1];
                    if(dp[i][j] && j - i + 1 > max) {   // ***
                        max = j - i + 1;
                        idx = i;
                    }
                }
            }
        }
        return string(s.begin() + idx, s.begin() + idx + max);
    }
};


// 2024 年 5 月 8 日
// 16:43--16:52
// s [i] == s [j]
// i == j    dp [i][j] = 1;
// j = i + 1 dp [i][j] = 1;
// j > i + 1 dp [i][j] = dp [i+1][j-1];
class Solution {
public:
    string longestPalindrome (string s) {
        int n = s.size ();
        vector<vector<int>> dp (n, vector<int>(n, 0));
        int start = 0;
        int end = 0;
        for (int i=n-1; i>=0; i--) {
            for (int j=i; j<n; j++) {
                if (s [i] == s [j]) {
                    if (j<=i+1) dp [i][j] = 1;
                    else dp [i][j] = dp [i+1][j-1];
                    if (dp [i][j] && j - i + 1 > end - start + 1) {
                        start = i;
                        end = j;
                    }
                }
            }
        }
        return string (s.begin () + start, s.begin () + end + 1);
    }
};

