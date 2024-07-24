// https://leetcode.cn/problems/coin-change
// 322. 零钱兑换
// labuladong 题解思路
// 中等
// 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。
// 计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
// 你可以认为每种硬币的数量是无限的。

// 示例 1：
// 输入：coins = [1, 2, 5], amount = 11
// 输出：3 
// 解释：11 = 5 + 5 + 1

// 示例 2：
// 输入：coins = [2], amount = 3
// 输出：-1

// 示例 3：
// 输入：coins = [1], amount = 0
// 输出：0

// 提示：
// 1 <= coins.length <= 12
// 1 <= coins[i] <= 23^1 - 1
// 0 <= amount <= 10^4

#include<iostream>
#include<vector>
#include<algorithm>
using std::vector;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {

    }
};


// 12:04--12:09(读题找思路)--12:15(贪心走不通)--12:19(完全背包组合，改错)--12:38
// coins = {6, 3, 2}, amount = 10 时，不好分析
// dp[0] = 0
// INT_MAX
// != INT_MAX
// == INT_MAX
// dp[i][j]
// i 物品，j 背包
// 完全背包，i正序, 如果是 0 1 背包 i倒序
// dp[i][j] = std::min(dp[i-1][j], dp[i][j-coin[i]] + 1)    // j正序
// dp[j] = std::min(dp[j], dp[j-coin[i]]);
class Solution_M1 {
public:
    int coinChange(vector<int>& coins, int amount) {
        if(amount == 0) return 0;   // ***
        // std::sort(coins.begin(), coins.end());  // 升序排列
        vector<int> dp(amount + 1, INT_MAX);    // ***
        dp[0] = 0;                  // ***
        for(int i=0; i<coins.size(); i++) {     // 正序遍历物品
            for(int j=1; j<=amount; j++) {      // 正序遍历背包 [1, amount]
                if(j >= coins[i] && dp[j - coins[i]] != INT_MAX) {  // dp[j-coins[i]]得有值才能继续加
                    dp[j] = std::min(dp[j], dp[j - coins[i]] + 1);  // ***
                }
                // else dp[j] = dp[j];
            }
        }
        return dp.back() == INT_MAX ? -1 : dp.back();   // ***
    }
};

// 完全背包，背包正序遍历
// 外层 for 循环遍历物品，内层 for 遍历背包
// 时间复杂度: O (n * amount)，其中 n 为 coins 的长度
// 空间复杂度: O (amount)
class Solution_D1_copy {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < coins.size(); i++) { // 遍历物品
            for (int j = coins[i]; j <= amount; j++) { // 遍历背包
                if (dp[j - coins[i]] != INT_MAX) { // 如果dp[j - coins[i]]是初始值则跳过
                    dp[j] = std::min(dp[j - coins[i]] + 1, dp[j]);
                }
            }
        }
        if (dp[amount] == INT_MAX) return -1;
        return dp[amount];
    }
};

// 外层 for 遍历背包，内层 for 循环遍历物品
class Solution_D2_copy {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {  // 遍历背包
            for (int j = 0; j < coins.size(); j++) { // 遍历物品
                if (i - coins[j] >= 0 && dp[i - coins[j]] != INT_MAX ) {
                    dp[i] = std::min(dp[i - coins[j]] + 1, dp[i]);
                }
            }
        }
        if (dp[amount] == INT_MAX) return -1;
        return dp[amount];
    }
};




class Solution_L1_copy {
    vector<int> memo;

    public:
    int coinChange(vector<int>& coins, int amount) {
        memo.resize(amount + 1);
        // dp 数组全都初始化为特殊值
        fill(memo.begin(), memo.end(), -666);
        return dp(coins, amount);
    }

    int dp(vector<int>& coins, int amount) {
        if (amount == 0) return 0;
        if (amount < 0) return -1;
        // 查备忘录，防止重复计算
        if (memo[amount] != -666)
            return memo[amount];

        int res = INT_MAX;
        for (int coin : coins) {
            // 计算子问题的结果
            int subProblem = dp(coins, amount - coin);
            // 子问题无解则跳过
            if (subProblem == -1) continue;
            // 在子问题中选择最优解，然后加一
            res = std::min(res, subProblem + 1);
        }
        // 把计算结果存入备忘录
        memo[amount] = (res == INT_MAX) ? -1 : res;
        return memo[amount];
    }
};



// 2024年5月9日
// 10:44--12:00
// 完全背包，正序遍历物品，正序遍历空间
// dp[i][j] = std::min(dp[i-1][j], dp[i][j-coins[i]]);
// i-1 --> i：i正序，注意 i==0
class Solution_M1 {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<vector<int>> dp(coins.size(), vector<int>(amount+1, INT_MAX));
        // 第 0 列置零，dp[i][j-coins[i]] == dp[i][0] when j == coins[i]
        for(int i=0; i<coins.size(); i++) {
            dp[i][0] = 0;
        }
        // 第 0 行， 有 i-1 , 提前计算 i == 0
        for(int j=0; j<=amount; j++) {
            if(j >= coins[0] && dp[0][j-coins[0]] != INT_MAX) {
                dp[0][j] = dp[0][j-coins[0]] + 1;
            }
        }
        for(int i=1; i<coins.size(); i++) {
            for(int j=0; j<=amount; j++) {
                if(j < coins[i] || dp[i][j-coins[i]] == INT_MAX) {
                    dp[i][j] = dp[i-1][j];
                }
                else {
                    // 上一行正好装满的，本行正好少了一个coins[i]的
                    dp[i][j] = std::min(dp[i-1][j], dp[i][j - coins[i]] + 1);
                }
            }
        }
        return dp.back().back() == INT_MAX ? -1 : dp.back().back();
    }
};


class Solution_M2 {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<vector<int>> dp(coins.size() + 1, vector<int>(amount+1, INT_MAX));
        // 第 0 列置零，dp[i][j-coins[i]] == dp[i][0] when j == coins[i]
        for(int i=0; i<coins.size(); i++) {
            dp[i][0] = 0;
        }
        for(int i=1; i<=coins.size(); i++) {
            for(int j=0; j<=amount; j++) {
                if(j < coins[i-1] || dp[i][j-coins[i-1]] == INT_MAX) {
                    dp[i][j] = dp[i-1][j];
                }
                else {
                    // 上一行正好装满的，本行正好少了一个coins[i]的
                    dp[i][j] = std::min(dp[i-1][j], dp[i][j - coins[i-1]] + 1);
                }
            }
        }
        return dp.back().back() == INT_MAX ? -1 : dp.back().back();
    }
};