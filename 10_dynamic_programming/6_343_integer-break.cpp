// 343. 整数拆分
// 提示
// 中等
// 给定一个正整数 n ，将其拆分为 k 个 正整数 的和（ k >= 2 ），并使这些整数的乘积最大化。
// 返回 你可以获得的最大乘积 。

// 示例 1:
// 输入: n = 2
// 输出: 1
// 解释: 2 = 1 + 1, 1 × 1 = 1。

// 示例 2:
// 输入: n = 10
// 输出: 36
// 解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。

// 提示:
// 2 <= n <= 58


#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int integerBreak(int n) {

    }
};

// 16:44--16:59(读题找思路)--15:10
// 贪心
// 分的数需要大于等于 3 4 才有意义
// 满足上面的条件时，分解的个数越多越好
// 3 越多越好
// 时间复杂度：O (n)
// 空间复杂度：O (1)
class Solution {
public:
    int integerBreak(int n) {
        // 已知 n >= 2
        if(n == 2) return 1;    // 1*1
        if(n == 3) return 2;    // 1*2
        if(n == 4) return 4;    // 2*2
        int result = 1;
        while(n>4) {            // 当 n 大于 4 时，分离出一个 3
            n -= 3;
            result *= 3;
        }
        return result *= n;     // 剩下 3 或 4
    }
};


// 15:12--15:18(看 D1 思路和代码)--17:29
// 动态规划
// 自下而上得到每个整数的最大值
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n+1, INT_MIN);   // i需要等于 n
        dp[2] = 1;
        // 直接把 i 分成两个数: (i - j) * j
        // 把 i 分出一个数，剩下的按照 dp 中记录的分法分：j * dp[i - j]
        // j 从 1 自增到 i/2：dp[i]
        for(int i=3; i<=n; i++) {       // i >= 3 才需要计算
            for(int j=1; j<=i/2; j++) { // j <= i/2 ,后面的相当于重复计算
                // 循环比较 自身、 (i - j) * j 和 j * dp[i - 1] 那个大
                dp[i] = std::max(dp[i], std::max((i - j) * j, j * dp[i-j]));
            }
        }
        return dp[n];
    }
};




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution {
private:
    vector<int> memo;

public:
    int integerBreak(int n) {
        memo = vector<int>(n + 1, -1);
        return dp(n);
    }

    // 定义：拆分 n 获得的最大乘积为 dp(n)
    int dp(int n) {
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return 1;
        }
        if (memo[n] != -1) {
            return memo[n];
        }

        // 状态转移方程
        int res = INT_MIN;
        for (int i = 1; i <= n; i++) {
            res = std::max(res, i * std::max(dp(n - i), n - i));
        }
        memo[n] = res;
        return res;
    }
};


