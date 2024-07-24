// 674. 最长连续递增序列
// 简单
// 给定一个未经排序的整数数组，找到最长且 连续递增的子序列，并返回该序列的长度。
// 连续递增的子序列 可以由两个下标 l 和 r（l < r）确定，如果对于每个 l <= i < r，都有 nums[i] < nums[i + 1] ，
// 那么子序列 [nums[l], nums[l + 1], ..., nums[r - 1], nums[r]] 就是连续递增子序列。

// 示例 1：
// 输入：nums = [1,3,5,4,7]
// 输出：3
// 解释：最长连续递增序列是 [1,3,5], 长度为3。
// 尽管 [1,3,5,7] 也是升序的子序列, 但它不是连续的，因为 5 和 7 在原数组里被 4 隔开。 

// 示例 2：
// 输入：nums = [2,2,2,2,2]
// 输出：1
// 解释：最长连续递增序列是 [2], 长度为1。

// 提示：
// 1 <= nums.length <= 10^4
// -10^9 <= nums[i] <= 10^9


#include<iostream>
#include<vector>
using std::vector;
using std::max;

class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {

    }
};


// 16:24--16:40(M1,M2,M3)
// 试试贪心
// 输入
// nums =
// [1,3,5,7]
// 输出
// 0
// 预期结果
// 4
#if 0
class Solution_M1 {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int left = 0;
        int right = 0;
        int result = 0;
        for(int i=1; i<nums.size(); i++) {
            if(nums[i] > nums[right]) right = i;    // 没有考虑最后一个数仍在上升时的情况
            else {
                // 统计结果重新开始
                if(result < right - left + 1) result = right - left + 1;
                right = i;
                left = i;
            }
        }
        return result;
    }
};
#endif

#if 0
// 输入
// nums =
// [2,2,2,2,2]
// 输出
// 0
// 预期结果
// 1
class Solution_M2 {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int left = 0;
        int right = 0;
        int result = 0;
        for(int i=1; i<nums.size(); i++) {
            if(nums[right] >= nums[i]) {
                left = i;
                right = i;
                continue;
            }
            right++;
            if(result < right - left + 1) result = right - left + 1;
        }
        return result;  // 没有考虑结果只有一个数的情况
    }
};
#endif

// 贪心
class Solution_M3 {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if(nums.size() < 2) return nums.size(); // ***
        int left = 0;
        int right = 0;
        int result = 1; // 从 1 开始            // ***
        for(int i=1; i<nums.size(); i++) {
            if(nums[right] >= nums[i]) {
                left = i;
                right = i;
                continue;
            }
            right++;
            if(result < right - left + 1) result = right - left + 1;
        }
        return result;
    }
};

// 16:45--16:48
// 动态规划
// dp[i]:以nums[i]为结尾的最长递增子序列的长度
class Solution_M4 {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int size = nums.size();
        if(size < 2) return size;
        vector<int> dp(size, 1);
        int result = 0;
        for(int i=1; i<size; i++) {
            if(nums[i] > nums[i-1]) {
                dp[i] = dp[i-1] + 1;
            }
            if(dp[i] > result) result = dp[i];
        }
        return result;
    }
};


// D2 贪心
// 用count代替 left right，count从1开始
class Solution_D2_copy {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        int result = 1; // 连续子序列最少也是1
        int count = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) { // 连续记录
                count++;
            } else { // 不连续，count从头开始
                count = 1;
            }
            if (count > result) result = count;
        }
        return result;
    }
};