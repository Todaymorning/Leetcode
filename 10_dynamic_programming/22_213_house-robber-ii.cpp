// 213. 打家劫舍 II
// labuladong 题解思路
// 中等
// 你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。
// 同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。
// 给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，今晚能够偷窃到的最高金额。

// 示例 1：
// 输入：nums = [2,3,2]
// 输出：3
// 解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。

// 示例 2：
// 输入：nums = [1,2,3,1]
// 输出：4
// 解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
//      偷窃到的最高金额 = 1 + 3 = 4 。

// 示例 3：
// 输入：nums = [1,2,3]
// 输出：3

// 提示：
// 1 <= nums.length <= 100
// 0 <= nums[i] <= 1000


#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int rob(vector<int>& nums) {

    }
};

// 10:46--10:48(读题找思路)--11:01(不会)--11:31(看 D1 的思路写)
// 对于一个数组，成环的话主要有如下三种情况：
// 情况一：考虑不包含首尾元素
// 情况二：考虑包含首元素，不包含尾元素
// 情况三：考虑包含尾元素，不包含首元素
// 输入
// nums =
// [1]
// 输出
// 0
// 预期结果
// 1
// 输入
// nums =
// [1,1]
// 输出
// 0
// 预期结果
// 1
// 输入
// nums =
// [1,3,1,3,100]
// 输出
// 101
// 预期结果
// 103
// 时间复杂度: O (n)
// 空间复杂度: O (n)
class Solution {
    // [start, end]
    int robRange(vector<int>& nums, int start, int end) {
        int len = end - start + 1;
        if(len <= 0) return 0;
        if(len == 1) return nums[start];
        vector<int> dp(len, 0);
        dp[0] = nums[start];
        dp[1] = std::max(dp[0], nums[start + 1]);   // ***
        for(int i=2; i<len; i++) {
            dp[i] = std::max(dp[i-1], dp[i-2] + nums[start + i]);
        }
        return dp.back();
    }
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];    // ***
        int left = robRange(nums, 0, nums.size() - 2);
        int right = robRange(nums, 1, nums.size() - 1);
        return std::max(left, right);
    }
};



// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution_L1_copy {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];

        vector<int> memo1(n, -1);
        vector<int> memo2(n, -1);
        // 两次调用使用两个不同的备忘录
        return std::max(
                dp(nums, 0, n - 2, memo1),
                dp(nums, 1, n - 1, memo2)
        );
    }

    // 定义：计算闭区间 [start,end] 的最优结果
    int dp(vector<int>& nums, int start, int end, vector<int>& memo) {
        if (start > end) {
            return 0;
        }

        if (memo[start] != -1) {
            return memo[start];
        }
        // 状态转移方程
        int res = std::max(
                dp(nums, start + 2, end, memo) + nums[start],
                dp(nums, start + 1, end, memo)
        );

        memo[start] = res;
        return res;
    }
};