// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock
// 121. 买卖股票的最佳时机


#include<iostream>
#include<vector>
using std::vector;
using std::max;

class Solution {
public:
    int maxProfit(vector<int>& prices) {

    }
};

// 2024年4月28日
// 15:03--15:07
// 贪心
class Solution {
public:
    int maxProfit(vector<int>& prices) {

        int res = 0;
        int min = prices[0];
        for(int i=1; i<prices.size(); i++) {
            if(prices[i] > min) {
                int temp = prices[i] - min;
                if(temp > res) res = temp;
            }
            if(prices[i] < min) min = prices[i];
        }
        return  res;
    }
};



// 2024年4月28日
// 15:12--15:51(看思路)
// 动态规划
// 初始状态
// dp[-1][0] = 0;
// dp[-1][1] = INT_MIN;
// 状态转移
// dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
// dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
// dp[i][0] = std::max(dp[i-1][0], dp[i-1][1] + prices[i]);
// dp[i][1] = std::max(dp[i-1][1], - prices[i]);

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for(int i=1; i<n; i++) {
            dp[i][0] = std::max(dp[i-1][0], dp[i-1][1] + prices[i]);
            dp[i][1] = std::max(dp[i-1][1], -prices[i]);
            // 只有一次交易的机会
            // dp[i][1] = std::max(dp[i-1][1], dp[i-1][0] - prices[i]);     ***
        }
        return dp[n-1][0];
    }
};