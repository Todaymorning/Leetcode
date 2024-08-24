// https://leetcode.cn/problems/product-of-array-except-self/description/?envType=study-plan-v2&envId=top-100-liked
// 238. 除自身以外数组的乘积
// 中等
// 相关标签
// 相关企业
// 提示
// 给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积 。
// 题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。
// 请 不要使用除法，且在 O(n) 时间复杂度内完成此题。

// 示例 1:
// 输入: nums = [1,2,3,4]
// 输出: [24,12,8,6]

// 示例 2:
// 输入: nums = [-1,1,0,-3,3]
// 输出: [0,0,9,0,0]

// 提示：
// 2 <= nums.length <= 105
// -30 <= nums[i] <= 30
// 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内

// 进阶：你可以在 O(1) 的额外空间复杂度内完成这个题目吗？（ 出于对空间复杂度分析的目的，输出数组 不被视为 额外空间。）


#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {

    }
};



// left[i-1] * right[i+1]
// 这道题和 前缀和数组技巧 有些类似，前缀和数组中两个元素之差是子数组元素之和，
// 那么如果构造「前缀积」数组，两个元素相除就是子数组元素之和。
// 所以我们构造一个 prefix 数组记录「前缀积」，再用一个 suffix 记录「后缀积」，
// 根据前缀和后缀积就能计算除了当前元素之外其他元素的积。
class Solution_L1_M1 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        // [0..i]的乘积
        vector<int> left(nums.size());
        left[0] = nums[0];
        for(int i=1; i<nums.size(); i++) {
            left[i] = left[i-1] * nums[i];
        }
        // [i, n-1]的乘积
        vector<int> right(nums.size());
        right.back() = nums.back();
        for(int i=nums.size() - 2; i>=0; i--) {
            right[i] = right[i+1] * nums[i];
        }
        vector<int> res(nums.size());
        res[0] = right[1];
        res.back() = left[nums.size() - 2];
        for(int i=1; i<nums.size() - 1; i++) {
            res[i] = left[i-1] * right[i+1];
        }
        return res;
    }
};


class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res(nums.size());
        // 使用res[i]暂存 [0..i-1]的乘积，即i左侧所有元素乘积
        // 因为索引为 '0' 的元素左侧没有元素， 所以 res[0] = 1
        res[0] = 1;
        for(int i=1; i<nums.size(); i++) {
            res[i] = res[i-1] * nums[i-1];
        }
        // 使用 right 暂存 [i+1, n],即 i 右侧所有元素乘积
        // 刚开始右边没有元素, right = 1;
        int right = 1;
        for(int i=nums.size() - 1; i>=0; i--) {
            // 对于索引 i，左边的乘积为 res[i]，右边的乘积为 right
            res[i] *= right;
            // 需要包含右边所有的乘积，所以计算下一个结果时需要将当前值乘到 R 上
            right *= nums[i];
        }
        return res;
    }
};