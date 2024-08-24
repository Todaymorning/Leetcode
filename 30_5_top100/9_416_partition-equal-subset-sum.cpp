// https://leetcode.cn/problems/partition-equal-subset-sum/?envType=study-plan-v2&envId=top-100-liked416. 分割等和子集
// 416. 分割等和子集
// labuladong 题解思路
// 中等
// 给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

// 示例 1：
// 输入：nums = [1,5,11,5]
// 输出：true
// 解释：数组可以分割成 [1, 5, 5] 和 [11] 。

// 示例 2：
// 输入：nums = [1,2,3,5]
// 输出：false
// 解释：数组不能分割成两个元素和相等的子集。

// 提示：
// 1 <= nums.length <= 200
// 1 <= nums[i] <= 100

#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    bool canPartition(vector<int>& nums) {

    }
};


// 2024年8月1日
// 21:06--21:25
// 0 1 背包
// 给一个可装载重量为 sum / 2 的背包和 N 个物品，每个物品的重量为 nums[i]。
// 现在让你装物品，是否存在一种装法，能够恰好将背包装满？
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int size = nums.size();
        int sum = 0;
        for(int i=0; i<size; i++) {
            sum += nums[i];
        }
        if(sum % 2 == 1) return false;
        sum /= 2;
        // dp[i][j]，前 i 件物体能不能装满大小为j的背包
        vector<vector<int>> dp(size+1, vector<int>(sum + 1, false));
        // for(int j=1; j<sum+1; j++) {
        //     dp[0][j] = false;    // 没有物体，填不满背包
        // }
        for(int i=0; i<size+1; i++) {
            dp[i][0] = true;    // 背包空间为零，肯定可以填满
        }
        for(int i=1; i<size+1; i++) {   // 先取一个物体，往背包里放，背包空间不断变大
            for(int j=1; j<sum+1; j++) {    // 即先遍历物体再遍历背包空间
                if(nums[i-1] > j) { // *** 背包空间放不下
                    dp[i][j] = dp[i-1][j];  // 看前 i - 1 个物体，即上一行能不能
                }
                else {
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]];  // *** 上一行
                }
            }
        }
        return dp[size][sum];
    }
};
