// D:\Learning\Leetcode\Cpp\3_hashtable\7_15_ThreeSum.cpp
// https://leetcode.cn/problems/3sum/
#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
using std::sort;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        
    }
};

// 三数之和
// 10:54
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end()); // 默认升序排列
        vector<vector<int>> result;
        // 首尾都不满足条件
        if(nums[0] > 0 || nums.back() < 0) return result;
        for(int i=0; i<nums.size()-2; i++) {
            // i, left, right
            // nums[i] <= nums[left] <= nums[right]
            // nums[i] <= 0 nums[right] >= 0

            // 第一个数大于 0 不用接着往下找了
            if(nums[i] > 0) break;   // nums[i] <= 0
            if(i > 0 && nums[i-1] == nums[i]) continue; // nums[i] 去重
            // 从两边往中间找
            int left = i + 1;
            int right = nums.size() - 1;
            while(left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if(sum > 0) {
                    right--;
                }
                else if(sum < 0) {
                    left++;
                }
                else {
                    result.push_back({nums[i], nums[left], nums[right]});
                    // left right 去重
                    while(left < right && nums[left] == nums[left+1]) left++;
                    while(left < right && nums[right] == nums[right-1]) right--;
                    // 找到答案时，双指针同时收缩
                    left++;
                    right--;
                }
            }
        }
        return result;
    }
};