// 309. 买卖股票的最佳时机含冷冻期
// labuladong 题解思路
// 中等
// 给定一个整数数组prices，其中第  prices[i] 表示第 i 天的股票价格 。​
// 设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:
// 卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
// 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

// 示例 1:
// 输入: prices = [1,2,3,0,2]
// 输出: 3 
// 解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]

// 示例 2:
// 输入: prices = [1]
// 输出: 0

// 提示：
// 1 <= prices.length <= 5000
// 0 <= prices[i] <= 1000


#include<iostream>
#include<vector>
using std::vector;
using std::max;

class Solution {
public:
    int maxProfit(vector<int>& prices) {

    }
};


// 20:47--20:50(读题找思路)--21:14(错误)
// dp[i][0]:继续前一天不持有
// dp[i][1]:持有
// dp[i][2]:卖出
// 判断前一天是否卖出，卖出则按兵不动，卖出则正常操作
// 解答错误
// 49 / 210 个通过的测试用例
// 输入
// prices =
// [2,1]
// 输出
// -1
// 预期结果
// 0
#if 0
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(size < 2) return 0;
        vector<vector<int>> dp(size, vector<int>(3, 0));
        dp[0] = {0, -prices[0], 0};
        for(int i=1; i<size; i++) {
            dp[i][0] = std::max(dp[i-1][0], dp[i-1][2]);    // 继续前一天不持有，前一天卖出
            if(i == 1) {
                dp[i][1] = dp[i-1][1];  // 继续持有（没法卖了买入）
            }
            else {
                dp[i][1] = std::max(dp[i-1][1], dp[i-2][2] - prices[i]);    // 继续前一天持有，前天卖了之后今天买入
            }
            dp[i][2] = dp[i-1][1] + prices[i];              // 今天卖出
        }
        return dp.back()[2];
    }
};
#endif




// dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
// dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i])
// 解释：第 i 天选择 buy 的时候，要从 i-2 的状态转移，而不是 i-1 。     ???
class Solution_L1 {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(size < 2) return 0;
        vector<vector<int>> dp(size, vector<int>(2, 0));
        // 前两天正常
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        dp[1][0] = std::max(dp[0][0], dp[0][1] + prices[1]);    // 继续不持有、持有的卖出
        dp[1][1] = std::max(dp[0][1], dp[0][0] - prices[1]);    // 继续持有、前一天不持有今天买入
        for(int i=2; i<size; i++) {
            dp[i][0] = std::max(dp[i-1][0], dp[i-1][1] + prices[i]);    // 继续不持有、持有的卖出
            dp[i][1] = std::max(dp[i-1][1], dp[i-2][0] - prices[i]);    // 继续持有、前两天不持有的买入
        }
        return dp.back()[0];
    }
};


// 空间复杂度优化版本
int maxProfit_with_cool_copy(vector<int>& prices) {
    int n = prices.size();
    int dp_i_0 = 0, dp_i_1 = INT_MIN;
    int dp_pre_0 = 0; // 代表 dp[i-2][0]
    for (int i = 0; i < n; i++) {
        int temp = dp_i_0;
        dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
        dp_i_1 = max(dp_i_1, dp_pre_0 - prices[i]);
        dp_pre_0 = temp;
    }
    return dp_i_0;
}



// 可以区分出如下四个状态：
// 状态一：持有股票状态（今天买入股票，或者是之前就买入了股票然后没有操作，一直持有）
// 不持有股票状态，这里就有两种卖出股票状态
//      状态二：保持卖出股票的状态（两天前就卖出了股票，度过一天冷冻期。或者是前一天就是卖出股票状态，一直没操作）
//      状态三：今天卖出股票
// 状态四：今天为冷冻期状态，但冷冻期状态不可持续，只有一天！
// 确定递推公式
// 达到买入股票状态（状态一）即：dp [i][0]，有两个具体操作：
//      操作一：前一天就是持有股票状态（状态一），dp [i][0] = dp [i - 1][0]
//      操作二：今天买入了，有两种情况
//          前一天是冷冻期（状态四），dp [i - 1][3] - prices [i]
//          前一天是保持卖出股票的状态（状态二），dp [i - 1][1] - prices [i]
//      那么 dp [i][0] = max (dp [i - 1][0], dp [i - 1][3] - prices [i], dp [i - 1][1] - prices [i]);
// 达到保持卖出股票状态（状态二）即：dp [i][1]，有两个具体操作：
//      操作一：前一天就是状态二
//      操作二：前一天是冷冻期（状态四）
//      dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
// 达到今天就卖出股票状态（状态三），即：dp [i][2] ，只有一个操作：
//      昨天一定是持有股票状态（状态一），今天卖出
//      即：dp [i][2] = dp [i - 1][0] + prices [i];
// 达到冷冻期状态（状态四），即：dp [i][3]，只有一个操作：
//      昨天卖出了股票（状态三）
//      dp[i][3] = dp[i - 1][2];
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(size < 2) return 0;
        vector<vector<int>> dp(size, vector<int>(4, 0));
        // 0, 1, 2, 3 分别代表 买入、今天卖出、冷冻、卖出
        dp[0][0] = -prices[0];
        for(int i=1; i<size; i++) {
            dp[i][0] = max(dp[i-1][0], max(dp[i-1][2] - prices[i], dp[i-1][3] - prices[i])); // 继续持有、昨天冰冻今天解冻就买，解冻好久的卖出状态买
            dp[i][1] = dp[i-1][0] + prices[i];  // 昨天的持有今天卖出
            dp[i][2] = dp[i-1][1];              // 昨天的卖出(转为今天冰冻)
            dp[i][3] = max(dp[i-1][3], dp[i-1][2]); // 继续不持有、昨天的冰冻刚转为不持有
        }
        int result = 0;
        for(int n:dp.back()) result = result > n ? result : n;
        return result;
    }
};