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


// 动态规划
// 见：动态规划第 25 题


