// 122. 买卖股票的最佳时机 II
// 中等
// 给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
// 在每一天，你可以决定是否购买和 / 或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。
// 返回 你能获得的 最大 利润 。

 
// 示例 1：
// 输入：prices = [7,1,5,3,6,4]
// 输出：7
// 解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
//      随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3 。
//      总利润为 4 + 3 = 7 。

// 示例 2：
// 输入：prices = [1,2,3,4,5]
// 输出：4
// 解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
//      总利润为 4 。

// 示例 3：
// 输入：prices = [7,6,4,3,1]
// 输出：0
// 解释：在这种情况下, 交易无法获得正利润，所以不参与交易可以获得最大利润，最大利润为 0 。
 
// 提示：
// 1 <= prices.length <= 3 * 10^4
// 0 <= prices[i] <= 10^4


#include<iostream>
#include<vector>
using std::vector;
using std::max;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        return 0;
    }
};


// 10:21--10:25
// 找到所有正收益的区间相加，这样会使得交易次数最多
// 时间复杂度：O (n)
// 空间复杂度：O (1)
class Solution_D1_M1 {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size() - 1;
        int result = 0;
        int diff = 0;
        for(int i=0; i<size; i++) {
            diff = prices[i+1] - prices[i];
            if(diff > 0) result += diff;
        }
        return result;
    }
};


// 10:27--10:38
// 找到波峰波谷，用最小的交易次数获得最大的收益
// while
class Solution_M2 {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(size < 2) return 0;
        vector<int> results;
        size--;
        // 找到所有的波峰波谷
        results.push_back(prices[0]);   // ***
        for(int i=0, j; i<size; ) {
            while(i<size && prices[i+1] == prices[i]) i++;
            j = i;
            while(i<size && prices[i+1] >= prices[i]) i++;
            if(i != j) results.push_back(prices[i]);
            j = i;
            while(i<size && prices[i+1] <= prices[i]) i++;
            if(i != j) results.push_back(prices[i]);
        }
        size = results.size() - 1;
        int diff = 0;
        int result = 0;
        for(int i=0; i<size; i++) {
            diff = results[i+1] - results[i];
            if(diff > 0) result += diff;
        }
        return result;
    }
};


// 10:39--10:54
// 找到波峰波谷，用最小的交易次数获得最大的收益
// 贪心
class Solution_M3 {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(size<2) return 0;
        size--;
        vector<int> results;
        int prediff = 0;
        int curdiff = 0;
        for(int i=0; i<size; i++) {
            curdiff = prices[i+1] - prices[i];
            if((prediff <= 0 && curdiff > 0) || (prediff >= 0 && curdiff < 0)) {    // = 上下坡中有平台
                results.push_back(prices[i]);
                prediff = curdiff;  // 连续上坡或连续下坡中有平台，只有在变号的时候才更新prediff
            }
        }
        results.push_back(prices.back());   // ***
        // 计算收益
        int result = 0;
        int diff = 0;
        size = results.size() - 1;
        for(int i=0; i<size; i++) {
            diff = results[i+1] - results[i];
            if(diff > 0) result += diff;
        }
        return result;
    }
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 动态规划
// 22:07
// dp [i][0] 表示第 i 天持有股票所得最多现金。
// dp [i][1] 表示第 i 天不持有股票所得最多现金
// 如果第 i 天持有股票即 dp [i][0]， 那么可以由两个状态推出来
//      第 i-1 天就持有股票，那么就保持现状，所得现金就是昨天持有股票的所得现金 即：dp [i - 1][0]
//      第 i 天买入股票，所得现金就是昨天不持有股票的所得现金减去 今天的股票价格 即：dp [i - 1][1] - prices [i]     // ***
// 如果第 i 天不持有股票即 dp [i][1] 的情况， 依然可以由两个状态推出来
//      第 i-1 天就不持有股票，那么就保持现状，所得现金就是昨天不持有股票的所得现金 即：dp [i - 1][1]
//      第 i 天卖出股票，所得现金就是按照今天股票价格卖出后所得现金即：prices [i] + dp [i - 1][0]

// 22:17--22:29(错误)--22:38(继续不持有写成了dp[i-1][0])
// prices = [7,1,5,3,6,4]
// -7, 0
// (-7, -1)(-1), (0, -7+1)(0)
// (-1, -5)(-1), (0, -1+5)(4)
// (-1, 4-3)(1), (4, -1+3)(4)
// ( 1, 4-6)(1), (4,  1+6)(7)
// ( 1, 7-4)(3), (7,  1+4)(7)
// 时间复杂度：O (n)
// 空间复杂度：O (n)
class Solution_D1_DP {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(size < 2) return 0;
        vector<vector<int>> dp(size, vector<int>(2, 0));
        dp[0][0] = -prices[0];  // 持有
        dp[0][1] = 0;           // 不持有
        for(int i=1; i<size; i++) {
            // 由于这里可以多次买卖，所以每次购买前的本金都是前一天不持有时的量(这里题目里已经假定只能持有一支，不能加仓)
            dp[i][0] = std::max(dp[i-1][0], dp[i-1][1] - prices[i]);    // 继续持有、今天购买
            // 卖出的只能时之前已有的，所以本金是前一天持有时的量
            dp[i][1] = std::max(dp[i-1][1], dp[i-1][0] + prices[i]);    // 继续不持有、持有的今天卖出   ***
        }
        return dp.back()[1];
    }
};

// 滚动数组
class Solution_D2_copy {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        vector<vector<int>> dp(2, vector<int>(2)); // 注意这里只开辟了一个2 * 2大小的二维数组
        dp[0][0] -= prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < len; i++) {
            dp[i % 2][0] = std::max(dp[(i - 1) % 2][0], dp[(i - 1) % 2][1] - prices[i]);
            dp[i % 2][1] = std::max(dp[(i - 1) % 2][1], prices[i] + dp[(i - 1) % 2][0]);
        }
        return dp[(len - 1) % 2][1];
    }
};






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 交易次数无穷多
// dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
// dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
//             = max(dp[i-1][k][1], dp[i-1][k][0] - prices[i])
// 我们发现数组中的 k 已经不会改变了，也就是说不需要记录 k 这个状态了：
// dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
// dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])

// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码不保证正确性，仅供参考。如有疑惑，可以参照我写的 java 代码对比查看。

// 原始版本
int maxProfit_k_inf(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2, 0));
    for (int i = 0; i < n; i++) {
        if (i - 1 == -1) {
            // base case
            dp[i][0] = 0;
            dp[i][1] = -prices[i];
            continue;
        }
        dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
        dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
    }
    return dp[n - 1][0];
}

// 空间复杂度优化版本
int maxProfit_k_inf(vector<int>& prices) {
    int n = prices.size();
    int dp_i_0 = 0, dp_i_1 = INT_MIN;
    for (int i = 0; i < n; i++) {
        int temp = dp_i_0;
        dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
        dp_i_1 = max(dp_i_1, temp - prices[i]);
    }
    return dp_i_0;
}

