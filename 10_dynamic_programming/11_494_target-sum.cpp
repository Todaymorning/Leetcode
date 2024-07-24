// 494. 目标和
// labuladong 题解思路
// 中等
// 给你一个非负整数数组 nums 和一个整数 target 。
// 向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：
// 例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
// 返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。

// 示例 1：
// 输入：nums = [1,1,1,1,1], target = 3
// 输出：5
// 解释：一共有 5 种方法让最终目标和为 3 。
// -1 + 1 + 1 + 1 + 1 = 3
// +1 - 1 + 1 + 1 + 1 = 3
// +1 + 1 - 1 + 1 + 1 = 3
// +1 + 1 + 1 - 1 + 1 = 3
// +1 + 1 + 1 + 1 - 1 = 3

// 示例 2：
// 输入：nums = [1], target = 1
// 输出：1

// 提示：
// 1 <= nums.length <= 20
// 0 <= nums[i] <= 1000
// 0 <= sum(nums[i]) <= 1000
// -1000 <= target <= 1000


#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
using std::string;
using std::unordered_map;
using std::vector;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {

    }
};


// 9:43--9:50(读题找思路，不会)--9:54(看下面的思路)
// 本题要如何使表达式结果为 target，
// 既然为 target，那么就一定有 left 组合 - right 组合 = target。
// left + right = sum，而 sum 是固定的。right = sum - left
// 公式来了， left - (sum - left) = target 推导出 left = (target + sum)/2 。
// target 是固定的，sum 是固定的，left 就可以求出来。
// 此时问题就是在集合 nums 中找出和为 left 的组合。
// 此时问题可以用回溯解决
// 9:58--10:08--10:14(改错，未考虑没有方案)
// 肯定会超时
class Solution_M1 {
    int track = 0;
    int result = 0;
    void backtracking(vector<int>& nums, int start, int left) {
        if(track >= left || start == nums.size()) {
            if(track == left) result++;
            return;
        }
        for(int i=start; i<nums.size(); i++) {
            track += nums[i];
            backtracking(nums, i+1, left);
            track -= nums[i];
        }
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int left = 0;
        for(int i:nums) left += i;
        // if(target > left) return 0;  // 没有方案                ***
        if((left + target) % 2 == 1) return 0; // 没有方案      ***
        left = (left + target) / 2;
        backtracking(nums, 0, left);
        return result;
    }
};


// 11:17--11:50(改错)
// 其实，这个问题可以转化为一个子集划分问题，而子集划分问题又是一个典型的背包问题。
// 可以推出 sum(A) = (target + sum(nums)) / 2，也就是把原问题转化成：nums 中存在几个子集 A，使得 A 中元素的和为 (target + sum(nums)) / 2
// 变成背包问题的标准形式：
// 有一个背包，容量为 sum，现在给你 N 个物品，第 i 个物品的重量为 nums[i - 1]（注意 1 <= i <= N），每个物品只有一个，请问你有几种不同的方法能够恰好装满这个背包？
// 1. 确定 dp 数组以及下标的含义
// dp [j] 表示：填满 j（包括 j）这么大容积的包，有 dp [j] 种方法
// 时间复杂度：O (n × m)，n 为正数个数，m 为背包容量
// 空间复杂度：O (m)，m 为背包容量
class Solution_D2_L3_M2 {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for(int i:nums) sum += i;
        if(target > sum || target < -sum || (sum + target) % 2) return 0;

        int bag = (sum + target) / 2;   // 背包容量
        vector<int> dp(bag + 1, 0);
        dp[0] = 1;  // ***
        for(int i=0; i<nums.size(); i++) {
            for(int j=bag; j>=nums[i]; j--) {
                dp[j] = dp[j] + dp[j-nums[i]];  // 不放 nums[i]的种类 + 放 nums[i]种类
            }
        }
        return dp.back();
    }
};






// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码还未经过力扣测试，仅供参考，如有疑惑，可以参照我写的 java 代码对比查看。
// 回溯：在每个数字前加上一次 + 加上一次 -，计算和
// 时间复杂度 O(2^N)
class Solution_L1_copy {
    int result = 0;
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        if (nums.size() == 0) return 0;
        backtrack(nums, 0, target);
        return result;
    }
    void backtrack(vector<int>& nums, int i, int remain) {
        // base case
        if (i == nums.size()) {
            if (remain == 0) {
                // 说明恰好凑出 target
                result++;
            }
            return;
        }
        // 给 nums[i] 选择 - 号
        remain += nums[i];
        // 穷举 nums[i + 1]
        backtrack(nums, i + 1, remain);
        // 撤销选择
        remain -= nums[i]; 
        
        // 给 nums[i] 选择 + 号
        remain -= nums[i];
        // 穷举 nums[i + 1]
        backtrack(nums, i + 1, remain);
        // 撤销选择
        remain += nums[i];
    }
};

// 使用备忘录优化回溯
// 将 nums[i-1]
class Solution_L2_copy {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        if (nums.size() == 0) return 0;
        return dp(nums, 0, target);
    }

private:
    // 备忘录
    unordered_map<string, int> memo;
    int dp(vector<int>& nums, int i, int remain) {
        // base case
        if (i == nums.size()) {
            if (remain == 0) return 1;
            return 0;
        }
        // 把它俩转成字符串才能作为哈希表的键
        string key = std::to_string(i) + "," + std::to_string(remain);
        // 避免重复计算
        if (memo.count(key)) {
            return memo[key];
        }
        // 还是穷举
        int result = dp(nums, i + 1, remain - nums[i]) + dp(nums, i + 1, remain + nums[i]);
        // 记入备忘录
        memo[key] = result;
        return result;
    }
};


// 其实，这个问题可以转化为一个子集划分问题，而子集划分问题又是一个典型的背包问题。
// 可以推出 sum(A) = (target + sum(nums)) / 2，也就是把原问题转化成：nums 中存在几个子集 A，使得 A 中元素的和为 (target + sum(nums)) / 2
// 变成背包问题的标准形式：
// 有一个背包，容量为 sum，现在给你 N 个物品，第 i 个物品的重量为 nums[i - 1]（注意 1 <= i <= N），每个物品只有一个，请问你有几种不同的方法能够恰好装满这个背包？
class Solution_L3_copy {
    int subsets(vector<int>& nums, int sum) {
        vector<vector<int>> dp(nums.size() + 1, vector<int>(sum + 1, 0));
        dp[0][0] = 1;   // nums[i] 可以为 0
        for(int i=1; i<=nums.size(); i++) {
            for(int j=0; j<=sum; j++) {
                if(j >= nums[i-1]) {
                    // 两种选择的结果之和
                    dp[i][j] = dp[i-1][j] + dp[i-1][j - nums[i-1]];
                }
                else {
                    // 背包的空间不足，只能选择不装物品 i
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[nums.size()][sum];
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for(int i:nums) sum += i;
        if(sum < abs(target) || (sum + target) % 2 == 1) return 0;
        return subsets(nums, (sum + target) / 2);
    }
};


class Solution_L3_copy {
    int subsets(vector<int>& nums, int sum) {
        int n = nums.size();
        vector<int> dp(sum + 1);
        // base case
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            // j 要从后往前遍历
            for (int j = sum; j >= 0; j--) {
                // 状态转移方程
                if (j >= nums[i-1]) {
                    dp[j] = dp[j] + dp[j-nums[i-1]];
                } else {
                    dp[j] = dp[j];
                }
            }
        }
        return dp[sum];
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for(int i:nums) sum += i;
        if(sum < abs(target) || (sum + target) % 2 == 1) return 0;
        return subsets(nums, (sum + target) / 2);
    }
};