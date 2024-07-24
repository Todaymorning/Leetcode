// 1049. 最后一块石头的重量 II
// 提示
// 中等
// 有一堆石头，用整数数组 stones 表示。其中 stones[i] 表示第 i 块石头的重量。
// 每一回合，从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <= y。那么粉碎的可能结果如下：
// 如果 x == y，那么两块石头都会被完全粉碎；
// 如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。
// 最后，最多只会剩下一块 石头。返回此石头 最小的可能重量 。如果没有石头剩下，就返回 0。

// 示例 1：
// 输入：stones = [2,7,4,1,8,1]
// 输出：1
// 解释：
// 组合 2 和 4，得到 2，所以数组转化为 [2,7,1,8,1]，
// 组合 7 和 8，得到 1，所以数组转化为 [2,1,1,1]，
// 组合 2 和 1，得到 1，所以数组转化为 [1,1,1]，
// 组合 1 和 1，得到 0，所以数组转化为 [1]，这就是最优值。

// 示例 2：
// 输入：stones = [31,26,33,21,40]
// 输出：5

// 提示：
// 1 <= stones.length <= 30
// 1 <= stones[i] <= 100

#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {

    }
};


// 12:01--12:11(读题找思路)--12:18
// 分为两组，最后的结果是两组相减
// dp[j] = dp[j] || dp[j - stones[i]]：
// 访问 stones[i] 因此 i=[0, stones.size())
// 当 j == stones[j]时，dp[j]应该为true，而上一行的dp[j]可能为false，为保证dp[j]为true，dp[j-stones[i]] = dp[0] = true;
//
// 一维数组，只需要初始化一个，列从后往前遍历
class Solution_M1 {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = 0;
        for(int n:stones) sum += n;
        int target = sum / 2;
        int m = stones.size();
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for(int i=0; i<m; i++) {
            for(int j=target; j>=stones[i]; j--) {
                dp[j] = dp[j] || dp[j - stones[i]];
            }
        }
        for(int j=target; j>=0; j--) {
            if(dp[j] != false) return (sum - j*2);  // j*2 而不是 dp[j]*2       ***
        }
        return stones[0];   // 只有一个元素
    }
};


// 12:25--12:34(错误)--12：37
// 二维数组，有个不加 1
// 初始化一行一列
class Solution_M2 {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = 0;
        for(int n:stones) sum += n;
        int target = sum / 2;
        int m = stones.size();
        vector<vector<bool>> dp(m, vector<bool>(target + 1, false));

        // 初始化
        for(int i=0; i<m; i++) dp[i][0] = true;
        if(stones[0] <= target) dp[0][stones[0]] = true;    // ***

        for(int i=1; i<m; i++) {
            for(int j=1; j<=target; j++) {
                if(j < stones[i]) {
                    dp[i][j] = dp[i-1][j];
                }
                else {
                    dp[i][j] = dp[i-1][j] || dp[i-1][j - stones[i]];
                }
            }
        }
        for(int j=target; j>=1; j--) {
            if(dp[m-1][j] != false) return (sum - j * 2);
        }
        return stones[0];
    }
};

// 二维数组，两个都加 1
// 初始化一行一列
class Solution_M3 {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = 0;
        for(int n:stones) sum += n;
        int target = sum / 2;
        int m = stones.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(target + 1, false));

        // 初始化
        for(int i=0; i<=m; i++) dp[i][0] = true;

        for(int i=1; i<m; i++) {
            for(int j=1; j<=target; j++) {
                if(j < stones[i-1]) {
                    dp[i][j] = dp[i-1][j];
                }
                else {
                    dp[i][j] = dp[i-1][j] || dp[i-1][j - stones[i-1]];
                }
            }
        }
        for(int j=target; j>=1; j--) {
            if(dp[m][j] != false) return (sum - j * 2);
        }
        return stones[0];
    }
};