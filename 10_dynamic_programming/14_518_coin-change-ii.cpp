// 518. 零钱兑换 II
// labuladong 题解思路
// 中等
// 给你一个整数数组 coins 表示不同面额的硬币，另给一个整数 amount 表示总金额。
// 请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回 0 。
// 假设每一种面额的硬币有无限个。 
// 题目数据保证结果符合 32 位带符号整数。

// 示例 1：
// 输入：amount = 5, coins = [1, 2, 5]
// 输出：4
// 解释：有四种方式可以凑成总金额：
// 5=5
// 5=2+2+1
// 5=2+1+1+1
// 5=1+1+1+1+1

// 示例 2：
// 输入：amount = 3, coins = [2]
// 输出：0
// 解释：只用面额 2 的硬币不能凑成总金额 3 。

// 示例 3：
// 输入：amount = 10, coins = [10] 
// 输出：1

// 提示：
// 1 <= coins.length <= 300
// 1 <= coins[i] <= 5000
// coins 中的所有值 互不相同
// 0 <= amount <= 5000

#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int change(int amount, vector<int>& coins) {

    }
};

// 16:34--16:56(不会)
// 求装满背包的几种方法，dp[j] += dp[j-nums[i]]
// 时间复杂度: O (mn)，其中 m 是 amount，n 是 coins 的长度
// 空间复杂度: O (m)
//
// 假设：coins [0] = 1，coins [1] = 5
// 计算组合数
// for (int i = 0; i < coins.size(); i++) { // 遍历物品
//     for (int j = coins[i]; j <= amount; j++) { // 遍历背包容量
//         dp[j] += dp[j - coins[i]];
//     }
// }
//          1,  1, 2,      3,          4,                5
// coins[i]=1,  1, 11,     111,        1111,             11111
// coins[i]=2,  1, 11 + 2, 111 + (1)2, 1111 + (11 + 2)2, 11111 + (111 + (1)2)2
// coins[i]=5,  1, 11 + 2, 111 + (1)2, 1111 + (11 + 2)2, 11111 + (111 + (1)2)2 + 5

// 先把 1 加入计算，然后再把 5 加入计算，得到的方法数量只有 {1, 5} 这种情况。而不会出现 {5, 1} 的情况。
// 计算排列数
// for (int j = 0; j <= amount; j++) { // 遍历背包容量
//     for (int i = 0; i < coins.size(); i++) { // 遍历物品
//         if (j - coins[i] >= 0) dp[j] += dp[j - coins[i]];
//     }
// }
// 背包容量的每一个值，都是经过 1 和 5 的计算，包含了 {1, 5} 和 {5, 1} 两种情况。
class Solution_D1 {
public:
    int change(int amount, vector<int>& coins) {
        int m = coins.size();
        vector<int> dp(m + 1, 0);
        dp[0] = 1;
        for(int i=0; i<m; i++) {    // 遍历物品
            for(int j=coins[i]; j<=amount; j++) {   // 遍历背包
                dp[j] += dp[j - coins[i]];
            }
        }
    }
};

// dp[i][j] = dp[i-1][j] + dp[i][j-coins[i-1]];
// 加入coin[i-1]的组合等于：（同一列）没coin[i-1]时的组合加上有coin[i-1]（同一行）时少了一个coins[i-1]的组合
class Solution_L1 {
public:
    int change(int amount, vector<int>& coins) {
        int m = coins.size();
        vector<vector<int>> dp(m+1, vector<int>(amount+1, 0));
        for(int i=0; i<=m; i++) {
            dp[i][0] = 1;
        }
        for(int i=1; i<=m; i++) {
            for(int j=1; j<=amount; j++) {
                if(j >= coins[i-1]) {
                    dp[i][j] = dp[i-1][j] + dp[i][j-coins[i-1]];  // ***
                }
                else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[m][amount];
    }
};
