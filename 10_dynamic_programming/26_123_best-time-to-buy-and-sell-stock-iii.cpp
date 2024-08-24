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
using std::max;

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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 动态规划
// 11:55--12:17
// 只能买卖一次、可以无限次买卖、有限次买卖
// 没有操作 （其实我们也可以不设置这个状态）
// 第 0 天
// 第一次持有股票： -prices[0]
// 第一次不持有股票: -prices[0] + prices[0]
// 第二次持有股票:  -prices[0] + prices[0] - prices[0]
// 第二次不持有股票: -prices[0] + prices[0] - prices[0] + prices[0]
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if(len < 2) return 0;
        vector<vector<int>> dp(len, vector<int>(4, 0));
        dp[0] = {-prices[0], 0, -prices[0], 0};     // ***
        for(int i=1; i<len; i++) {
            dp[i][0] = std::max(dp[i-1][0], - prices[i]);               // 继续持有、第一次买入
            dp[i][1] = std::max(dp[i-1][1], dp[i-1][0] + prices[i]);    // 继续第一次不持有、第一次持有后卖出
            dp[i][2] = std::max(dp[i-1][2], dp[i-1][1] - prices[i]);    // 继续第二次持有、从第一次不持有买入
            dp[i][3] = std::max(dp[i-1][3], dp[i-1][2] + prices[i]);    // 继续第二次不持有、第二次持有后卖出
        }
        return dp.back().back();
    }
};


// 时间复杂度：O (n)
// 空间复杂度：O (n × 5)
class Solution_D1_copy {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        vector<vector<int>> dp(prices.size(), vector<int>(5, 0));
        dp[0][1] = -prices[0];
        dp[0][3] = -prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
            dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);
            dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);
            dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + prices[i]);
        }
        return dp[prices.size() - 1][4];
    }
};

// 时间复杂度：O (n)
// 空间复杂度：O (1)
// 大家会发现 dp [2] 利用的是当天的 dp [1]。 但结果也是对的。
// 我来简单解释一下：
// dp [1] = max (dp [1], dp [0] - prices [i]);
//  如果 dp [1] 取 dp [1]，即保持买入股票的状态，那么 dp [2] = max (dp [2], dp [1] + prices [i]); 中 dp [1] + prices [i] 就是今天卖出。
// 如果 dp [1] 取 dp [0] - prices [i]，今天买入股票，那么 dp [2] = max (dp [2], dp [1] + prices [i]); 中的 dp [1] + prices [i] 
// 相当于是今天再卖出股票，一买一卖收益为 0，对所得现金没有影响。相当于今天买入股票又卖出股票，等于没有操作，保持昨天卖出股票的状态了。
// 这种写法看上去简单，其实思路很绕，不建议大家这么写，这么思考，很容易把自己绕进去！
class Solution_D2_copy {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        vector<int> dp(5, 0);
        dp[1] = -prices[0];
        dp[3] = -prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[1] = max(dp[1], dp[0] - prices[i]);
            dp[2] = max(dp[2], dp[1] + prices[i]);
            dp[3] = max(dp[3], dp[2] - prices[i]);
            dp[4] = max(dp[4], dp[3] + prices[i]);
        }
        return dp[4];
    }
};


// 17:20--18:02
// k = 2;
// dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]); // 继续不持有，持有的卖出
// dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]);// 继续持有，减少一次交易量买入
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(size < 2) return 0;
        int max_k = 2;
        vector<vector<vector<int>>> dp(size, vector<vector<int>>(max_k + 1, vector<int>(2, 0)));    // k + 1，防止 [k-1] < 0
        for(int i=0; i<size; i++) {
            for(int k=1; k<=max_k; k++) {   // k = 1，这里的k正序倒序都可以，因为最外层循环是 i，dp[i]只依赖dp[i-1]
                if(i == 0 ) {   // *** 每个k都需要赋值
                    dp[i][k][0] = 0;
                    dp[i][k][1] = -prices[i];
                }
                else {
                    dp[i][k][0] = std::max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
                    dp[i][k][1] = std::max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]); // k-1 = 0 时默认为 0 ***
                    // dp[i][k][1] = std::max(dp[i-1][k][0], dp[i-1][k-1][0] - prices[i]); 这个错误找半天
                }
            }
        }
        return dp.back().back()[0];
    }
};