// 123. 买卖股票的最佳时机 III
// 困难
// 给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
// 设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。
// 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

// 示例 1:
// 输入：prices = [3,3,5,0,0,3,1,4]
// 输出：6
// 解释：在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
//      随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。

// 示例 2：
// 输入：prices = [1,2,3,4,5]
// 输出：4
// 解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。   
//      注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。   
//      因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。

// 示例 3：
// 输入：prices = [7,6,4,3,1] 
// 输出：0 
// 解释：在这个情况下, 没有交易完成, 所以最大利润为 0。

// 示例 4：
// 输入：prices = [1]
// 输出：0

// 提示：
// 1 <= prices.length <= 10^5
// 0 <= prices[i] <= 10^5


#include<iostream>
#include<vector>
#include<algorithm>
using std::vector;
using std::sort;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        return 0;
    }
};


// 11:05--11:55--12:11(错误)
// prices = [6, 1, 3, 2, 4, 7] 答案是 7 下面的代码输出 6
// [-5, 2, -1, 5] 子序列连续和：2-1 = 1 > 0 会继续往后加，这种算法适合只交易一次，有时候不太适合交易两次
#if 0
class Solution_M1 {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(size < 2) return 0;
        // 找到波峰波谷
        vector<int> results;
        size--;
        int prediff = 0;
        int curdiff = 0;
        for(int i=0; i<size; i++) {
            curdiff = prices[i+1] - prices[i];
            if((prediff <= 0 && curdiff > 0) || (prediff >= 0 && curdiff < 0)) {
                results.push_back(prices[i]);
                prediff = curdiff;
            }
        }
        results.push_back(prices.back());
        // 找到数组连续和的前两个最大值（不使用重复元素）
        int sum = 0;
        vector<int> max(3, 0);
        size = results.size() - 1;
        for(int i=0; i<size; i++) {
            sum += results[i+1] - results[i];
            if(sum > max[0]) {
                max[0] = sum; // 找到每个阶段的最大值
            }
            if(sum <= 0) {  // 即将开启下一阶段
                sum = 0;
                sort(max.begin(), max.end());   // 升序排列
            }
        }
        sort(max.begin(), max.end());
        return max[1] + max[2];
    }
};


int main() {
    vector<int> prices = { 6,1,3,2,4,7 };
    Solution_M1 s;
    s.maxProfit(prices);
    return 0;
}
#endif



// 动态规划
// 见动态规划 26