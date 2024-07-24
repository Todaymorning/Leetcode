// 279. 完全平方数
// 思路
// 相关企业
// 给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。
// 完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。

// 示例 1：
// 输入：n = 12
// 输出：3 
// 解释：12 = 4 + 4 + 4

// 示例 2：
// 输入：n = 13
// 输出：2
// 解释：13 = 4 + 9

// 提示：
// 1 <= n <= 10^4

#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int numSquares(int n) {

    }
};


// 16:48--17:02(错误)--17:14
// 完全背包，每个平方数都可以重复使用
// 组合
// 求最小值，初始化为 INT_MAX
// i不能等于 nums.size()
// dp[0] = 0， 如 nums[i] = 4, j = 4, 此时dp[j] = dp[j-nums[i]] + 1 = dp[4 -4] + 1 = 0 + 1 = 1;
class Solution_M1 {
public:
    int numSquares(int n) {
        // 找nums[i]
        vector<int> nums;
        for(int i=1; i<=n; i++) {
            int p = i*i;
            if(p < n) nums.push_back(p);
            else if(p == n) return 1;
            else break;
        }
        vector<int> dp(n + 1, INT_MAX); // ***
        dp[0] = 0;  // ***
        for(int i=0; i<nums.size(); i++) { // 遍历物品  // **
            for(int j=nums[i]; j<=n; j++) { // 遍历背包，从前往后
                dp[j] = std::min(dp[j], dp[j-nums[i]] + 1);
            }
        }
        return dp[n];
    }
};


// 17:23--17:33
// 先遍历背包，再遍历物品
class Solution_M2 {
public:
    int numSquares(int n) {
        vector<int> nums;
        for(int i=1; i<=n; i++) {
            int p = i * i;
            if(p < n) nums.push_back(p);
            else if(p == n) return 1;
            else break;
        }
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for(int j=1; j<=n; j++) {
            for(int i=0; i<nums.size(); i++) {
                if(j >= nums[i]) {
                    dp[j] = std::min(dp[j], dp[j - nums[i]] + 1);
                }
            }
        }
        // for(int j=1; j<=n; j++) {
        //     for(int i=0; nums[i]<=j && i<nums.size(); i++) {
        //         dp[j] = std::min(dp[j], dp[j - nums[i]] + 1);
        //     }
        // }
        return dp[n];
    }
};


// 不适用额外的空间
class Solution_M3 {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for(int j=1; j<=n; j++) {
            for(int i=1; j >= i*i; i++) {   // ***
                dp[j] = std::min(dp[j], dp[j - i*i] + 1);
            }
        }
        return dp[n];
    }
};



// 先遍历背包，再遍历物品
// 时间复杂度: O (n * √n)
// 空间复杂度: O (n)
class Solution_D1_copy {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i <= n; i++) { // 遍历背包
            for (int j = 1; j * j <= i; j++) { // 遍历物品
                dp[i] = std::min(dp[i - j * j] + 1, dp[i]);
            }
        }
        return dp[n];
    }
};


// 先遍历物品，再遍历背包
class Solution_D2_copy {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i * i <= n; i++) { // 遍历物品
            for (int j = i * i; j <= n; j++) { // 遍历背包
                dp[j] = std::min(dp[j - i * i] + 1, dp[j]);
            }
        }
        return dp[n];
    }
};