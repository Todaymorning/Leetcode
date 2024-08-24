// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/description/
// 121. 买卖股票的最佳时机
// labuladong 题解思路
// 简单
// 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
// 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
// 返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。

// 示例 1：
// 输入：[7,1,5,3,6,4]
// 输出：5
// 解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
//      注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。

// 示例 2：
// 输入：prices = [7,6,4,3,1]
// 输出：0
// 解释：在这种情况下, 没有交易完成, 所以最大利润为 0。

// 提示：
// 1 <= prices.length <= 10^5
// 0 <= prices[i] <= 10^4


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// L：股票交易问题
// dp[i][k][0]：第 i 天，最多交易 k 次，不持有股票时最大获利
// dp[i][k][1]：第 i 天，最多交易 k 次，持有股票时最大获利
// dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + price[i])   // 继续不持有，持有的卖出
// dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1] - price[i])    // 继续持有，不持有的耗费一次交易机会买入

// dp[-1][...][0] = 0
// 解释：因为 i 是从 0 开始的，所以 i = -1 意味着还没有开始，这时候的利润当然是 0。

// dp[-1][...][1] = INT_MIN
// 解释：还没开始的时候，是不可能持有股票的。
// 因为我们的算法要求一个最大值，所以初始值设为一个最小值，方便取最大值。

// dp[...][0][0] = 0
// 解释：因为 k 是从 1 开始的，所以 k = 0 意味着根本不允许交易，这时候利润当然是 0。

// dp[...][0][1] = -infinity
// 解释：不允许交易的情况下，是不可能持有股票的。
// 因为我们的算法要求一个最大值，所以初始值设为一个最小值，方便取最大值。

// base case：
// dp[-1][...][0] = dp[...][0][0] = 0
// dp[-1][...][1] = dp[...][0][1] = -infinity

// 状态转移方程：
// dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
// dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])



#include<iostream>
#include<vector>
using std::vector;
using std::max;

class Solution {
public:
    int maxProfit(vector<int>& prices) {

    }
};


// 11:56--12:11(读题找思路)--12:22
// 找到波峰波谷后也不能实现一次交易利润最大化，不能用贪心，只有一次交易，没有局部最优
// 动态规划
class Solution_M1 {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() < 2) return 0;
        int result = 0;
        int min = prices[0];
        int max = prices[0];
        for(int i=1; i<prices.size(); i++) {
            if(prices[i] >= max) {
                max = prices[i];
                if(max - min > result)
                    result = max - min; // 大的更大，更新结果
            }
            if(prices[i] < min) {       // 小的更小，重新开始
                min = prices[i];
                max = prices[i];
            }
        }
        return result;
    }
};


// 暴力求间距----超时
// 时间复杂度：O (n^2)
// 空间复杂度：O (1)
class Solution_D1_copy {
public:
    int maxProfit(vector<int>& prices) {
        int result = 0;
        for (int i = 0; i < prices.size(); i++) {
            for (int j = i + 1; j < prices.size(); j++){
                result = std::max(result, prices[j] - prices[i]);
            }
        }
        return result;
    }
};

// 贪心----与 M1 相似
// 因为股票就买卖一次，那么贪心的想法很自然就是取最左最小值，取最右最大值，那么得到的差值就是最大利润。
// 时间复杂度：O (n)
// 空间复杂度：O (1)
class Solution_D2_copy {
public:
    int maxProfit(vector<int>& prices) {
        int low = INT_MAX;
        int result = 0;
        for (int i = 0; i < prices.size(); i++) {
            low = std::min(low, prices[i]);  // 取最左最小价格
            result = std::max(result, prices[i] - low); // 直接取最大区间利润
        }
        return result;
    }
};



