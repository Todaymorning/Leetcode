// https://leetcode.cn/problems/two-sum/
// 1.两数之和
#include<iostream>
#include<vector>
#include<unordered_map>
using std::vector;
using std::unordered_map;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
    }
};


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 22:20--22:26
        unordered_map<int, int> mp;
        for(int i=0; i<nums.size(); i++) {
            if(mp.find(target - nums[i]) != mp.end()) {
                return {mp[target - nums[i]], i};
            }
            mp[nums[i]] = i;
        }
        return {};
    }
};