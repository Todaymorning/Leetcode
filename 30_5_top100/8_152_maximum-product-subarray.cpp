// https://leetcode.cn/problems/maximum-product-subarray/?envType=study-plan-v2&envId=top-100-liked
// 152. 乘积最大子数组
// 尝试过
// 中等
// 相关标签
// 相关企业
// 给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续
// 子数组
// （该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

// 测试用例的答案是一个 32-位 整数。

 

// 示例 1:

// 输入: nums = [2,3,-2,4]
// 输出: 6
// 解释: 子数组 [2,3] 有最大乘积 6。
// 示例 2:

// 输入: nums = [-2,0,-1]
// 输出: 0
// 解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。
 

// 提示:

// 1 <= nums.length <= 2 * 104
// -10 <= nums[i] <= 10
// nums 的任何前缀或后缀的乘积都 保证 是一个 32-位 整数



#include<iostream>
#include<vector>
using std::vector;




// 执行出错
// 190 / 191 个通过的测试用例
// Line 13: Char 65: runtime error: signed integer overflow: 1000000000 * -10 cannot be represented in type 'value_type' (aka 'int') (solution.cpp)
// SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior solution.cpp:13:65
// 最后执行的输入
// 添加到测试用例
// nums =
// [0,10,10,10,10,10,10,10,10,10,-10,10,10,10,10,10,10,10,10,10,0]
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // 2024年8月5日
        // 21:32--21:45
        // dp[i][1] [0, i]中包含i的最大乘积
        // dp[i][0] [0, i]中包含i的最小乘积
        vector<vector<int>> dp(nums.size() + 1, vector<int>(2, 0));
        // base case
        dp[0][0] = dp[0][1] = 1;
        int res = INT_MIN;
        for(int i=1; i<=nums.size(); i++) {
            dp[i][0] = std::min(dp[i-1][0]*nums[i-1], dp[i-1][1]*nums[i-1]);
            dp[i][0] = std::min(dp[i][0], nums[i-1]);
            dp[i][1] = std::max(dp[i-1][0]*nums[i-1], dp[i-1][1]*nums[i-1]);
            dp[i][1] = std::max(dp[i][1], nums[i-1]);
            if(res < dp[i][1]) res = dp[i][1];
        }
        return res;
    }
};





// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码不保证正确性，仅供参考。如有疑惑，可以参照我写的 java 代码对比查看。

class Solution_L1_copy {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();

        // 定义：以 nums[i] 结尾的子数组，乘积最小为 dp1[i]
        vector<int> dp1(n);
        // 定义：以 nums[i] 结尾的子数组，乘积最大为 dp2[i]
        vector<int> dp2(n);

        // base case
        dp1[0] = nums[0];
        dp2[0] = nums[0];

        // 状态转移方程
        for (int i = 1; i < n; i++) {
            dp1[i] = std::min(std::min(dp1[i - 1] * nums[i], dp2[i - 1] * nums[i]), nums[i]);
            dp2[i] = std::max(std::max(dp1[i - 1] * nums[i], dp2[i - 1] * nums[i]), nums[i]);
        }

        // 遍历所有子数组的最大乘积，求最大值
        int res = INT_MIN;
        for (int i = 0; i < n; i++) {
            res = std::max(res, dp2[i]);
        }

        return res;
    }
};