// 70. 爬楼梯
// 思路
// 简单
// 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
// 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

// 示例 1：
// 输入：n = 2
// 输出：2
// 解释：有两种方法可以爬到楼顶。
// 1. 1 阶 + 1 阶
// 2. 2 阶

// 示例 2：
// 输入：n = 3
// 输出：3
// 解释：有三种方法可以爬到楼顶。
// 1. 1 阶 + 1 阶 + 1 阶
// 2. 1 阶 + 2 阶
// 3. 2 阶 + 1 阶

// 提示：
// 1 <= n <= 45

#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int climbStairs(int n) {

    }
};

// 9:50--9:54(超出时间限制)
// 回溯解法
// 通过数目：21/45
class Solution_M1 {
    int result = 0;
    void backtracking(int n) {
        if(n <= 0) {
            if(n == 0) result++;
            return;
        }
        for(int i=1; i<=2; i++) {
            n-=i;
            backtracking(n);
            n+=i;
        }
    }
public:
    int climbStairs(int n) {
        result = 0;
        backtracking(n);
        return result;
    }
};

// 9:57--10:01(报错)--10:11(推导公式)--10:17
// 动态规划解法
// 首先是 dp [i - 1]，上 i-1 层楼梯，有 dp [i - 1] 种方法，那么再一步跳一个台阶不就是 dp [i] 了么。
// 还有就是 dp [i - 2]，上 i-2 层楼梯，有 dp [i - 2] 种方法，那么再一步跳两个台阶不就是 dp [i] 了么。
// 时间复杂度：O (n)
// 空间复杂度：O (1)
class Solution_D2 {
public:
    int climbStairs(int n) {
        // vector<int> dp(n+1, -1);
        // dp[0] = 0;
        // dp[1] = 1;
        // dp[2] = 2;
        if(n<2) return n;
        int dp[3] = {1, 2, -1};
        for(int i=3; i<=n; i++) {
            dp[2] = dp[0] + dp[1];
            dp[0] = dp[1];
            dp[1] = dp[2];
        }
        return dp[2];
    }
};


class Solution_D1 {
public:
    int climbStairs(int n) {
        vector<int> dp(n+1, -1);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        for(int i=3; i<=n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
};







// 拓展
// https://kamacoder.com/problempage.php?pid=1067
// 就是一步一个台阶，两个台阶，三个台阶，直到 m 个台阶，有多少种方法爬到 n 阶楼顶。
// m = 3, n = 5
// 0, 1, 2, 3, 4, 5
// 1, 1, 2, 4, 7, 13
// dp[3] = dp[3-1] + dp[3-2] + dp[3-3];
class Solution {
public:
    int climbStairs(int n, int m) {
        vector<int> dp(n+1, 0);
        dp[0] = 1;  // ***
        for(int i=1; i<=n; i++) {
            for(int j=1; i>=j && j<=m; j++) {
                dp[i] += dp[i-j];
            }
        }
        return dp[n];
    }
};