// https://leetcode.cn/problems/maximum-subarray
// 53.最大子数组之和

#include<iostream>
#include<vector>
using std::vector;
using std::max;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {

    }
};

// 11:22--11:25
// 贪心
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int result = INT_MIN;
        int sum = 0;
        for(int i=0; i<nums.size(); i++) {
            sum += nums[i];
            result = result > sum ? result : sum;
            if(sum <= 0) sum = 0;
        }
        return result;
    }
};

// 11:25--11:36
// 动态规划
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        int result = nums[0];
        for(int i=1; i<nums.size(); i++) {
            dp[i] = max(dp[i-1] + nums[i], nums[i]);
            result = max(result, dp[i]);
        }
        return result;
    }
};