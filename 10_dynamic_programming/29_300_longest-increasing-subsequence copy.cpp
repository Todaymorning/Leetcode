// https://leetcode.cn/problems/longest-increasing-subsequence
// 300. 最长递增子序列
// labuladong 题解思路
// 中等
// 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
// 子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。

// 示例 1：
// 输入：nums = [10,9,2,5,3,7,101,18]
// 输出：4
// 解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。

// 示例 2：
// 输入：nums = [0,1,0,3,2,3]
// 输出：4

// 示例 3：
// 输入：nums = [7,7,7,7,7,7,7]
// 输出：1

// 提示：
// 1 <= nums.length <= 2500
// -10^4 <= nums[i] <= 10^4


#include<iostream>
#include<vector>
using std::vector;
using std::max;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {

    }
};


// 15:54--16:02(不会)--16:17(看 D1 中 dp[i] 定义后写出，)
// 试试带 memo 的回溯，做不了，可能后面最小的数比前面的数大
// dp [i] 的定义
// dp [i] 表示 i 之前包括 i 的以 nums [i] 结尾的最长递增子序列的长度
class Solution_D1_M1 {
public:
    int lengthOfLIS(vector<int>& nums) {
        int size = nums.size();
        if(size < 2) return nums.size();
        vector<int> dp(size, 1);
        for(int i=1; i<size; i++) {
            for(int j=i-1; j>=0; j--) {
                if(nums[j] < nums[i] && dp[j] + 1 > dp[i]) {    // ***
                    dp[i] = dp[j] + 1;  // ***
                }
            }
        }
        int result = 0;
        for(int n:dp) {     // 可以将这一步放在循环中比较
            if(n > result) result = n;
        }
        return result;
    }
};



// ***************************************************************************************************************************
// 时间复杂度: O (n^2)
// 空间复杂度: O (n)
class Solution_D1_copy {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();
        vector<int> dp(nums.size(), 1);
        int result = 0;
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);
            }
            if (dp[i] > result) result = dp[i]; // 取长的子序列
        }
        return result;
    }
};





// 2024年5月20日
// 21:56--22:13
// 动态规划
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        for(int j=1; j<nums.size(); j++) {
            for(int i=0; i<j; i++) {
                if(nums[i] < nums[j]) {
                    dp[j] = std::max(dp[j], dp[i] + 1);
                }
            }
        }
        int res = 0;
        for(auto& n : dp) {
            if(n > res) res = n;
        }
        return res;
    }
};