// 动态规划
// 1. 确定 dp 数组（dp table）以及下标的含义
// dp [i][0] 表示第 i 天持有股票所得最多现金,一开始现金是 0，那么加入第 i 天买入股票现金就是 -prices [i]， 这是一个负数。
// dp [i][1] 表示第 i 天不持有股票所得最多现金, 注意这里说的是 “持有”，“持有” 不代表就是当天 “买入”！也有可能是昨天就买入了，今天保持持有的状态
// 2. 确定递推公式
// 如果第 i 天持有股票即 dp [i][0]， 那么可以由两个状态推出来
//      第 i-1 天就持有股票，那么就保持现状，所得现金就是昨天持有股票的所得现金 即：dp [i - 1][0]
//      第 i 天买入股票，所得现金就是买入今天的股票后所得现金即：-prices [i]
//      那么 dp [i][0] 应该选所得现金最大的，所以 dp [i][0] = max (dp [i - 1][0], -prices [i]);
// 如果第 i 天不持有股票即 dp [i][1]， 也可以由两个状态推出来
//      第 i-1 天就不持有股票，那么就保持现状，所得现金就是昨天不持有股票的所得现金 即：dp [i - 1][1]
//      第 i 天卖出股票，所得现金就是按照今天股票价格卖出后所得现金即：prices [i] + dp [i - 1][0]
//      同样 dp [i][1] 取最大的，dp [i][1] = max (dp [i - 1][1], prices [i] + dp [i - 1][0]);
// 3. dp 数组如何初始化
// 由递推公式 dp [i][0] = max (dp [i - 1][0], -prices [i]); 和 dp [i][1] = max (dp [i - 1][1], prices [i] + dp [i - 1][0]); 可以看出
// 其基础都是要从 dp [0][0] 和 dp [0][1] 推导出来。
// 那么 dp [0][0] 表示第 0 天持有股票，此时的持有股票就一定是买入股票了，因为不可能有前一天推出来，所以 dp [0][0] -= prices [0];
// dp [0][1] 表示第 0 天不持有股票，不持有股票那么现金就是 0，所以 dp [0][1] = 0;
// 4. 确定遍历顺序
// 从递推公式可以看出 dp [i] 都是由 dp [i - 1] 推导出来的，那么一定是从前向后遍历。
// 5. 举例推导 dp 数组
// 以示例 1，输入：[7,1,5,3,6,4] 为例
// -7, 0
// (-7, -1)(-1), (0, 1-7)(0)
// (-1, -5)(-1), (0, 5-1)(4)
// (-1, -3)(-1), (4, 3-1)(4)
// (-1, -6)(-1), (4, 6-1)(5)
// (-1, -4)(-1), (5, 4-1)(5)
// dp[i][0] 始终保存最低票价
// dp[i][1] 始终保存 历史最大收益中的最大值

// 21:30(看完 D3 思路后开始)--21:45
// dp[i][0]: 第 i 天持有股票的最大收益
// dp[i][1]: 第 i 天不持有股票的最大收益
// 时间复杂度：O (n)
// 空间复杂度：O (n)
class Solution_D3 {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() < 2) return 0;
        vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for(int i=1; i<prices.size(); i++) {
            dp[i][0] = std::max(dp[i-1][0], -prices[i]);    // 继续前一天的持有、今天买入
            dp[i][1] = std::max(dp[i-1][1],  prices[i] + dp[i-1][0]);   // 继续前一天的不持有， 今天卖出
        }
        return dp[prices.size() - 1][1];
    }
};

// 由于今天的最大值只和前一天的最大值有关，将 dp 数组可以简化为两个数
class Solution_D3_2 {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() < 2) return 0;
        int dp00 = -prices[0];  // 历史最低票价
        int dp01 = 0;           // 最大收益
        for(int i=1; i<prices.size(); i++) {
            dp01 = std::max(dp01,  prices[i] + dp00);   // 这里和dp00(历史最低价格有关)，因此放在前面
            dp00 = std::max(dp00, -prices[i]);
        }
        return dp01;
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])
// dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - prices[i]) 
//             = max(dp[i-1][1][1], -prices[i])
// 解释：k = 0 的 base case，所以 dp[i-1][0][0] = 0。
// 现在发现 k 都是 1，不会改变，即 k 对状态转移已经没有影响了。
// 可以进行进一步化简去掉所有 k：
// dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
// dp[i][1] = max(dp[i-1][1], -prices[i])
class Solution_L1 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for (int i = 1; i < n; ++i) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
            dp[i][1] = max(dp[i-1][1], -prices[i]);     // ***
        }
        return dp[n-1][0];
    }
};

// 空间复杂度优化版本
class Solution_L2 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // base case: dp[-1][0] = 0, dp[-1][1] = -infinity
        int dp_i_0 = 0, dp_i_1 = INT_MIN;
        for (int i = 0; i < n; i++) {
            // dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
            dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
            // dp[i][1] = max(dp[i-1][1], -prices[i])
            dp_i_1 = max(dp_i_1, -prices[i]);
        }
        return dp_i_0;
    }
};