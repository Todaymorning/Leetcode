// 96. 不同的二叉搜索树
// labuladong 题解思路
// 中等
// 给你一个整数 n ，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的 二叉搜索树 有多少种？返回满足题意的二叉搜索树的种数。

// 示例 1：
// 输入：n = 3
// 输出：5

// 示例 2：
// 输入：n = 1
// 输出：1

// 提示：
// 1 <= n <= 19


#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int numTrees(int n) {

    }
};


// 18:46--19:10(看题推导递推公式)--19:20(公式错误)--19:48(重新推导)
// 时间复杂度：O (n^2)
// 空间复杂度：O (n)
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n+1, 0);
        dp[0] = 1;      // ***
        dp[1] = 1;
        for(int i=2; i<=n; i++) {
            for(int j=1; j<=i; j++) {   // j 最大值为 i     ***
                dp[i] += dp[j-1] * dp[i-j];
            }
        }
        return dp[n];
    }
};


class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n+1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for(int i=2; i<=n; i++) {
            for(int j=1; j<=i/2; j++) { // 取到一半
                dp[i] += 2 * dp[j-1] * dp[i-j];
            }
            if(i%2 == 1) dp[i] += dp[i/2] * dp[i/2];    // j为中间的那个奇数时
        }
        return dp[n];
    }
};