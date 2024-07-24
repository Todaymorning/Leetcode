// 714. 买卖股票的最佳时机含手续费
// labuladong 题解思路
// 提示
// 中等
// 给定一个整数数组 prices，其中 prices[i] 表示第 i 天的股票价格 ；整数 fee 代表了交易股票的手续费用。
// 你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
// 返回获得利润的最大值。
// 注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

// 示例 1：
// 输入：prices = [1, 3, 2, 8, 4, 9], fee = 2
// 输出：8
// 解释：能够达到的最大利润:  
// 在此处买入 prices[0] = 1
// 在此处卖出 prices[3] = 8
// 在此处买入 prices[4] = 4
// 在此处卖出 prices[5] = 9
// 总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8

// 示例 2：
// 输入：prices = [1,3,7,5,10,3], fee = 3
// 输出：6

// 提示：
// 1 <= prices.length <= 5 * 10^4
// 1 <= prices[i] < 5 * 10^4
// 0 <= fee < 5 * 10^4

#include<iostream>
#include<vector>
using std::vector;
using std::max;

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {

    }
};

// 贪心解法:
// https://programmercarl.com/0714.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BA%E5%90%AB%E6%89%8B%E7%BB%AD%E8%B4%B9.html


// 15:21--15:27
// 不限交易次数，将交易费放在卖出的时候
// 时间复杂度：O (n)
// 空间复杂度：O (1)
class Solution_M1 {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int size = prices.size();
        if(size < 2) return 0;
        int dp0 = 0;
        int dp1 = -prices[0];
        for(int i=1; i<size; i++) {
            dp0 = max(dp0, dp1 + prices[i] - fee);  // 继续不持有、持有的卖出减去手续费
            dp1 = max(dp1, dp0 - prices[i]);        // 继续持有、不持有的买入
        }
        return dp0;
    }
};

// 将交易费放在买入的时候
class Solution_M2 {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int size = prices.size();
        if(size < 2) return 0;
        int dp0 = 0;
        int dp1 = -prices[0] - fee;
        for(int i=1; i<size; i++) {
            dp0 = max(dp0, dp1 + prices[i]);        // 继续不持有、持有的卖出减去手续费
            dp1 = max(dp1, dp0 - prices[i] - fee);  // 继续持有、不持有的买入
        }
        return dp0;
    }
};





// 股票问题总结
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码不保证正确性，仅供参考。如有疑惑，可以参照我写的 java 代码对比查看。

// 同时考虑交易次数的限制、冷冻期和手续费
int maxProfit_all_in_one(int max_k, vector<int>& prices, int cooldown, int fee) {
    int n = prices.size();
    if (n < 2) {
        return 0;
    }
    if (max_k > n / 2) {
        // 交易次数 k 没有限制的情况
        return maxProfit_k_inf(prices, cooldown, fee);
    }

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(max_k + 1, vector<int>(2)));
    // k = 0 时的 base case
    for (int i = 0; i < n; i++) {
        dp[i][0][0] = 0;
        dp[i][0][1] = INT_MIN;
    }

    for (int i = 0; i < n; i++) {
        for (int k = max_k; k >= 1; k--) {  // 正序应该可以
            if (i == 0) {
                // base case 1
                dp[i][k][0] = 0;
                dp[i][k][1] = -prices[i] - fee;
                continue;
            }

            // 包含 cooldown 的 base case
            if (i - cooldown - 1 < 0) {     // i <= cooldown
                // base case 2
                dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
                // 别忘了减 fee
                dp[i][k][1] = max(dp[i-1][k][1], -prices[i] - fee);  // 因为 冷冻期为 cooldown，因此在cooldown之前没有卖出后再持有的，要买只能从 0 开始
                continue;
            }
            dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
            // 同时考虑 cooldown 和 fee
            dp[i][k][1] = max(dp[i-1][k][1], dp[i-cooldown-1][k-1][0] - prices[i] - fee);   // 大于 cooldown，后面就可以有卖了再买的情况
        }
    }
    return dp[n - 1][max_k][0];
}

// k 无限制，包含手续费和冷冻期
int maxProfit_k_inf(vector<int>& prices, int cooldown, int fee) {
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        if (i - 1 == -1) {
            // base case 1
            dp[i][0] = 0;
            dp[i][1] = -prices[i] - fee;
            continue;
        }

        // 包含 cooldown 的 base case
        if (i - cooldown - 1 < 0) {
            // base case 2
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
            // 别忘了减 fee
            dp[i][1] = max(dp[i-1][1], -prices[i] - fee);
            continue;
        }
        dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
        // 同时考虑 cooldown 和 fee
        dp[i][1] = max(dp[i-1][1], dp[i-cooldown-1][0] - prices[i] - fee);
    }
    return dp[n - 1][0];
}
