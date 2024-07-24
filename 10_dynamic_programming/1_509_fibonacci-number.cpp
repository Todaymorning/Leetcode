// 509. 斐波那契数
// labuladong 题解思路
// 简单
// 斐波那契数 （通常用 F(n) 表示）形成的序列称为 斐波那契数列 。该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。也就是：

// F(0) = 0，F(1) = 1
// F(n) = F(n - 1) + F(n - 2)，其中 n > 1
// 给定 n ，请计算 F(n) 。

// 示例 1：
// 输入：n = 2
// 输出：1
// 解释：F(2) = F(1) + F(0) = 1 + 0 = 1

// 示例 2：
// 输入：n = 3
// 输出：2
// 解释：F(3) = F(2) + F(1) = 1 + 1 = 2

// 示例 3：
// 输入：n = 4
// 输出：3
// 解释：F(4) = F(3) + F(2) = 2 + 1 = 3

// 提示：
// 0 <= n <= 30


// 动规五部曲：
// 确定 dp 数组以及下标的含义
// 确定递推公式
// dp 数组如何初始化
// 确定遍历顺序
// 举例推导 dp 数组



#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int fib(int n) {

    }
};

// 暴力递归--自上而下
// 时间复杂度： O (2^n)
// 空间复杂度：O (n)，算上了编程语言中实现递归的系统栈所占空间
class Solution_L1_M1 {
public:
    int fib(int n) {
        if(n < 2) return n; // ***
        // if(n == 0) return 0;
        // if(n == 1 || n == 2) return 1;
        return fib(n-2) + fib(n-1);
    }
};

// 20:26--20:36(base case，n可以为0)--20:39
// 带备忘录的递归--自上而下
// 时间复杂度 O (n)
class Solution_L2_M2 {
    vector<int> memo;
    int dp(int n, vector<int>& memo) {
        // base case
        if(n == 0 || n == 1) return n;  // ***
        if(memo[n] == 0) memo[n] = dp(n-2, memo) + dp(n-1, memo);
        return memo[n];
    }
public:
    int fib(int n) {
        memo = vector<int>(n+1, 0);
        return dp(n, memo);
    }
};

// 20:43--20:46
// 迭代（递推）解法--自下而上
// 时间复杂度：O (n)
// 空间复杂度：O (n)
class Solution_L3_M3_L1 {
public:
    int fib(int n) {
        if(n<2) return n;
        vector<int> dp(n+1, 0);
        // base case
        dp[0] = 0;
        dp[1] = 1;
        // 状态转移
        for(int i=2; i<=n; i++) {
            dp[i] = dp[i-2] + dp[i-1];
        }
        return dp[n];
    }
};


// 20:47--20:49
// 迭代法优化
// 时间复杂度：O (n)
// 空间复杂度：O (1)
class Solution {
public:
    int fib(int n) {
        if(n < 2) return n;
        int dp_i_2 = 0;
        int dp_i_1 = 1;
        int dp;
        for(int i=2; i<=n; i++) {
            dp = dp_i_2 + dp_i_1;
            dp_i_2 = dp_i_1;
            dp_i_1 = dp;
        }
        return dp;
    }
};