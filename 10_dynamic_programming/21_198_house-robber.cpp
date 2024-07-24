// 198. 打家劫舍
// labuladong 题解思路
// 中等
// 你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，
// 如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
// 给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

// 示例 1：
// 输入：[1,2,3,1]
// 输出：4
// 解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
//      偷窃到的最高金额 = 1 + 3 = 4 。

// 示例 2：
// 输入：[2,7,9,3,1]
// 输出：12
// 解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
//      偷窃到的最高金额 = 2 + 9 + 1 = 12 。

// 提示：
// 1 <= nums.length <= 100
// 0 <= nums[i] <= 400


#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int rob(vector<int>& nums) {

    }
};


// 9:39--9:48(读题找思路)--9:59(错误)
// 输入
// nums =
// [1,2,3,1]
// 输出
// 3
// 预期结果
// 4
class Solution {
public:
    int rob(vector<int>& nums) {
        // dp[i]：从[0,i]中盗窃第 i 间房子时能盗窃到的最大值
        vector<int> dp(nums.begin(), nums.end());
        for(int i=2; i<nums.size(); i++) {
            for(int j=0; j<i-1; j++) {
                dp[i] = std::max(dp[i], dp[j] + nums[i]);
            }
        }
        // ***
        // 找到 dp 中的最大值 
        int result=0;
        for(int n:dp) {
            if(n > result) result = n;
        }
        return result;
    }
};


class Solution {
public:
    int rob(vector<int>& nums) {
        // dp[i]：从[0,i]中盗窃第 i 间房子时能盗窃到的最大值
        vector<int> dp(nums.begin(), nums.end());
        int result=0;
        for(int i=0; i<nums.size(); i++) {
            for(int j=0; j<i-1; j++) {
                dp[i] = std::max(dp[i], dp[j] + nums[i]);
            }
            if(dp[i] > result) result = dp[i];
        }
        return result;
    }
};


// dp [i]：考虑下标 i（包括 i）以内的房屋，最多可以偷窃的金额为 dp [i]
// 时间复杂度: O (n)
// 空间复杂度: O (n)
class Solution_D1 {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            dp[i] = std::max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[nums.size() - 1];
    }
};


// 10:16
// 看完 L1 思路
class Solution_L1 {
    vector<int> memo;
    int dp(vector<int>& nums, int start) {
        if(start >= nums.size()) return 0;
        if(memo[start] != -1) return memo[start];
        memo[start] = std::max(dp(nums, start + 1), nums[start] + dp(nums, start + 2));
        return memo[start];
    }
public:
    int rob(vector<int>& nums) {
        memo = vector<int>(nums.size(), -1);    // nums[i] 可能等于 0
        return dp(nums, 0);
    }
};